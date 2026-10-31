"""Write a comment stub for every TSE function not decompiled yet, where the function sat in TSE's file, and a gap
comment for every run of blank lines that holds code below it at its original line numbers.

    python3 -I -B tools/round/stubs.py            # rewrite every stub and gap (make -C src stubs; splat-scan and splat-match run it)
    python3 -I -B tools/round/stubs.py --check    # exit 1 naming each stub or gap missing, extra, stale or out of place (CI)
    python3 -I -B tools/round/stubs.py --strip FILE...   # turn a file's stubs and gaps back into blank lines, before editing it
    python3 -I -B tools/round/stubs.py --report   # what --check checks, and the counts, without writing

A stub is two comment lines, inside a run that `// <stubs>` and `// </stubs>` enclose:

    // f7010 · 683 B · unmatched · name unknown
    // void f7010(i32, i32) { ... }

The first line is the target function index, its body size and its status, then `placement: link order` when no
std::source_location record of the function gives it a line (its place comes from the recovered link order) and
`name unknown` when splat/symbol_addrs.txt has no name for it. The second is its signature: the demangled name with
`?` for the return type unless the wasm signature settles it (`void`: the function returns nothing and its wasm
parameters leave no room for a returned struct), or, with no name, `f<index>` and the wasm types.

Which functions. Every target function of a TSE component (splat/scan.tsv's group: vota, comum, api, simulador,
vota-web, ecourna, asn1-modules, ASN1) that splat/matched.txt does not list, unless it has code of ours already: our
link has a body that is it (the scan's candidate, when the symbol file names the function by it; a census pair, the
scan's source `ledger`, only when its symbol names the class and member of a record of the function or of a name the
symbol file gives it, or the class of a vtable that holds it or of a vptr it stores); or every record of it in its
file falls on a line of code of ours or names a function our file defines (a definition with the record's qualified
name and parameter types: an overload never stands for another, nor a destructor for its constructor); or it fills a
slot of a vtable our link holds (the symbol file gives that vtable a size, which it takes from our link) or of the
vtable of a class whose members our sources define. An asn1-modules function that no evidence puts in a source file
is left out, since the generated modules hold data, not functions (src/asn1/README.md).

Where. The file, in this order of evidence: the file of its std::source_location records (ledger/source-locations.tsv;
the .cpp holding most of them, else the header); the file of its class (ledger/vtables.json: the class whose vtable
holds it and from which every other class holding it derives; else ledger/func-attribution.tsv's vptr classes, the
most derived), the class's file being the one its members' records name, else the one of our sources that defines
its members, else the recorded or existing file named after the class; otherwise the tree's unplaced.cpp
(src/uenux2/, src/ecourna/, src/asn1/), grouped by the link-order cluster of ledger/tu-clusters.tsv. A file that does
not exist yet is created holding its stubs only, and removed when its last stub goes. In a file, a stub with a record
goes into the run of blank lines holding the record's line, ending just above it; a stub without one goes after the
nearest function of its use-count band that precedes it in link order and has a record in the file (or before the
nearest that follows), else after the end of the file.

Lines. A decompiled function's throw sites must keep the line their records give, so stubs only ever take blank
lines at namespace level: a run of k stubs needs 3k+1 lines (markers, two lines a stub, a blank line between stubs)
and the rest of the blank lines stay blank. When the run of blank lines holding a stub's record is too short, the run
is written whole and followed by `#line N`, which gives the next line its number again without touching the file
name (an object compiles byte-identical). Stubs after the end of a file and in stub-only files take no blank lines.

Gaps. A run of GAP_MIN (3) or more empty lines of code (outside comments, directive continuations and preprocessor
conditionals) between two other lines, with a line that a record of the file names below it, stands for original
lines we have not recovered. Once the stubs are laid out, each such run left is written as its first blank line,
then the comment `// (original lines A-B: content not recovered)` (ASCII; indented like the line under it; it sits on
line A) and `#line B+1`. Runs of 1 or 2 lines are formatting and stay blank. A gap comment that no longer sits on
line A means lines above it were added or removed: --check names it, and the generator writes it again over the
lines left, keeping `#line B+1`, so the code below keeps its numbers.

--strip undoes stubs and gaps exactly: each becomes as many blank lines as it took, which is how a file is edited by
hand; the generator then lays the stubs and gaps out again around the new code.

Inputs, all tracked: splat/scan.tsv, splat/matched.txt, splat/symbol_addrs.txt, ledger/functions.tsv,
ledger/ordinals.tsv, ledger/source-locations.tsv, ledger/vtables.json, ledger/classes.json,
ledger/func-attribution.tsv, ledger/tu-clusters.tsv, target/vota_web_wasm.wasm (the wasm signatures) and the sources.
A named stub's signature is demangled by llvm-cxxfilt (the pinned toolchain's lists in build/out/wasm/vota_web/ when
they hold the name, else llvm-cxxfilt or c++filt on the PATH, with `> >` spelled `>>` as llvm-cxxfilt does).
The files are read and written as Latin-1 bytes; `·` is written in the charset .editorconfig gives the file.
"""
import bisect
import collections
import json
import os
import re
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import check_encoding  # noqa: E402  (the .editorconfig charset of a path)

TREES = ('src/ecourna', 'src/uenux2', 'src/asn1')
SOURCE_EXT = ('.cpp', '.cxx', '.h', '.hpp')
UENUX2 = ['vota', 'comum', 'api', 'simulador', 'vota-web']
TSE = set(UENUX2) | {'ecourna', 'asn1-modules', 'ASN1'}
UNPLACED = {'src/uenux2/unplaced.cpp': UENUX2, 'src/ecourna/unplaced.cpp': ['ecourna'], 'src/asn1/unplaced.cpp': ['ASN1']}
OPEN, CLOSE = '// <stubs>', '// </stubs>'
LINE_RE = re.compile(r'^#line (\d+)$')
GAP_RE = re.compile(r'^([ \t]*)// \(original lines (\d+)-(\d+): content not recovered\)$')
GAP_LIKE_RE = re.compile(r'^\s*//.*original lines?\b.*not recovered')
GAP_MIN = 3
HEAD_RE = re.compile(r'^// f(\d+) \xb7 ')
DOT = '\xb7'
WASM_TYPES = {0x7f: 'i32', 0x7e: 'i64', 0x7d: 'f32', 0x7c: 'f64', 0x7b: 'v128', 0x70: 'funcref', 0x6f: 'externref'}
LINK_LISTS = os.path.join(ROOT, 'build', 'out', 'wasm', 'vota_web', 'symbols.{}.txt')


class StubError(Exception):
    pass


def tsv(path):
    with open(os.path.join(ROOT, path), encoding='utf-8') as f:
        next(f)
        for line in f:
            yield line.rstrip('\n').split('\t')


def local_path(file):
    """The path in this repository of a file a source_location record names, or None."""
    for pat, rep in ((r'^/home/rubio/tse/uenux2/', 'src/uenux2/'),
                     (r'^/home/rubio/\.conan2/p/b/[^/]+/[bp]/(?:src|include)/ecourna/', 'src/ecourna/')):
        if re.match(pat, file):
            return re.sub(pat, rep, file)
    return None


# ---- the target ---------------------------------------------------------------------------------------------------

def uleb(b, i):
    r = s = 0
    while True:
        c = b[i]
        i += 1
        r |= (c & 0x7f) << s
        s += 7
        if not c & 0x80:
            return r, i


