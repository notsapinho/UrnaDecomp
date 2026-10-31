// The splat symbol maps on the real modules of this checkout: the target, the plain skeleton link, the scratch
// relink with wasm-ld's map (tools/round/link-map.sh) and the generated splat/symbol_addrs.txt.
import { existsSync, mkdtempSync, readFileSync, rmSync, writeFileSync } from 'node:fs';
import { tmpdir } from 'node:os';
import { join } from 'node:path';
import { describe, expect, it } from 'vitest';

import { type Instr, disassemble } from '../src/disasm';
import { type NormalizedFn, normalizeModule } from '../src/normalize';
import { parseModule } from '../src/parse';
import { defaultKindsPath, readOperandKinds } from '../src/splat-kinds';
import { matchesTarget, remapBody } from '../src/splat-remap';
import { attempt, readingKind, selfVoted } from '../src/splat-sub';
import {
  CALL_CTORS,
  type DataObject,
  HAND_EDIT_MARKER,
  type OurSide,
  SAME_CONTENT_LIMIT,
  type SymbolMaps,
  type TargetSide,
  cStringAt,
  castBssVotes,
  castCtorVotes,
  compareObject,
  ctorVotes,
  dataObjectAt,
  emptySymbols,
  emptyVoteBox,
  isSourceLocationRecord,
  listedVoters,
  loadOurSide,
  loadTargetSide,
  memoryImage,
  objectPattern,
  operandAnchors,
  parseLinkMap,
  parseSymbolFile,
  refuteDataNames,
  renderSymbolEntry,
  renderSymbolFile,
  resolveBytes,
  resolveDataAddress,
  readSourceLocations,
  resolveRepointed,
  rttiClassAt,
  settleAnchorVotes,
  soleFnVoters,
  soleVoters,
  srclocAnchors,
  srclocKey,
  symbolMaps,
  targetSymbolsOf,
  vtableTypeinfoOffset,
} from '../src/splat-symbols';
import { URNA_ROOT } from './helpers';

const URNA = process.env.URNA_SPLAT_ROOT ?? URNA_ROOT;
const TARGET = `${URNA}/target/vota_web_wasm.wasm`;
const PLAIN = `${URNA}/build/out/wasm/vota_web/vota_web_wasm.wasm`;
const MAP_DIR = `${URNA}/build/out/wasm-map/vota_web`;
const SYMBOLS = `${URNA}/splat/symbol_addrs.txt`;
const TWIN_DIR = `${URNA}/build/out/wasm-named/vota_web`;
const real = existsSync(`${MAP_DIR}/names.tsv`) && existsSync(SYMBOLS);

describe('parseLinkMap', () => {
  it.skipIf(!real)("reads wasm-ld's data symbols, its merged strings and the code entries in link order", () => {
    const map = parseLinkMap(readFileSync(`${MAP_DIR}/vota_web_wasm.map`, 'utf8'));
    const ours = parseModule(new Uint8Array(readFileSync(PLAIN)));
    expect(map.outputs.map((o) => o.name)).toEqual(
      expect.arrayContaining(['CODE', 'DATA', '.rodata', '.data', '.bss']),
    );
    const strings = map.data.find((d) => d.section === '<merged strings>');
    expect(strings).toMatchObject({ addr: 1024, out: '.rodata', object: '<internal>' });
    // every data symbol of the final module sits where wasm-ld put it: wasm-opt does not move data
    const { image } = memoryImage(ours);
    const ti = map.data.find((d) => d.name.startsWith('_ZTS') && d.out === '.rodata')!;
    expect(cStringAt(image, 1024, ti.addr)?.toString('latin1')).toBe(ti.name.slice(4));
    expect(map.functions.length).toBeGreaterThan(ours.funcs.length);
  });
});

describe('loadOurSide', () => {
  it.skipIf(!real)('refuses a map directory whose scratch link is not the plain module', () => {
    expect(() => loadOurSide(PLAIN, TWIN_DIR)).toThrow(/does not describe/);
  });

  it.skipIf(!real)('names every function of the plain link', () => {
    const ours = loadOurSide(PLAIN, MAP_DIR);
    expect(ours.fns.size).toBe(ours.module.funcs.length);
    expect(ours.fnByKey.get('sqlite3ErrorMsg')).toBeDefined();
    expect(ours.dataEnd + ours.stackSize).toBe(Number(ours.module.globals[0].init.split(' ')[1]));
  });
});

describe('remapBody', () => {
  const load = () => {
    const ours = loadOurSide(PLAIN, MAP_DIR);
    const target = loadTargetSide(TARGET, SYMBOLS, `${URNA}/ledger`, ours.stackSize);
    return symbolMaps(ours, target);
  };

  it.skipIf(!real)(
    're-points bodies the census paired by address into the target bodies, ambiguous constants read either way',
    () => {
      const maps = load();
      const tf = (i: number) => maps.target.module.funcs[i - maps.target.module.importedFuncCount];
      for (const name of ['sqlite3ErrorMsg', 'BN_CTX_get']) {
        const o = maps.ours.fnByKey.get(name)!;
        const t = maps.target.symbols.fns.get(name)!;
        const r = remapBody(maps, o);
        expect(r.ok).toBe(true);
        if (r.ok) {
          // BN_CTX_get's 786688 is an integer that falls inside RHVoice's unicode table: only the target decides
          expect(matchesTarget(r.pieces, tf(t).bodyBytes).match).toBe(true);
          expect(r.rewritten.func ?? 0).toBeGreaterThan(0);
        }
      }
    },
  );

  it.skipIf(!real)('reads a constant as a table slot when the target holds a function pointer there', () => {
    const maps = load();
    const o = maps.ours.fnByKey.get('__cxa_allocate_exception')!;
    const t = maps.target.symbols.fns.get('__cxa_allocate_exception')!;
    const r = remapBody(maps, o);
    expect(r.ok).toBe(true);
    if (r.ok) {
      const m = matchesTarget(r.pieces, maps.target.module.funcs[t - maps.target.module.importedFuncCount].bodyBytes);
      expect(m.match).toBe(true);
      expect(m.readings?.some((x) => x.startsWith('table slot'))).toBe(true);
    }
  });

  it.skipIf(!real)('reports a call to an import the target lacks as unresolved, naming it', () => {
    const maps = load();
    const om = maps.ours.module;
    const imports = om.imports.filter((i) => i.kind === 'func');
    const missing = imports.findIndex((i) => !maps.target.importByName.has(maps.ours.importNames[i.name] ?? i.name));
    expect(missing).toBeGreaterThanOrEqual(0);
    const caller = om.funcs.find((f) =>
      disassemble(f).some((i) => i.opcode === 0x10 && (i.imms[0] as { value: number }).value === missing),
    )!;
    const r = remapBody(maps, caller.index);
    expect(r.ok).toBe(false);
    if (!r.ok) {
      expect(r.unresolved.some((u) => /^import \S+ is not imported by the target$/.test(u.reason))).toBe(true);
    }
  });

  it.skipIf(!real)('resolves a string literal by content and a source_location record by what it records', () => {
    const maps = load();
    const strings = maps.ours.map.data.find((d) => d.section === '<merged strings>')!;
    const r = resolveDataAddress(maps.ours, maps.ourImage, maps.target, strings.addr + 0x100);
    if (r.ok) {
      const ours = cStringAt(maps.ourImage, 1024, strings.addr + 0x100)!;
      expect(cStringAt(maps.target.image, 1024, r.addr)!.equals(ours)).toBe(true);
    } else {
      expect(r.reason).toMatch(/string/);
    }
    let resolved = 0;
    let numbered = 0;
    for (const loc of maps.ours.map.data.filter(isSourceLocationRecord)) {
      const l = resolveDataAddress(maps.ours, maps.ourImage, maps.target, loc.addr + 8);
      expect(dataObjectAt(maps.ours.map.data, loc.addr + 15)?.addr).toBe(loc.addr);
      if (l.ok) {
        expect(l.how).toBe('srcloc');
        expect(srclocKey(maps.target.image, 1024, l.addr - 8)).toBe(srclocKey(maps.ourImage, 1024, loc.addr));
        resolved++;
        numbered += loc.name === '.L.constant' ? 0 : 1;
      } else if (l.same !== undefined) {
        // a right record the target holds at several addresses: each is the record, and the target body picks one
        expect(l.same.length).toBeGreaterThan(1);
        for (const a of l.same) {
          expect(srclocKey(maps.target.image, 1024, a - 8)).toBe(srclocKey(maps.ourImage, 1024, loc.addr));
        }
      } else {
        // a reconstructed unit whose line, column or function spelling is not yet the target's
        expect(l.reason).toBe('source_location not in the target');
      }
    }
    expect(resolved).toBeGreaterThan(0);
    // the second and later records of one object are .L.constant.<n>
    expect(numbered).toBeGreaterThan(0);
  });
});

