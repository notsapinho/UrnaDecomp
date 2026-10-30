# uenux2 comum::CAssinador::~CAssinador (target fn 1007, CAssinador vtable @1553252 slot 0) and its deleting destructor
# (fn 4694, slot 1) in src/uenux2/src/app/comum/gravadores/cassinador.cpp: the file the records of Assina and
# AssinaArquivosResultado name (lines 114 and 141-149) and the stubs' link-order placement give the destructors. No
# record falls in the destructor, so its line is a choice; the lines of those two members stay free. The destructor
# is the class's only virtual member, and the target's deleting destructor shows it is defined out of line: 4694
# calls 1007 (`f1007(p0); f136(p0)`), which clang gives only for an out-of-line destructor (its D0 calls the D1, an
# alias of the D2 that is not inlined through); one defined in the class would have the D2's body inlined into the
# D0, the three frees and then the delete. Out of line, it is the key function, so cassinador.cpp emits the vtable
# and the RTTI. Its body stores the vptr, since vota::CAssinadorVota derives from the class, and frees the three
# std::string members (+36, +24, +12).
# With it: the class header (cassinador.h) and the ESavdPacote type of its +8 member, declared beside ESavdAplic in
# app/comum/iinterfacesavd.h. In the target the deleting destructor 4694 is also slot 1 of vota::CAssinadorVota's
# vtable (binaryen merged the two identical bodies); that class (fns 7766, 1501) is not reconstructed. Paths relative
# to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CASSINADOR_SRCS := src/app/comum/gravadores/cassinador.cpp
UENUX2_SRCS += $(CASSINADOR_SRCS)
# the destructor's ten callers other than the deleting destructor are not reconstructed yet:
# 34-uenux2-cassinador-roots.cpp gives it two direct callers and takes their addresses
$(ROOT)/$(APP)/34-uenux2-cassinador-roots.o: $(ROOT)/src/units/34-uenux2-cassinador-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/34-uenux2-cassinador-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/34-uenux2-cassinador-roots.o
