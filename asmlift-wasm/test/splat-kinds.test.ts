// Operand kinds on the real links of this checkout: the plain link and its shifted relink
// (tools/round/link-kinds.sh, build/out/wasm-kinds/vota_web), the table splat-kinds wrote from them, and the target's
// split. The perturbation cases (CASES below) guard the kind check: one operand of a matched function of ours
// changed, in both links the way a source edit would change it (an integer stays put in the relink, an address moves
// by the data shift, a table slot by the table shift), then the build. baseSums, which follows a __table_base
// constant through the operand stack, is tested on hand-written bodies.
//
// Every landing moves our data and our table, so no address or slot of our link is written here: each is found in
// the link the suite runs on, from the target's number for the same thing or from a symbol name (the "our link's
// numbers" helpers below). The target's numbers never move and are literals.
import { copyFileSync, existsSync, mkdtempSync, readFileSync, writeFileSync } from 'node:fs';
import { tmpdir } from 'node:os';
import { join } from 'node:path';
import { describe, expect, it } from 'vitest';

import { type Instr, disassemble } from '../src/disasm';
import { GLOBAL_BASE } from '../src/normalize';
import type { Func, Module } from '../src/parse';
import { parseModule } from '../src/parse';
import {
  type FunctionKinds,
  type KindsSide,
  type OperandKinds,
  baseSums,
  classifyDataWords,
  classifyFunction,
  classifyOperands,
  defaultKindsPath,
  kindsPathOf,
  kindsSide,
  kindsSummary,
  linkShifts,
  noMoreArgs,
  operandKind,
  parseOperandKinds,
  readOperandKinds,
  renderOperandKinds,
  tableBase,
} from '../src/splat-kinds';
import { type Piece, remapBody } from '../src/splat-remap';
import {
  MatchesFailed,
  attempt,
  buildSplat,
  kindUnverifiedOverLimit,
  parseMatchList,
  readPieceBodies,
  referencedFunctionsAt,
  reviewWarnings,
  withMatches,
} from '../src/splat-sub';
import { runSplatSubCommand } from '../src/splat-sub-cli';
import {
  type SymbolMaps,
  cStringAt,
  loadOurSide,
  loadTargetSide,
  resolveDataAddress,
  symbolMaps,
} from '../src/splat-symbols';
import { URNA_ROOT } from './helpers';

const URNA = process.env.URNA_SPLAT_ROOT ?? URNA_ROOT;
const TARGET = `${URNA}/target/vota_web_wasm.wasm`;
const PLAIN = `${URNA}/build/out/wasm/vota_web/vota_web_wasm.wasm`;
const MAP_DIR = `${URNA}/build/out/wasm-map/vota_web`;
const SHIFTED_DIR = `${URNA}/build/out/wasm-kinds/vota_web`;
const KINDS = defaultKindsPath(PLAIN);
const SYMBOLS = `${URNA}/splat/symbol_addrs.txt`;
const PIECES = `${URNA}/build/out/splat/pieces`;
const TARGET_SHA = '8579ef8d1a93819152cecdbf52906d2e4dd0f57999cb2e1e8c0d1161cd1007e2';
const D = 1_048_576;
const T = 20_000;
const real =
  existsSync(`${MAP_DIR}/names.tsv`) &&
  existsSync(`${SHIFTED_DIR}/names.tsv`) &&
  existsSync(KINDS) &&
  existsSync(SYMBOLS) &&
  existsSync(`${PIECES}/manifest.json`);

const NEXT_ENTRY = '_ZN3api10CDirReader9NextEntryEv';
const INVERT_COLORS = '_ZN3api13CBmpConversor12InvertColorsEPhii';
const DO_CONVERTE =
  '_ZNK5comum3asn36CConversorNumViasImpressasRelatorios10DoConverteERKNS_2md15estadoaplicacao27CNumViasImpressasRelatoriosE';
const RAW_READ = '_ZNK7ecourna3api2io5CFile7RawReadEPvj';
const DSA_PEM_THUNK = 'byn$mgfn-shared$dsa_to_SubjectPublicKeyInfo_pem_encode';
// the vtable DO_CONVERTE stores at +0xc
const VTABLE = '_ZTVN21ModuloEstadoGeralDefs26NumViasImpressasRelatoriosE';

interface Loaded {
  maps: SymbolMaps;
  kinds: OperandKinds;
  plain: KindsSide;
  shifted: KindsSide;
}
let cache: Loaded | null = null;
function load(): Loaded {
  if (cache === null) {
    const ours = loadOurSide(PLAIN, MAP_DIR);
    const target = loadTargetSide(TARGET, SYMBOLS, `${URNA}/ledger`, ours.stackSize);
    const kinds = readOperandKinds(KINDS, ours.module.bytes);
    const shiftedModule = parseModule(new Uint8Array(readFileSync(`${SHIFTED_DIR}/vota_web_wasm.wasm`)));
    cache = {
      maps: symbolMaps(ours, target, kinds),
      kinds,
      plain: kindsSide(ours.module, `${MAP_DIR}/names.tsv`),
      shifted: kindsSide(shiftedModule, `${SHIFTED_DIR}/names.tsv`),
    };
  }
  return cache;
}

function indexOf(side: KindsSide, name: string): number {
  const i = [...side.names].find(([, n]) => n === name)?.[0];
  expect(i, name).toBeDefined();
  return i!;
}

function funcOf(m: Module, index: number): Func {
  return m.funcs[index - m.importedFuncCount];
}

/** LEB128 of `v`: signed (an i32.const or i64.const) or not (a callee) */
function encode(v: number | bigint, signed: boolean): number[] {
  const out: number[] = [];
  let x = BigInt(v);
  for (;;) {
    const b = Number(x & 0x7fn);
    x >>= 7n;
    const done = signed ? (x === 0n && (b & 0x40) === 0) || (x === -1n && (b & 0x40) !== 0) : x === 0n;
    if (done) {
      out.push(b);
      return out;
    }
    out.push(b | 0x80);
  }
}

/** The module with the i32.const or i64.const value, memarg offset or callee of our function `index`'s instruction at
 *  body offset `at` replaced (on the parsed module: the body re-encoded around the new operand). */
function patched(m: Module, index: number, at: number, value: number | bigint): Module {
  const fn = funcOf(m, index);
  const i: Instr | undefined = disassemble(fn).find((x) => x.offset === at);
  const im = i?.imms.find(
    (x) => x.kind === 's32' || x.kind === 's64' || x.kind === 'memarg' || (x.kind === 'u32' && x.role === 'func'),
  );
  if (i === undefined || im === undefined) {
    throw new Error(`no constant, memory offset or call at +0x${at.toString(16)}`);
  }
  const from = im.kind === 'memarg' ? im.offsetAt : im.at;
  const next = i.imms[i.imms.indexOf(im) + 1]?.at ?? i.end;
  const bodyBytes = Uint8Array.from([
    ...fn.bodyBytes.subarray(0, from),
    ...encode(value, im.kind === 's32' || im.kind === 's64'),
    ...fn.bodyBytes.subarray(next),
  ]);
  return { ...m, funcs: m.funcs.map((f) => (f === fn ? { ...f, bodyBytes, size: bodyBytes.length } : f)) };
}

/** The offset in the relink's function `s` of the instruction at `at` in the plain link's `p`: the same instruction
 *  sequence, but a moved constant may take another LEB length. */
function shiftedAt(p: number, s: number, at: number): number {
  const { plain, shifted } = load();
  const k = disassemble(funcOf(plain.module, p)).findIndex((x) => x.offset === at);
  return disassemble(funcOf(shifted.module, s))[k].offset;
}