// target 700 is vota::CThreadVota::StartTick with api::CTickManager::StartTick inlined, target 5447 api::CWait's ctor:
// each references a source_location record of its own, and both call the same std::format helpers
const START_TICK = '_ZN4vota11CThreadVota9StartTickEh';
const CWAIT_CTOR = '_ZN3api5CWaitC2Em';
const VFORMAT_TO =
  '_ZNSt3__28__format12__vformat_toB8ne210108INS_26basic_format_parse_contextIcEENS_20basic_format_contextINS_20back_insert_iteratorINS0_15__output_bufferIcEEEEcEEEENT0_8iteratorEOT_OSA_';
const real700 = real && existsSync(`${URNA}/src/uenux2/src/app/vota/cthreadvota.cpp`);

describe('srclocAnchors', { timeout: 180_000 }, () => {
  it.skipIf(!real700)(
    'pairs the one target function and the one of ours that reference a source_location record',
    () => {
      const ours = loadOurSide(PLAIN, MAP_DIR);
      const target = loadTargetSide(TARGET, SYMBOLS, `${URNA}/ledger`, ours.stackSize);
      const { image } = memoryImage(ours.module);
      const anchors = srclocAnchors(
        ours,
        image,
        target,
        normalizeModule(target.module, { depth: 0 }),
        normalizeModule(ours.module, { depth: 0 }),
      );
      const anchored = new Map(anchors.map(([t, o]) => [o, t]));
      expect(anchored.get(ours.fnByKey.get(START_TICK)!)).toBe(700);
      expect(anchored.get(ours.fnByKey.get(CWAIT_CTOR)!)).toBe(5447);
      // a function is anchored to one function of the other side, never two
      expect(new Set(anchors.map(([t]) => t)).size).toBe(anchors.length);
      expect(anchored.size).toBe(anchors.length);
    },
  );

  it.skipIf(!real700)('names a callee its anchored callers vote for, listing them as its voters', () => {
    const syms = targetSymbolsOf(parseSymbolFile(readFileSync(SYMBOLS, 'utf8')));
    expect(syms.fns.get(START_TICK)).toBe(700);
    expect(syms.fnEvidence.get(START_TICK)?.evidence).toBe('srcloc-anchor');
    expect(syms.fns.get(VFORMAT_TO)).toBe(146);
    expect(syms.fnEvidence.get(VFORMAT_TO)?.evidence).toBe('call');
    // every landed function that throws a formatted message votes for it too, and past the symbol file's limit no
    // voter is listed; while they are listed, the two anchored callers are among them
    const voters = soleFnVoters(syms, VFORMAT_TO);
    if (voters !== null) {
      expect(voters).toEqual(expect.arrayContaining([700, 5447]));
    }
    // the symbol file lists the voters of the names call votes give, while they are few
    expect([...syms.fnEvidence.values()].some((e) => e.evidence === 'call' && (e.voters?.length ?? 0) > 0)).toBe(true);
    // a name a seed pair voted for lists no voters
    expect(soleFnVoters(syms, '__cxa_allocate_exception')).toBeNull();
  });
});

// A header-inline throw has its record once per TU that inlines it. Whichever keys our link holds, these cases make
// target 700's record such a one: they edit a copy of the target's image, and the ledger's rows read it as
// loadTargetSide does. 1108468 and 1110696 are the ledger's first two records, lower than 700's and in no function
// these cases re-point.
const RECORDS = `${URNA}/ledger/source-locations.tsv`;
const GET_KEY_RECORDS = [1538968, 1547328, 1580692, 1593104];

