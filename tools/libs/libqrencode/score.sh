#!/bin/bash
# Score the target's libqrencode functions against a probe of tools/libs/libqrencode/build.sh (depth 0: the body alone).
#   tools/libs/libqrencode/score.sh <tag>-<variant>        (from the urna root; Node 24 first on PATH)
# One line per pair: target index, the probe function, `pnpm wasm score`'s line (rows differing over rows), then the sum
# of the differing rows. The pairs are the census pairs of the 4.1.1 probe, whose QRcode_free is the body binaryen merges
# BitStream_free into, and 5348 Split_eat8, which pairs in the whole link (docs/reference/facts/libraries.md B10).
set -uo pipefail
P=build/out/libqrencode-probe/${1:?usage: score.sh <tag>-<variant>}
ROOT=$(cd "$(dirname "$0")/../../.." && pwd)
cd "$ROOT/asmlift-wasm"
sum=0
while read -r t name; do
  i=$(awk -F: -v n="$name" '$2==n{print $1}' "../$P/probe.js.symbols")
  if [ -z "$i" ]; then echo "$t $name: not in the probe"; continue; fi
  s=$(pnpm --silent wasm score ../target/vota_web_wasm.wasm "$t" "../$P/probe.wasm" "$i" --depth 0 2>&1 | /usr/bin/grep -m1 '^score')
  echo "$t $name: $s"
  sum=$((sum + $(echo "$s" | sed -n 's/^score \([0-9]*\) over.*/\1/p')))
done <<'EOF'
493 BitStream_appendNum
1147 QRspec_lengthIndicator
1253 MMask_writeFormatInformation
1254 QRcode_free
1534 QRinput_estimateBitsMode8
1899 QRinput_estimateBitsModeAn
2218 MQRspec_lengthIndicator
2718 QRinput_encodeBitStream
2719 QRinput_estimateBitsModeNum
3595 RSECC_encode
3596 QRinput_List_newEntry
3597 QRinput_append
5346 MQRspec_getWidth
5347 MQRspec_getDataLengthBit
5348 Split_eat8
5349 QRspec_getMinimumVersion
5350 BitStream_appendBytes
5351 QRinput_getByteStream
5352 QRinput_isSplittableMode
10241 MQRspec_getECCLength
EOF
echo "differing rows: $sum"