function valueAt(m: Module, index: number, at: number): number | bigint {
  const i = disassemble(funcOf(m, index)).find((x) => x.offset === at)!;
  const im = i.imms.find((x) => x.kind === 'memarg') ?? i.imms[0];
  return im.kind === 'memarg' ? im.offset : im.kind === 's32' || im.kind === 'u32' || im.kind === 's64' ? im.value : Number.NaN;
}

// ---------------------------------------------------------------------------------------------------------------
// our link's numbers, found in the link the suite runs on (the plain link: the relink's are these plus D or T)

/** Our table slot of function `name`: the one slot our table gives it. */
function slotOf(l: Loaded, name: string): number {
  const f = l.maps.ours.fnByKey.get(name);
  const slots = [...l.maps.ours.elem].filter(([, g]) => f !== undefined && g === f).map(([s]) => s);
  expect(slots, `our slots of ${name}`).toHaveLength(1);
  return slots[0];
}

/** Our table slot of function `name` relative to our table base: an operand of an unfolded __table_base sum. */
function relativeSlotOf(l: Loaded, name: string): number {
  return slotOf(l, name) - tableBase(l.plain.module);
}

/** An operand relative to the base whose slot is `past` slots after the end of our table: the base plus it is no slot
 *  of ours, and that holds however far our table grows, which a target slot's number does not promise. */
function relativePastOurTable(l: Loaded, past: number): number {
  return l.maps.ours.tableSize + past - tableBase(l.plain.module);
}

/** Our table slot of the function the target keeps in its slot `targetSlot` (the function the symbol file gives that
 *  target function's name): the one slot our table gives it. */
function ourSlotOf(l: Loaded, targetSlot: number): number {
  const { ours, target } = l.maps;
  const f = target.elem.get(targetSlot);
  const slots = [...ours.elem]
    .filter(([, g]) => f !== undefined && target.symbols.fns.get(ours.fns.get(g)?.key ?? '') === f)
    .map(([s]) => s);
  expect(slots, `our slots of the function in target slot ${targetSlot}`).toHaveLength(1);
  return slots[0];
}

/** The target's slot of the function in our slot `slot` (the target function the symbol file gives its name): the
 *  one slot the target's table gives it. */
function targetSlotOf(l: Loaded, slot: number): number {
  const { ours, target } = l.maps;
  const f = target.symbols.fns.get(ours.fns.get(ours.elem.get(slot) ?? -1)?.key ?? '');
  const slots = f === undefined ? [] : (target.slots.get(f) ?? []);
  expect(slots, `target slots of the function in our slot ${slot}`).toHaveLength(1);
  return slots[0];
}

/** Our address of the C string the target keeps at `addr`: the one place our data holds those bytes as a whole
 *  string (a NUL before and after). */
function ourStringOf(l: Loaded, addr: number): number {
  const { ourImage, target } = l.maps;
  const s = cStringAt(target.image, target.imageBase, addr);
  expect(s, `a string at the target's ${addr}`).not.toBeNull();
  const whole = Buffer.concat([Buffer.from([0]), s!, Buffer.from([0])]);
  const places: number[] = [];
  for (let k = ourImage.indexOf(whole); k >= 0; k = ourImage.indexOf(whole, k + 1)) {
    places.push(GLOBAL_BASE + k + 1);
  }
  expect(places, `our copies of ${JSON.stringify(s!.toString('latin1'))}`).toHaveLength(1);
  return places[0];
}

/** Our address of data symbol `name` (the link map). */
function dataAddressOf(l: Loaded, name: string): number {
  const objects = l.maps.ours.map.data.filter((d) => d.key === name);
  expect(objects, name).toHaveLength(1);
  return objects[0].addr;
}

/** NextEntry +0x23: the string the target keeps at 124328 ("O diretório não está aberto"). */
const ourString = (l: Loaded): number => ourStringOf(l, 124328);
/** NextEntry +0x37, __cxa_throw's destructor argument: CError's destructor, which the target keeps in slot 69. */
const ourDtorSlot = (l: Loaded): number => ourSlotOf(l, 69);
/** The slot of ours whose function the target keeps in slot 7010, the value of NextEntry's enum at +0x1b. */
const ourSlot7010 = (l: Loaded): number => ourSlotOf(l, 7010);
/** DO_CONVERTE +0xc: its vtable's address point, past the offset-to-top and typeinfo words. */
const ourVtable = (l: Loaded): number => dataAddressOf(l, VTABLE) + 8;

/** A function of one i32 parameter whose body is `code` (no locals, the final `end` added), alone in a module. */
function handWritten(code: number[]): { m: Module; fn: Func; instrs: Instr[] } {
  const bodyBytes = Uint8Array.from([0, ...code, 0x0b]);
  const fn: Func = {
    index: 0,
    typeIndex: 0,
    params: ['i32'],
    results: [],
    locals: [],
    bodyOffset: 0,
    size: bodyBytes.length,
    bodyBytes,
    codeStart: 1,
  };
  const m = { types: [{ params: ['i32'], results: [] }], imports: [], importedFuncCount: 0, funcs: [fn] } as unknown as Module;
  return { m, fn, instrs: disassemble(fn) };
}

describe('baseSums', () => {
  const i32 = (v: number): number[] => [0x41, ...encode(v, true)];
  const LOCAL_GET = [0x20, 0];
  const LOCAL_SET = [0x21, 0];
  const SELECT = [0x1b];
  const ADD = [0x6a];
  const DROP = [0x1a];
  // the body offset of each instruction that is an i32.const of `v`
  const at = (instrs: Instr[], v: number): number[] =>
    instrs.filter((i) => i.opcode === 0x41 && i.imms[0].kind === 's32' && i.imms[0].value === v).map((i) => i.offset);
  // the base is the constant 1; `slots` are the values of the other moved table slots
  const sums = (code: number[], slots: number[] = []) => {
    const { m, fn, instrs } = handWritten(code);
    return { r: baseSums(m, fn, instrs, new Set(at(instrs, 1)), new Set(slots.flatMap((v) => at(instrs, v)))), instrs };
  };

  it('reads the constants added to the base through select arms as relative to it', () => {
    // vdbeSorterSort's `select(2035, 2036, c) + __table_base`
    const { r, instrs } = sums([...i32(2035), ...i32(2036), ...LOCAL_GET, ...SELECT, ...i32(1), ...ADD, ...DROP]);
    expect(r).toEqual({ sums: new Map([[at(instrs, 1)[0], [...at(instrs, 2035), ...at(instrs, 2036)]]]), slotSums: [] });
  });

  it('leaves out a base used as a value: a slot or address of its own', () => {
    const none = { sums: new Map(), slotSums: [] };
    expect(sums([...i32(1), 0x10, 0]).r).toEqual(none); // call 0 (i32)
    expect(sums([...LOCAL_GET, ...i32(1), 0x36, 2, 0]).r).toEqual(none); // i32.store
  });

  it('lists another table slot added to constants: a sum with part of the base in it', () => {
    // binaryen folded 1 of the relative operands into the base: `select(2034, 2035, c) + 2`, and 2 moved as a slot
    const { r, instrs } = sums([...i32(2034), ...i32(2035), ...LOCAL_GET, ...SELECT, ...i32(2), ...ADD, ...DROP], [2]);
    expect(r).toEqual({ sums: new Map(), slotSums: at(instrs, 2) });
    // a slot added to another slot
    const both = sums([...i32(7), ...i32(9), ...ADD, ...DROP], [7, 9]);
    expect(both.r).toEqual({ sums: new Map(), slotSums: [...at(both.instrs, 7), ...at(both.instrs, 9)] });
    // a slot used as a pointer (stored, passed, added to a variable) is not followed further
    const pointer = { sums: new Map(), slotSums: [] };
    expect(sums([...LOCAL_GET, ...i32(7), 0x36, 2, 0], [7]).r).toEqual(pointer);
    expect(sums([...i32(7), ...LOCAL_SET], [7]).r).toEqual(pointer);
    expect(sums([...LOCAL_GET, ...i32(7), ...ADD, ...DROP], [7]).r).toEqual(pointer);
    // the base added to a slot: neither part can be told
    expect(sums([...i32(7), ...i32(1), ...ADD, ...DROP], [7]).r).toEqual({ why: expect.stringMatching(/added to a table slot$/) });
  });

  it('cannot tell where a base kept in a local, carried out of a block or added to a variable ends up', () => {
    expect(sums([...i32(1), ...LOCAL_SET]).r).toEqual({ why: expect.stringMatching(/base itself, kept in a local$/) });
    // block (result i32) i32.const 1 end; i32.const 5; i32.add
    expect(sums([0x02, 0x7f, ...i32(1), 0x0b, ...i32(5), ...ADD, ...DROP]).r).toEqual({
      why: expect.stringMatching(/a block result$/),
    });
    expect(sums([...i32(1), ...i32(7), 0x0d, 0, ...ADD, ...DROP]).r).toEqual({
      why: expect.stringMatching(/carried by a branch$/),
    }); // br_if 0
    expect(sums([...LOCAL_GET, ...i32(1), ...ADD, ...DROP]).r).toEqual({
      why: expect.stringMatching(/added to a value that is not a constant$/),
    });
    // the relative operands chosen first and kept in a local: the sum's other side is a local.get
    const viaLocal = [...i32(2035), ...i32(2036), ...LOCAL_GET, ...SELECT, ...LOCAL_SET];
    expect(sums([...viaLocal, ...LOCAL_GET, ...i32(1), ...ADD, ...DROP]).r).toEqual({
      why: expect.stringMatching(/added to a value that is not a constant$/),
    });
    // the base in a select arm, the select added to a constant
    expect(sums([...i32(1), ...i32(5), ...LOCAL_GET, ...SELECT, ...i32(7), ...ADD, ...DROP]).r).toEqual({
      why: expect.stringMatching(/in a sum this cannot follow$/),
    });
  });
});