describe('a source_location record the target holds more than once', { timeout: 180_000 }, () => {
  const load = () => {
    const ours = loadOurSide(PLAIN, MAP_DIR);
    const target = loadTargetSide(TARGET, SYMBOLS, `${URNA}/ledger`, ours.stackSize);
    const kinds = readOperandKinds(defaultKindsPath(PLAIN), new Uint8Array(readFileSync(PLAIN)));
    const maps = symbolMaps(ours, target, kinds);
    const index = ours.fnByKey.get(START_TICK)!;
    const record = disassemble(ours.module.funcs[index - ours.module.importedFuncCount])
      .flatMap((i) => (i.opcode === 0x41 && i.imms[0]?.kind === 's32' ? [i.imms[0].value] : []))
      .map((v) => (v >= 1024 && v < ours.dataEnd ? dataObjectAt(ours.map.data, v) : null))
      .find((d) => d !== null && isSourceLocationRecord(d))!;
    const held = resolveDataAddress(ours, maps.ourImage, target, record.addr);
    if (!held.ok) {
      throw new Error(`target 700's record: ${held.reason}`);
    }
    const tm = target.module;
    return {
      maps,
      record,
      /** where the target holds target 700's record: the operand its body loads */
      own: held.addr,
      body: tm.funcs[700 - tm.importedFuncCount].bodyBytes,
      candidate: { ours: index, symbol: START_TICK, source: 'symbol' as const },
    };
  };

  /** `maps` with `edit` applied to a copy of the target's image, the ledger's rows read over it. */
  const edited = (maps: SymbolMaps, edit: (image: Buffer) => void): SymbolMaps => {
    const image = Buffer.from(maps.target.image);
    edit(image);
    const srcloc = readSourceLocations(RECORDS, image, maps.target.imageBase);
    return { ...maps, target: { ...maps.target, image, srcloc } };
  };
  const copyTo = (image: Buffer, from: number, to: number): void => {
    image.copy(image, to - 1024, from - 1024, from - 1024 + 16);
  };
  /** Another line in the record at `at`: the key it held is no longer there. */
  const moveLine = (image: Buffer, at: number): void => {
    image.writeUInt32LE(image.readUInt32LE(at - 1024 + 8) + 1, at - 1024 + 8);
  };

  it('keeps every address of a key, the ten keys the target holds more than once among them', () => {
    const target = loadTargetSide(TARGET, null, `${URNA}/ledger`);
    expect(target.srcloc.get(srclocKey(target.image, 1024, GET_KEY_RECORDS[0])!)).toEqual(GET_KEY_RECORDS);
    expect(target.srcloc.get(srclocKey(target.image, 1024, 1110696)!)).toEqual([1110696]);
    const held = [...target.srcloc.values()].filter((a) => a.length > 1);
    expect(held.length).toBe(10);
    expect(held.flat().length).toBe(106);
  });

  it('reads a row twice as one address', () => {
    const dir = mkdtempSync(join(tmpdir(), 'srcloc-'));
    const target = loadTargetSide(TARGET, null);
    const rows = `loc_addr\tfile\n${GET_KEY_RECORDS[0]}\ta\n${GET_KEY_RECORDS[0]}\ta\n`;
    writeFileSync(join(dir, 'source-locations.tsv'), rows);
    const out = readSourceLocations(join(dir, 'source-locations.tsv'), target.image, target.imageBase);
    expect([...out.values()]).toEqual([[GET_KEY_RECORDS[0]]]);
    rmSync(dir, { recursive: true });
  });

  it.skipIf(!real700)('offers every address, and the match takes the one the target body holds', () => {
    const { maps, record, own, body, candidate } = load();
    const held = edited(maps, (image) => copyTo(image, own, 1108468));
    const r = resolveDataAddress(held.ours, held.ourImage, held.target, record.addr);
    expect(r).toMatchObject({ ok: false, same: [1108468, own] });
    // a byte inside the record, as an operand can point at
    expect(resolveDataAddress(held.ours, held.ourImage, held.target, record.addr + 8).same).toEqual([
      1108468 + 8,
      own + 8,
    ]);
    const a = attempt(held, candidate, 700, body);
    expect(a.verdict).toBe('match');
    expect(a.verdict === 'match' && Buffer.from(a.bytes).equals(Buffer.from(body))).toBe(true);
    const copy = a.verdict === 'match' ? a.chosen.filter((c) => c.reading.startsWith('address same-content')) : [];
    // the target's own address, not the first reading; on the meter it is "which copy", never "re-pointing alone"
    expect(copy.map((c) => c.reading)).toEqual([`address same-content 0x${own.toString(16)}`]);
    expect(copy[0].preferred).toBe(false);
    expect(readingKind(copy[0].reading)).toBe('copy');
  });

  it.skipIf(!real700)('fails a function whose key the target holds, but not at the address its body loads', () => {
    const { maps, own, body, candidate } = load();
    const held = edited(maps, (image) => {
      copyTo(image, own, 1108468);
      copyTo(image, own, 1110696);
      moveLine(image, own);
    });
    const a = attempt(held, candidate, 700, body);
    expect(a.verdict).toBe('differs');
    expect(a.verdict === 'differs' && a.detail).toMatch(/: source_location record occurs 2 times in the target\]$/);
  });

  // passes on the code before readings too: that path did not change, and no reading may reach it
  it.skipIf(!real700)('fails a function loading a key the target does not hold', () => {
    const { maps, own, body, candidate } = load();
    const a = attempt(edited(maps, (image) => moveLine(image, own)), candidate, 700, body);
    expect(a.verdict).toBe('unresolved');
    expect(a.verdict === 'unresolved' && a.detail).toMatch(/an address of ours: source_location not in the target$/);
  });

  // passes on the code before readings too: a held record never named anything, and readings must not start to
  it.skipIf(!real700)('names nothing: no anchor, and no name for the self-vote rule to hold', () => {
    const { maps, own, body, candidate } = load();
    // the copy lies above 700's record, in a function these cases do not re-point: with it below, this case passes even
    // with the anchor rule broken
    const held = edited(maps, (image) => copyTo(image, own, 1601348));
    const anchored = (m: SymbolMaps): number[] =>
      srclocAnchors(
        m.ours,
        m.ourImage,
        m.target,
        normalizeModule(m.target.module, { depth: 0 }),
        normalizeModule(m.ours.module, { depth: 0 }),
      )
        .filter(([t]) => t === 700)
        .map(([, o]) => o);
    expect(anchored(maps)).toEqual([candidate.ours]);
    expect(anchored(held)).toEqual([]);
    // the reading is a copy of bytes, not a name a vote gave: the self-vote rule has nothing to ask of it
    const a = attempt(held, candidate, 700, body);
    const chosen = a.verdict === 'match' ? a.chosen.filter((c) => c.reading.startsWith('address same-content')) : [];
    expect(chosen.length).toBe(1);
    expect(selfVoted(held, new Map([[700, { chosen }]])).size).toBe(0);
  });

  it.skipIf(!real)('gives no such record a symbol line', () => {
    const target = loadTargetSide(TARGET, SYMBOLS, `${URNA}/ledger`);
    const places = new Set([...target.srcloc.values()].filter((a) => a.length > 1).flat());
    const named = [...target.symbols.data].filter(([name]) => name.startsWith('srcloc.')).map(([, addr]) => addr);
    expect(named.length).toBeGreaterThan(0);
    expect(named.filter((a) => places.has(a))).toEqual([]);
  });
});

// target 0x18336c is api::AudioCollector's vtable; our ASN1 OBJECT_IDENTIFIER destructors have the shape of its
// destructors, so aligning them votes OBJECT_IDENTIFIER's vtable onto it
const AUDIO_COLLECTOR_VTABLE = 0x18336c;
const OID_VTABLE = '_ZTVN4ASN117OBJECT_IDENTIFIERE';
const STRINGSTREAM = 'NSt3__218basic_stringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE';

