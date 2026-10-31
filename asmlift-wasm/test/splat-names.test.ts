// tools/round/splat_names.py's names of binaryen's bodies: the real function, on synthetic rows, so no link is needed. A
// merge body takes its first member's name, and an internal symbol repeats across objects, so two bodies can take one.
import { spawnSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';
import { describe, expect, it } from 'vitest';

const ROOT = fileURLToPath(new URL('../..', import.meta.url));

type Row = [number, string, string, string, number];

const SCRIPT = `
import json, sys
sys.path.insert(0, 'tools/round')
from splat_names import name_rows
functions, entries = json.load(sys.stdin)
print(json.dumps(name_rows(functions, entries)))
`;

function run(functions: [number, number, string][], entries: [string, string][]) {
  return spawnSync('python3', ['-I', '-B', '-c', SCRIPT], {
    cwd: ROOT,
    input: JSON.stringify([functions, entries]),
    encoding: 'utf8',
  });
}

function rows(functions: [number, number, string][], entries: [string, string][]): Row[] {
  const r = run(functions, entries);
  expect(r.stderr).toBe('');
  expect(r.status).toBe(0);
  return JSON.parse(r.stdout) as Row[];
}

const DTOR = '__cxx_global_array_dtor';
const ENTRIES: [string, string][] = [
  [DTOR, 'app/a.cpp.o'],
  [DTOR, 'app/b.cpp.o'],
  ['_ZN1T7GetInstEv', 'app/a.cpp.o'],
];

describe('name_rows', () => {
  it('gives a wasm-ld function its name and object', () => {
    expect(rows([[10, 5, '2']], ENTRIES)).toEqual([[10, '_ZN1T7GetInstEv', 'app/a.cpp.o', '2', 5]]);
  });

  it('leaves a merge body bare when its first member takes no other body', () => {
    const named = rows(
      [
        [10, 5, 'byn$mgfn-shared$2'],
        [11, 6, 'byn$mgfn-shared$0'],
      ],
      ENTRIES,
    );
    expect(named.map((r) => r[1])).toEqual(['byn$mgfn-shared$_ZN1T7GetInstEv', `byn$mgfn-shared$${DTOR}`]);
    expect(named.every((r) => r[2] === '<binaryen>' && r[3] === '-')).toBe(true);
  });

  it('spells the object of two merge bodies over one internal symbol, and of no other', () => {
    const named = rows(
      [
        [10, 5, 'byn$mgfn-shared$0'],
        [11, 6, 'byn$mgfn-shared$1'],
        [12, 7, 'byn$mgfn-shared$2'],
      ],
      ENTRIES,
    );
    expect(named.map((r) => r[1])).toEqual([
      `byn$mgfn-shared$${DTOR}@app/a.cpp.o`,
      `byn$mgfn-shared$${DTOR}@app/b.cpp.o`,
      'byn$mgfn-shared$_ZN1T7GetInstEv',
    ]);
  });

  it('keeps any other name of binaryen as it is', () => {
    expect(rows([[10, 5, '__wasm_call_ctors']], ENTRIES)).toEqual([[10, '__wasm_call_ctors', '<binaryen>', '-', 5]]);
  });

  it('allows two wasm-ld functions one name: their objects part them', () => {
    const named = rows(
      [
        [10, 5, '0'],
        [11, 6, '1'],
      ],
      ENTRIES,
    );
    expect(named.map((r) => r[1])).toEqual([DTOR, DTOR]);
  });

  it('stops when two merge bodies keep one name, one object spelled or not', () => {
    const r = run(
      [
        [10, 5, 'byn$mgfn-shared$0'],
        [11, 6, 'byn$mgfn-shared$1'],
      ],
      [
        [DTOR, 'app/a.cpp.o'],
        [DTOR, 'app/a.cpp.o'],
      ],
    );
    expect(r.status).not.toBe(0);
    expect(r.stderr).toContain(`byn$mgfn-shared$${DTOR}@app/a.cpp.o`);
    expect(r.stdout).toBe('');
  });

  it('stops when two bodies of binaryen hold any one name', () => {
    const r = run(
      [
        [10, 5, '__wasm_call_ctors'],
        [11, 6, '__wasm_call_ctors'],
      ],
      ENTRIES,
    );
    expect(r.status).not.toBe(0);
    expect(r.stderr).toContain('__wasm_call_ctors');
  });
});