// Two hand-written links of one function, the second with the data and the table moved: what classifyFunction makes
// of each constant, with no build output (these run in CI).
describe('classifyFunction on hand-written links', () => {
  const i32 = (v: number): number[] => [0x41, ...encode(v, true)];
  const DROP = [0x1a];
  const LOCAL_GET = [0x20, 0];
  const SELECT = [0x1b];
  const ADD = [0x6a];
  /** `code` as the one function of a link whose data starts at `data` and whose table (every slot holding the
   *  function) at `table` */
  const link = (code: number[], data: number, table: number): KindsSide => {
    const { m } = handWritten(code);
    const module = {
      ...m,
      datas: [{ mode: 'active', offset: data, bytes: new Uint8Array(4) }],
      globals: [{ type: 'i32', mutable: true, init: `i32.const ${data + 65536}` }],
      elems: [{ mode: 'active', tableIndex: 0, offset: { value: table }, funcIndices: Array(2100).fill(0) }],
    } as unknown as Module;
    return { module, names: new Map([[0, 'f']]) };
  };
  // the plain link's constants, and the relink's: each moved by D (an address), T (a slot) or not at all
  const classify = (plain: (number | number[])[], shifted: (number | number[])[]): { k: FunctionKinds; instrs: Instr[] } => {
    const code = (xs: (number | number[])[]): number[] => xs.flatMap((x) => (typeof x === 'number' ? i32(x) : x));
    const p = link(code(plain), 1024, 1);
    const s = link(code(shifted), 1024 + D, 1 + T);
    return {
      k: classifyFunction(p, s, linkShifts(p.module, s.module), 0, 0),
      instrs: disassemble(p.module.funcs[0]),
    };
  };
  const at = (instrs: Instr[], v: number): number =>
    instrs.find((i) => i.opcode === 0x41 && i.imms[0].kind === 's32' && i.imms[0].value === v)!.offset;

  it('reads a constant that did not move as an integer, one moved by D as an address, by T as a table slot', () => {
    const { k, instrs } = classify([7010, DROP, 2048, DROP, 16, DROP], [7010, DROP, 2048 + D, DROP, 16 + T, DROP]);
    expect([7010, 2048, 16].map((v) => operandKind(k, at(instrs, v)))).toEqual(['literal', 'address', 'slot']);
  });

  it('leaves the function kind-unverified when a constant moved by neither shift', () => {
    expect(classify([2048, DROP], [2048 + D + 4, DROP]).k).toEqual({
      verified: false,
      why: `+0x1 i32.const 2048 moved to ${2048 + D + 4}, by neither shift`,
    });
  });

  it("reads an unfolded __table_base sum's base and the constants relative to it", () => {
    const sum = (base: number): (number | number[])[] => [2035, 2036, LOCAL_GET, SELECT, base, ADD, DROP];
    const { k, instrs } = classify(sum(1), sum(1 + T));
    expect([2035, 2036, 1].map((v) => operandKind(k, at(instrs, v)))).toEqual(['table-rel', 'table-rel', 'table-base']);
  });

  it('leaves the function kind-unverified when another table slot is added to constants', () => {
    // binaryen folded 1 of the relative operands into the base: which part of 2 is the base cannot be told
    const sum = (base: number): (number | number[])[] => [2034, 2035, LOCAL_GET, SELECT, base, ADD, DROP];
    expect(classify(sum(2), sum(2 + T)).k).toEqual({
      verified: false,
      why: '+0xa i32.const 2 is a table slot added to constants: a __table_base sum with part of the base in it',
    });
    // a slot stored as a pointer is one
    const { k, instrs } = classify([LOCAL_GET, 2, [0x36, 2, 0]], [LOCAL_GET, 2 + T, [0x36, 2, 0]]);
    expect(operandKind(k, at(instrs, 2))).toBe('slot');
  });
});

describe('classifyDataWords on hand-written links', () => {
  // a link's data at `base` (its words), its table at `table` of 2100 slots, slot k holding function k % 2 named f or g
  const link = (words: number[], base: number, table: number, names = ['f', 'g']): KindsSide => {
    const bytes = new Uint8Array(words.length * 4);
    words.forEach((w, k) => new DataView(bytes.buffer).setUint32(k * 4, w, true));
    const module = {
      datas: [{ mode: 'active', offset: base, bytes }],
      elems: [{ mode: 'active', tableIndex: 0, offset: { value: table }, funcIndices: Array.from({ length: 2100 }, (_, k) => k % 2) }],
    } as unknown as Module;
    return { module, names: new Map(names.map((n, k) => [k, n])) };
  };
  const shifts = { dataShift: D, tableShift: T, dataBase: 1024, tableBase: 1 };
  const classify = (plain: number[], shifted: number[], names?: string[]) =>
    classifyDataWords(link(plain, 1024, 1), link(shifted, 1024 + D, 1 + T, names), shifts, 4096);

  it('reads a word the relink did not move as an integer, one moved by D as an address, by T as a table slot', () => {
    // 23 and 3000 read as a slot and as an address of ours, and are integers: an ASN.1 tag, a size. 2500 and 16 are
    // an address and a slot, each of which reads as that one alone, so the table leaves them out; 0 and 5000 read as
    // neither (past the table and past dataEnd)
    const k = classify([23, 3000, 2500, 16, 0, 5000], [23, 3000, 2500 + D, 16 + T, 0, 5000]);
    expect(k).toEqual(
      new Map([
        [1024, 'literal'],
        [1028, 'literal'],
      ]),
    );
  });

  it('says which of the two a word that reads as both is', () => {
    // from 1024 to the table's end a value is both one of our addresses and one of our slots
    const k = classify([1500, 1504, 1508], [1500 + T, 1504 + D, 1508]);
    expect(k).toEqual(
      new Map([
        [1024, 'slot'],
        [1028, 'address'],
        [1032, 'literal'],
      ]),
    );
  });

  it('leaves a word unverified when it moved by neither shift, or its two slots hold functions of other names', () => {
    expect(classify([2052], [2052 + D + 4])).toEqual(new Map([[1024, 'unverified']]));
    // slot 31 holds f in the plain link; the relink's slot 31 + T holds the function the relink names h
    expect(classify([31], [31 + T], ['h', 'g'])).toEqual(new Map([[1024, 'unverified']]));
  });
});