describe('operandAnchors', () => {
  const fn = (index: number, shape: string, ...consts: number[]): NormalizedFn =>
    ({
      index,
      shape,
      instrs: consts.map((value) => ({ opcode: 0x41, imms: [{ kind: 's32', value }] })),
    }) as unknown as NormalizedFn;
  const places = new Set([5000]);
  const read = (v: number): number | null => (v === 1500 ? 5000 : null);

  it('pairs the one holder on each side, whatever their shapes', () => {
    expect(operandAnchors([fn(7, 'a', 5000)], [fn(70, 'b', 1500)], places, read)).toEqual([[7, 70]]);
  });

  it('asks for one holder on each side unless told to read shapes', () => {
    const tn = [fn(7, 'a', 5000), fn(8, 'b', 5000)];
    const on = [fn(70, 'a', 1500)];
    expect(operandAnchors(tn, on, places, read)).toEqual([]);
    expect(operandAnchors(tn, on, places, read, true)).toEqual([[7, 70]]);
  });

  it('anchors nothing when two pairs of holders have one shape', () => {
    const tn = [fn(7, 'a', 5000), fn(8, 'a', 5000)];
    expect(operandAnchors(tn, [fn(70, 'a', 1500)], places, read, true)).toEqual([]);
  });

  it('anchors nothing to two functions of the other side', () => {
    const more = new Set([5000, 5004]);
    const both = (v: number): number | null => (v === 1500 ? 5000 : v === 1504 ? 5004 : null);
    const tn = [fn(7, 'a', 5000), fn(8, 'b', 5004)];
    expect(operandAnchors(tn, [fn(70, 'c', 1500, 1504)], more, both)).toEqual([]);
  });

  it.skipIf(!real)('agrees with the match list wherever a vptr or a table anchors a function', () => {
    const matched = new Map(
      readFileSync(`${URNA}/splat/matched.txt`, 'latin1')
        .split('\n')
        .filter((l) => l !== '' && !l.startsWith('#'))
        .map((l) => [Number(l.split(' ')[0]), l.split(' ')[1].split('@')[0]]),
    );
    const anchored = parseSymbolFile(readFileSync(SYMBOLS, 'utf8')).generated.filter(
      (e) => e.at.kind === 'func' && /^(vptr|content)-anchor$/.test(e.evidence),
    );
    const checked = anchored.filter((e) => matched.has((e.at as { index: number }).index));
    expect(checked.length).toBeGreaterThan(300);
    const named = (e: { name: string }): string => e.name.split('@')[0];
    expect(checked.filter((e) => matched.get((e.at as { index: number }).index) !== named(e))).toEqual([]);
  });
});

describe('settleAnchorVotes', () => {
  /** A call vote our `o` gets for target `t`, cast by target function `by`. */
  const vote = (box: ReturnType<typeof emptyVoteBox>, o: number, t: number, by: number): void => {
    const places = box.fn.get(o) ?? box.fn.set(o, new Map()).get(o)!;
    places.set(t, (places.get(t) ?? 0) + 1);
    (box.fnVoters.get(o) ?? box.fnVoters.set(o, new Set()).get(o)!).add(by);
  };
  const state = () => ({
    votes: emptyVoteBox(),
    anchorVotes: emptyVoteBox(),
    pairOf: new Map<number, number>(),
    namedT: new Set<number>(),
    anchoredT: new Set<number>(),
    evidence: new Map<number, string>(),
  });

  it('lets a function the votes name vote in turn, down a chain of callees', () => {
    const s = state();
    vote(s.anchorVotes, 1, 100, 900);
    const next = new Map([
      [100, () => vote(s.anchorVotes, 2, 200, 100)],
      [200, () => vote(s.anchorVotes, 3, 300, 200)],
    ]);
    const n = settleAnchorVotes(s, () => true, (t) => {
      next.get(t)?.();
      return next.has(t);
    });
    expect([...s.pairOf]).toEqual([
      [1, 100],
      [2, 200],
      [3, 300],
    ]);
    expect(n).toBe(3);
    expect([...s.anchoredT]).toEqual([100, 200]);
  });

  it('names no function across signatures, so its chain stops there', () => {
    const s = state();
    vote(s.anchorVotes, 1, 100, 900);
    const align = (): boolean => {
      vote(s.anchorVotes, 2, 200, 100);
      return true;
    };
    expect(settleAnchorVotes(s, (o) => o !== 1, align)).toBe(0);
    expect(s.pairOf.size).toBe(0);
    expect(s.namedT.size).toBe(0);
  });

  it('leaves a function the seed pairs reach, and an index already named, alone', () => {
    const s = state();
    vote(s.anchorVotes, 1, 100, 900);
    vote(s.votes, 1, 100, 800);
    vote(s.anchorVotes, 2, 200, 900);
    s.namedT.add(200);
    expect(settleAnchorVotes(s, () => true, () => false)).toBe(0);
  });

  // the order the two calls take is the order a Map yields: find, ours 452, is named 305 or not by it alone
  it.each([
    ['named before the vote against it', [5, 1]],
    ['named after it', [1, 5]],
  ])('drops a name a later vote contradicts: %s', (_, order) => {
    const s = state();
    for (const o of order) {
      vote(s.anchorVotes, o, o * 100, 900);
    }
    const n = settleAnchorVotes(s, () => true, (t) => {
      if (t === 100) {
        vote(s.anchorVotes, 5, 600, 100);
      }
      return t === 100;
    });
    expect(s.pairOf.has(5)).toBe(false);
    expect(s.namedT.has(500)).toBe(false);
    expect(s.evidence.has(5)).toBe(false);
    expect(n).toBe(1);
  });

  it('gives the index of a dropped name to the function it blocked', () => {
    const s = state();
    vote(s.anchorVotes, 5, 500, 900);
    vote(s.anchorVotes, 6, 500, 900);
    vote(s.anchorVotes, 1, 100, 900);
    settleAnchorVotes(s, () => true, (t) => {
      if (t === 100) {
        vote(s.anchorVotes, 5, 600, 100);
      }
      return t === 100;
    });
    expect(s.pairOf.get(6)).toBe(500);
    expect(s.pairOf.has(5)).toBe(false);
  });

  it('takes a dropped name off the voters of the rest', () => {
    const s = state();
    vote(s.anchorVotes, 5, 500, 900);
    vote(s.anchorVotes, 1, 100, 900);
    settleAnchorVotes(s, () => true, (t) => {
      if (t === 500) {
        vote(s.anchorVotes, 7, 700, 500);
      } else if (t === 100) {
        vote(s.anchorVotes, 5, 600, 100);
      }
      return t === 500 || t === 100;
    });
    expect(s.pairOf.has(5)).toBe(false);
    expect([...(s.anchorVotes.fnVoters.get(7) ?? [])]).toEqual([]);
  });

  it('reads call or table from the final votes, not from the first', () => {
    const s = state();
    const table = (o: number, t: number, by: number): void => {
      s.anchorVotes.table.set(o, new Map([[t, 1]]));
      s.anchorVotes.fnVoters.set(o, new Set([by]));
    };
    table(5, 500, 900);
    vote(s.anchorVotes, 1, 100, 900);
    table(8, 800, 900);
    settleAnchorVotes(s, () => true, (t) => {
      if (t === 100) {
        vote(s.anchorVotes, 5, 500, 100);
      }
      return t === 100;
    });
    expect(s.evidence.get(5)).toBe('call');
    expect(s.evidence.get(8)).toBe('table');
  });
});

describe('the hand line of CPolySingletonList::find', () => {
  const FIND =
    '_ZN3api18CPolySingletonList4findIKNS_19TPolySingletonsInfoEEEDaRKNSt3__212basic_stringIcNS4_11char_traitsIcEENS4_9allocatorIcEEEERT_';

  it('names 305 below the marker, and no generated line names it: votes for 305 and 608 disagree', () => {
    const file = parseSymbolFile(readFileSync(SYMBOLS, 'utf8'));
    expect(file.generated.filter((e) => e.name === FIND)).toEqual([]);
    expect(file.hand.filter((e) => e.name === FIND)).toMatchObject([
      { at: { kind: 'func', index: 305 }, evidence: 'callers+content' },
    ]);
  });
});

