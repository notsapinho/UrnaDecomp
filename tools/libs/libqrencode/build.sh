#!/bin/bash
# Probe build of libqrencode at one release tag, with the pinned toolchain (docs/reference/facts/libraries.md B10).
#   tools/libs/libqrencode/build.sh <tag> <variant> [compile flags...]      (from the urna root)
# <tag>      a tag of the full clone in third_party/libqrencode (v4.1.1, v4.1.0, v4.0.2, …): its tree is exported with
#            `git archive` into build/out/libqrencode-probe/src/<tag>, so the checkout itself stays at the pinned tag.
# <variant>  names the output dir for the flags given (O3pic, O2pic, …).
# The nine library sources are compiled in CMakeLists.txt's order with the defines that file adds (the version, HAVE_SDL=0,
# STATIC_IN_RELEASE=static) after the flags given, and linked with driver.c at the target's link line
# (-Oz -fexceptions); --emit-symbol-map names the probe's functions and changes only their order.
# Output: build/out/libqrencode-probe/<tag>-<variant>/{obj/*.o,probe.js,probe.wasm,probe.js.symbols}
set -euo pipefail
TAG=${1:?usage: build.sh <tag> <variant> [flags...]}
VARIANT=${2:?usage: build.sh <tag> <variant> [flags...]}
shift 2
ROOT=$(cd "$(dirname "$0")/../../.." && pwd)
cd "$ROOT"
SRC=build/out/libqrencode-probe/src/$TAG
OUT=build/out/libqrencode-probe/$TAG-$VARIANT
if [ -z "${INSIDE_DOCKER:-}" ]; then
  git -C third_party/libqrencode rev-parse -q --verify "refs/tags/$TAG" >/dev/null \
    || { echo "third_party/libqrencode has no tag $TAG (tools/setup/bootstrap.sh clones the full repository)" >&2; exit 2; }
  if [ ! -d "$SRC" ]; then
    mkdir -p "$SRC.part"
    git -C third_party/libqrencode archive "$TAG" | tar -x -C "$SRC.part"
    mv "$SRC.part" "$SRC"
  fi
  export TMPDIR=/tmp
  exec build/docker-build.sh env INSIDE_DOCKER=1 bash tools/libs/libqrencode/build.sh "$TAG" "$VARIANT" "$@"
fi
VER=${TAG#v}
DEFS=(-DMAJOR_VERSION="${VER%%.*}" -DMINOR_VERSION="$(echo "$VER" | cut -d. -f2)" -DMICRO_VERSION="$(echo "$VER" | cut -d. -f3)"
  "-DVERSION=\"$VER\"" -DHAVE_SDL=0 -DSTATIC_IN_RELEASE=static)
rm -rf "$OUT"
mkdir -p "$OUT/obj"
printf '%s\n' "$@" > "$OUT/cflags.txt"
for f in qrencode qrinput bitstream qrspec rsecc split mask mqrspec mmask; do
  emcc "$@" "${DEFS[@]}" -I"$SRC" -c "$SRC/$f.c" -o "$OUT/obj/$f.o"
done
emcc -O3 -I"$SRC" -c tools/libs/libqrencode/driver.c -o "$OUT/driver.o"
OBJS=()
for f in qrencode qrinput bitstream qrspec rsecc split mask mqrspec mmask; do OBJS+=("$OUT/obj/$f.o"); done
em++ -Oz -fexceptions "${OBJS[@]}" "$OUT/driver.o" -o "$OUT/probe.js" --no-entry -sEXPORTED_FUNCTIONS=_probe_qr \
  -sALLOW_MEMORY_GROWTH=1 -sSTACK_SIZE=8MB --emit-symbol-map
ls -l "$OUT/probe.wasm"