describe('the table argument', () => {
  it('is required unless --no-kinds says to check without one', () => {
    const dir = mkdtempSync(join(tmpdir(), 'kinds-'));
    const plain = join(dir, 'wasm', 'vota_web', 'vota_web_wasm.wasm');
    expect(() => kindsPathOf(plain, undefined, false)).toThrow(/no operand-kind table at .*wasm-kinds\/vota_web\/kinds\.json/);
    expect(() => kindsPathOf(plain, join(dir, 'none.json'), false)).toThrow(/no operand-kind table/);
    expect(kindsPathOf(plain, undefined, true)).toBeNull();
    expect(() => kindsPathOf(plain, join(dir, 'none.json'), true)).toThrow(/--kinds and --no-kinds/);
    writeFileSync(join(dir, 'k.json'), '{}');
    expect(kindsPathOf(plain, join(dir, 'k.json'), false)).toBe(join(dir, 'k.json'));
  });

  it('is not skipped by a flag the command does not take', () => {
    expect(() => noMoreArgs('splat-build', [])).not.toThrow();
    expect(() => noMoreArgs('splat-build', ['--kinds /x'])).toThrow("splat-build: unexpected argument '--kinds /x'");
    // splat-build refuses before reading anything
    const dir = mkdtempSync(join(tmpdir(), 'kinds-'));
    const target = join(dir, 'target', 'x.wasm');
    const plain = join(dir, 'plain', 'x.wasm');
    expect(() => runSplatSubCommand('splat-build', [target, plain, '--no-kinds', '--kinds /x'])).toThrow(
      /unexpected argument '--kinds \/x'/,
    );
    expect(() => runSplatSubCommand('splat-build', [target, plain])).toThrow(/no operand-kind table/);
    // the limits take counts (an empty make variable would leave the flag without one)
    for (const flag of ['--max-kind-unverified']) {
      expect(() => runSplatSubCommand('splat-build', [target, plain, flag, '-o', 'x.wasm'])).toThrow(
        `${flag} takes a count, not '-o'`,
      );
    }
  });
});

describe('linkShifts', () => {
  it.skipIf(!real)('reads how far the relink moved the data and the table', () => {
    const { plain, shifted } = load();
    expect(linkShifts(plain.module, shifted.module)).toEqual({ dataShift: D, tableShift: T, dataBase: 1024, tableBase: 1 });
  });

  it.skipIf(!real)('refuses two links that are the same', () => {
    const { plain } = load();
    expect(() => linkShifts(plain.module, plain.module)).toThrow(/two different positive amounts/);
  });
});

describe('classifyFunction', { timeout: 180_000 }, () => {
  const kindsOf = (name: string, plainModule?: Module, shiftedModule?: Module): FunctionKinds => {
    const { plain, shifted } = load();
    const p = { ...plain, module: plainModule ?? plain.module };
    const s = { ...shifted, module: shiftedModule ?? shifted.module };
    return classifyFunction(p, s, linkShifts(plain.module, shifted.module), indexOf(plain, name), indexOf(shifted, name));
  };

  it.skipIf(!real)("tells api::CDirReader::NextEntry's enum, string, typeinfo and destructor pointer apart", () => {
    // the enum 7010 equals the target's slot of a function in our table (case c2 below); +0x37 is __cxa_throw's
    // destructor argument, a table slot
    const k = kindsOf(NEXT_ENTRY);
    expect(k.verified).toBe(true);
    const kind = (at: number) => operandKind(k, at);
    expect([kind(0x1b), kind(0x23), kind(0x2a), kind(0x32), kind(0x37)]).toEqual([
      'literal',
      'address',
      'address',
      'address',
      'slot',
    ]);
    // the frame size and the field offsets are integers
    expect([kind(0x5), kind(0xe), kind(0x20), kind(0x46)]).toEqual(['literal', 'literal', 'literal', 'literal']);
  });

  it.skipIf(!real)('reads a vtable store as an address', () => {
    const k = kindsOf(DO_CONVERTE);
    expect([operandKind(k, 0x3), operandKind(k, 0xc)]).toEqual(['address', 'address']);
  });

  it.skipIf(!real)("reads an unfolded __table_base sum's base and the slots relative to it", () => {
    // sqlite's -fPIC objects add __table_base to a select of three slots relative to it: the base moves by T, the
    // relative operands do not, and alone they would read as literals
    const k = kindsOf('vdbeSorterSort');
    expect(k.verified).toBe(true);
    expect([0xa8, 0xab, 0xae, 0xbd].map((at) => operandKind(k, at))).toEqual([
      'table-rel',
      'table-rel',
      'table-rel',
      'table-base',
    ]);
    // a constant's encoded width moves this one's offset with our data, so read it by its kind
    const exec = kindsOf('sqlite3VdbeExec');
    expect(exec.verified && [...exec.ops.values()].filter((kind) => kind === 'table-base')).toEqual(['table-base']);
  });

  it.skipIf(!real)('leaves a function kind-unverified when a constant added to __table_base moved', () => {
    const l = load();
    const { plain, shifted } = l;
    const p = indexOf(plain, 'vdbeSorterSort');
    const s = indexOf(shifted, 'vdbeSorterSort');
    // +0xae is vdbeSorterCompare's slot relative to the base
    const rel = relativeSlotOf(l, 'vdbeSorterCompare');
    expect(valueAt(plain.module, p, 0xae)).toBe(rel);
    const k = kindsOf('vdbeSorterSort', undefined, patched(shifted.module, s, shiftedAt(p, s, 0xae), rel + T));
    expect(k).toEqual({
      verified: false,
      // the relative slot moved as a table slot: the base added to a slot, neither part can be told
      why: "+0xbd i32.const is the link's base itself, added to a table slot",
    });
  });

  it.skipIf(!real)('leaves a function kind-unverified when an operand moved by neither shift', () => {
    const { shifted } = load();
    const s = indexOf(shifted, NEXT_ENTRY);
    const at = shiftedAt(indexOf(load().plain, NEXT_ENTRY), s, 0x23);
    const str = ourString(load());
    expect(valueAt(shifted.module, s, at)).toBe(str + D);
    const k = kindsOf(NEXT_ENTRY, undefined, patched(shifted.module, s, at, str + D + 4));
    expect(k).toEqual({ verified: false, why: `+0x23 i32.const ${str} moved to ${str + D + 4}, by neither shift` });
  });

  it.skipIf(!real)('leaves a function kind-unverified when the relink has another shape', () => {
    const { shifted } = load();
    const s = indexOf(shifted, NEXT_ENTRY);
    // another callee of the same signature
    const at = shiftedAt(indexOf(load().plain, NEXT_ENTRY), s, 0x41);
    const k = kindsOf(NEXT_ENTRY, undefined, patched(shifted.module, s, at, indexOf(shifted, '_Znwm')));
    expect(k.verified).toBe(false);
    expect(!k.verified && k.why).toMatch(/^another shape in the shifted link: \+0x41 call: \S+ against _Znwm$/);
  });

  it.skipIf(!real)('leaves a function kind-unverified when the two slots hold different functions', () => {
    // the relink's table with the destructor's slot (+0x37) and the next swapped: the operand still moves by T, to a
    // slot naming another function
    const { shifted } = load();
    const slot = ourDtorSlot(load());
    const elems = shifted.module.elems.map((e) => {
      if (e.mode !== 'active') {
        return e;
      }
      const funcIndices = [...e.funcIndices];
      const at = slot + T - (e.offset!.value as number);
      [funcIndices[at], funcIndices[at + 1]] = [funcIndices[at + 1], funcIndices[at]];
      return { ...e, funcIndices };
    });
    expect(kindsOf(NEXT_ENTRY, undefined, { ...shifted.module, elems })).toEqual({
      verified: false,
      why: `+0x37 i32.const ${slot}: the two links' slots hold different functions`,
    });
  });
});