describe('listedVoters', () => {
  const anchored = new Set([1522, 5157, 9028, 1, 2, 3, 4, 5]);

  it('leaves a recursive function out of its own by: list', () => {
    expect(listedVoters([1522, 5157], 1522, anchored)).toEqual([5157]);
    expect(listedVoters([1522], 1522, anchored)).toBeUndefined();
  });

  it('lists a caller alone on a recursive callee, so that §3 sees it alone', () => {
    const syms = { ...emptySymbols(), fnEvidence: new Map([['f', { evidence: 'call', voters: [5157] }]]) };
    expect(listedVoters([1522, 5157], 1522, anchored)).toEqual(soleFnVoters(syms, 'f'));
  });

  it('lists only anchored voters, sorted, and at most four', () => {
    expect(listedVoters([4, 2], 1522, anchored)).toEqual([2, 4]);
    expect(listedVoters([4, 77], 1522, anchored)).toBeUndefined();
    expect(listedVoters([1, 2, 3, 4, 5], 1522, anchored)).toBeUndefined();
    expect(listedVoters([1, 2, 3, 4, 1522], 1522, anchored)).toEqual([1, 2, 3, 4]);
  });
});

describe('castBssVotes', () => {
  const object = (key: string, out: string): DataObject => ({
    addr: 2000,
    size: 12,
    key,
    name: key,
    object: 'o',
    section: `${out}.${key}`,
    out,
  });
  const objects = new Map([
    ['X', object('X', '.bss')],
    ['R', object('R', '.rodata')],
    ['D', object('D', '.data')],
  ]);
  const from = (): ReturnType<typeof emptyVoteBox> => {
    const box = emptyVoteBox();
    for (const key of ['X', 'R', 'D', 'gone']) {
      box.data.set(key, new Map([[3100, 2]]));
      box.voters.set(key, new Set([9148]));
    }
    return box;
  };

  it('takes .bss objects alone: a name for read-only or .data content would hide its copies', () => {
    const votes = emptyVoteBox();
    expect(castBssVotes(votes, from(), objects)).toBe(1);
    expect([...votes.data.keys()]).toEqual(['X']);
    expect([...votes.data.get('X')!]).toEqual([[3100, 2]]);
    expect([...votes.voters.get('X')!]).toEqual([9148]);
  });

  it('adds to what the pairs voted, and counts only what they did not', () => {
    const votes = emptyVoteBox();
    votes.data.set('X', new Map([[3100, 1]]));
    votes.voters.set('X', new Set([137]));
    expect(castBssVotes(votes, from(), objects)).toBe(0);
    expect([...votes.data.get('X')!]).toEqual([[3100, 3]]);
    expect([...votes.voters.get('X')!].sort((a, b) => a - b)).toEqual([137, 9148]);
  });
});

describe('castCtorVotes', () => {
  it('casts its votes by __wasm_call_ctors, which is what §3 reads', () => {
    const votes = emptyVoteBox();
    expect([...castCtorVotes(votes, new Map([['X', new Set([3100])]]), 14478)]).toEqual(['X']);
    expect([...votes.data.get('X')!]).toEqual([[3100, 1]]);
    expect([...votes.voters.get('X')!]).toEqual([14478]);
  });

  it('adds to a name another pair voted for, which stays a vote', () => {
    const votes = emptyVoteBox();
    votes.data.set('X', new Map([[3100, 2]]));
    votes.voters.set('X', new Set([9148]));
    expect(castCtorVotes(votes, new Map([['X', new Set([3100])]]), 14478).size).toBe(0);
    expect([...votes.voters.get('X')!].sort((a, b) => a - b)).toEqual([9148, 14478]);
  });

  it('leaves two places in the votes, so the name conflicts', () => {
    const votes = emptyVoteBox();
    castCtorVotes(votes, new Map([['X', new Set([3100, 3200])]]), 14478);
    expect(votes.data.get('X')!.size).toBe(2);
  });
});