def wasm_signatures():
    """index -> (params, results) as wasm type names, for every function of the target."""
    b = open(os.path.join(ROOT, 'target', 'vota_web_wasm.wasm'), 'rb').read()
    types, funcs, i = [], [], 8
    imported = []
    while i < len(b):
        sid = b[i]
        n, i = uleb(b, i + 1)
        a, end = i, i + n
        if sid == 1:
            cnt, j = uleb(b, a)
            for _ in range(cnt):
                np, j = uleb(b, j + 1)
                params = [WASM_TYPES.get(t, hex(t)) for t in b[j:j + np]]
                nr, j = uleb(b, j + np)
                results = [WASM_TYPES.get(t, hex(t)) for t in b[j:j + nr]]
                j += nr
                types.append((params, results))
        elif sid == 2:
            cnt, j = uleb(b, a)
            for _ in range(cnt):
                for _ in range(2):
                    ln, j = uleb(b, j)
                    j += ln
                kind = b[j]
                j += 1
                if kind == 0:
                    t, j = uleb(b, j)
                    imported.append(t)
                elif kind == 1:
                    flags, j = uleb(b, j + 1)
                    _, j = uleb(b, j)
                    if flags & 1:
                        _, j = uleb(b, j)
                elif kind == 2:
                    flags, j = uleb(b, j)
                    _, j = uleb(b, j)
                    if flags & 1:
                        _, j = uleb(b, j)
                elif kind == 3:
                    j += 2
                else:
                    _, j = uleb(b, j + 1)
        elif sid == 3:
            cnt, j = uleb(b, a)
            for _ in range(cnt):
                t, j = uleb(b, j)
                funcs.append(t)
        i = end
    return {k: types[t] for k, t in enumerate(imported + funcs)}


class Facts:
    """What the ledger, the scan and the match list say, read once."""

    def __init__(self):
        self.group, self.ours, self.object, self.candidate, self.source = {}, {}, {}, {}, {}
        for p in tsv('splat/scan.tsv'):
            i = int(p[0])
            self.group[i], self.ours[i], self.object[i] = p[8], p[2], p[10]
            self.candidate[i], self.source[i] = p[1], p[3]
        self.matched = set()
        for line in open(os.path.join(ROOT, 'splat', 'matched.txt')):
            p = line.split()
            if p and not p[0].startswith('#'):
                self.matched.add(int(p[0]))
        self.size = {int(p[0]): int(p[1]) for p in tsv('ledger/functions.tsv')}
        self.uses = {int(p[0]): int(p[1]) for p in tsv('ledger/ordinals.tsv')}
        self.records = collections.defaultdict(list)            # index -> [(file, line, function)]
        self.loaders = collections.defaultdict(lambda: collections.defaultdict(list))  # local file -> index -> lines
        self.class_records = collections.defaultdict(collections.Counter)            # class -> local .cpp -> count
        self.recorded_files = set()
        self.record_lines = collections.defaultdict(set)      # local file -> the lines its records name
        for p in tsv('ledger/source-locations.tsv'):
            file, line, func = p[1], int(p[2]), p[4]
            path = local_path(file)
            if path is None:
                continue
            self.recorded_files.add(path)
            self.record_lines[path].add(line)
            for f in p[5].split(','):
                if f.isdigit():
                    self.records[int(f)].append((path, line, func))
                    self.loaders[path][int(f)].append(line)
            q = qualifier(func)
            if q and not path.endswith(('.h', '.hpp')):
                self.class_records[q][path] += 1
        self.names = collections.defaultdict(list)
        linked_vtables = set()      # mangled classes whose vtable our plain link holds (the symbol file gives its size)
        for line in open(os.path.join(ROOT, 'splat', 'symbol_addrs.txt'), encoding='utf-8'):
            m = re.match(r'^(\S+) = func:(\d+);', line)
            if m and not m.group(1).startswith('byn$'):
                self.names[int(m.group(2))].append(m.group(1))
            m = re.match(r'^_ZTV(\S+) = 0x[0-9a-f]+;.* size:0x', line)
            if m:
                linked_vtables.add(m.group(1))
        classes = json.load(open(os.path.join(ROOT, 'ledger', 'classes.json')))['classes']
        mangled = {c['typeinfo']: c['mangled'] for c in classes}
        self.bases = {c['name']: [b['name'] for b in c.get('bases', [])] for c in classes}
        self.vtable_classes = collections.defaultdict(set)
        self.in_linked_vtable = set()   # functions in a slot of a vtable our link holds
        for v in json.load(open(os.path.join(ROOT, 'ledger', 'vtables.json'))):
            linked = mangled.get(v['typeinfo']) in linked_vtables
            for f in v['functions']:
                self.vtable_classes[f].add(v['class'])
                if linked:
                    self.in_linked_vtable.add(f)
        self.vptr_classes = {}
        for p in tsv('ledger/func-attribution.tsv'):
            if len(p) > 3 and p[2] == 'vptr':
                self.vptr_classes[int(p[0])] = [c for c in p[3].split(';') if c]
        self.clusters = {}
        stretches = []
        for p in tsv('ledger/tu-clusters.tsv'):
            sid, band, lo, hi = int(p[0]), int(p[1]), int(p[2]), int(p[3])
            self.clusters[sid] = (band, p[9])
            stretches.append((('twin' in p[11]), sid, band, lo, hi))
        by_band = collections.defaultdict(list)
        for twin, sid, band, lo, hi in sorted(stretches):
            by_band[band].append((lo, hi, sid))
        self.by_band = by_band
        self.signatures = wasm_signatures()

    def cluster_of(self, i):
        for lo, hi, sid in self.by_band.get(self.uses.get(i), ()):
            if lo <= i - 136 <= hi:
                return sid
        return None

    def ancestors(self, c):
        out, todo = set(), [c]
        while todo:
            for b in self.bases.get(todo.pop(), ()):
                if b not in out:
                    out.add(b)
                    todo.append(b)
        return out


def param_open(s):
    """Where the parameter list of the function a pretty function name names opens (its `(`), or None."""
    depth, k = 0, 0
    while k < len(s):
        ch = s[k]
        if ch == '<':
            depth += 1
        elif ch == '>':
            depth -= 1
        elif ch == '(' and depth == 0:
            if s[:k].endswith('operator'):
                k += 2
                continue
            return k
        k += 1
    return None


def name_scopes(func):
    """The scopes of the function a pretty function name (a record's) names: `virtual void a::B::C(int)` -> [a, B, C].
    An anonymous namespace is spelled `{anon}`."""
    s = func.replace('(anonymous namespace)', '{anon}')
    cut = param_open(s)
    head = s[:cut] if cut is not None else s
    depth, start = 0, 0
    for k, ch in enumerate(head):
        if ch == '<':
            depth += 1
        elif ch == '>':
            depth -= 1
        elif ch == ' ' and depth == 0 and not head[:k].endswith('operator'):
            start = k + 1
    return scope_split(head[start:].lstrip('&*'))


def qualifier(func):
    """The class (or namespace) a pretty function name is a member of, without template arguments."""
    return class_key('::'.join(name_scopes(func)[:-1]))


def class_key(c):
    """A class name without anonymous namespaces and template arguments."""
    c = c.replace('(anonymous namespace)::', '').replace('{anon}::', '')
    out, depth = '', 0
    for ch in c:
        if ch == '<':
            depth += 1
        elif ch == '>':
            depth -= 1
        elif depth == 0:
            out += ch
    return out


def record_params(func):
    """The parameter types of the function a pretty function name (a record's) names, as param_key spells them:
    `size_t api::EncodeTime(const std::string &)` -> ['const string &']; None when the text has no parameter list."""
    s = func.replace('(anonymous namespace)', '{anon}')
    k = param_open(s)
    end = matching_paren(s, k) if k is not None else None
    if end is None:
        return None
    return [param_key(p) for p in split_params(s[k + 1:end])]


def matching_paren(s, k):
    """The index of the `)` that closes the `(` at s[k], or None."""
    depth = 0
    for j in range(k, len(s)):
        if s[j] == '(':
            depth += 1
        elif s[j] == ')':
            depth -= 1
            if depth == 0:
                return j
    return None


CV = {'const', 'volatile'}
ELABORATED = {'struct', 'class', 'enum', 'union', 'typename'}
BUILTIN = {'void', 'bool', 'char', 'wchar_t', 'char8_t', 'char16_t', 'char32_t', 'short', 'int', 'long', 'signed',
           'unsigned', 'float', 'double', 'auto'}
