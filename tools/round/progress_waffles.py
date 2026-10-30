"""The README's progress waffles, for status.py: squares coloured by the scan's verdict.

    docs/img/progress-origins-{light,dark}.svg      a 10 x 10 waffle for the module and for each origin
    docs/img/progress-tse-{light,dark}.svg          one square per function of TSE code, by component
    docs/img/progress-components-{light,dark}.svg   a 10 x 10 waffle per component, by origin

A 10 x 10 waffle splits 100 squares between the verdicts in proportion to their functions (largest remainder), matched
first, row by row from the top left. The function waffle has one square per target function, each component on rows of
its own, sorted by verdict and then by index. `make -C src status` writes them from splat/scan.tsv; `status.py --check`
fails when one is not what the scan draws.
"""
import os

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
IMG = os.path.join(ROOT, 'docs', 'img')

VERDICTS = ['match', 'differs', 'unresolved', 'no-candidate']
LABELS = ['matched', 'differs', 'unresolved', 'no candidate yet']
FONT = "system-ui, -apple-system, 'Segoe UI', Helvetica, Arial, sans-serif"
MONO = "ui-monospace, SFMono-Regular, Menlo, Consolas, monospace"
# Matched, differs and unresolved validated all-pairs (the squares touch on every side) against GitHub's #ffffff and
# #0d1117 with the dataviz skill's validate_palette.js; no candidate is an empty slot a step off the surface.
THEMES = {
    'light': {'primary': '#0b0b0b', 'secondary': '#52514e', 'muted': '#6e6d68',
              'verdict': ['#1baf7a', '#2a78d6', '#eb6834', '#e3e5e8']},
    'dark': {'primary': '#f0efec', 'secondary': '#c3c2b7', 'muted': '#9a998f',
             'verdict': ['#199e70', '#3987e5', '#d95926', '#21262d']},
}


def esc(s):
    return s.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;')


def n(x):
    return f'{x:,}'


def pct(a, b):
    return f'{100 * a / b:.1f}%' if b else '0.0%'


def f1(x):
    s = f'{x:.1f}'
    return s[:-2] if s.endswith('.0') else s


def text(x, y, s, fill, size=12, anchor='start', weight=None, family=None):
    w = f' font-weight="{weight}"' if weight else ''
    fam = f' font-family="{family}"' if family else ''
    a = f' text-anchor="{anchor}"' if anchor != 'start' else ''
    return f'<text x="{f1(x)}" y="{f1(y)}" font-size="{size}" fill="{fill}"{a}{w}{fam}>{esc(s)}</text>\n'


def svg(width, height, body, label):
    return (f'<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}" '
            f'viewBox="0 0 {width} {height}" role="img" aria-label="{esc(label)}" font-family="{FONT}">\n'
            f'<title>{esc(label)}</title>\n{body}</svg>\n')


def counts(rows):
    c = [0, 0, 0, 0]
    for r in rows:
        c[VERDICTS.index(r['verdict'])] += 1
    return c


def cells(c):
    """100 squares split between the verdicts in proportion to c, by largest remainder."""
    total = sum(c)
    if total == 0:
        return [0, 0, 0, 100]
    exact = [100 * x / total for x in c]
    out = [int(e) for e in exact]
    for k in sorted(range(4), key=lambda k: (-(exact[k] - out[k]), k))[:100 - sum(out)]:
        out[k] += 1
    return out


