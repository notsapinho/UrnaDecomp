# uenux2 api::CTextBox: Move (target fn 10957, slot 9 of the vtable @1582232) in src/uenux2/src/api/gui/ctextbox.cpp,
# the file the class's records name, with its throw on the record's line 90, column 15 (the lines around it are a
# choice); the class header api/gui/ctextbox.h, the 4963 enumerator of eueguierror.h, the layout header
# api/gui/cfixedtext.h and the base api/gui/iform.h, which was stub-only. Draw is the key function and is pending, so
# the pending object emits the vtable with the implicit destructors (10955, 10954) and the inline GetTypeName (10953),
# and those match from there. The destructors inline CFixedText's, so that object emits CFixedText's vtable too, whose
# D2 and D0 (7706, 7666) are the two thunks into binaryen's merged bodies 1727 and 1969. Paths relative to src/uenux2;
# the generic uenux2 rule depends on the source and every uenux2 header.
#
# Chosen, no evidence gives them: the paths of ctextbox.h and cfixedtext.h, every member and parameter name of both,
# the enumerator's name, the names IForm's header marks. The class head follows the destructors' bytes (an implicit
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
# Draw and Rect are not reconstructed: 65-uenux2-ctextbox-pending.cpp defines them with trapping bodies (see its
# header), and nothing reconstructed references the vtable yet: 65-uenux2-ctextbox-roots.cpp takes its address. The
# pending rule lists the headers by directory: every header ctextbox.h includes, transitively, is in api/gui/
# ($(UENUX2_HDRS) is still empty when the fragments are read)
$(ROOT)/$(APP)/65-uenux2-ctextbox-pending.o: $(ROOT)/src/units/65-uenux2-ctextbox-pending.cpp $(ROOT)/src/units/65-uenux2-ctextbox.mk $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/65-uenux2-ctextbox-pending.cpp -o $(R)
$(ROOT)/$(APP)/65-uenux2-ctextbox-roots.o: $(ROOT)/src/units/65-uenux2-ctextbox-roots.cpp $(ROOT)/src/units/65-uenux2-ctextbox.mk $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/65-uenux2-ctextbox-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/65-uenux2-ctextbox-pending.o $(APP)/65-uenux2-ctextbox-roots.o