INTEGER = {'signed', 'unsigned', 'short', 'long', 'int', 'char'}
TOKEN_RE = re.compile(r'[A-Za-z_]\w*|::|\.\.\.|&&|\d[\w.]*|\S')
IDENT_RE = re.compile(r'[A-Za-z_]\w*$')


def param_key(text):
    """One parameter's type, spelled so that two spellings of a type compare equal: without the parameter's name and
    default argument, namespace and class qualifiers, `struct`/`class`/`enum`/`typename`, and top-level const (not
    part of the function's type); `X const` as `const X`; `unsigned int` as `unsigned`, `long int` as `long`."""
    depth = 0
    for k, ch in enumerate(text):
        if ch in '<([':
            depth += 1
        elif ch in '>)]':
            depth -= 1
        elif ch == '=' and depth == 0:
            text = text[:k]
            break
    toks = []
    for t in TOKEN_RE.findall(text):
        if t in ELABORATED:
            continue
        if t != '::':
            toks.append(t)
            continue
        # drop the qualifier this `::` ends: an identifier, with its template arguments
        if toks and toks[-1] == '>':
            d = 0
            while toks:
                x = toks.pop()
                d += {'>': 1, '<': -1}.get(x, 0)
                if d == 0:
                    break
        if toks and IDENT_RE.match(toks[-1]) and toks[-1] not in BUILTIN | CV:
            toks.pop()
    depths, d = [], 0
    for t in toks:
        if t in '<([':
            depths.append(d)
            d += 1
        elif t in '>)]':
            d -= 1
            depths.append(d)
        else:
            depths.append(d)
    drop = set()
    # the name of a pointer to function or array: `void (*name)(int)`, `int (&name)[4]`
    for k, t in enumerate(toks):
        if t == '(':
            j = k + 1
            while j < len(toks) and toks[j] in {'*', '&', '&&'} | CV:
                j += 1
            if j > k + 1 and j + 1 < len(toks) and IDENT_RE.match(toks[j]) and toks[j + 1] == ')':
                drop.add(j)
    if not drop:
        # the declarator's name: the last identifier at depth 0, followed by nothing but array bounds, after a type
        last = None
        for k, t in enumerate(toks):
            if depths[k] == 0 and IDENT_RE.match(t):
                last = k
        if last is not None and toks[last] not in BUILTIN | CV and all(
                depths[j] > 0 or toks[j] in '[]' for j in range(last + 1, len(toks))) and any(
                depths[j] == 0 and t not in CV and (IDENT_RE.match(t) or t in ('>', '*', '&', '&&', ')'))
                for j, t in enumerate(toks[:last])):
            drop.add(last)
    toks = [t for k, t in enumerate(toks) if k not in drop]
    depths = [x for k, x in enumerate(depths) if k not in drop]
    # cv first in each part between pointer and reference declarators at depth 0
    parts, cur = [], []
    for t, x in zip(toks, depths):
        if x == 0 and t in ('*', '&', '&&'):
            parts.append(cur)
            parts.append([t])
            cur = []
        else:
            cur.append((t, x))
    parts.append(cur)
    simple = not any(x == 0 and t in '([' for t, x in zip(toks, depths))
    out = []
    for n, part in enumerate(parts):
        if part and isinstance(part[0], str):
            out += part
            continue
        cv = sorted(t for t, x in part if x == 0 and t in CV)
        rest = [t for t, x in part if not (x == 0 and t in CV)]
        top = n == len(parts) - 1 and (len(parts) == 1 or parts[-2][0] == '*')
        out += ([] if top and simple else cv) + rest
    # one spelling of each integer type
    canon, k = [], 0
    while k < len(out):
        if out[k] not in INTEGER:
            canon.append(out[k])
            k += 1
            continue
        j = k
        while j < len(out) and out[j] in INTEGER:
            j += 1
        spec = out[k:j]
        if 'int' in spec and set(spec) & {'short', 'long', 'signed', 'unsigned'}:
            spec = [t for t in spec if t != 'int']
        if 'signed' in spec and 'char' not in spec:
            spec = [t for t in spec if t != 'signed'] or ['int']
        canon += sorted(spec)
        k = j
    return ' '.join(canon)


def name_key(text):
    """(class, member) of a demangled or pretty function name, spelled for comparison: `std::__2::` as `std::`, no
    ABI tags, integer suffixes, spaces, or template arguments on the member. `api::X<int>::~X()` -> ('api::X<int>',
    '~X')."""
    scopes = name_scopes(text)
    return spelled('::'.join(scopes[:-1])), spelled(scopes[-1].split('<')[0])


def spelled(s):
    s = s.replace('(anonymous namespace)', '{anon}').replace('std::__2::', 'std::')
    s = re.sub(r'\[abi:[^\]]*\]', '', s)
    s = re.sub(r'\b(\d+)(?:ull|ul|ll|u|l)\b', r'\1', s, flags=re.I)
    return re.sub(r'\s+', '', s)


def bare(symbol):
    """A symbol without binaryen's merge prefix: `byn$mgfn-shared$_ZN...` -> `_ZN...`."""
    return re.sub(r'^byn\$[^$]*\$', '', symbol)


def code_only(lines):
    """`lines` with every comment and the inside of every string and character literal turned into spaces, and every
    preprocessor directive (with its continuation lines) emptied; the line count and the columns stay."""
    out, in_block, in_directive = [], False, False
    for line in lines:
        if in_directive or (not in_block and line.lstrip().startswith('#')):
            in_directive = line.endswith('\\')
            out.append('')
            continue
        chars, k = list(line), 0
        while k < len(line):
            if in_block:
                e = line.find('*/', k)
                stop = len(line) if e < 0 else e + 2
                chars[k:stop] = ' ' * (stop - k)
                in_block, k = e < 0, stop
                continue
            if line.startswith('//', k):
                chars[k:] = ' ' * (len(line) - k)
                break
            if line.startswith('/*', k):
                chars[k:k + 2] = '  '
                in_block, k = True, k + 2
                continue
            if line[k] in '"\'':
                q, e = line[k], k + 1
                while e < len(line) and line[e] != q:
                    e += 2 if line[e] == '\\' else 1
                e = min(e, len(line) - 1)
                chars[k + 1:e] = ' ' * (e - k - 1)
                k = e + 1
                continue
            k += 1
        out.append(''.join(chars))
    return out


def scopes_at_lines(code):
    """For each line of code_only text, the braces open at its start: ('ns', [names]) for a namespace (`{anon}` for
    an anonymous one, none for `extern "C"`), ('class', name), or ('other', None) for any other brace."""
    stack, prefix, out = [], '', []
    for line in code:
        out.append(tuple(stack))
        for ch in line:
            if ch == '{':
                m = re.search(r'\bnamespace\s*((?:[A-Za-z_]\w*\s*::\s*)*[A-Za-z_]\w*)?\s*$', prefix)
                c = re.search(r'\b(?:class|struct|union)\s+([A-Za-z_]\w*)\s*(?:<[^;{}]*>)?\s*(?:final\s*)?'
                              r'(?::[^;{}]*)?$', prefix)
                if m:
                    stack.append(('ns', [n.strip() for n in m.group(1).split('::')] if m.group(1) else ['{anon}']))
                elif re.search(r'\bextern\s*"\s*"\s*$', prefix):
                    stack.append(('ns', []))
                elif c and not re.search(r'\benum\s+(?:class|struct)\s+\w+[^;{}]*$', prefix):
                    stack.append(('class', c.group(1)))
                else:
                    stack.append(('other', None))
                prefix = ''
            elif ch == '}':
                if stack:
                    stack.pop()
                prefix = ''
            elif ch == ';':
                prefix = ''
            else:
                prefix += ch
        prefix += ' '
    return out


