# RHVoice built with no landing pads (RHVOICE_DIR in src/Makefile, docs/reference/facts/libraries.md B6), with what that
# build takes away from the link put back. No source of its own: the flags, one roots rule, and names under the hand-edit
# marker of splat/symbol_addrs.txt, each with its evidence in its comment. It changes no RHVoice source but the one the
# build overlays (tools/libs/rhvoice/build.sh).
#
# The build is per object: every object without strict aliasing, at the allow-list but userdict.cpp, which is at
# -fignore-exceptions (build.sh's --only). It is a new directory under build/out/rhvoice/, so a checkout runs
# `make -C src libs` once before its next link.
#
# Matches: 172 added to the base with the allow-list alone. 41 follow from the flag and the roots alone: 208, 2653, 3469,
# 9687, 2567 and 3904 and 12014 among them. 3904 is the merged destructor body step 1 of docs/how-to-decompile.md names,
# whose third caller is api::CSubReport's D2. 131 more follow from the hand-edit names, among them 2186, 8890 and the hts_*
# feature functions over their merged bodies 863 and 3880. 5805 is not one of them. It once matched as RHVoice::text_token's
# D2 through a twin, but its target callers, 7787 and 11561, are not RHVoice's, and only landing pads reached that
# destructor in our link. It is comum::CCargos::~CCargos, unit 110's.
# The per-object build adds 28 (9528 to 9556 matches) and loses none: 756, 896, 915, 1199, 1530, 2211, 2215, 2705, 2875,
# 3535, 3537, 3550, 3560, 3566, 3568, 5219, 5224, 5245, 5246, 5256, 5257, 5265, 5286, 5320, 9591, 9625, 9678, 9682. The
# scan names 915, 1199, 2705, 2875, 3550, 3560, 5286 and 5320 by content. Our candidates for the target callers 9638,
# 9644, 9727 and 9921 call the bodies named 915, 1199, 2705, 3560 and 5320, as the target's do. 3550 follows 3548 and 3549
# in userdict.cpp.o, and 5286 sits in params.cpp.o's run, each with ld_index falling as the index rises; 2875 and 3550
# share their target caller 1245.
#
# Choices, each measured:
# - The flags. -fno-strict-aliasing gives the reloads the target has (HTS_SStreamSet_clear, item::remove: B6). At the
#   allow-list it costs the four get_key rows (4975, 9683, 9697, 9700), which userdict.cpp.o at -fignore-exceptions keeps,
#   adding 2875, 3550, 5265, 9678 and 9682 (B6's per-object table). The other objects stay at the allow-list, a choice:
#   one object off the default is the smallest step from the uniform build, the closest one flag set found that loses no
#   row, whose evidence is the vector<T>::push_back family alone. B6 also measured a per-object build with
#   -fignore-exceptions as the default that loses no row and adds more. B6 reads most objects better at
#   -fignore-exceptions, and why that family has the target's shape is unknown.
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
# - 3674: its target callers (395, 1151, 5410) are not written. It matched by content only with RHVoice at
#   -fignore-exceptions, where a twin's body is the target's; userdict.cpp.o alone at -fignore-exceptions does not give it.
# - 8811, 194, 2706: differ past the first local. Not read further.
# - C++20 (B6): the best per-object build found has 9601 matches, 45 more than this one, and loses 354, whose callee
#   needs language.cpp.o at -fignore-exceptions while 938 and 1682 need it at the allow-list.
$(ROOT)/$(APP)/103-rhvoice-nocatch-roots.o: $(ROOT)/src/units/103-rhvoice-nocatch-roots.cpp $(ROOT)/src/units/103-rhvoice-nocatch.mk $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/103-rhvoice-nocatch-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/103-rhvoice-nocatch-roots.o