describe('ctorVotes', () => {
  // ours: strings from 1024, .bss from 2000. The target: strings from 1024 at another offset, .bss from 3000.
  const row = (opcode: number, name: string, imms: Instr['imms']): Instr => ({ offset: 0, end: 0, opcode, name, imms });
  const i32 = (value: number): Instr => row(0x41, 'i32.const', [{ kind: 's32', value, at: 0, role: 's32' }]);
  const i64 = (value: bigint): Instr => row(0x42, 'i64.const', [{ kind: 's64', value, at: 0, role: 's64' }]);
  const call = (value: number): Instr => row(0x10, 'call', [{ kind: 'u32', value, at: 0, role: 'func' }]);
  const local = (value: number): Instr => row(0x20, 'local.get', [{ kind: 'u32', value, at: 0, role: 'local' }]);
  const memarg = (offset: number) => [{ kind: 'memarg', align: 0, offset, memory: 0, at: 0, offsetAt: 0, role: 'memarg' }];
  const load = (offset = 0): Instr => row(0x29, 'i64.load', memarg(offset) as Instr['imms']);
  const store = (offset = 0): Instr => row(0x37, 'i64.store', memarg(offset) as Instr['imms']);
  const prologue = row(0x23, 'global.get', [{ kind: 'u32', value: 0, at: 0, role: 'global' }]);
  const CAP = -9223371865056083936n;
  /** std::string X = <the two chunks at `head` and `head + 8`>, built in place as clang inlines it */
  const build = (x: number, head: number, l = 0, malloc = 1): Instr[] => [
    i32(x),
    i32(32),
    call(malloc),
    i32(x + 4),
    i64(CAP),
    store(),
    local(l),
    i32(head + 8),
    load(),
    store(8),
    local(l),
    i32(head),
    load(),
    store(),
  ];
  const STRINGS = ['first static string!', 'other static string!', 'xxxxxxxxtatic string!', 'twice static string!'];
  const image = (texts: string[], pad: number): Buffer =>
    Buffer.concat([Buffer.alloc(pad, 1), Buffer.from(`\0${texts.join('\0')}\0`, 'latin1')]);
  const object = (key: string, addr: number): DataObject => ({
    addr,
    size: 12,
    key,
    name: key,
    object: 'o',
    section: `.bss.${key}`,
    out: '.bss',
  });
  const ourImage = image(STRINGS, 0);
  const at = (text: string, img = ourImage, base = 1024): number => base + img.indexOf(`\0${text}\0`) + 1;
  const ours = {
    map: {
      data: [
        {
          addr: 1024,
          size: ourImage.length,
          key: 'strs',
          name: 'strs',
          object: '<internal>',
          section: '<merged strings>',
          out: '.rodata',
        },
        object('X', 2000),
        object('Y', 2012),
      ],
    },
    dataEnd: 3000,
    elem: new Map(),
  } as unknown as OurSide;
  const sideOf = (texts: string[]): TargetSide =>
    ({
      image: image(texts, 40),
      imageBase: 1024,
      dataEnd: 4000,
      elem: new Map(),
      symbols: emptySymbols(),
      srcloc: new Map(),
    }) as unknown as TargetSide;
  const votes = (oi: Instr[], side: TargetSide, ti: Instr[]): Record<string, number[]> =>
    Object.fromEntries(
      [...ctorVotes(ours, ourImage, side, oi, ti, () => true)].map(([k, v]) => [k, [...v]]),
    );
  const first = at(STRINGS[0]);

  it("votes an object's address from a run the target's body holds, whatever the locals", () => {
    const side = sideOf(STRINGS);
    const ti = [i32(9), ...build(3100, at(STRINGS[0], side.image), 3)];
    expect(votes(build(2000, first), side, ti)).toEqual({ X: [3100] });
  });

  it("votes nothing for a run that shares only its string's tail with the target's", () => {
    // the target's literal ends like ours and starts otherwise: the last chunk fits, the first cannot
    const side = sideOf(['first static string!'.replace('first', 'FIRST')]);
    const tail = side.image.indexOf('tatic string!');
    const ti = build(3100, 1024 + tail - 7);
    expect(votes(build(2000, first), side, ti)).toEqual({});
  });

  it('votes nothing for a literal two statics of the target build: it tells neither from the other', () => {
    const side = sideOf(STRINGS);
    const head = at(STRINGS[0], side.image);
    expect(votes(build(2000, first), side, [...build(3100, head), ...build(3200, head)])).toEqual({});
  });

  it('drops both objects of ours built alike at one target address', () => {
    const side = sideOf(STRINGS);
    const ti = build(3100, at(STRINGS[0], side.image));
    expect(votes([...build(2000, first), ...build(2012, first)], side, ti)).toEqual({});
  });

  it('ends a run at the next prologue: a telling row of the next initialiser does not break it', () => {
    const side = sideOf(STRINGS);
    const ti = [
      ...build(3100, at(STRINGS[0], side.image)),
      i32(7),
      ...build(3200, at(STRINGS[1], side.image)),
    ];
    const oi = [...build(2000, first), prologue, ...build(2012, at(STRINGS[1]))];
    expect(votes(oi, side, ti)).toEqual({ X: [3100], Y: [3200] });
  });

  it('does not read a table slot after the last telling row as a chunk of a string', () => {
    // the slot's number is an address inside the strings; a function pointer the two tables number otherwise
    const slot = first + 3;
    const withSlot = { ...ours, elem: new Map([[slot, 200]]) } as unknown as OurSide;
    const side = { ...sideOf(STRINGS), elem: new Map([[7, 100]]) } as unknown as TargetSide;
    const run = build(2000, first);
    const ti = [...build(3100, at(STRINGS[0], side.image)), i32(5000)];
    const placed = ctorVotes(withSlot, ourImage, side, [...run, i32(slot)], ti, () => true);
    expect([...placed.get('X')!]).toEqual([3100]);
  });

  it('votes nothing for a run whose address is not in the target .bss', () => {
    const side = sideOf(STRINGS);
    const inData = side.imageBase + 4;
    expect(votes(build(2000, first), side, build(inData, at(STRINGS[0], side.image)))).toEqual({});
  });

  it.skipIf(!real)('reads the .bss places of the real bodies: one object, one place, and the hand-checked ones', () => {
    const om = loadOurSide(PLAIN, MAP_DIR);
    const side = loadTargetSide(TARGET, null, `${URNA}/ledger`, om.stackSize);
    const body = (m: typeof om.module, index: number) => disassemble(m.funcs[index - m.importedFuncCount]);
    const ctorsT = targetSymbolsOf(parseSymbolFile(readFileSync(SYMBOLS, 'utf8'))).fns.get(CALL_CTORS)!;
    const placed = ctorVotes(
      om,
      memoryImage(om.module).image,
      side,
      body(om.module, om.fnByKey.get(CALL_CTORS)!),
      body(side.module, ctorsT),
      () => true,
    );
    expect(placed.size).toBeGreaterThan(25);
    for (const addrs of placed.values()) {
      expect(addrs.size).toBe(1);
    }
    // the hand edit's address, read from the same body by hand: 14478 builds it from " bad end of stream"
    expect([...placed.get('_ZN4ASN1L14badEndOfStreamE')!]).toEqual([1914448]);
    // an object the census cannot name: its 36-B destructor reads this address + 11 and loads nothing else
    expect([...placed.get('_ZN9CBaseTypeItLt0ELt99ELi10EE4NOMEE')!]).toEqual([0x1d2cd0]);
  });
});

describe('refuteDataNames', () => {
  const load = () => {
    const ours = loadOurSide(PLAIN, MAP_DIR);
    return symbolMaps(ours, loadTargetSide(TARGET, SYMBOLS, `${URNA}/ledger`, ours.stackSize));
  };

  it.skipIf(!real)('drops an RTTI name whose target bytes describe another class', () => {
    const { ours, ourImage, target } = load();
    expect(rttiClassAt(target.image, target.imageBase, OID_VTABLE, AUDIO_COLLECTOR_VTABLE)).toBe(
      'N3api14AudioCollectorE',
    );
    const names = new Map([
      ['_ZTVN3api14AudioCollectorE', { addr: AUDIO_COLLECTOR_VTABLE, evidence: 'rtti' }],
      [OID_VTABLE, { addr: AUDIO_COLLECTOR_VTABLE, evidence: 'vote:2', voters: [10822, 10840] }],
    ]);
    const stats = refuteDataNames(ours, ourImage, target, new Map(), names);
    expect([...names.keys()]).toEqual(['_ZTVN3api14AudioCollectorE']);
    expect(stats.rttiRefuted).toBe(1);
  });

  it.skipIf(!real)('drops a voted name that shares its target address with another object of ours', () => {
    const { ours, ourImage, target } = load();
    const names = new Map([
      ['_ZTVN3api14AudioCollectorE', { addr: AUDIO_COLLECTOR_VTABLE, evidence: 'rtti' }],
      // stdout's one word points at __stdout_FILE, which has no target name: its bytes cannot refute it
      ['stdout', { addr: AUDIO_COLLECTOR_VTABLE, evidence: 'vote:1', voters: [394] }],
    ]);
    const stats = refuteDataNames(ours, ourImage, target, new Map(), names);
    expect([...names.keys()]).toEqual(['_ZTVN3api14AudioCollectorE']);
    expect(stats).toMatchObject({ voteBytesRefuted: 0, placeRefuted: 1 });
    // two names of ours with the same bytes may share a place: K256 and SHA256_K_ARRAY are the same table
    const same = new Map([
      ['K256', { addr: 0x164290, evidence: 'vote:8' }],
      ['SHA256_K_ARRAY', { addr: 0x164290, evidence: 'content' }],
    ]);
    refuteDataNames(ours, ourImage, target, new Map(), same);
    expect(same.size).toBe(2);
  });

  it.skipIf(!real)('keeps the generated symbol file free of the class the target does not have', () => {
    const syms = targetSymbolsOf(parseSymbolFile(readFileSync(SYMBOLS, 'utf8')));
    expect(syms.data.has(OID_VTABLE)).toBe(false);
    expect(syms.data.get('_ZTVN3api14AudioCollectorE')).toBe(AUDIO_COLLECTOR_VTABLE);
  });
});