def definition_follows(text, k):
    """Whether what follows a parameter list closing just before text[k] makes it a definition: after the function's
    qualifiers (cv, ref, noexcept, throw(), override, final, a trailing return type) comes its body, a constructor's
    initializers, `try` or `= default`."""
    while True:
        m = re.match(r'\s*(?:(?:const|volatile|override|final|mutable)\b|&&|&|(noexcept|throw)\b\s*)', text[k:])
        if not m:
            break
        k += m.end()
        if m.group(1) and text[k:k + 1] == '(':
            end = matching_paren(text, k)
            if end is None:
                return False
            k = end + 1
    rest = text[k:].lstrip()
    if rest.startswith('->'):
        stop = re.search(r'[{;]', rest)
        return bool(stop) and stop.group(0) == '{'
    return (rest.startswith('{') or (rest.startswith(':') and not rest.startswith('::')) or
            re.match(r'try\b', rest) is not None or re.match(r'=\s*default\b', rest) is not None)


def qualifier_before(line, k):
    """The scopes written before line[k] (`a::B<T>::` -> ['a', 'B<T>']), up to the start of the qualified name."""
    out, j = [], k
    while True:
        i = j
        while i > 0 and line[i - 1] in ' \t':
            i -= 1
        if line[i - 2:i] != '::':
            return out
        i -= 2
        while i > 0 and line[i - 1] in ' \t':
            i -= 1
        end = i
        if i > 0 and line[i - 1] == '>':
            d = 0
            while i > 0:
                i -= 1
                d += {'>': 1, '<': -1}.get(line[i], 0)
                if d == 0:
                    break
            while i > 0 and line[i - 1] in ' \t':
                i -= 1
        m = re.search(r'[A-Za-z_]\w*$', line[:i])
        if not m:
            return out
        out.insert(0, line[m.start():end].replace(' ', ''))
        j = m.start()


# ---- source files -------------------------------------------------------------------------------------------------

SECTIONS = []


def charset_of(path):
    """The charset .editorconfig gives a file (latin1 when none does: TSE's sources are Latin-1)."""
    if not SECTIONS:
        SECTIONS.extend(check_encoding.sections())
    charset = 'latin1'
    for glob, cs in SECTIONS:
        if glob.match(path):
            charset = cs
    return charset


def read_lines(path):
    full = os.path.join(ROOT, path)
    if not os.path.exists(full):
        return None
    text = open(full, 'rb').read().decode('latin-1')
    if charset_of(path) == 'utf-8':
        text = text.replace(DOT.encode('utf-8').decode('latin-1'), DOT)
    if text and not text.endswith('\n'):
        raise StubError(f'{path}: no newline at the end of the file')
    return text.split('\n')[:-1] if text else []


def is_unplaced(path):
    return path in UNPLACED


def parse(path, lines):
    """Split a file into its base (every stub run and every gap turned back into the blank lines it took), its
    stubs and its gaps. Returns (base lines, [(index, physical line, header, signature)],
    [(physical line, first, last, line it sits on)]): a gap's comment names original lines first-last and sits on
    line `first` of the base unless lines above it were added or removed since it was written."""
    base, stubs, gaps, k = [], [], [], 0
    while k < len(lines):
        line = lines[k]
        m = GAP_RE.match(line)
        if m:
            first, last = int(m.group(2)), int(m.group(3))
            directive = LINE_RE.match(lines[k + 1]) if k + 1 < len(lines) else None
            if directive is None:
                raise StubError(f'{path}:{k + 1}: a gap comment without its `#line` on the next line. Gaps are '
                                f'generated: put the `#line` back as it was (git diff shows it), or delete the comment '
                                f'too and restore the blank lines it stood for')
            n = int(directive.group(1))
            at = len(base) + 1
            if last != n - 1 or first > last:
                raise StubError(f'{path}:{k + 1}: the gap comment says original lines {first}-{last}, but the '
                                f'`#line {n}` under it ends the gap at line {n - 1}. Gaps are generated, never edited: '
                                f'put back the lines the generator wrote (git diff shows them)')
            if at >= n:
                raise StubError(f'{path}:{k + 1}: lines added above the gap comment reach past the gap: the comment '
                                f'sits on line {at}, and the `#line {n}` under it would number the next line {n} '
                                f'again. Delete the comment and its `#line`, take out blank lines above so that the '
                                f'code below is at line {n} again, then run `make -C src stubs`')
            gaps.append((k + 1, first, last, at))
            base.extend([''] * (n - at))
            k += 2
            continue
        if line != OPEN:
            if LINE_RE.match(line):
                raise StubError(f'{path}:{k + 1}: `{line}` under neither a gap comment nor a stub run. The '
                                f'generator writes every `#line` of these sources: put back the line above it '
                                f'(git diff shows it)')
            if GAP_LIKE_RE.match(line):
                raise StubError(f'{path}:{k + 1}: `{line.strip()[:60]}` is not a gap comment as the generator '
                                f'writes it. Gaps are generated, never edited: put back the lines the generator wrote '
                                f'(git diff shows them)')
            if line == CLOSE or HEAD_RE.match(line):
                raise StubError(f'{path}:{k + 1}: `{line[:40]}` outside a stub run')
            base.append(line)
            k += 1
            continue
        start = k
        k += 1
        while k < len(lines) and lines[k] != CLOSE:
            line = lines[k]
            m = HEAD_RE.match(line)
            if m:
                if k + 1 >= len(lines) or not lines[k + 1].startswith('// ') or HEAD_RE.match(lines[k + 1]):
                    raise StubError(f'{path}:{k + 1}: a stub without its signature line')
                stubs.append((int(m.group(1)), k + 1, line, lines[k + 1]))
                k += 2
                continue
            if line == '' or (is_unplaced(path) and line.startswith('// ')):
                k += 1
                continue
            raise StubError(f'{path}:{k + 1}: `{line[:60]}` inside a stub run; stub runs are generated: move it out '
                            f'of the markers, or run `tools/round/stubs.py --strip {path}` before editing the file')
        if k >= len(lines):
            raise StubError(f'{path}:{start + 1}: `{OPEN}` without `{CLOSE}`')
        k += 1
        taken = k - start
        if k < len(lines) and LINE_RE.match(lines[k]):
            n = int(LINE_RE.match(lines[k]).group(1))
            taken = n - (len(base) + 1)
            if taken < 0:
                raise StubError(f'{path}:{k + 1}: `#line {n}` names a line before the stub run')
            k += 1
        elif all(x == '' for x in lines[k:]):
            # a run after the end of the file's own lines takes none of them, and one blank line before it
            if base and base[-1] == '':
                base.pop()
            continue
        base.extend([''] * taken)
    if base and all(x == '' for x in base):
        base = []
    return base, stubs, gaps


def blank_lines(base):
    """The 1-based numbers of the empty lines that are code: outside every comment, directive continuation and
    preprocessor conditional. Returns (those at namespace level, outside every function and class; all of them)."""
    namespace, code = set(), set()
    stack, prefix = [], ''
    in_block = in_directive = False
    conditionals = 0
    for n, line in enumerate(base, 1):
        if line == '' and not in_block and not in_directive and not conditionals:
            code.add(n)
            if all(k == 'ns' for k in stack):
                namespace.add(n)
        k = 0
        if in_directive or (not in_block and line.lstrip().startswith('#')):
            if not in_directive:
                word = line.lstrip()[1:].lstrip()
                if re.match(r'if(n?def)?\b', word):
                    conditionals += 1
                elif re.match(r'endif\b', word):
                    conditionals = max(conditionals - 1, 0)
            in_directive = line.endswith('\\')
            continue
        while k < len(line):
            if in_block:
                e = line.find('*/', k)
                if e < 0:
                    k = len(line)
                    break
                in_block, k = False, e + 2
                continue
            ch = line[k]
            if line.startswith('//', k):
                break
            if line.startswith('/*', k):
                in_block, k = True, k + 2
                continue
            if ch in '"\'':
                e = k + 1
                while e < len(line) and line[e] != ch:
                    e += 2 if line[e] == '\\' else 1
                prefix += '"S"' if ch == '"' else "'c'"
                k = e + 1
                continue
            if ch == '{':
                kind = 'ns' if re.search(r'(\bnamespace\b[^;{}()]*|\bextern\s*"S"\s*)$', prefix) else 'other'
                stack.append(kind)
                prefix = ''
            elif ch == '}':
                if stack:
                    stack.pop()
                prefix = ''
            elif ch == ';':
                prefix = ''
            else:
                prefix += ch
            k += 1
        prefix += ' '
    return namespace, code


