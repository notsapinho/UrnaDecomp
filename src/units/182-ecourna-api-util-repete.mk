# ecourna ecourna::api::util::Repete in src/ecourna/api/util/repete.cpp, with its header repete.hpp: it appends a
# string to another a given number of times, reserving the room first. It has no target index of its own: its one
# caller, api::CGenericTags::EncodeTLV (target fn 5467, unit 33), holds its body, which binaryen inlined, and our link
# does the same (no Repete in build/out/wasm-map/vota_web/names.tsv). Its tree is a reading from a measured flag:
# EncodeTLV matches only with the loop compiled with -fno-delete-null-pointer-checks (in the forms measured;
# src/units/33-uenux2-cgenerictags.mk gives the scores), and ecourna is the one tree here compiled with that flag
# (docs/reference/facts/app-flags.md F3); no record names the tree. No record names the function either:
# its name, its being a free function, its namespace and its files' paths are chosen. It needs no roots: the target
# inlines it into its only caller, and so does our link. Paths relative to src/ecourna; the generic ecourna rule depends
# on the source and every ecourna header.
REPETE_SRCS := api/util/repete.cpp
ECOURNA_SRCS += $(REPETE_SRCS)