describe('classifyOperands', { timeout: 180_000 }, () => {
  it.skipIf(!real)('classifies every function of the link, every match kind-verified', () => {
    const { plain, shifted, kinds, maps } = load();
    const k = classifyOperands(plain, shifted, maps.ours.dataEnd);
    expect(renderOperandKinds(k)).toBe(readFileSync(KINDS, 'utf8'));
    expect(k.functions.size).toBe(plain.module.funcs.length);
    const { matches } = parseMatchList(readFileSync(`${URNA}/splat/matched.txt`, 'utf8'));
    const s = kindsSummary(kinds, plain.module, matches.map((m) => maps.ours.fnByKey.get(m.symbol)!));
    expect(s.functions - s.verified).toBe(0);
    expect(s.operands.address).toBeGreaterThan(20_000);
    expect(s.operands.slot).toBeGreaterThan(1_000);
    // vdbeSorterSort's
    expect([s.operands['table-base'], s.operands['table-rel']]).toEqual([1, 3]);
  });

  it.skipIf(!real)("reads ASN1::UTCTime::theInfo's tag 23 as an integer, which also reads as our table slot 23", () => {
    // (create, 23, 0): the tag equals a slot number of ours, the create function's slot is a slot
    const { kinds, maps } = load();
    const obj = maps.ours.map.data.find((d) => d.key === '_ZN4ASN17UTCTime7theInfoE')!;
    expect(maps.ourImage.readUInt32LE(obj.addr + 4 - GLOBAL_BASE)).toBe(23);
    expect(maps.ours.elem.has(23)).toBe(true);
    expect(kinds.data.get(obj.addr + 4)).toBe('literal');
    expect(maps.ours.dataKinds).toBe(kinds.data);
    const create = maps.ourImage.readUInt32LE(obj.addr - GLOBAL_BASE);
    // a slot past 1024 reads as an address too, and the table says which
    expect(kinds.data.get(obj.addr)).toBe(create >= GLOBAL_BASE ? 'slot' : undefined);
  });

  it.skipIf(!real)('writes a table that reads back the same, and refuses it for another plain link', () => {
    const { kinds, shifted } = load();
    expect(renderOperandKinds(parseOperandKinds(renderOperandKinds(kinds)))).toBe(renderOperandKinds(kinds));
    expect(() => readOperandKinds(KINDS, shifted.module.bytes)).toThrow(/describes another plain link/);
  });
});

describe('remapBody with operand kinds', { timeout: 180_000 }, () => {
  it.skipIf(!real)('offers an operand only the readings of its kind', () => {
    const { maps } = load();
    const ours = maps.ours.fnByKey.get(NEXT_ENTRY)!;
    const r = remapBody(maps, ours);
    expect(r.ok && r.kindUnverified).toBeUndefined();
    const ambiguous = r.ok ? r.pieces.filter((p): p is Exclude<Piece, Uint8Array> => !(p instanceof Uint8Array)) : [];
    // the enum offers nothing (a literal is fixed bytes); the string, the typeinfo and the vtable only addresses, the
    // destructor only its table slot
    expect(ambiguous.map((p) => p.at)).toEqual([0x23, 0x2a, 0x32, 0x37]);
    expect(ambiguous.every((p) => !p.readings.includes('literal'))).toBe(true);
    expect(ambiguous.at(-1)!.readings.every((x) => x.startsWith('table slot'))).toBe(true);
    const all = remapBody({ ...maps, kinds: undefined }, ours);
    expect(all.ok && all.kindUnverified).toBe('no operand-kind table');
    expect(all.ok && all.pieces.some((p) => !(p instanceof Uint8Array) && p.at === 0x1b)).toBe(true);
  });

  it.skipIf(!real)("offers an unfolded sum's base the target's table base, its relative slots minus it", () => {
    const { maps } = load();
    const r = remapBody(maps, maps.ours.fnByKey.get('vdbeSorterSort')!);
    const ambiguous = r.ok ? r.pieces.filter((p): p is Exclude<Piece, Uint8Array> => !(p instanceof Uint8Array)) : [];
    const at = (x: number) => ambiguous.find((p) => p.at === x)!.readings;
    expect(at(0xbd)).toEqual(['table base']);
    for (const x of [0xa8, 0xab, 0xae]) {
      expect(at(x).every((y) => /^table slot (copy \d+ )?of .* − the table base$/.test(y)), x.toString(16)).toBe(true);
    }
  });
});