describe('vtableTypeinfoOffset', () => {
  it.skipIf(!real)("places a vtable with virtual bases at its first offset word, ahead of the ledger's", () => {
    const ours = loadOurSide(PLAIN, MAP_DIR);
    const { image } = memoryImage(ours.module);
    const byKey = new Map(ours.map.data.map((d) => [d.key, d]));
    expect(vtableTypeinfoOffset(byKey, image, `_ZTV${STRINGSTREAM}`)).toBe(8);
    expect(vtableTypeinfoOffset(byKey, image, '_ZTVN3api14AudioCollectorE')).toBe(4);
    // ledger/vtables.json gives the primary table's offset-to-top word, 0x13c48c
    const syms = targetSymbolsOf(parseSymbolFile(readFileSync(SYMBOLS, 'utf8')));
    expect(syms.data.get(`_ZTV${STRINGSTREAM}`)).toBe(0x13c488);
  });
});

describe('compareObject', () => {
  it.skipIf(!real)('compares an object word by word, re-pointing our pointers, and says when it cannot tell', () => {
    const ours = loadOurSide(PLAIN, MAP_DIR);
    const maps = symbolMaps(ours, loadTargetSide(TARGET, SYMBOLS, `${URNA}/ledger`, ours.stackSize));
    const obj = (key: string) => maps.ours.map.data.find((d) => d.key === key)!;
    // an EVP_CIPHER: integers, then function pointers (table slots that also look like data addresses)
    expect(compareObject(maps, obj('aes_128_cbc'), maps.target.symbols.data.get('aes_128_cbc')!).verdict).toBe(
      'agrees',
    );
    // OID's vtable never agrees with AudioCollector's; whether a word proves it depends on where our link puts its
    // strings, since a table slot of ours can also be the address of one of them
    expect(compareObject(maps, obj(OID_VTABLE), AUDIO_COLLECTOR_VTABLE).verdict).not.toBe('agrees');
    // a .bss object is zeros on both sides
    expect(
      compareObject(maps, obj('__cxa_new_handler'), maps.target.symbols.data.get('__cxa_new_handler')!).verdict,
    ).toBe('unknown');
  });
});

describe('resolveRepointed', { timeout: 180_000 }, () => {
  const load = () => {
    const ours = loadOurSide(PLAIN, MAP_DIR);
    return symbolMaps(ours, loadTargetSide(TARGET, SYMBOLS, `${URNA}/ledger`, ours.stackSize));
  };
  const obj = (maps: ReturnType<typeof load>, key: string) => maps.ours.map.data.find((d) => d.key === key)!;

  it.skipIf(!real)('places a .data object the symbol file does not name by its bytes, its pointers re-pointed', () => {
    // CMAC's OSSL_PARAM table: string pointers, small integers, NULLs and -1 sizes
    const maps = load();
    const o = obj(maps, 'cmac_gettable_params.gettable_params');
    expect(maps.target.symbols.data.has(o.key)).toBe(false);
    const r = resolveRepointed(maps, o);
    expect(r).toMatchObject({ ok: true, how: 'content-repointed' });
    if (r.ok) {
      const p = objectPattern(maps, o);
      const at = r.addr - maps.target.imageBase;
      expect(p.words.every((w) => w.values.includes(maps.target.image.readUInt32LE(at + w.at)))).toBe(true);
      expect(p.fixed.every((b, k) => b === null || maps.target.image[at + k] === b)).toBe(true);
      expect(compareObject(maps, o, r.addr).verdict).not.toBe('differs');
      // an address inside the object lands at the same offset inside the target's
      const inside = resolveDataAddress(maps.ours, maps.ourImage, maps.target, o.addr + 20);
      expect(inside).toMatchObject({ ok: true, addr: r.addr + 20, how: 'content-repointed' });
    }
  });

  it.skipIf(!real)('offers every place of read-only content it finds more than once, for the body to pick', () => {
    // boost's bad_weekday typeinfo: the target holds three objects with these words
    const maps = load();
    const o = obj(maps, '_ZTIN5boost9gregorian11bad_weekdayE');
    expect(o.section.startsWith('.data.rel.ro')).toBe(true);
    const r = resolveDataAddress(maps.ours, maps.ourImage, maps.target, o.addr);
    expect(r.ok).toBe(false);
    expect(r.same?.length).toBeGreaterThan(1);
  });

  it.skipIf(!real)('does not offer the places of a writable object it finds more than once', () => {
    const maps = load();
    const o = obj(maps, '_ZN21ModuloInformacaoMidia15InformacaoMidia8fieldIdsE');
    expect(o.section.startsWith('.data.rel.ro')).toBe(false);
    expect(resolveRepointed(maps, o).same?.length).toBeGreaterThan(1);
    expect(resolveDataAddress(maps.ours, maps.ourImage, maps.target, o.addr).same).toBeUndefined();
  });
});

describe('resolveBytes', () => {
  // two images from address 1024, and an object of ours that our link happens to put at a multiple of 4
  const images = () => {
    const ourImage = Buffer.alloc(64);
    const image = Buffer.alloc(64);
    const target = { image, imageBase: 1024 } as unknown as TargetSide;
    const object = (name: string, addr: number, bytes: Buffer): DataObject => {
      bytes.copy(ourImage, addr - 1024);
      return { addr, size: bytes.length, key: name, name, object: 'a.o', section: `.rodata.${name}`, out: '.rodata' };
    };
    return { ourImage, image, target, object };
  };

  it("finds a typeinfo name at the target's odd address when ours is a multiple of 4", () => {
    const { ourImage, image, target, object } = images();
    const name = Buffer.from('N3api5CFooE\0', 'latin1');
    const zts = object('_ZTSN3api5CFooE', 1032, name);
    name.copy(image, 1045 - 1024);
    expect(resolveBytes(ourImage, target, zts)).toEqual({ ok: true, addr: 1045, how: 'content' });
  });

  it('searches any other object at a multiple of 4 only there: a constant also occurs at an odd offset', () => {
    // OpenSSL's default_iv, eight 0xa6 bytes, sits in a run of nine in the target
    const { ourImage, image, target, object } = images();
    const iv = object('default_iv', 1048, Buffer.alloc(8, 0xa6));
    image.fill(0xa6, 1064 - 1024, 1073 - 1024);
    expect(resolveBytes(ourImage, target, iv)).toEqual({ ok: true, addr: 1064, how: 'content' });
  });
});

describe('resolveDataAddress on a short string', { timeout: 180_000 }, () => {
  it.skipIf(!real)('offers every place the target holds the same C string, past the limit for other content', () => {
    // our " \t\r\n" is once in the target, and its tail "\n" is in hundreds of places: the target's ffc_params
    // printer loads the "\n" that ends "UE DE {}\n\n"
    const ours = loadOurSide(PLAIN, MAP_DIR);
    const maps = symbolMaps(ours, loadTargetSide(TARGET, SYMBOLS, `${URNA}/ledger`, ours.stackSize));
    const ws = maps.ourImage.indexOf(Buffer.from('\0 \t\r\n\0', 'latin1'));
    expect(ws).toBeGreaterThan(0);
    const newline = 1024 + ws + 4;
    const used = maps.target.imageBase + maps.target.image.indexOf(Buffer.from('UE DE {}\n\n\0', 'latin1')) + 9;
    const r = resolveDataAddress(maps.ours, maps.ourImage, maps.target, newline);
    expect(r.ok).toBe(true);
    expect(r.same?.length).toBeGreaterThan(SAME_CONTENT_LIMIT);
    expect(r.same).toContain(used);
  });
});

