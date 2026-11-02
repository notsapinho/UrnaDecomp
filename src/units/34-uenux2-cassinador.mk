# uenux2 comum::CAssinador in src/uenux2/src/app/comum/gravadores/cassinador.cpp: the destructor (target fn 1007,
# CAssinador vtable @1553252 slot 0) and its deleting destructor (fn 4694, slot 1), Assina (fn 1277, record 114:19) and
# the constructor (no target index). The file is the one the records of Assina and AssinaArquivosResultado name (lines
# 114 and 141-149), and the stubs' link-order placement gives the destructors. No record falls in the destructor or the
# constructor, so their lines are a choice; lines 141 to 149, AssinaArquivosResultado's (fn 12098 holds it inlined, not
# written), stay blank. The destructor is the class's only virtual member, and the target's deleting destructor shows
# it is defined out of line: 4694 calls 1007 (`f1007(p0); f136(p0)`), which clang gives only for an out-of-line
# destructor (its D0 calls the D1, an alias of the D2 that is not inlined through); one defined in the class would have
# the D2's body inlined into the D0, the three frees and then the delete. Out of line, it is the key function, so
# cassinador.cpp emits the vtable and the RTTI. Its body stores the vptr, since vota::CAssinadorVota derives from the
# class, and frees the three std::string members (+36, +24, +12).
# With it: the class header (cassinador.h) and the ESavdPacote type of its +8 member, declared beside ESavdAplic in
# app/comum/iinterfacesavd.h. In the target the deleting destructor 4694 is also slot 1 of vota::CAssinadorVota's
# vtable (binaryen merged the two identical bodies); fragment 165 writes that class's destructor (7766), whose object
# links first, so 4694's match line names its D0.
#
# Added since:
# - Assina (1277): CPolySingleton<IInterfaceSavd>::instance() first (its default location is the record, 114:19; the
#   column is the one `auto& iSavd = ` gives at four spaces, a name chosen to that length), a CApplicationContextGuard
#   from CApplication::CriaContexto(11, "Erro na assinatura", "", "Ocorreu um erro durante a assinatura do arquivo: " +
#   DescricaoArquivo(arquivo)) (the order of the four arguments' temporaries is the target's), then comum::AssinarUE
#   (iinterfacesavd.cpp, unit 95's) with the ESavdAplic at +4, the command 66 and the file. binaryen inlined AssinarUE,
#   which has one caller, behind a stack frame of its own; the order of the two objects decides 1277's locals, so
#   cassinador.cpp is compiled by fragment 95 now, after iinterfacesavd.cpp (that fragment has the measurement).
# - The constructor CAssinador(ESavdAplic, ESavdPacote): binaryen inlined it into vota::CAssinadorVota's (fn 1501, unit
#   165's), its one caller, behind a stack frame of its own, and 1501 stores CAssinadorVota's vptr after that frame's
#   epilogue, so the constructor is out of line in another TU than CAssinadorVota's, a reading. It stores the ESavdAplic
#   at +4 and the package at +8, takes the package's entry of comum::CArquivosSavd (fn 275 on fn 1164's result), and
#   assigns api::GetDirName of it (fn 5462) with a '/' appended to +24 and api::GetFileName of it (fn 2763) to +12; +36
#   stays empty. That the ESavdAplic is a parameter (CAssinadorVota passes 1) and not the constructor's constant is a
#   choice, and so are the members' names.
# cassinador.cpp is compiled by fragment 95, after iinterfacesavd.cpp (the paragraph above), so this fragment lists no
# source. Five of the destructor's callers are not reconstructed yet: 34-uenux2-cassinador-roots.cpp gives it two direct
# callers and takes their addresses
$(ROOT)/$(APP)/34-uenux2-cassinador-roots.o: $(ROOT)/src/units/34-uenux2-cassinador-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/34-uenux2-cassinador-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/34-uenux2-cassinador-roots.o