// The perturbation cases. Without the operand-kind table (every reading offered), c2, c5, c8 and c9 build the target;
// with it, c2, c5 and c8 are rejected and c9 is a review warning. The others: the target's number written as an
// integer (c5L, c8L, I2, TH2), an integer of the target's written as a pointer (c2S), integers over vdbeSorterSort's
// relative slots (V1, V2), and a function the relink does not name. Each case: our function, the instruction, the
// original value, the value in the plain link and the value the shifted relink would have (by the operand's kind in
// the source). A value of our link (an original address or slot, a slot or address of ours a case writes) is a
// function of the links, found as the helpers above say; the target's numbers are literals, but c9's, which has to stay
// past our data and is chosen from the link (pastOurData).
type Value = number | bigint | ((l: Loaded) => number | bigint);
interface Case {
  name: string;
  symbol: string;
  target: number;
  at?: number;
  was?: Value;
  plain?: Value;
  shifted?: Value;
  /** the relink names no function after the symbol */
  unnamed?: boolean;
}
/** c4's wrong string: the one after the right one in our merged strings */
function nextString(l: Loaded): number {
  const right = ourString(l);
  return right + cStringAt(l.maps.ourImage, GLOBAL_BASE, right)!.length + 1;
}
const CASES: Case[] = [
  { name: 'c0 identity', symbol: NEXT_ENTRY, target: 1260 },
  { name: 'c1 enum 7011', symbol: NEXT_ENTRY, target: 1260, at: 0x1b, was: 7010, plain: 7011, shifted: 7011 },
  // our slot of the function the target keeps in slot 7010
  { name: 'c2 enum our slot of target slot 7010', symbol: NEXT_ENTRY, target: 1260, at: 0x1b, was: 7010, plain: ourSlot7010, shifted: ourSlot7010 },
  { name: 'c3 enum 1622', symbol: INVERT_COLORS, target: 3663, at: 0xc7, was: 4903, plain: 1622, shifted: 1622 },
  {
    name: 'c4 wrong string',
    symbol: NEXT_ENTRY,
    target: 1260,
    at: 0x23,
    was: ourString,
    plain: nextString,
    shifted: (l) => nextString(l) + D,
  },
  // 124328 is the target's address of the right string, and an address inside our merged strings
  { name: 'c5 string at the target number', symbol: NEXT_ENTRY, target: 1260, at: 0x23, was: ourString, plain: 124328, shifted: 124328 + D },
  {
    name: 'c6 wrong callee',
    symbol: NEXT_ENTRY,
    target: 1260,
    at: 0x41,
    plain: (l) => l.maps.ours.fnByKey.get('_Znwm')!,
    shifted: (l) => indexOf(l.shifted, '_Znwm'),
  },
  // the slot after the destructor's
  {
    name: 'c7 wrong slot',
    symbol: NEXT_ENTRY,
    target: 1260,
    at: 0x37,
    was: ourDtorSlot,
    plain: (l) => ourDtorSlot(l) + 1,
    shifted: (l) => ourDtorSlot(l) + 1 + T,
  },
  // 69 is the target's slot of the destructor
  { name: 'c8 slot 69, the target number', symbol: NEXT_ENTRY, target: 1260, at: 0x37, was: ourDtorSlot, plain: 69, shifted: 69 + T },
  {
    name: 'c10 vtable + 4',
    symbol: DO_CONVERTE,
    target: 11386,
    at: 0xc,
    was: ourVtable,
    plain: (l) => ourVtable(l) + 4,
    shifted: (l) => ourVtable(l) + 4 + D,
  },
  // the target's numbers written as integers: the string's address, the destructor's slot, a packed string view
  // (length 9 << 32 | the target's address 3395) and a string's address in a binaryen thunk
  { name: 'c5L the string address as an integer', symbol: NEXT_ENTRY, target: 1260, at: 0x23, was: ourString, plain: 124328, shifted: 124328 },
  { name: 'c8L the slot as an integer', symbol: NEXT_ENTRY, target: 1260, at: 0x37, was: ourDtorSlot, plain: 69, shifted: 69 },
  {
    name: 'I2 the string view as an integer',
    symbol: RAW_READ,
    target: 598,
    at: 0x25f,
    // our "size = {}", the string the target keeps at 3395
    was: (l) => (9n << 32n) | BigInt(ourStringOf(l, 3395)),
    plain: (9n << 32n) | 3395n,
    shifted: (9n << 32n) | 3395n,
  },
  // our "key2any_encode", the string the target keeps at 187586
  {
    name: 'TH2 a thunk string as an integer',
    symbol: DSA_PEM_THUNK,
    target: 1724,
    at: 0x3a,
    was: (l) => ourStringOf(l, 187586),
    plain: 187586,
    shifted: 187586,
  },
  // the enum 7010 written as a pointer to the function in our slot of it, which the target keeps in slot 7010
  {
    name: 'c2S the enum as a pointer',
    symbol: NEXT_ENTRY,
    target: 1260,
    at: 0x1b,
    was: 7010,
    plain: ourSlot7010,
    shifted: (l) => ourSlot7010(l) + T,
  },
  // vdbeSorterSort's relative slots (+0xa8, +0xae) written as integers past our table: the table reads them as
  // table-rel, relative to the base, and the slots that makes of them (our base + each) are no slots of ours. Ours are
  // vdbeSorterCompare's slot (+0xae) and vdbeSorterCompareInt's (+0xa8), relative to the base.
  {
    name: 'V1 a relative slot as an integer',
    symbol: 'vdbeSorterSort',
    target: 6458,
    at: 0xae,
    was: (l) => relativeSlotOf(l, 'vdbeSorterCompare'),
    plain: (l) => relativePastOurTable(l, 2),
    shifted: (l) => relativePastOurTable(l, 2),
  },
  {
    name: 'V2 another',
    symbol: 'vdbeSorterSort',
    target: 6458,
    at: 0xa8,
    was: (l) => relativeSlotOf(l, 'vdbeSorterCompareInt'),
    plain: (l) => relativePastOurTable(l, 0),
    shifted: (l) => relativePastOurTable(l, 0),
  },
  {
    name: 'U c2 in a function the relink does not name',
    symbol: NEXT_ENTRY,
    target: 1260,
    at: 0x1b,
    was: 7010,
    plain: ourSlot7010,
    shifted: ourSlot7010,
    unnamed: true,
  },
];

/** c9: the target's address of an object written as an integer. The first listed match that builds alone, with no
 *  review warning of its own, and holds an address the target keeps past the end of our data, where no reading of ours
 *  names it. Our data grows with every landing, so no one target number stays past it. */
function pastOurData(l: Loaded): Case {
  const { ours, target } = l.maps;
  const named = new Set(l.shifted.names.values());
  const bodies = readPieceBodies(PIECES);
  const value = (i: Instr | undefined): number | undefined => {
    const im = i?.imms[0];
    return i?.opcode === 0x41 && im?.kind === 's32' ? im.value : undefined;
  };
  for (const match of parseMatchList(readFileSync(`${URNA}/splat/matched.txt`, 'utf8')).matches) {
    const p = ours.fnByKey.get(match.symbol);
    if (p === undefined || !named.has(match.symbol)) {
      continue;
    }
    const mine = disassemble(funcOf(ours.module, p));
    const theirs = disassemble(funcOf(target.module, match.index));
    const fk = l.kinds.functions.get(p);
    const k = mine.findIndex((i, n) => {
      const v = value(theirs[n]);
      return v !== undefined && v >= ours.dataEnd && v < target.dataEnd! && operandKind(fk, i.offset) === 'address';
    });
    if (
      k >= 0 &&
      attempt(l.maps, { ours: p, symbol: match.symbol, source: 'symbol' }, match.index, bodies.get(match.index)!).verdict === 'match' &&
      reviewWarnings(l.maps, new Map([[match.index, { match, ours: p }]])).length === 0
    ) {
      const v = value(theirs[k])!;
      return { name: 'c9 an address of the target', symbol: match.symbol, target: match.index, at: mine[k].offset, was: value(mine[k]), plain: v, shifted: v };
    }
  }
  throw new Error('no match holds an address past our data');
}

/** The maps of the case: our module patched, and its function's kinds from the patched pair of links. */
function caseMaps(c: Case): { maps: SymbolMaps; kinds: FunctionKinds } {
  const l = load();
  const p = indexOf(l.plain, c.symbol);
  const s = indexOf(l.shifted, c.symbol);
  if (c.at === undefined) {
    return { maps: l.maps, kinds: l.kinds.functions.get(p)! };
  }
  const v = (x: Value | undefined): number | bigint => (typeof x === 'function' ? x(l) : x!);
  if (c.was !== undefined) {
    expect(valueAt(l.plain.module, p, c.at), c.name).toBe(v(c.was));
  }
  const plainModule = patched(l.plain.module, p, c.at, v(c.plain));
  const shiftedModule = patched(l.shifted.module, s, shiftedAt(p, s, c.at), v(c.shifted));
  const pair = { ...l.plain, module: plainModule };
  const names = new Map(l.shifted.names);
  if (c.unnamed) {
    names.delete(s);
  }
  const kinds = c.unnamed
    ? classifyOperands(pair, { module: shiftedModule, names }, l.maps.ours.dataEnd).functions.get(p)!
    : classifyFunction(pair, { ...l.shifted, module: shiftedModule }, linkShifts(l.plain.module, l.shifted.module), p, s);
  const functions = new Map(l.kinds.functions);
  functions.set(p, kinds);
  return {
    maps: {
      ...l.maps,
      ours: { ...l.maps.ours, module: plainModule },
      kinds: { ...l.kinds, functions },
    },
    kinds,
  };
}