describe('remapBody on a function the target holds in several table slots', { timeout: 180_000 }, () => {
  it.skipIf(!real)('offers each of its slots and lets the target body pick one', () => {
    // sqlite3_result_text64 (target 1311) holds a pointer to a function that the target's table holds in several
    // slots: binaryen merged identical bodies, and each slot that pointed at one of them now points at the survivor
    const ours = loadOurSide(PLAIN, MAP_DIR);
    const maps = symbolMaps(ours, loadTargetSide(TARGET, SYMBOLS, `${URNA}/ledger`, ours.stackSize));
    const r = remapBody(maps, ours.fnByKey.get('sqlite3_result_text64')!);
    expect(r.ok).toBe(true);
    if (r.ok) {
      const tm = maps.target.module;
      const m = matchesTarget(r.pieces, tm.funcs[1311 - tm.importedFuncCount].bodyBytes);
      expect(m.match).toBe(true);
      expect(m.readings?.some((x) => x.startsWith('table slot copy'))).toBe(true);
    }
  });
});

describe('remapBody on a packed string_view', { timeout: 180_000 }, () => {
  it.skipIf(!real700)("re-points an i64.const holding a string's length and address into the target's", () => {
    const ours = loadOurSide(PLAIN, MAP_DIR);
    const maps = symbolMaps(ours, loadTargetSide(TARGET, SYMBOLS, `${URNA}/ledger`, ours.stackSize));
    const o = ours.fnByKey.get(CWAIT_CTOR)!;
    const packed = disassemble(ours.module.funcs[o - ours.module.importedFuncCount]).find(
      (i) => i.opcode === 0x42 && (i.imms[0] as { value: bigint }).value > 1n << 32n,
    )!;
    const v = (packed.imms[0] as { value: bigint }).value;
    // "Quantidade excessiva de milissegundos {}": 40 bytes
    expect(v >> 32n).toBe(40n);
    expect(cStringAt(maps.ourImage, 1024, Number(v & 0xffffffffn))?.length).toBe(40);
    const r = remapBody(maps, o);
    expect(r.ok).toBe(true);
    if (r.ok) {
      const tf = maps.target.module.funcs[5447 - maps.target.module.importedFuncCount];
      const m = matchesTarget(r.pieces, tf.bodyBytes);
      expect(m.match).toBe(true);
      expect(m.readings?.filter((x) => x.endsWith('(string_view)')).length).toBe(2);
    }
  });
});

describe('matchesTarget', () => {
  it('takes whichever reading of an ambiguous constant the target body has', () => {
    const pieces = [
      Uint8Array.from([0x00, 0x41]),
      {
        alternatives: [Uint8Array.from([0x90, 0x64]), Uint8Array.from([0x05])],
        readings: ['table slot of f', 'literal'],
        at: 1,
      },
      Uint8Array.from([0x0b]),
    ];
    expect(matchesTarget(pieces, Uint8Array.from([0x00, 0x41, 0x05, 0x0b]))).toEqual({
      match: true,
      readings: ['literal'],
    });
    expect(matchesTarget(pieces, Uint8Array.from([0x00, 0x41, 0x90, 0x64, 0x0b]))).toEqual({
      match: true,
      readings: ['table slot of f'],
    });
    expect(matchesTarget(pieces, Uint8Array.from([0x00, 0x41, 0x06, 0x0b]))).toEqual({
      match: false,
      firstDifference: 2,
    });
  });
});

describe('symbol file', () => {
  it('keeps the hand-edit section verbatim and lets it win over a generated line', () => {
    const generated = [
      { name: 'foo', at: { kind: 'func' as const, index: 200 }, evidence: 'pair-addr' },
      { name: 'bar', at: { kind: 'data' as const, addr: 0x1234 }, size: 8, evidence: 'rtti' },
      { name: 'baz', at: { kind: 'data' as const, addr: 0x1240 }, size: 4, evidence: 'vote:3', voters: [137, 140] },
    ];
    const text = renderSymbolFile(['header'], generated, ['foo = func:201; // evidence:hand checked by eye']);
    expect(text).toContain(`${renderSymbolEntry(generated[2])}\n${HAND_EDIT_MARKER}\n`);
    const parsed = parseSymbolFile(text);
    expect(parsed.generated).toHaveLength(3);
    expect(parsed.handLines).toEqual(['foo = func:201; // evidence:hand checked by eye']);
    expect(targetSymbolsOf(parsed).fns.get('foo')).toBe(201);
    expect(targetSymbolsOf(parsed).data.get('bar')).toBe(0x1234);
    expect(parsed.generated[1]).toMatchObject({ size: 8, evidence: 'rtti' });
    expect(soleVoters(targetSymbolsOf(parsed), 'baz')).toEqual([137, 140]);
    expect(soleVoters(targetSymbolsOf(parsed), 'bar')).toBeNull();
  });

  it.skipIf(!real)(
    'names the i2d_/d2i_ wrappers that differ only by their ASN1_ITEM through their callers, not by position',
    () => {
      // each wrapper's body is the same but for the item's address; the item's sname says which one it is
      const target = parseModule(new Uint8Array(readFileSync(TARGET)));
      const { image } = memoryImage(target);
      const syms = targetSymbolsOf(parseSymbolFile(readFileSync(SYMBOLS, 'utf8')));
      let checked = 0;
      for (const [name, t] of syms.fns) {
        const m =
          /^(?:i2d|d2i)_(RSAPublicKey|RSAPrivateKey|X509_SIG|X509_ALGOR|ASN1_OCTET_STRING|ASN1_INTEGER|DHparams)$/.exec(
            name,
          );
        if (m === null) {
          continue;
        }
        const item = disassemble(target.funcs[t - target.importedFuncCount])
          .flatMap((i) => i.imms)
          .find((im) => im.kind === 's32' && im.value >= 1024);
        const sname = image.readUInt32LE((item as { value: number }).value + 24 - 1024);
        expect(cStringAt(image, 1024, sname)?.toString('latin1')).toBe(m[1]);
        checked++;
      }
      expect(checked).toBeGreaterThanOrEqual(6);
    },
  );

  it.skipIf(!real)('names a target function by call or table votes only after a function of ours of its signature', () => {
    const target = parseModule(new Uint8Array(readFileSync(TARGET)));
    const ours = loadOurSide(PLAIN, MAP_DIR);
    const om = ours.module;
    const signature = (m: typeof om, i: number) => JSON.stringify(m.types[m.funcs[i - m.importedFuncCount].typeIndex]);
    const voted = parseSymbolFile(readFileSync(SYMBOLS, 'utf8')).generated.filter(
      (e) => e.at.kind === 'func' && (e.evidence === 'call' || e.evidence === 'table'),
    );
    const differing = voted.filter((e) => {
      const o = ours.fnByKey.get(e.name);
      const t = (e.at as { index: number }).index;
      return o !== undefined && o >= om.importedFuncCount && signature(om, o) !== signature(target, t);
    });
    expect(voted.length).toBeGreaterThan(100);
    expect(differing.map((e) => e.name)).toEqual([]);
  });
});
