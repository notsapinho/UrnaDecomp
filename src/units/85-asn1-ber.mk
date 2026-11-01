# ASN.1 runtime: BEREncoder, BERDecoder and DataLengthCounter, with the helpers they share. src/mk/asn1.mk builds and
# keeps these objects, so this fragment has no sources and no rules: it holds what docs/how-to-decompile.md step 3 asks
# a fragment to say. docs/reference/facts/asn1.md has the evidence (§A2 the flags, §A5 the names, §A6 the files).
#
# 3473 (decodeCommon) matches, held up by the link (docs/reference/facts/splat.md §S10 item 19): no body of the runtime
# equals its callee 543 (§A5), and it matches since unit 89's ccandidaturas.cpp.o, ahead of asn1.o on the link line,
# gives the vector<unsigned>::push_back(&&) it calls, a copy binaryen merges into the body that matches 543 (unit 89's
# fragment says how). Before that ours called 3475 there. The source stays as written.
#
# What the target decided:
# - checkTag: a bool, inverted from upstream's int dontCheckTag. 996 and 8853 store 1 where upstream clears the flag,
#   8861 stores 0 where upstream sets it, all with i32.store8 at +28; 8861 tests it with a compare with 1, a bool's
#   read in a condition (docs/reference/facts/reading.md §R14), and saves and restores one byte around the visit,
#   which is FlagSaver over a bool. Its name is chosen (asn1.h says so).
# - CountBits (1066) compares with >=: the target tests range >> nBits, which LLVM folds from >= and not from upstream's
#   >, which keeps a shift of 1.
# - decodeHeader(unsigned&, bool&, unsigned&) (1669) refuses a long-form tag under 31 after its loop, which upstream
#   does not; the target's `i32.lt_u(tagVal, 31)` is that test.
# - getHeaderLength and encodeTag mask 0x1FFFFFFF, and encodeTag masks the identifier with 0xE0: the constants of 3463
#   and 5045.
# - DataLengthCounter's SEQUENCE_OF_Base visitor (8759) reads end() once: the form that rereads it gives other rows.
# - BEREncoder::do_visit(const CHOICE&) (8792) tests both no-selection values: the target's `<= -3` unsigned.
# - visitUnknownExtensions (8852) returns whether the position already was the sequence's end. A form that branches
#   gives 24 rows against the target's 21.
# - CHOICE::setID (5077) restores the id it loses on a failed search, and does not fall back to the selection's own
#   tag, which getSelectionTag would. Of the six block orders tried, only the form with the id saved at the top and
#   result tested after the if/else gives the target's.
# - Inliners. wasm-opt: getDataLength into encodeHeader (994), decodeChoicePreamle into do_visit(CHOICE&) (8861) and
#   vector<const char*>::push_back into preVisitExtensionRoots (8854), each behind a second prologue, each with one
#   caller left. clang: getDataLength into getObjectLength (2647), in one frame. encodeHeader and the two INTEGER
#   visitors keep calls because the bodies are in other TUs (§A6). 8854 needed BERDecoder::decode out of the roots.
#
# Chosen, with the forms measured to give the same bytes (one function's rows, object-local numbers masked):
# - The flag's spelling: plain -Os -std=c++17 -DNDEBUG gives the same 47 objects, the 15 runtime TUs and the 32 modules
#   (cmp).
# - src/asn1/DataLengthCounter.cxx, the file and its name: the data put the class outside BEREncoder's object and go no
#   further. With the class at the end of PEREncoder.cxx the link gives the same 8046 matches and the target's sha256;
#   DataFree.cxx was not tried.
# - getHeaderLength sits in that file: both TUs call it and clang inlines it in neither (cost 85 against 50). In
#   BEREncoder.cxx the link gives the same 8046 matches and the target's sha256.
# - getIntegerDataLength in asn1.cxx: any TU but those two gives the same calls.
# - CHOICE::setID stays in BERDecoder.cxx, upstream's file, though 5077 sits next to asn1.o's 5078 in its band. It spells
#   info()->tags[choiceID]. In asn1.cxx over getSelectionTagInternal(), which clang inlines there, it gives the same
#   rows.
# - The spelling of each of these, every alternative the same bytes: 8792 with the two tests swapped, or written over
#   currentSelection(); 8852 saving the old position in a local before the store; 1669 with `tagVal <= 0x1e`; 5045's
#   identifier as `(char)((a_tag >> 24) & 0xe0)` or `(char)((a_tag & 0xe0000000) >> 24)`; 8759's end declared before
#   the loop; FlagSaver's two members in either order; 1066's test as `(range >> nBits) != 0` (the whole asn1.o, cmp).