function build(c: Case, maps: SymbolMaps) {
  return buildSplat(maps, PIECES, parseMatchList(`${c.target} ${c.symbol}\n`).matches, TARGET_SHA);
}

function failure(c: Case, maps: SymbolMaps): string {
  try {
    build(c, maps);
  } catch (e) {
    expect(e).toBeInstanceOf(MatchesFailed);
    return (e as MatchesFailed).message;
  }
  return 'built';
}

describe('the perturbation cases', { timeout: 300_000 }, () => {
  const byName = (prefix: string): Case => CASES.find((c) => c.name.startsWith(`${prefix} `))!;

  it.skipIf(!real)('c0: the unpatched function builds the target, kind-verified, with no review warning', () => {
    const c = byName('c0');
    const r = build(c, caseMaps(c).maps);
    expect(r.assembled.sha256).toBe(TARGET_SHA);
    expect(r.kindUnverified).toEqual([]);
    expect(r.reviewWarnings).toEqual([]);
  });

  it.skipIf(!real)('c2, c5, c8: a value written as another kind than the target number is rejected', () => {
    // every reading offered (no table): each one builds the target
    for (const name of ['c2', 'c5', 'c8']) {
      expect(failure(byName(name), { ...caseMaps(byName(name)).maps, kinds: undefined }), name).toBe('built');
    }
    const l = load();
    // c2: an integer that our table slot reading would have turned into the target's 7010
    const c2 = caseMaps(byName('c2'));
    const slot = ourSlot7010(l);
    expect(operandKind(c2.kinds, 0x1b)).toBe('literal');
    // the first differing byte is either of the literal's two, by the low bits of our slot
    expect(failure(byName('c2'), c2.maps)).toMatch(
      new RegExp(
        `function 1260 .* DIFFERS at \\+0x1[cd] target \\+0x1b i32\\.const 7010 \\| ours \\+0x1b i32\\.const ${slot} \\[ours ${slot}: an integer`,
      ),
    );
    // c5: an address whose literal is the target's number for the right string; re-pointed, it is the target's
    // address of what our data holds at 124328
    const c5 = caseMaps(byName('c5'));
    const there = resolveDataAddress(l.maps.ours, l.maps.ourImage, l.maps.target, 124328);
    expect(there.ok).toBe(true);
    const addr = there.ok ? there.addr : Number.NaN;
    expect(operandKind(c5.kinds, 0x23)).toBe('address');
    // the first differing byte is any of the literal's three, by what our data holds at 124328
    expect(failure(byName('c5'), c5.maps)).toMatch(
      new RegExp(
        `function 1260 .* DIFFERS at \\+0x2[4-6] target \\+0x23 i32\\.const 124328 \\| ours \\+0x23 i32\\.const ${addr} \\[ours 124328 = .*: address string`,
      ),
    );
    // c8: a table slot whose literal is the target's slot number; re-pointed, it is the target's slot of the function
    // in our slot 69
    const c8 = caseMaps(byName('c8'));
    expect(operandKind(c8.kinds, 0x37)).toBe('slot');
    const theirs = targetSlotOf(l, 69);
    expect(failure(byName('c8'), c8.maps)).toMatch(
      new RegExp(`function 1260 .* DIFFERS at \\+0x38 target \\+0x37 i32\\.const 69 \\| ours \\+0x37 i32\\.const ${theirs}$`, 'm'),
    );
  });

  it.skipIf(!real)('c1, c3, c4, c6, c7, c10: a wrong value that coincides with nothing stays rejected', () => {
    for (const name of ['c1', 'c3', 'c4', 'c6', 'c7', 'c10']) {
      const c = byName(name);
      const { maps, kinds } = caseMaps(c);
      expect(kinds.verified, name).toBe(true);
      expect(failure(c, maps), name).toMatch(new RegExp(`function ${c.target} .*(DIFFERS|UNRESOLVED)`));
    }
  });

  it.skipIf(!real)('c9, c5L, I2, TH2: the target number written as an integer builds, and is a review warning', () => {
    // an integer is compared as itself, so the bytes agree: the check cannot reject these, it lists them
    const c9 = pastOurData(load());
    const expected: [Case, string, number][] = [
      [c9, 'past-data', c9.plain as number],
      [byName('c5L'), 'target-object', 124328],
      [byName('I2'), 'target-object', 3395],
      [byName('TH2'), 'target-object', 187586],
    ];
    for (const [c, why, value] of expected) {
      const { name } = c;
      const { maps, kinds } = caseMaps(c);
      expect(operandKind(kinds, c.at!), name).toBe('literal');
      const r = build(c, maps);
      expect(r.assembled.sha256, name).toBe(TARGET_SHA);
      expect(r.kindUnverified, name).toEqual([]);
      expect(
        r.reviewWarnings.map((w) => [w.match.index, w.at, w.why, w.value]),
        name,
      ).toEqual([[c.target, c.at, why, value]]);
    }
    // the same value where the source wrote an address (the relink moved it): no target address of ours, rejected
    const address = { ...c9, shifted: (c9.plain as number) + D };
    const a = caseMaps(address);
    expect(operandKind(a.kinds, c9.at!)).toBe('address');
    expect(failure(address, a.maps)).toMatch(
      new RegExp(`function ${c9.target} .* is UNRESOLVED: ours \\+0x${c9.at!.toString(16)} i32\\.const ${c9.plain as number}: an address of ours`),
    );
  });

  it.skipIf(!real)('an integer in the target table past ours is a review warning', () => {
    // midway between the end of our table and the end of the target's
    const { ours, target } = load().maps;
    const past = Math.floor((ours.tableSize + target.module.tables[0].min) / 2);
    expect(past).toBeGreaterThan(ours.tableSize);
    const c = { ...byName('c1'), plain: past, shifted: past };
    const { maps } = caseMaps(c);
    const matched = new Map([[1260, { match: parseMatchList(`1260 ${NEXT_ENTRY}\n`).matches[0], ours: indexOf(load().plain, NEXT_ENTRY) }]]);
    expect(reviewWarnings(maps, matched).map((w) => [w.at, w.why, w.value])).toEqual([[0x1b, 'past-table', past]]);
  });

  it.skipIf(!real)('c8L, c2S: the limits of the check build the target, with no review warning', () => {
    // c8L: the target's slot 69 written as an integer, inside our table (every small integer equals some target slot);
    // c2S: an integer of the target's (7010) written as a pointer to the function the target keeps in that slot (our
    // kind is checked, the target's cannot be)
    for (const [name, kind] of [
      ['c8L', 'literal'],
      ['c2S', 'slot'],
    ] as const) {
      const c = byName(name);
      const { maps, kinds } = caseMaps(c);
      expect(operandKind(kinds, c.at!), name).toBe(kind);
      const r = build(c, maps);
      expect(r.assembled.sha256, name).toBe(TARGET_SHA);
      expect([r.kindUnverified, r.reviewWarnings], name).toEqual([[], []]);
    }
  });

  it.skipIf(!real)("V1, V2: an integer over vdbeSorterSort's relative slots is read relative to the base and rejected", () => {
    const unchanged = build(byName('V1'), load().maps);
    expect([unchanged.assembled.sha256, unchanged.kindUnverified]).toEqual([TARGET_SHA, []]);
    for (const [name, at, past] of [
      ['V1', 0xae, 2],
      ['V2', 0xa8, 0],
    ] as const) {
      const c = byName(name);
      const value = relativePastOurTable(load(), past);
      const { maps, kinds } = caseMaps(c);
      expect(kinds, name).toEqual({ verified: true, ops: expect.any(Map) });
      expect(operandKind(kinds, at), name).toBe('table-rel');
      expect(failure(c, maps), name).toMatch(
        new RegExp(`function 6458 .* UNRESOLVED: ours \\+0x${at.toString(16)} i32\\.const ${value}: a table slot relative to the base of ours`),
      );
    }
  });

  it.skipIf(!real)('a function the relink does not name is kind-unverified: it builds with every reading, over the limit', () => {
    const c = byName('U');
    const { maps, kinds } = caseMaps(c);
    expect(kinds).toEqual({ verified: false, why: `no functions of the shifted link are ${NEXT_ENTRY}` });
    const r = build(c, maps);
    expect(r.assembled.sha256).toBe(TARGET_SHA);
    expect(r.kindUnverified.map((u) => [u.match.index, u.why])).toEqual([[1260, kinds.verified ? '' : kinds.why]]);
    expect(kindUnverifiedOverLimit(r, 1)).toBeNull();
    expect(kindUnverifiedOverLimit(r, 0)).toMatch(
      /^1 matches are kind-unverified, more than the 0 allowed \(--max-kind-unverified\)[^]*\n {2}line 1: function 1260 /,
    );
  });
});

