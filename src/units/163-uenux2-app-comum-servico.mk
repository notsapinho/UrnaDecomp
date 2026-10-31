# uenux2 comum::servico and the DAO registry, api::persistencia::CDAORepositorio.
#
# Target functions matched:
# - comum::servico::CJustificadorServico's destructor and deleting destructor (3740, 11464), in
#   app/comum/justificativa/servico/cjustificadorservico.cpp, and CComparecimentoMesarioServico's (3607, 10312), in
#   app/comum/comparecimentomesario/servico/ccomparecimentomesarioservico.cpp. Both D2s are thunks into binaryen's 2899,
#   which they form with api::CFormPart's and comum::CParteEleitores' D2s (10888, 11205), as in the target; 2899's match
#   line now names the first member in link order, CJustificadorServico's D2 (step 9 renamed it).
# - The registry's map (src/api/persistencia/cdaorepositorio.cpp): its exit destructor (10292) and
#   std::map<std::string, std::shared_ptr<api::persistencia::IDAO>>'s destroy (3845). The map's name in
#   splat/symbol_addrs.txt is generated (vote:8 by:3742,10292).
# - CDAORepositorio::Entregar (cdaorepositorio.hpp, its throw on the record's line 79, column 15) matches inside unit
#   113's comum::CJustificador constructor (3742), which holds it and CJustificadorServico's constructor inlined.
#
# Not matched:
# - Fn 815: it inlines comum::CRegistradorMesario's constructor, which holds CComparecimentoMesarioServico's and
#   Entregar<IComparecimentoMesarioDAO> (record cdaorepositorio.hpp:79), and its callee 5380 (the registrador's
#   destructor) calls 1902 and 2728, which nothing names. cregistradormesario.cpp is not this unit's. Its stub is gone:
#   its record falls on the written Entregar, so this comment is its only note. CComparecimentoMesarioServico's
#   constructor is written and the link drops it, since nothing reconstructed calls it.
# - Registrar (records at lines 35 and 52, held by fn 7787) is not written: its lines stay blank in the header.
#
# Read from the bytes:
# - Both classes: no base (their typeinfo's kind), two vtable slots, a std::shared_ptr at +4 (2899 releases it). The D0
#   calls the D2 and then frees this: the destructor is out of line (docs/reference/facts/reading.md R5); the D2 stores
#   the class's vptr, so the class is not final (R4). 3742 stores CJustificadorServico's vptr at +28 and Entregar's
#   result at +32 and +36; 815 stores the other's at +40 and the result at +44 and +48.
# - The constructors call Entregar: each Entregar record (1560952, 1595692) follows its servico's typeinfo in that
#   object's run of the data, not the run of the object that holds the servico.
# - Entregar: the key is typeid(I_DOMINIO_DAO).name(), with typeid(I_ORIGEM).name() appended when the two differ, and
#   the target frees both names after the result is built; the found DAO's slot 2 (Clone) is cast with __dynamic_cast
#   from IDAO's typeinfo to I_DOMINIO_DAO's, the clone deleted through slot 1 when the cast fails, and the result's
#   control block is std::shared_ptr<I_DOMINIO_DAO>'s default-delete pointer block (its typeinfo, 1560996 and 1595736).
#   The throw passes 6802 and std::format of the format string at 375451 with the key.
# - The map: 3845 frees a std::string key at the node's +16 and releases a std::shared_ptr at +28; __wasm_call_ctors
#   initializes it with no guard, so one .cpp defines it.
#
# Placement: no record names the servico files. Their directories are chosen beside each DAO's dao/: the data put
# CJustificadorServico's vtable right after app/comum/justificativa/dao/cjustificadordao.cpp's data, and
# CComparecimentoMesarioServico's after estados/ipedetitulomesario.cpp's record and before cregistradormesario.cpp's.
# cdaorepositorio.cpp's path, beside its header, is chosen too.
#
# Chosen, no evidence names them: m_dao, s_daos and its being a static data member, the locals' names, I_ORIGEM's
# default, the paths above, the order of each servico .cpp's constructor and destructor, and the enumerator name
# EUE_PERSISTENCIA_DAO_NAO_REGISTRADA (api/persistencia/euepersistenciaerror.h).
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 and ecourna header.
COMUM_SERVICO_SRCS := src/api/persistencia/cdaorepositorio.cpp src/app/comum/justificativa/servico/cjustificadorservico.cpp src/app/comum/comparecimentomesario/servico/ccomparecimentomesarioservico.cpp
UENUX2_SRCS += $(COMUM_SERVICO_SRCS)
# nothing reconstructed stores CComparecimentoMesarioServico's vtable: 163-uenux2-app-comum-servico-roots.cpp keeps it,
# as the constructor fn 815 inlines does
$(ROOT)/$(APP)/163-uenux2-app-comum-servico-roots.o: $(ROOT)/src/units/163-uenux2-app-comum-servico-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/163-uenux2-app-comum-servico.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/163-uenux2-app-comum-servico-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/163-uenux2-app-comum-servico-roots.o
