# RHVoice built with no landing pads (RHVOICE_DIR in src/Makefile, docs/reference/facts/libraries.md B6), with what that
# build takes away from the link put back. No source of its own: the flag, one roots rule, and names under the hand-edit
# marker of splat/symbol_addrs.txt, each with its evidence in its comment. It changes no RHVoice source but the one the
# build overlays (tools/libs/rhvoice/build.sh).
#
# Matches: 172 added to the base. 41 follow from the flag and the roots alone: 208, 2653, 3469, 9687, 2567 and
# 3904 and 12014 among them. 3904 is the merged destructor body step 1 of docs/how-to-decompile.md names, whose third
# caller is api::CSubReport's D2. 131 more follow from the hand-edit names, among them 2186, 8890 and the hts_* feature
# functions over their merged bodies 863 and 3880. 5805 is not one of them. It once matched as RHVoice::text_token's D2
# through a twin, but its target callers, 7787 and 11561, are not RHVoice's, and only landing pads reached that destructor
# in our link. It is comum::CCargos::~CCargos, unit 110's.
#
# Choices, each measured:
# - The flag. The allow-list is the closest build found that loses no row, as one flag set for every object. The evidence
#   for it is the vector<T>::push_back family alone: other objects read better at -fignore-exceptions, and why that family
#   has the target's shape is unknown (docs/reference/facts/libraries.md B6 has the per-object table).
#   -sEXCEPTION_CATCHING_ALLOWED=[nothing] and -mllvm -enable-emscripten-cxx-exceptions=0 give the same 54 objects, by cmp,
#   so between those two the spelling is a choice.
# - HTS_Audio_initialize with one parameter, in the overlay of str_hts_engine_impl.cpp. Giving HTS_engine.c's call and
#   HTS_hidden.h's declaration three parameters is the other form: two objects differ and the plain link is byte for byte
#   the same (shasum of the wasm), so the target cannot tell them apart.
# - The roots' stand-in names and bodies.
#
# What waits, and for what:
# - 2650 calls 388 where ours calls 424: two ~shared_ptr bodies in the target, one in our link, and 388 keeps a result no
#   caller of ours reads. 3552 is unit 115's.
# - 3473 (decodeCommon): calls 543, a body none of ours equals. document.cpp.o, the object that defines
#   vector<unsigned>::push_back(&&), ahead of the runtime moves the row to `call 938` and matches nothing.
# - 9682: the target holds word_editor::delete_char inline, 53 rows ours has behind a call. Ours keeps that in-class member
#   out of line in both its callers (symbol::apply, deletion::apply), so this is what clang inlines, not a name.
# - 2875 and 3674: match by content only at -fignore-exceptions, where their twins' bodies are the target's. Their target
#   callers (813, 1245, 11943, 11946 and 395, 1151, 5410) are not written. 2875 scores 6 over 557 rows here, 4 operand-only.
# - 8811, 194, 2706: differ past the first local. Not read further.
# - 2875 and 9682 match with userdict.cpp.o alone at -fignore-exceptions, a per-object build this unit does not land.
# - The rows -fno-strict-aliasing adds, the four get_key rows it costs at the allow-list, and C++20: docs/reference/facts/libraries.md B6.
$(ROOT)/$(APP)/103-rhvoice-nocatch-roots.o: $(ROOT)/src/units/103-rhvoice-nocatch-roots.cpp $(ROOT)/src/units/103-rhvoice-nocatch.mk $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/103-rhvoice-nocatch-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/103-rhvoice-nocatch-roots.o