def interior_runs(base, eligible):
    """[(first, last)] runs of eligible empty lines with a non-empty line before and after them."""
    runs, n = [], 1
    while n <= len(base):
        if n in eligible:
            m = n
            while m + 1 <= len(base) and (m + 1) in eligible:
                m += 1
            if n > 1 and m < len(base):
                runs.append((n, m))
            n = m + 1
        else:
            n += 1
    return runs


def lay_out_gaps(lines, records):
    """Write each padding run of a file as a gap: its first blank line, then the comment naming the original lines
    the rest of the run stood for, then `#line` with the number of the line after the run. A padding run is GAP_MIN
    or more empty lines of code (blank_lines) between two other lines, with a line that a source_location record of
    the file names below it. `lines` may hold stub runs, whose `#line` it follows. Returns (lines, [(first, last)])."""
    below = max(records, default=0)
    code = blank_lines(lines)[1]
    numbers, n = [], 1
    for line in lines:
        numbers.append(n)
        m = LINE_RE.match(line)
        n = int(m.group(1)) if m else n + 1
    out, gaps, k = [], [], 0
    while k < len(lines):
        if lines[k] != '' or (k + 1) not in code:
            out.append(lines[k])
            k += 1
            continue
        j = k
        while j + 1 < len(lines) and lines[j + 1] == '' and (j + 2) in code:
            j += 1
        first, last = numbers[k] + 1, numbers[j]
        if j - k + 1 >= GAP_MIN and k > 0 and j + 1 < len(lines) and last < below:
            nxt = lines[j + 1]
            indent = '' if nxt.lstrip().startswith('#') else nxt[:len(nxt) - len(nxt.lstrip())]
            out += ['', f'{indent}// (original lines {first}-{last}: content not recovered)', f'#line {last + 1}']
            gaps.append((first, last))
        else:
            out += lines[k:j + 1]
        k = j + 1
    return out, gaps


# ---- signatures ---------------------------------------------------------------------------------------------------

def demangle_all(names):
    names = sorted(set(n for n in names if n.startswith('_Z')))
    out = {}
    if not names:
        return out
    mangled, demangled = LINK_LISTS.format('mangled'), LINK_LISTS.format('demangled')
    if os.path.exists(mangled) and os.path.exists(demangled):
        want = set(names)
        with open(mangled, encoding='latin-1') as a, open(demangled, encoding='latin-1') as b:
            for x, y in zip(a, b):
                x = x.rstrip('\n')
                if x in want:
                    out[x] = y.rstrip('\n')
    rest = [n for n in names if n not in out]
    if rest:
        tool = shutil.which('llvm-cxxfilt') or shutil.which('c++filt')
        if tool is None:
            raise StubError('no llvm-cxxfilt or c++filt on the PATH to demangle the named stubs')
        res = subprocess.run([tool], input='\n'.join(rest) + '\n', capture_output=True, text=True, check=True)
        for x, y in zip(rest, res.stdout.split('\n')):
            while '> >' in y:
                y = y.replace('> >', '>>')
            out[x] = y
    return out


def split_params(text):
    """Top-level comma split of a parameter list."""
    out, depth, cur = [], 0, ''
    for ch in text:
        if ch in '<([':
            depth += 1
        elif ch in '>)]':
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(cur.strip())
            cur = ''
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return [] if out == ['void'] else out


def scope_split(name):
    """`a::b<c::d>::e` -> ['a', 'b<c::d>', 'e']."""
    out, depth, cur, k = [], 0, '', 0
    while k < len(name):
        ch = name[k]
        if ch in '<(':
            depth += 1
        elif ch in '>)':
            depth -= 1
        if depth == 0 and name.startswith('::', k):
            out.append(cur)
            cur, k = '', k + 2
            continue
        cur += ch
        k += 1
    return out + [cur]


def signature_of(i, facts, demangled):
    params, results = facts.signatures[i]
    names = facts.names.get(i, [])
    if not names:
        return f'{"void" if not results else "?"} f{i}({", ".join(params)})', False
    name = sorted(names)[0]
    text = demangled.get(name)
    if text is None or text == name:
        return f'{"void" if not results else "?"} {name}({", ".join(params)})', True
    # the outermost parameter list: the last top-level (...) before the trailing qualifiers
    tail = re.search(r'(\s+(const|volatile|&&|&))*$', text)
    quals = text[tail.start():] if tail else ''
    core = text[:tail.start()] if tail else text
    depth, open_at = 0, None
    for k in range(len(core) - 1, -1, -1):
        if core[k] == ')':
            depth += 1
        elif core[k] == '(':
            depth -= 1
            if depth == 0:
                open_at = k
                break
    if open_at is None:
        return f'? {text}', True
    head, plist = core[:open_at], core[open_at + 1:-1]
    # a template function's demangling starts with its return type: drop it, the rule below decides
    depth, start = 0, 0
    for k, ch in enumerate(head):
        if ch in '<(':
            depth += 1
        elif ch in '>)':
            depth -= 1
        elif ch == ' ' and depth == 0 and not head[:k].endswith('operator'):
            start = k + 1
    qualified = head[start:]
    parts = scope_split(qualified)
    last = parts[-1]
    ctor_dtor = last.startswith('~') or (len(parts) > 1 and last == parts[-2].split('<')[0])
    conversion = last.startswith('operator ') and not re.match(r'operator (new|delete)', last)
    n = len(split_params(plist))
    if ctor_dtor or conversion:
        return f'{qualified}({plist}){quals}', True
    cv = re.match(r'_ZN([rVK]*)([RO]?)', name)
    member = bool(cv and (cv.group(1) or cv.group(2))) or bool(facts.vtable_classes.get(i))
    this = 1 if member else (None if name.startswith('_ZN') else 0)
    if results:
        ret = '?'
    elif this is not None:
        ret = 'void' if len(params) == this + n else '?'
    else:
        ret = 'void' if len(params) == n else '?'
    return f'{ret} {qualified}({plist}){quals}', True


# ---- placement ----------------------------------------------------------------------------------------------------

class Stub:
    __slots__ = ('index', 'file', 'lines', 'how', 'header', 'signature', 'named', 'mark')

    def __init__(self, index):
        self.index, self.file, self.lines, self.how = index, None, [], None
        self.header = self.signature = None
        self.named = self.mark = False


def tree_of(group):
    for path, groups in UNPLACED.items():
        if group in groups:
            return path
    return None


def tse_sources():
    out = []
    for tree in TREES:
        for dp, dn, fs in os.walk(os.path.join(ROOT, tree)):
            dn.sort()
            for f in sorted(fs):
                if f.endswith(SOURCE_EXT):
                    out.append(os.path.relpath(os.path.join(dp, f), ROOT))
    return out


