# uenux2 simulador::CWasmScreenMT, the wasm build's api::IScreenMT, in src/uenux2/mock/app/simulador/wasm/cwasmscreenmt.cpp
# (+ cwasmscreenmt.h), with every slot of the api::IScreenMT interface (api/gui/iscreenmt.h), the Draws of
# api::CBeepFieldMT, CBuzzFieldMT and CClockFieldMT (api/gui/c{beep,buzz,clock}fieldmt.{h,cpp}) and api::CPreShowClearMT
# (api/gui/cpreshowclearmt.{h,cpp}, over the template api::IPreShow<MEDIA>, api/gui/ipreshow.h):
# - matched: Clear (target fn 8810, slot 2), Buzz (8787, slot 6), Beep (5039, slots 7 and 19, one body), Led0 (5038, slots
#   8 and 11, one body), Led1 (5036, slots 9 and 10, one body), GetWidth (8743, slot 17), GetHeight (8742, slot 18), the
#   three Draws (11053, 11049, 11048), PreShow (11047), and the empty slots 4, 5, 13, 15 and 16 (the shared 1870 and 218).
#   std::string::assign(size_type, char), target fn 1355, is libc++'s: Clear calls it and the roots keep its result.
# - written, and `differs` at the tree's flags: ShowText (8799, slot 3) and Refresh (8746, slot 14). These are the
#   sources measured right, and each needs one flag uenux2 does not have; a private whole link with
#   UENUX2_EXTRA='-O3 -std=c++23' (docs/reference/facts/app-flags.md section F9 item 6) gives both target bodies.
#   ShowText needs -std=c++23: `text.GetText().substr(0, 40)` on an rvalue is C++23's `substr() &&`, which moves the
#   string into place. At -std=c++20 it copies, and no public string call in C++20 gives the moved form: a helper
#   that moves and then resizes reads the size after the move, and one that reads it first keeps resize's append path.
#   Its object is the same at -O2 and -O3. Refresh needs -O3: libc++'s push_back costs 225 against -O2's threshold of
#   225 and inlines at -O3's 250, and -O3 unrolls the loop; at -O2 it stays a call. Its object is the same under
#   both standards, once the object-local indices are normalised. Both stay as written, so the rows match with no edit
#   if the tree's flags change.
# - pending: ShowClock (8757, slot 12) and ~IScreenMT (8741), with CWasmScreenMT's implicit D2 and D0 (8745, 8744) waiting
#   on the second: 78-uenux2-cwasmscreenmt-pending.cpp says for what.
# Choices, no evidence decides them:
# - the paths. No record names any of these files. cwasmscreenmt.cpp is the probable_file of cluster 128 in
#   ledger/tu-clusters.tsv (class-convention), in the directory where simulador's other wasm classes have records. The
#   field files are chosen beside cledfieldmt.cpp, the one recorded file of the family. The data order is CBeepFieldMT,
#   CLedFieldMT, CBuzzFieldMT, CClockFieldMT, CPreShowClearMT, after cmoviefield.cpp's data, and the band order agrees
#   (11053, 11050, 11049, 11048, 11047 of ledger/ordinals.tsv's uses 1). That is not name order, so it says neither one
#   file nor several; all of them in cledfieldmt.cpp would fit it, Beep in that file's unrecovered lines 18-29.
# - every name but ShowClock's (iscreenmt.h says from what), the data members', the constructors' parameters and
#   IPreShow's member.
# - IText's default argument and CFixedText's constructor signature (api/gui/itext.h, cfixedtext.h).
# Forms that give the same code, measured by `cmp` of the object at -O2 -std=c++20 and at -O3 -std=c++23 unless a list says
# otherwise. Forms that differ from what is written, and so are not choices, are listed last.
# - Clear: four explicit assign calls.
# - ShowText: y as an int; x as a TPosition; coluna as an int with a cast at the compare, or not initialized; texto const;
#   std::copy_n over begin() iterators, std::copy, or char_traits::copy.
# - Refresh: append and push_back for the two +=; a local const char* for the conditional; data() for c_str(); and, at
#   -O3 only, an index loop for the range-for.
# - the class: std::array for the C array; m_led set in the constructor's mem-initializer.
# - api::CTextFieldMT::Draw (10934): `m_textDesenhado != nullptr` or `.get()` for the bool test. Compared by Draw's
#   body: these objects hold their own file names.
# - api::CTextFieldUpdateMT::Draw (10548): an explicit ALINHAMENTO_ESQUERDA for the default; a named local moved into
#   m_textoDesenhado.
# Forms that do not give the target's code: in ShowText, `linha` taken after the string (the object then has the mul
# nested in the add, and the final add has this on the left, not on the right), posicao.y read each time instead of
# once, the range test written `!(y >= 1 && y <= 4)`, x read inside the else, memcpy or replace for the copy, the two
# arguments of std::min swapped; in Refresh, four explicit appends (other block placement at -O3); in both Draws, the
# compare's operands swapped, or the string of spaces in a named local; and a member alignment in CFixedText (itext.h
# says why).
# Paths relative to src/uenux2; the generic uenux2 rule compiles mock/ too and depends on each source and every uenux2
# header.
CWASMSCREENMT_SRCS := mock/app/simulador/wasm/cwasmscreenmt.cpp src/api/gui/cbeepfieldmt.cpp src/api/gui/cbuzzfieldmt.cpp \
    src/api/gui/cclockfieldmt.cpp src/api/gui/cpreshowclearmt.cpp
UENUX2_SRCS += $(CWASMSCREENMT_SRCS)
# ShowClock and ~IScreenMT are not reconstructed: 78-uenux2-cwasmscreenmt-pending.cpp gives the vtables trapping bodies,
# compiled with the unit's flags
$(ROOT)/$(APP)/78-uenux2-cwasmscreenmt-pending.o: $(ROOT)/src/units/78-uenux2-cwasmscreenmt-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/78-uenux2-cwasmscreenmt.mk $(ROOT)/src/uenux2/mock/app/simulador/wasm/cwasmscreenmt.h $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/78-uenux2-cwasmscreenmt-pending.cpp -o $(R)
# nothing reconstructed creates the screen or CPreShowClearMT yet: 78-uenux2-cwasmscreenmt-roots.cpp keeps the vtables,
# std::string::assign and the control blocks the way the target reaches them; it reads the classes' headers
$(ROOT)/$(APP)/78-uenux2-cwasmscreenmt-roots.o: $(ROOT)/src/units/78-uenux2-cwasmscreenmt-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/78-uenux2-cwasmscreenmt.mk $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h) $(ROOT)/src/uenux2/src/app/vota/operador/comum/ctextfieldupdatemt.h
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/78-uenux2-cwasmscreenmt-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/78-uenux2-cwasmscreenmt-pending.o $(APP)/78-uenux2-cwasmscreenmt-roots.o