describe('table slots read with operand kinds', { timeout: 300_000 }, () => {
  it.skipIf(!real)("names the functions in vdbeSorterSort's relative slots: the table base plus each", () => {
    const { maps } = load();
    const ours = maps.ours.fnByKey.get('vdbeSorterSort')!;
    const a = attempt(maps, { ours, symbol: 'vdbeSorterSort', source: 'symbol' }, 6458, readPieceBodies(PIECES).get(6458)!);
    expect(a.verdict).toBe('match');
    const refs = referencedFunctionsAt(maps, ours, a.verdict === 'match' ? a.chosen : []);
    const named = (at: number) => refs.filter((r) => r.at === at).map((r) => maps.ours.fns.get(r.f)?.key);
    // each operand is relative to the base: our table base (1) plus it is the slot of the function named, the
    // operand alone the slot before it
    expect([0xa8, 0xab, 0xae].map(named)).toEqual([['vdbeSorterCompareInt'], ['vdbeSorterCompareText'], ['vdbeSorterCompare']]);
  });

  it.skipIf(!real)('offers a table slot every target slot of its function, however many', () => {
    // sqlite3_initialize's +0x32 names the empty function binaryen merged the target's into, which fills 126 slots.
    // Read with the match list applied, as the scan reads it: a landing can drop that function's line from the symbol
    // file and bring it back (docs/reference/facts/splat.md §S8), and its match line stays
    const { matches } = parseMatchList(readFileSync(`${URNA}/splat/matched.txt`, 'utf8'));
    const maps = withMatches(load().maps, matches);
    const ours = maps.ours.fnByKey.get('sqlite3_initialize')!;
    const piece = (m: SymbolMaps) => {
      const r = remapBody(m, ours);
      return r.ok ? r.pieces.find((p) => !(p instanceof Uint8Array) && p.at === 0x32) : undefined;
    };
    const p = piece(maps);
    expect(p !== undefined && !(p instanceof Uint8Array) && p.alternatives.length).toBe(126);
    const a = attempt(maps, { ours, symbol: 'sqlite3_initialize', source: 'symbol' }, 250, readPieceBodies(PIECES).get(250)!);
    expect(a.verdict).toBe('match');
    // an operand that may be anything is offered a function's slots only while they are few: here no slot, only the
    // integer and, as our slot number is past GLOBAL_BASE, what our data holds at that address. Which object that is
    // depends on the link: one the target lacks gives no piece, only a soft note of why the slots were not offered
    const anything = { ...maps, kinds: undefined };
    const unverified = piece(anything);
    const readings = unverified !== undefined && !(unverified instanceof Uint8Array) ? unverified.readings : [];
    const r = remapBody(anything, ours);
    const note = r.ok ? r.soft.find((s) => s.at === 0x32)?.reason : undefined;
    expect(readings.length === 0 ? note : readings.at(-1)).toMatch(/^literal$|the target function fills 126 slots$/);
    expect(readings.slice(0, -1).filter((x) => !x.startsWith('address '))).toEqual([]);
  });

  it.skipIf(!real)("reads renameUnmapSelectCb's slot in sqlite3AddDefaultValue as a table slot, as both links' tables say", () => {
    // its object as a whole has address relocations, which does not make this operand an address
    const l = load();
    const { kinds, plain } = l;
    const p = indexOf(plain, 'sqlite3AddDefaultValue');
    expect(valueAt(plain.module, p, 0x292)).toBe(slotOf(l, 'renameUnmapSelectCb'));
    expect(operandKind(kinds.functions.get(p), 0x292)).toBe('slot');
  });
});

describe('buildSplat with operand kinds', { timeout: 300_000 }, () => {
  it.skipIf(!real)('reports the kind-unverified matches and the review warnings apart', () => {
    const { maps } = load();
    const { matches } = parseMatchList('162 sqlite3ErrorMsg\n6458 vdbeSorterSort\n3418 LzmaEnc_WriteProperties\n');
    const r = buildSplat(maps, PIECES, matches, TARGET_SHA);
    expect(r.matched).toBe(3);
    expect(r.kindUnverified).toEqual([]);
    // LZMA's dictionary-size bounds, the source's integers, so literals: 3 << 12 (+ 1) and 3 << 19 (+ 1). Each is a
    // warning while it is past our table or our data, and a landing moves both ends
    const past = (why: string, end: number, values: number[]) => values.filter((v) => v >= end).map((v) => [3418, why, v]);
    expect(r.reviewWarnings.filter((w) => w.why !== 'target-object').map((w) => [w.match.index, w.why, w.value])).toEqual([
      ...past('past-table', maps.ours.tableSize, [12288, 12289]),
      ...past('past-data', maps.ours.dataEnd, [1572864, 1572865]),
    ]);
    // without a table every match is kind-unverified, and still builds; a limit below their count fails the build
    const none = buildSplat({ ...maps, kinds: undefined }, PIECES, matches, TARGET_SHA);
    expect(none.kindUnverified.map((u) => u.why)).toEqual(Array(3).fill('no operand-kind table'));
    const bodies = readPieceBodies(PIECES);
    expect(none.kindUnverifiedBytes).toBe([162, 6458, 3418].reduce((n, t) => n + bodies.get(t)!.length, 0));
    expect(kindUnverifiedOverLimit(none, 3)).toBeNull();
    expect(kindUnverifiedOverLimit(none, 2)?.split('\n')).toHaveLength(5);
  });
});

describe('splat-kinds', { timeout: 300_000 }, () => {
  it.skipIf(!real)('refuses names that do not describe the links it compares', () => {
    const dir = mkdtempSync(join(tmpdir(), 'kinds-'));
    for (const f of ['vota_web_wasm.wasm', 'names.tsv']) {
      copyFileSync(join(SHIFTED_DIR, f), join(dir, f));
    }
    const out = join(dir, 'kinds.json');
    writeFileSync(join(dir, 'names.sha256'), `${'0'.repeat(64)}\n`);
    expect(() => runSplatSubCommand('splat-kinds', [PLAIN, '--shifted', dir, '-o', out])).toThrow(
      /names\.tsv does not describe its vota_web_wasm\.wasm/,
    );
    copyFileSync(join(SHIFTED_DIR, 'names.sha256'), join(dir, 'names.sha256'));
    // the shifted link's names offered as the plain link's
    expect(() => runSplatSubCommand('splat-kinds', [PLAIN, '--shifted', dir, '--map-dir', SHIFTED_DIR, '-o', out])).toThrow(
      /does not describe .*vota_web_wasm\.wasm: run make -C src link-map/,
    );
    expect(existsSync(out)).toBe(false);
  });
});