class Plan:
    """Every file's current text and stubs, and the stubs it should have."""

    def __init__(self):
        self.facts = facts = Facts()
        self.current = {}       # path -> lines (None when absent)
        self.base = {}          # path -> base lines
        self.found = {}         # path -> [(index, line, header, signature)]
        self.found_gaps = {}    # path -> [(line, first, last, line it sits on)]
        self.errors = []
        self.broken = set()     # files whose stub runs or gaps do not parse: left as they are
        for path in tse_sources():
            lines = read_lines(path)
            self.current[path] = lines
            try:
                self.base[path], self.found[path], self.found_gaps[path] = parse(path, lines)
            except StubError as e:
                self.errors.append(str(e))
                self.broken.add(path)
                self.base[path], self.found[path], self.found_gaps[path] = lines, [], []
        self.code_files = {p for p, b in self.base.items() if b and not is_unplaced(p)}
        self.member_files = self._member_files()
        self._defines_memo = {}
        self._code_memo = {}
        self.defined = {}       # index -> why it is not stubbed
        self.not_ours = {}      # index -> why its census candidate is another function's body, not code of ours for it
        self.excluded = []      # asn1-modules functions no evidence puts in a file
        self.stubs = {}
        paired = [i for i in sorted(facts.group) if facts.group[i] in TSE and i not in facts.matched and
                  facts.ours[i] != '-' and facts.source[i] != 'symbol']
        self.demangled = demangle_all([bare(n) for i in paired for n in [facts.candidate[i]] + facts.names.get(i, [])])
        for i in sorted(facts.group):
            if facts.group[i] not in TSE or i in facts.matched:
                continue
            if facts.ours[i] != '-':
                why = self._other_function(i)
                if why is None:
                    self.defined[i] = 'candidate'
                    continue
                self.not_ours[i] = why
            if i in facts.in_linked_vtable:
                self.defined[i] = 'vtable'
                continue
            s = self._place(i)
            if s is None:
                continue
            self.stubs[i] = s
        names = [n for i in self.stubs for n in facts.names.get(i, [])]
        demangled = demangle_all(names)
        for i, s in self.stubs.items():
            sig, s.named = signature_of(i, facts, demangled)
            s.signature = f'// {sig} {{ ... }}'

    def _other_function(self, i):
        """None when the scan's candidate for target function i is code of ours for it; else why it is not. The
        symbol file's name is evidence: a candidate it gives (scan source `symbol`) is the function. Any other, a
        census pair (`ledger`), is only a body of like shape: it counts when its symbol names the class and member of a
        record of i or of a name the symbol file gives i, or the class of a vtable that holds i or of a vptr i stores.
        With no such evidence nothing shows the pair is i, and i keeps its stub."""
        facts = self.facts
        if facts.source[i] == 'symbol':
            return None
        cls, member = name_key(self.demangled.get(bare(facts.candidate[i]), bare(facts.candidate[i])))
        evidence = [name_key(self.demangled.get(bare(n), bare(n))) for n in facts.names.get(i, [])]
        evidence += [name_key(func) for _, _, func in facts.records.get(i, [])]
        evidence += [(spelled(c), None) for c in sorted(facts.vtable_classes.get(i, ()))]
        evidence += [(spelled(c), None) for c in facts.vptr_classes.get(i, [])]
        if any(c == cls and m in (None, member) for c, m in evidence):
            return None
        return 'evidence names another function' if evidence else 'no evidence names it'

    def _head(self, s):
        parts = [f'f{s.index}', f'{self.facts.size[s.index]} B', 'unmatched']
        if s.mark:
            parts.append('placement: link order')
        if not s.named:
            parts.append('name unknown')
        s.header = '// ' + f' {DOT} '.join(parts)

    def _member_files(self):
        """class key -> files of our sources that define one of its members (`Class::member(` at column 0)."""
        out = collections.defaultdict(set)
        pat = re.compile(r'^[^\s/#][^\n]*?\b([A-Za-z_]\w*)::~?[A-Za-z_]\w*\s*\(', re.M)
        for path in sorted(self.code_files):
            if path.endswith(('.h', '.hpp')):
                continue
            for m in pat.finditer('\n'.join(self.base[path])):
                out[m.group(1)].add(path)
        return out

    def _defines(self, path, func):
        """Whether our file defines the function a record names, wherever it sits: a definition (a body, a ctor's
        initializers or `= default` after its parameter list; not a declaration or a call) on a line that starts at
        column 0, whose qualified name (the enclosing namespaces and classes, then the scopes written before the name)
        is the record's, without anonymous namespaces and template arguments, and whose parameter types are the
        record's (param_key). A destructor never stands for a constructor, nor one overload for another."""
        key = (path, func)
        if key not in self._defines_memo:
            self._defines_memo[key] = self._find_definition(path, func)
        return self._defines_memo[key]

    def _find_definition(self, path, func):
        if path not in self._code_memo:
            code = code_only(self.base[path])
            starts, n = [], 0
            for line in code:
                starts.append(n)
                n += len(line) + 1
            self._code_memo[path] = (code, '\n'.join(code), starts, scopes_at_lines(code))
        code, text, starts, scopes = self._code_memo[path]
        parts = name_scopes(func)
        want = class_key('::'.join(parts))
        params = record_params(func)
        name = parts[-1].split('<')[0]
        if name.startswith('~'):
            rx = r'~\s*' + re.escape(name[1:].strip()) + r'\s*\('
        elif name.startswith('operator'):
            rx = r'\boperator' + ''.join(r'\s*' + re.escape(c) for c in name[len('operator'):].strip()) + r'\s*\('
        else:
            rx = r'(?<![\w~])' + re.escape(name) + r'\s*\('
        for m in re.finditer(rx, text):
            n = bisect.bisect_right(starts, m.start()) - 1
            line, col = code[n], m.start() - starts[n]
            if not line or line[0] in ' \t/#' or any(ch in ';{}' for ch in line[:col]):
                continue
            if not name.startswith('~') and line[:col].rstrip().endswith('~'):
                continue                                    # a destructor, not the constructor
            if any(kind == 'other' for kind, _ in scopes[n]):
                continue                                    # inside a function body or an initializer
            enclosing = [x for kind, names in scopes[n] for x in (names if kind == 'ns' else [names])]
            if class_key('::'.join(enclosing + qualifier_before(line, col) + [name])) != want:
                continue
            k = m.end() - 1
            end = matching_paren(text, k)
            if end is None or not definition_follows(text, end + 1):
                continue
            if params is None or [param_key(p) for p in split_params(text[k + 1:end])] == params:
                return True
        return False

    def _class_file(self, cls):
        key = class_key(cls)
        if key.startswith(('std::', 'boost::')) or not key:
            return None
        recorded = self.facts.class_records.get(key)
        if recorded:
            return sorted(recorded.items(), key=lambda kv: (-kv[1], kv[0]))[0][0]
        last = key.split('::')[-1]
        files = self.member_files.get(last, set())
        if len(files) == 1:
            return next(iter(files))
        base = last.lower() + '.cpp'
        named = {p for p in self.facts.recorded_files | self.code_files if p.rsplit('/', 1)[-1] == base}
        if len(named) == 1:
            return next(iter(named))
        return None

    def _owner_class(self, i):
        facts = self.facts
        classes = facts.vtable_classes.get(i)
        if classes:
            roots = [c for c in classes if all(c == o or c in facts.ancestors(o) for o in classes)]
            return roots[0] if len(roots) == 1 else None
        classes = [c for c in facts.vptr_classes.get(i, []) if not class_key(c).startswith(('std::', 'boost::'))]
        if classes:
            leaves = [c for c in classes if all(c == o or o in facts.ancestors(c) for o in classes)]
            return leaves[0] if len(leaves) == 1 else None
        return None

    def _place(self, i):
        facts = self.facts
        s = Stub(i)
        recs = facts.records.get(i, [])
        for want_header in (False, True):
            per_file = collections.Counter(p for p, _, _ in recs if p.endswith(('.h', '.hpp')) == want_header)
            if per_file:
                s.file = sorted(per_file.items(), key=lambda kv: (-kv[1], kv[0]))[0][0]
                s.lines = sorted({ln for p, ln, _ in recs if p == s.file})
                s.how = 'srcloc'
                break
        if s.file:
            base = self.base.get(s.file)
            if s.file in self.code_files and all(
                    (ln <= len(base) and base[ln - 1].strip()) or self._defines(s.file, func)
                    for p, ln, func in recs if p == s.file):
                self.defined[i] = 'srcloc'
                return None
            return s
        cls = self._owner_class(i)
        f = self._class_file(cls) if cls else None
        if f and facts.vtable_classes.get(i) and f in self.member_files.get(class_key(cls).split('::')[-1], ()):
            # a virtual member of a class our sources define, by the class's last name alone: this slot may have
            # no body in our link (src/units/README.md "Pending members")
            self.defined[i] = 'class'
            return None
        if f:
            s.file, s.how, s.mark = f, 'rtti', True
            return s
        if facts.group[i] == 'asn1-modules':
            self.excluded.append(i)
            return None
        s.file, s.how, s.mark = tree_of(facts.group[i]), 'unplaced', True
        return s

    # ---- layout ---------------------------------------------------------------------------------------------------

    def expected(self):
        """path -> expected lines (None: the file should not exist)."""
        by_file = collections.defaultdict(list)
        for s in self.stubs.values():
            by_file[s.file].append(s)
        out = {}
        self.gaps = {}          # path -> [(first, last)] the gaps it should have
        self.line_directives = 0
        self.runs_used = 0
        self.tail_stubs = 0
        for path in sorted(set(self.current) | set(by_file)):
            if path in self.broken:
                out[path] = self.current[path]
                continue
            if is_unplaced(path):
                out[path] = self._unplaced(path, by_file.get(path, []))
                continue
            base = self.base.get(path) or []
            stubs = by_file.get(path, [])
            if not stubs and not base:
                out[path] = None
                continue
            lines = self._lay_out(path, base, stubs) if stubs else base
            out[path], self.gaps[path] = lay_out_gaps(lines, self.facts.record_lines.get(path, ()))
        return out

    def _lay_out(self, path, base, stubs):
        facts = self.facts
        eligible = blank_lines(base)[0]
        runs = interior_runs(base, eligible)
        run_of = {}
        for g in runs:
            for n in range(g[0], g[1] + 1):
                run_of[n] = g
        known = {}                                  # function -> its first record line in this file
        for j, lines in facts.loaders.get(path, {}).items():
            known[j] = min(lines)
        in_run = collections.defaultdict(list)
        tail = []
        for s in stubs:
            if s.how == 'srcloc':
                hits = collections.Counter(run_of[ln] for ln in s.lines if ln in run_of)
                if hits:
                    g = sorted(hits.items(), key=lambda kv: (-kv[1], kv[0]))[0][0]
                    first = min(ln for ln in s.lines if run_of.get(ln) == g)
                    s.mark = False
                    in_run[g].append((first, s.index, first - 2, s))
                    continue
                beyond = [ln for ln in s.lines if ln > len(base)]
                if beyond:
                    s.mark = False
                    tail.append((min(beyond), -s.index, s))
                    continue
            s.mark = True
            band = facts.uses.get(s.index)
            peers = [j for j in known if j != s.index and facts.uses.get(j) == band]
            pred = min((j for j in peers if j > s.index), default=None)
            succ = max((j for j in peers if j < s.index), default=None)
            lo = known[pred] if pred is not None else None
            hi = known[succ] if succ is not None else None
            g = None
            if lo is not None:
                g = next((x for x in runs if x[0] > lo and (hi is None or x[1] < hi)), None)
                key = lo + 0.5
            elif hi is not None:
                g = next((x for x in reversed(runs) if x[1] < hi), None)
                key = hi - 0.5
            else:
                key = float('inf')
            if g is not None:
                in_run[g].append((key, s.index, None, s))
            else:
                tail.append((key, -s.index, s))
        for s in stubs:
            self._head(s)
        out = list(base)
        for g in sorted(in_run, reverse=True):      # bottom-up, so earlier line numbers stay valid
            items = sorted(in_run[g], key=lambda t: (t[0], -t[1]))
            gs, ge = g
            size = ge - gs + 1
            while 3 * len(items) + 1 > size and any(t[2] is None for t in items):
                weak = max((t for t in items if t[2] is None), key=lambda t: (t[0], -t[1]))
                items.remove(weak)
                tail.append((weak[0], -weak[1], weak[3]))
            k = len(items)
            if not items:
                continue
            self.runs_used += 1
            if 3 * k + 1 > size:
                region = [OPEN]
                for n, t in enumerate(items):
                    if n:
                        region.append('')
                    region += [t[3].header, t[3].signature]
                region.append(CLOSE)
                out[gs - 1:ge] = [''] + region + [f'#line {ge + 1}']
                self.line_directives += 1
                continue
            margin = 1 if size >= 3 * k + 3 else 0
            lo, hi = gs + 1 + margin, ge - 2 - margin
            pos = []
            for t in items:
                want = t[2] if t[2] is not None else lo
                pos.append(max(want, lo, pos[-1] + 3 if pos else lo))
            pos[-1] = min(pos[-1], hi)
            for n in range(k - 2, -1, -1):
                pos[n] = min(pos[n], pos[n + 1] - 3)
            block = [''] * size
            for n, (p, t) in enumerate(zip(pos, items)):
                r = p - gs
                block[r], block[r + 1] = t[3].header, t[3].signature
                if n == 0 or pos[n - 1] + 3 != p:
                    block[r - 1] = OPEN
                if n == k - 1 or pos[n + 1] != p + 3:
                    block[r + 2] = CLOSE
            out[gs - 1:ge] = block
        if tail:
            self.tail_stubs += len(tail)
            tail.sort(key=lambda t: (t[0], t[1]))
            region = [OPEN]
            for n, t in enumerate(tail):
                if n:
                    region.append('')
                region += [t[2].header, t[2].signature]
            region.append(CLOSE)
            out = out + ([''] if out else []) + region
        return out

    def _unplaced(self, path, stubs):
        if not stubs:
            return None
        facts = self.facts
        tree = path.split('/')[1]
        out = [f'// The unmatched {tree} functions that no evidence places in a source file, generated by',
               '// tools/round/stubs.py (make -C src stubs): never edit it, and never compile it. They are grouped by',
               "// component, then by link-order cluster (ledger/tu-clusters.tsv), whose neighbours' file is a hint,",
               '// not evidence; inside a cluster they are in link order.',
               '', OPEN]
        groups = UNPLACED[path]
        for g in groups:
            mine = [s for s in stubs if facts.group[s.index] == g]
            if not mine:
                continue
            if len(groups) > 1:
                out += [f'// component {g}', '']
            by_cluster = collections.defaultdict(list)
            for s in mine:
                self._head(s)
                by_cluster[facts.cluster_of(s.index)].append(s)
            for c in sorted(by_cluster, key=lambda c: (c is None, c if c is not None else 0)):
                if c is None:
                    out.append('// no link-order cluster')
                else:
                    band, file = facts.clusters[c]
                    out.append(f'// link-order cluster {c} {DOT} uses={band}' +
                               (f" {DOT} neighbours' file {file}" if file else ''))
                out.append('')
                for s in sorted(by_cluster[c], key=lambda s: -s.index):
                    out += [s.header, s.signature, '']
        out[-1] = CLOSE
        return out


