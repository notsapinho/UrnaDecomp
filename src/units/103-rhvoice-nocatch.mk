# RHVoice built with no landing pads (RHVOICE_DIR in src/Makefile, docs/reference/facts/libraries.md B6), with what that
# build takes away from the link put back. No source of its own: the flag, one roots rule, and names under the hand-edit
# marker of splat/symbol_addrs.txt, each with its evidence in its comment. It changes no RHVoice source but the one the
# build overlays (tools/libs/rhvoice/build.sh).
#
# Matches: 172 against the base, none lost. 41 follow from the flag and the roots alone: 208, 2653, 3469, 9687, 2567 and
# 3904 and 12014 among them. 3904 is the merged destructor body step 1 of docs/how-to-decompile.md names, whose third
# caller is api::CSubReport's D2. 131 more follow from the hand-edit names, among them 2186, 8890 and the hts_* feature
# functions over their merged bodies 863 and 3880.
#
# Choices, each measured:
# - The flag's spelling. The bytes need clang's exception semantics in the IR and no pad in the object;
#   -sEXCEPTION_CATCHING_ALLOWED=[nothing] gives that, and so does -mllvm -enable-emscripten-cxx-exceptions=0: the same 54
#   objects, by cmp. Which flag TSE's build used is not recoverable.
# - HTS_Audio_initialize with one parameter, in the overlay of str_hts_engine_impl.cpp. Giving HTS_engine.c's call and
#   HTS_hidden.h's declaration three parameters is the other form: two objects differ and the plain link is byte for byte
#   the same (shasum of the wasm), so the target cannot tell them apart.
# - The roots' stand-in names and bodies.
#
# What waits, and for what:
# - 2183 and 3552 (BERDecoderPartial's D2, vector<Visitante>::__destroy_vector): 3552 has 6 rows fewer than ours, and 8824,
#   8846, 8847 and 2650 hold the rest of that vector. 2650 calls 388 where ours calls 424: two ~shared_ptr bodies in the
#   target, one in our link, and 388 keeps a result no caller of ours reads.
# - 3473 (decodeCommon): calls 543, a body none of ours equals. document.cpp.o, the object that defines
#   vector<unsigned>::push_back(&&), ahead of the runtime moves the row to `call 938` and matches nothing.
# - 9682: word_editor::delete_char has no name, and its one caller is this row.
# - 2875 and 3674: match by content only at -fignore-exceptions, where their twins' bodies are the target's. Their target
#   callers (813, 1245, 11943, 11946 and 395, 1151, 5410) are not written. 2875 scores 6 over 557 rows here, 4 operand-only.
# - 8811, 194, 2706: differ past the first local. Not read further.
# - The 24 rows -fno-strict-aliasing adds, and the four get_key rows it costs: docs/reference/facts/libraries.md B6.
$(ROOT)/$(APP)/103-rhvoice-nocatch-roots.o: $(ROOT)/src/units/103-rhvoice-nocatch-roots.cpp $(ROOT)/src/units/103-rhvoice-nocatch.mk $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/103-rhvoice-nocatch-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/103-rhvoice-nocatch-roots.o
