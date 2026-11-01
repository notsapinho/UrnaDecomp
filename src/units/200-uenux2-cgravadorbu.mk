# uenux2 comum::CGravadorBU (app/comum/gravadores/cgravadorbu.h, the header of cgravadorbu.cpp, which its records name)
# and the BU's result data classes comum::md::CVotosCargo, md::CResultadoVotacao and md::CResultadoVotacaoPorEleicao
# (app/comum/gravadores/md/cvotoscargo.h, cresultadovotacao.h and cresultadovotacaoporeleicao.h, layouts only), paths
# relative to src/uenux2. The unit has no source of its own: its matches are code the compiler emits from these headers
# in its two companion objects, and cgravadorbu.cpp stays a stub-only file.
#
# Matched:
# - CGravadorBU's implicit destructors (target fns 5857 and 11628, slots 0 and 1) and the destroy of the tree of its
#   std::map<md::TCargoID, uebyte> at +284 (fn 3814), emitted with the vtable in 200-uenux2-cgravadorbu-pending.cpp,
#   whose trap of GravaResultado (fn 11629) is the class's key function; they move there with the vtable, under the same
#   symbols, when GravaResultado lands. The D2's other callees are in the link: fn 1405 (unit 155's) and fn 857.
# - libc++'s uninitialized copy of a range of md::CResultadoVotacaoPorEleicao (fn 2853) and
#   std::vector<md::CResultadoVotacaoPorEleicao>'s __base_destruct_at_end (fn 5859): template instances the roots file's
#   stand-in for their one target caller, CGravadorBU::GravaResultado (fn 11629), emits at the tree's flags (the roots
#   rule compiles with UENUX2_CXXFLAGS). They come from cgravadorbu.cpp's object once GravaResultado lands, and the
#   stand-in goes then. That the 20-byte elements they handle are md::CResultadoVotacaoPorEleicao is a reading:
#   MontaEntidadeBU (record cgravadorbu.cpp:636, inlined into fn 11629) takes a const
#   std::vector<md::CResultadoVotacaoPorEleicao> &, and fn 2853's nested copies have the three classes' layouts.
#
# Evidence and choices: cgravadorbu.h and the three md headers say what each layout comes from and which types and names
# are chosen; the paths of the md headers are chosen (beside cvotosvotavel.h). Measured in this unit's link before step
# 8 (pnpm wasm score against the target): 5857 9 over 101 rows, 11628 2 over 5, 3814 1 over 15, 2853 6 over 206 and 5859
# 3 over 122, every one operand-only and every operand a call's or a data address; step 9 matches them. No other form
# was measured.
#
# Not written, and what each waits for:
# - GravaResultado (fn 11629, slot 7): the -pending.cpp header says what it calls.
# - AcrescentaVotoVotavel (fn 3820, record cgravadorbu.cpp:221, static) and std::vector<md::CVotosVotavel>'s push_back
#   (fn 1944; its callers are 3819 and 3820): when CCandidaturas::Busca finds no candidacy, 3820 looks the number up in
#   comum::CPartidos's map with a find inlined that sets the cursor at +12 and returns the record or null
#   (api::CDataMap::Find), and throws CUeComumGravadoresError 8638 when it finds none; app/comum/dados/cpartidos.h does
#   not declare CPartidos as an api::CDataMap<ueword, md::CPartido>. Measured in a scratch whole-link try (try-tu.sh
#   --component uenux2/src/app/comum/gravadores, with variants of cpartidos.h, CPartidos derived from that CDataMap, and
#   of cgravadorbu.h under -iquote): 3820 scored 23 over 332 rows and 1944 4 over 137, operand-only, every operand a
#   call's, a data address, a packed format-string address, or a constant that reads as a table slot of that link (the
#   format buffer's and the exception's destructor's). The form measured: CGravadorBU declares `using
#   TVetorVotosVotaveis = std::vector<md::CVotosVotavel>;` and `using TQtdEleitor = ueword;` (ecourna's CBaseType for
#   the count masks the parameter, which the target does not), the body returns at once for a count of 0, pushes a
#   CVotosVotavel without identification for BRANCO, NULO and NULO_CARGO_SEM_CANDIDATO, one with CIdentificacaoVotavel
#   (candidato, 0) when cargo.IsConsulta(), and otherwise takes the party from the candidacy, or, when Busca returns
#   null, from CPartidos::GetInst().Find(candidato), testing for null first. The first try had both a CBaseType count
#   and the found candidacy tested first, and scored 95 over 359; the two were not measured apart. 3819 calls 3820 three
#   times and is not written.
W200_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null)
# CGravadorBU::GravaResultado is not reconstructed: 200-uenux2-cgravadorbu-pending.cpp gives it a trapping body,
# compiled with the tree's flags, and emits the class's vtable and implicit destructors
$(ROOT)/$(APP)/200-uenux2-cgravadorbu-pending.o: $(ROOT)/src/units/200-uenux2-cgravadorbu-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/200-uenux2-cgravadorbu.mk $(W200_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/200-uenux2-cgravadorbu-pending.cpp -o $(R)
override EXTRA_OBJS += $(APP)/200-uenux2-cgravadorbu-pending.o
# the constructor that stores the vtable and the caller of fn 2853 are not written: 200-uenux2-cgravadorbu-roots.cpp
# stands in for them; it compiles with the tree's flags
$(ROOT)/$(APP)/200-uenux2-cgravadorbu-roots.o: $(ROOT)/src/units/200-uenux2-cgravadorbu-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/200-uenux2-cgravadorbu.mk $(W200_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/200-uenux2-cgravadorbu-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/200-uenux2-cgravadorbu-roots.o