def encode(path, lines):
    text = '\n'.join(lines) + '\n'
    if charset_of(path) == 'utf-8':
        text = text.replace(DOT, DOT.encode('utf-8').decode('latin-1'))
    return text.encode('latin-1')


def report(plan, expected):
    """The problems --check fails on: one line each."""
    facts = plan.facts
    problems = list(plan.errors)
    where = collections.defaultdict(list)
    for path, stubs in plan.found.items():
        for idx, line, header, sig in stubs:
            where[idx].append((path, line, header, sig))
    exp_where = {}
    for path, lines in expected.items():
        if lines is None or path in plan.broken:
            continue
        for idx, line, header, sig in parse(path, lines)[1]:
            exp_where[idx] = (path, line, header, sig)
    for idx in sorted(where):
        places = where[idx]
        at = ', '.join(f'{p}:{ln}' for p, ln, _, _ in places)
        if idx not in facts.group:
            problems.append(f'f{idx} ({at}): the target has no function {idx}')
            continue
        if len(places) > 1:
            problems.append(f'f{idx} has {len(places)} stubs: {at}')
        if idx in facts.matched:
            problems.append(f'f{idx} ({at}) is matched in splat/matched.txt: its stub goes')
        elif idx in plan.defined:
            why = {'candidate': 'our link has a body for it (splat/scan.tsv)',
                   'srcloc': 'its source_location records fall on code of ours',
                   'vtable': 'it fills a slot of a vtable our link holds',
                   'class': 'it fills a slot of the vtable of a class our sources define'}[plan.defined[idx]]
            problems.append(f'f{idx} ({at}) is defined in our sources: {why}')
        elif facts.group[idx] not in TSE:
            problems.append(f'f{idx} ({at}) is not a TSE function (group {facts.group[idx]})')
        elif idx not in plan.stubs:
            problems.append(f'f{idx} ({at}) gets no stub')
        if idx in exp_where:
            ep, eln, eh, es = exp_where[idx]
            for p, ln, h, sg in places:
                if (h, sg) != (eh, es):
                    problems.append(f'f{idx} ({p}:{ln}): the stub says `{h[3:]}` / `{sg[3:]}`, the generator derives '
                                    f'`{eh[3:]}` / `{es[3:]}`')
                if p != ep:
                    problems.append(f'f{idx} is in {p}:{ln}; its evidence puts it in {ep}')
                elif ln != eln:
                    problems.append(f'f{idx} is at {p}:{ln}; its evidence puts it at line {eln}')
    for idx in sorted(set(exp_where) - set(where)):
        ep, eln, _, _ = exp_where[idx]
        problems.append(f'f{idx} is unmatched and has no stub; it goes in {ep}:{eln}')
    for path in sorted(expected):
        if path in plan.broken or expected[path] is None:
            continue
        want = {last: first for first, last in plan.gaps.get(path, [])}
        have, stale = {}, set()
        for line, first, last, at in plan.found_gaps.get(path, []):
            have[last] = at
            if at != first:
                stale.add(last)
                problems.append(f'{path}:{line}: the gap comment says original lines {first}-{last} but sits on line '
                                f'{at}: lines above it were {"added" if at > first else "removed"} since it was '
                                f'written. `make -C src stubs` writes it again and keeps line {last + 1} where it is; '
                                f'to move the code below instead, `tools/round/stubs.py --strip {path}` first')
            if last not in want:
                problems.append(f'{path}:{line}: a gap comment over lines {at}-{last}, where the generator writes '
                                f'blank lines (a gap is {GAP_MIN} or more blank lines with a source_location record of '
                                f'the file below them)')
        for last, first in sorted(want.items()):
            if last not in have:
                problems.append(f'{path}: original lines {first - 1}-{last} are {last - first + 2} blank lines that '
                                f'hold the code below at its records\' lines; the generator writes them as a gap '
                                f'comment and a `#line` (make -C src stubs)')
            elif have[last] != first and last not in stale:
                problems.append(f'{path}: the gap comment of original lines up to {last} sits on line {have[last]}; '
                                f'the generator writes it on line {first}, under one blank line (make -C src stubs)')
    for path in sorted(expected):
        want, have = expected[path], plan.current.get(path)
        if want is None and have is not None and (is_unplaced(path) or not plan.base.get(path)):
            problems.append(f'{path} holds stubs only and none is left: the generator removes it')
        elif want is not None and have is None:
            problems.append(f'{path} does not exist; the generator writes it')
        elif want is not None and want != have:
            problems.append(f'{path} differs from what the generator writes (make -C src stubs)')
    return problems