def waffle(x, y, c, cell, gap, t):
    """A 10 x 10 waffle at (x, y)."""
    out, i = '', 0
    for v, k in enumerate(cells(c)):
        for _ in range(k):
            cx, cy = x + (i % 10) * (cell + gap), y + (i // 10) * (cell + gap)
            out += (f'<rect x="{f1(cx)}" y="{f1(cy)}" width="{cell}" height="{cell}" rx="{f1(cell / 6)}" '
                    f'fill="{t["verdict"][v]}"/>\n')
            i += 1
    return out


def legend(x, y, t, c=None):
    out = ''
    for v, label in enumerate(LABELS):
        s = label if c is None else f'{label} {n(c[v])}'
        out += f'<rect x="{f1(x)}" y="{f1(y - 10)}" width="11" height="11" rx="2" fill="{t["verdict"][v]}"/>\n'
        out += text(x + 17, y, s, t['secondary'])
        x += 17 + 6.6 * len(s) + 22
    return out


def origins_image(module, origins, theme):
    """module: the scan's rows; origins: [(label, rows), ...]"""
    t = THEMES[theme]
    W, CARD, CELL, GAP = 800, 200, 15, 2
    c = counts(module)
    b = text(0, 18, 'Functions matched, by origin', t['primary'], size=15, weight='600')
    b += legend(0, 44, t, c)
    for k, (label, rows) in enumerate([('All functions', module)] + origins):
        x, cc = k * CARD, counts(rows)
        b += text(x, 82, label, t['primary'], size=13, weight='600')
        b += text(x, 108, pct(cc[0], sum(cc)), t['primary'], size=22, weight='600')
        b += text(x, 126, f'{n(cc[0])} / {n(sum(cc))} functions', t['secondary'])
        b += waffle(x, 140, cc, CELL, GAP, t)
    return svg(W, 140 + 10 * (CELL + GAP), b, 'Functions matched, by origin: one square per percent, coloured by verdict')


def function_image(groups, theme):
    """groups: [(component, rows), ...]: one square per function, each component on rows of its own."""
    t = THEMES[theme]
    W, CELL, GAP, LABEL, SPACE = 800, 7, 2, 22, 10
    cols = (W + GAP) // (CELL + GAP)
    every = [r for _, rows in groups for r in rows]
    c = counts(every)
    b = text(0, 18, 'Every function of TSE code', t['primary'], size=15, weight='600')
    b += text(W, 18, f'{n(c[0])} / {n(sum(c))} matched · {pct(c[0], sum(c))}', t['secondary'], size=13, anchor='end')
    b += legend(0, 44, t)
    y = 56
    for name, rows in groups:
        cc = counts(rows)
        y += SPACE + LABEL
        b += text(0, y - 8, name, t['primary'], size=12, weight='600', family=MONO)
        b += text(W, y - 8, f'{n(cc[0])} / {n(sum(cc))} · {pct(cc[0], sum(cc))}', t['secondary'], anchor='end')
        order = sorted(rows, key=lambda r: (VERDICTS.index(r['verdict']), r['index']))
        paths = ['', '', '', '']
        for i, r in enumerate(order):
            x0, y0 = (i % cols) * (CELL + GAP), y + (i // cols) * (CELL + GAP)
            paths[VERDICTS.index(r['verdict'])] += f'M{x0} {y0}h{CELL}v{CELL}h-{CELL}z'
        for v, d in enumerate(paths):
            if d:
                b += f'<path d="{d}" fill="{t["verdict"][v]}"/>\n'
        y += -(-len(rows) // cols) * (CELL + GAP) - GAP
    return svg(W, y + 2, b, 'Every function of TSE code: one square per function, coloured by verdict')


def components_image(origins, theme):
    """origins: [(label, [(component, rows), ...]), ...]: a 10 x 10 waffle per component."""
    t = THEMES[theme]
    W, PER, CELL, GAP = 800, 6, 10, 1
    CARD = W // PER
    b = text(0, 18, 'Functions matched, by component', t['primary'], size=15, weight='600')
    b += legend(0, 44, t)
    y = 56
    for label, comps in origins:
        rows = [r for _, rs in comps for r in rs]
        cc = counts(rows)
        y += 34
        b += text(0, y - 10, label, t['primary'], size=13, weight='600')
        b += text(W, y - 10, f'{n(cc[0])} / {n(sum(cc))} · {pct(cc[0], sum(cc))}', t['secondary'], anchor='end')
        for k, (name, rs) in enumerate(comps):
            x, top = (k % PER) * CARD, y + (k // PER) * 172
            c = counts(rs)
            b += text(x, top + 12, name, t['primary'], size=12, weight='600', family=MONO)
            b += text(x, top + 28, f'{pct(c[0], sum(c))} · {n(c[0])} / {n(sum(c))}', t['secondary'], size=11)
            b += waffle(x, top + 38, c, CELL, GAP, t)
        y += -(-len(comps) // PER) * 172 - 8
    return svg(W, y, b, 'Functions matched, by component: one square per percent, coloured by verdict')


def images(rows, origins):
    """The waffle files, as {path: text}. origins: [(label, [component, ...]), ...] in the status tables' order."""
    by = {}
    for r in rows:
        by.setdefault(r['group'], []).append(r)
    comps = [(label, [(c, by.get(c, [])) for c in cs]) for label, cs in origins]
    flat = [(label, [r for _, rs in cs for r in rs]) for label, cs in comps]
    out = {}
    for theme in THEMES:
        out[os.path.join(IMG, f'progress-origins-{theme}.svg')] = origins_image(rows, flat, theme)
        out[os.path.join(IMG, f'progress-tse-{theme}.svg')] = function_image(comps[0][1], theme)
        out[os.path.join(IMG, f'progress-components-{theme}.svg')] = components_image(comps, theme)
    return out
