# uenux2 comum's caller of libc++'s std::filesystem::remove_all: a stand-in in 261-uenux2-remove-all-callers-roots.cpp
# for target fn 5571 (comum, not written: it loads names such as ".AppleDouble", ".Spotlight-V100" and
# "Thumbs.db:encryptable", builds a path from each and calls remove_all on it in a loop; its callers are 5572 and 11166,
# slot 9 of comum::impl::CValidaMidia's vtable, unit 179). No source of its own: the roots declare __remove_all through
# an asm label and include no header, so they emit no code of TSE or of the library, and no match comes from this
# object; each match below is libc++.a's or libc.a's own object, which the stand-in keeps in the link and gives the
# target's callers.
#
# The target's 5571 holds __remove_all inlined (its ErrorHandler<uintmax_t> built in its frame with "remove_all" at
# 153755, a null error_code pointer and the path, then a direct call of fn 4678 with -100, AT_FDCWD), and with it:
# - fn 4678, remove_all_impl(int, const path&, error_code&) (operations.o), which calls itself through table slot 8859
#   and reaches libc's unlinkat (fn 6239, unlinkat.o);
# - fn 4679, ErrorHandler<unsigned long long>::report(const error_code&) (operations.o), with two callers in the
#   target, 5571 and CZip::DoAdd (9538, unit 06, whose std::filesystem::file_size reaches it: a reading), so binaryen
#   keeps it out of line; without the stand-in its row read `no-candidate`;
# - fn 4791, posix_readdir (directory_iterator.o), and fn 4789, path's constructor from a string_view, whose table slots
#   (8857, 8858) remove_all_impl's invoke calls take, so binaryen keeps them out of line in __dir_stream::advance (fn
#   4793) too: without remove_all_impl in our link, advance held posix_readdir inlined (a second stack frame) and read
#   `differs` on its locals.
# Measured with this unit's landing (the scan's verdicts against its base): 4678, 4679, 4791, 4793 and 6239 turn
# `match` and 4789 `differs` (below), besides units 06's and 122's rows; in our link the stand-in calls remove_all_impl
# and ErrorHandler<unsigned long long>::report directly, __remove_all inlined into it (pnpm wasm fn on its index). The
# stand-in's census pairs: none (step 7's command over the -roots.o).
#
# Not matched, and what each waits for:
# - fn 4789 (path's constructor from a string_view): named (`table`) and `differs`. The target's 4789 is a 15-byte thunk
#   f1085(p0, p1, p2, 8296) of binaryen's merged body 1085, which twelve such thunks share (4676, 4686, 4789, 5641,
#   10078, 10134, 11154, 11211, 11264, 11637, 11895, 12045: nine pass slots of one 15-byte body, fn 1266); in our link
#   4789's copy is a whole body (the scan's first difference is at +0x3) and the other eleven read `no-candidate`, so
#   no such merge forms. It waits for the merge to form (src/units/README.md "Pending members", a member whose target
#   body is a merge thunk); 1085, 4676 and 4686 wait with it.
# - fn 5571 itself, which the stand-in stands for; the stand-in goes when 5571 is in the link.
$(ROOT)/$(APP)/261-uenux2-remove-all-callers-roots.o: $(ROOT)/src/units/261-uenux2-remove-all-callers-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/261-uenux2-remove-all-callers.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/261-uenux2-remove-all-callers-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/261-uenux2-remove-all-callers-roots.o