def write(plan, expected):
    changed = 0
    for path, lines in sorted(expected.items()):
        have = plan.current.get(path)
        full = os.path.join(ROOT, path)
        if lines is None:
            if have is not None and (is_unplaced(path) or not plan.base.get(path)):
                os.remove(full)
                changed += 1
            continue
        if lines == have:
            continue
        if have is None and path.startswith('src/asn1/') and path.endswith('.cxx'):
            raise StubError(f'{path}: src/mk/asn1.mk compiles every .cxx of src/asn1, so no stub file may be one')
        roundtrip = parse(path, lines)[0]
        if not is_unplaced(path) and roundtrip != (plan.base.get(path) or []):
            raise StubError(f'{path}: the stub layout would move a line of code (internal error)')
        os.makedirs(os.path.dirname(full), exist_ok=True)
        with open(full, 'wb') as f:
            f.write(encode(path, lines))
        changed += 1
    return changed


def counts(plan):
    c = collections.Counter()
    for s in plan.stubs.values():
        c[(s.how, s.mark)] += 1
    per_group = collections.Counter(plan.facts.group[i] for i in plan.stubs)
    defined = collections.Counter()
    for i, why in plan.defined.items():
        if why == 'srcloc':
            defined['records on code of ours'] += 1
            continue
        if why == 'vtable':
            defined['a slot of a vtable our link holds'] += 1
            continue
        if why == 'class':
            defined['a virtual member of a class our sources define'] += 1
            continue
        o = plan.facts.object[i]
        if re.match(r'app/(ecourna|uenux2|asn1)/', o):
            defined['candidate from a TSE source'] += 1
        elif o == '<binaryen>':
            defined['candidate: a binaryen merge of our code'] += 1
        elif o.startswith('app/'):
            defined['candidate from a stand-in (src/app, src/units)'] += 1
        else:
            defined['candidate from a library object'] += 1
    files = collections.Counter(s.file for s in plan.stubs.values())
    new = {f for f in files if not plan.code_files.__contains__(f) and not is_unplaced(f)}
    lines = [f'stubs: {len(plan.stubs)}',
             '  by component: ' + ', '.join(f'{g} {per_group[g]}' for g in UENUX2 + ['ecourna', 'asn1-modules', 'ASN1']),
             f'  placed by a source_location line: {sum(v for (h, m), v in c.items() if h == "srcloc" and not m)}',
             f'  file by source_location, place by link order: {c[("srcloc", True)]}',
             f'  file by RTTI, place by link order: {c[("rtti", True)]}',
             f'  unplaced (tree unplaced.cpp): {c[("unplaced", True)]}',
             f'  in {len(files)} files: {len(files) - len(new)} with code of ours or unplaced.cpp, {len(new)} stub-only',
             f'  runs of blank lines used: {getattr(plan, "runs_used", 0)}, of which too short (#line): '
             f'{getattr(plan, "line_directives", 0)}; stubs after the end of a file: {getattr(plan, "tail_stubs", 0)}',
             f'gaps (padding runs written as a comment and #line): {sum(len(g) for g in plan.gaps.values())} in '
             f'{sum(1 for g in plan.gaps.values() if g)} files, for '
             f'{sum(last - first + 2 for g in plan.gaps.values() for first, last in g)} blank lines',
             f'unmatched TSE functions not stubbed because they have code: {len(plan.defined)} '
             f'({", ".join(f"{k} {v}" for k, v in sorted(defined.items()))})',
             f'census pairs not counted as code of ours, being another function\'s body: {len(plan.not_ours)} '
             f'({", ".join(f"{k} {v}" for k, v in sorted(collections.Counter(plan.not_ours.values()).items()))})',
             f'asn1-modules functions with no source file (left out): {len(plan.excluded)}']
    return lines


def strip(paths):
    for path in paths:
        rel = os.path.relpath(os.path.abspath(path), ROOT)
        lines = read_lines(rel)
        if lines is None:
            raise StubError(f'{rel}: no such file')
        base, stubs, gaps = parse(rel, lines)
        if not stubs and not gaps:
            continue
        with open(os.path.join(ROOT, rel), 'wb') as f:
            f.write(encode(rel, base))
        print(f'{rel}: {len(stubs)} stubs and {len(gaps)} gaps turned back into blank lines')


def main(argv):
    try:
        if argv[:1] == ['--strip']:
            strip(argv[1:])
            return 0
        plan = Plan()
        expected = plan.expected()
        if argv[:1] in (['--check'], ['--report']):
            problems = report(plan, expected)
            for p in problems:
                print(p, file=sys.stderr)
            for line in counts(plan):
                print(line)
            if argv[:1] == ['--check']:
                print(f'{len(problems)} problems' if problems else
                      'every unmatched TSE function has its stub, in place, and every padding run is a gap')
                return 1 if problems else 0
            return 0
        if argv:
            raise StubError(f'unknown arguments {" ".join(argv)}')
        if plan.errors:
            raise StubError('\n'.join(plan.errors))
        changed = write(plan, expected)
        for line in counts(plan):
            print(line)
        print(f'{changed} files written')
        return 0
    except StubError as e:
        print(e, file=sys.stderr)
        return 2


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
