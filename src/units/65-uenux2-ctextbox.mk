# uenux2 api::CTextBox: Draw and Move (target fns 10958 and 10957, slots 2 and 9 of the vtable @1582232) and the
# constructor (no target function: binaryen inlined it into fn 11805, whose second stack-pointer prologue holds its
# throw) in src/uenux2/src/api/gui/ctextbox.cpp, the file the class's records name, with the throws on the records' lines
# 41, 69 and 90 (the lines around them are a choice); the class header api/gui/ctextbox.h, the 4961, 4962 and 4963
# enumerators of eueguierror.h, the layout header api/gui/cfixedtext.h and the base api/gui/iform.h, which was stub-only.
# Draw is the key function, so ctextbox.o emits the vtable with the implicit destructors (10955, 10954) and the inline
# GetTypeName (10953). The destructors inline CFixedText's, so that object emits CFixedText's vtable too, whose D2 and D0
# (7706, 7666) are the two thunks into binaryen's merged bodies 1727 and 1969. Paths relative to src/uenux2; the generic
# uenux2 rule depends on the source and every uenux2 header.
#
# Draw's switch: the order of its cases is evidence, by the 24 orders of the three cases and `default` compiled and
# their calls compared with the target's: only 0, 2, 1, default and 2, 1, default, 0 give the target's blocks, and those
# two give the same code but for the object's own data offsets; so the first, which keeps `default` last, is a choice.
# Draw's other forms, by the function's disassembly with the object-local numbers masked. The same code: the SPoint's
# members assigned in either order instead of its braces, `rect.left + static_cast<TPosition>(rect.right - rect.left + 1)
# / 2` instead of Width() (here the member is a choice: api/gui/primitives.h says where it is evidence), and the text not
# const. Another code: the width in a local TPosition (it loads left and right first), the text built after Clear, and
# the SFont in one local before the switch (the target builds one in each case). The constructor is compared with
# nothing: its member order is read from 11805's stores and its forms cannot be measured.
#
# Chosen, no evidence gives them: the paths of ctextbox.h and cfixedtext.h, every member and parameter name of both,
# the enumerators' names (ETextStatus's among them), the names IForm's header marks. The class head follows the
# destructors' bytes (an implicit
# destructor: D0 10954 holds the D2's body; CFixedText's vtable lies among its first user's, so it has no key function).
# Forms that give Move's bytes: the same function body in a compile with the unit's flags for `if (posicao.x !=
# m_posicao.x || posicao.y != m_posicao.y) { ... }` around the body in place of the early return, for x and y read into
# locals before the test, for `!(x >= 3 && y >= 1)`, `x <= 2 || y <= 0` and `(x < 3) | (y < 1)`, and with IForm's flag
# as an unsigned char, a char or an enum class over unsigned char compared with 1, or as a byte IsVisible returns for
# Move to compare. So the early return, the test's spelling and the bool are choices. A SPoint operator== used as
# `posicao == m_posicao`, free or defaulted in the struct, adds in the object a mask on the second compare that binaryen
# removes: with the defaulted one, splat-remap against a whole try link says IDENTICAL. api/gui/primitives.h declares
# none, so the members are compared one by one. The notification (the lock, the flag, m_alterado, slot 4) is the same
# code in fns 2241, 2783, 5527, 11061 and 11062; whether the original shares it in a helper is not known, and it is
# spelled here. Forms that do not give the bytes, in a lone link at -Oz: `m_posicao.x == posicao.x` (the target loads
# the parameter first), y tested first, a local copy of the point (a second load).
CTEXTBOX_SRCS := src/api/gui/ctextbox.cpp
UENUX2_SRCS += $(CTEXTBOX_SRCS)
# Rect (10956): the record's col 9 is a statement in a block, and the assignment of a temporary gives the target's one
# i64 store. The tests in `m_largura != 0 && m_altura != 0`, the known size first, are evidence: the other way round
# differs in 125 lines. The tail calls SRect::MoveX, 108-uenux2-api-gui-primitives.mk says why it is out of line.
# The constructor's caller is not reconstructed: 65-uenux2-ctextbox-roots.cpp builds the box with std::make_shared as
# fn 11805 does, which keeps the vtable and brings the control block's D2 and D0 (target fns 11115, 11114). Both rules
# list the headers by directory: every header ctextbox.h includes, transitively, is in api/gui/ ($(UENUX2_HDRS) is still
# empty when the fragments are read)
$(ROOT)/$(APP)/65-uenux2-ctextbox-roots.o: $(ROOT)/src/units/65-uenux2-ctextbox-roots.cpp $(ROOT)/src/units/65-uenux2-ctextbox.mk $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/65-uenux2-ctextbox-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/65-uenux2-ctextbox-roots.o
