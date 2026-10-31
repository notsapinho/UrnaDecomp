# uenux2 comum::CAppInfo (src/app/comum/appinfo/), its md::estadoaplicacao heads, and the singletons comum::CFotos and
# comum::CPartidos (src/app/comum/dados/). CLocal's and CCandidaturas's singletons are in unit 89, whose files they share.
#
# Matched. CAppInfo: the accessor (target fn 185), its static destructors (11573, 11574), the constructor (5813), GetGeral and
# its const overload (291, 457, thunks of binaryen's merge 6040, the shared body, which the two form here too), GetVota and
# its const overload (261, 903), GetCodigosCarga (3788), EhTreinamentoEleitor (697), GetIdentificacaoUrna (1942), and
# CBaseError<EUeComumAppInfoError>'s constructor (1710, a thunk of 710). CFotos and CPartidos: the accessors (2819, 819), the
# static destructors (11512, 11513, 11502, 11503), the constructors (3756, 3751), the destructors (2818, 2815) and their
# __tree::destroy (1934, 1932). 376, vector<string>::push_back(&&), comes with GetCodigosCarga.
#
# Names from evidence: GetGeral, GetVota and GetGap are the literals the three pass to their throws; IndiceTurno and
# GetEstado<ESTADO> are records (cappinfo.cpp:472, :42, :57); EUeComumAppInfoError and its limits are RTTI; CFotos and
# CPartidos are the literals their constructors store as the set's name (CFotos is also the record cfotos.cpp:111).
#
# Written and not matched, each with its measurement:
# - CAppInfo::~CAppInfo (3792): -O3. The two vector loops of m_gap hold CDadoCorrespondencia's destructor inlined, the one
#   of m_geral calls it. At -O2 all three stay calls, at cost 385 against threshold 325, and ours is 343 B against 702. At -O3
#   one loop site goes in at threshold 525 and the member's site stays out, which is the target's split; that compile keeps
#   one loop's call, so the array's form is not settled. -Rpass=inline -Rpass-missed=inline on cappinfosingleton.cpp prints
#   it. uenux2's level is not this unit's to change (docs/reference/facts/levels.md V3), so the row stays.
# - CAppInfo::IndiceTurno (1553): one operand, `differs +0x3f target i32.const 474`. Slot 474 is 9868, EUrnaTurno's
#   format handle, and the target keeps it apart from the 31 slots of 536 because its copy has parse and format out of line
#   (calls 1558 and 5906, whose other caller 4027 is in invoke form): not a body this tree's level gives. Our link merges
#   the handle into 536's body, so no name can tell them apart. 1553's anchor votes 9868 and the other anchors 536, which
#   drops the generated name of 536 and five matches with it (275, 680, 1712, 2253, 3702), so splat/symbol_addrs.txt holds a
#   hand line for 536.
# - CDadoCorrespondencia's destructor (857) and CIdentificadorGeradorMidia's (2240): the target's copies call ~basic_string
#   out of line, 38 and 26 B, where 857's in our object is 222 B. A compile of the same class at -Oz -fexceptions gives the
#   target's calls in order (2240, the vector, two strings; three strings), which reads as the executable TU's copy (levels.md
#   V1). Named by hand, so their callers resolve, and `differs`.
#
# Not written: 436, which calls CPath::GetPathTrab (358, not written); CJustificador's singleton (1391, 2810, 3742, 11476,
# 11477); 1903's, whose class no body read names. 5635 stays a stub in md/estadoaplicacao/cestadogeral.cpp.
#
# What decides the form, measured:
# - The statics are class members defined after the accessor, pointer first: `.bss` then holds the mutex below the pointer,
#   as the target does (1838640 and 1838664 for CAppInfo), because the accessor's first mention creates them, and the
#   pointer's static destructor comes first in the object, as the target's band reads (11574 and 11573: a higher index has a
#   lower ld_index). Of the orders probed, pointer-first ahead of the accessor reverses the .bss, and mutex-first ahead of
#   it reverses the destructors, as does an anonymous namespace ahead of it; the accessor ahead of the definitions with the
#   mutex first was not probed. The two destructors' bytes do not depend on this. The names s_inst and s_mutex are chosen.
# - The accessor is in its class's own file for CFotos, CPartidos, CLocal and CCandidaturas: the bodies that hold it inlined
#   are that file's by their records (3755 cfotos.cpp, 2838 ccandidaturas.cpp), and clang inlines it there at cost 175
#   against 225. CAppInfo's is not in cappinfo.cpp: IndiceTurno (1553) and EhTreinamentoEleitor (697) call fn 185, and with the
#   accessor beside them clang inlines it into IndiceTurno (cost 175, threshold 225). So cappinfosingleton.cpp, a chosen path,
#   holds the accessor, its statics, the constructor, the destructor and 1942, which holds the accessor inlined.
# - The constructor and destructor stay calls beside their definitions, and that is clang's, not a choice: ccandidaturas.cpp's
#   object calls C1 and D1 of its class in GetInst, and -Rpass=inline -Rpass-missed=inline prints no line with either as
#   callee. So a body of the class's own file shows them as calls with the definitions in the same TU.
# - GetEstado is `static`. The target's single frame in 261, 903 and 6040 holds the literal and the throw's buffers, so clang
#   inlined it. A template of external linkage or `inline` stays out of line (40 rows for GetGeral against 238), and the record's
#   text cannot show `static` (docs/reference/facts/reading.md R8).
# - IndiceTurno switches on a value of its own: the throw formats the parameter, and the target stores it once (+44).
#   Assigning the parameter stores it twice and differs in 8 rows.
# - The CDataMap-shaped head of CFotos and CPartidos: their constructors copy from a const std::string& temporary, which
#   gives the target's two constant stores (+24, then +16) ahead of the map's; a member initializer from the literal
#   stores through memory and differs. So each delegates to a private constructor taking the name. See unit 89 for CCandidaturas,
#   whose temporary needs a heap and so tells a base class from a delegating constructor.
# - GetCodigosCarga is out of line and unrooted: 3788 opens a second frame after CAppInfo's code, so binaryen inlined it.
#   push_back(c.GetCodigoCarga()), a getter by value: emplace_back gives 268 rows for 111.
#
# Chosen, no evidence names them: every data member's name; every parameter's; GetInst for these five (the records give it
# to CRespostas and CEleitores); GetCodigosCarga, EhTreinamentoEleitor and GetIdentificacaoUrna, from their bodies and the
# literal "Codigo identificacao UE"; cappinfosingleton.cpp, cestadogeralgap.cpp, cpartidos.*, cfotos.h, cappinfo.h,
# euecomumappinfoerror.h, eurnaturno.h and every enumerator's name; EUrnaTurno's values' spelling; CFotos::SFotoIndexada and
# that its first 20 bytes are an md::CIndiceFoto; the types of the CEstadoGeral members no body reads; that 697 and 1942 are a
# static member and a free function; m_turnoCarregado's name and type. The member order of CAppInfo is the offsets'.
#
# Measured, the same code (the function's disassembly with object-local numbers masked, how-to step 3):
# - 185, 401, 521, 819, 2819: std::make_unique or reset(new T()) or an explicit unique_ptr; std::lock_guard, std::unique_lock or
#   std::scoped_lock; !s_inst or s_inst == nullptr; *s_inst or *s_inst.get().
# - 5813: = default or {}. 2815, 2818: = default or {}. 3751, 3756: the delegation from the literal or from an explicit std::string.
# - 291, 457, 261, 903: !estado or !estado.has_value(); *estado or estado.value().
# - 1553: the local or the same expression in the switch; a conditional or an if over a local.
# - 697: the if or one return with &&. 3788: const CDadoCorrespondencia& or const auto&.
CAPPINFO_SRCS := src/app/comum/appinfo/cappinfo.cpp src/app/comum/appinfo/cappinfosingleton.cpp \
  src/app/comum/dados/md/estadoaplicacao/cestadogeralgap.cpp src/app/comum/dados/cfotos.cpp \
  src/app/comum/dados/cpartidos.cpp
UENUX2_SRCS += $(CAPPINFO_SRCS)
$(ROOT)/$(APP)/109-uenux2-cappinfo-roots.o: $(ROOT)/src/units/109-uenux2-cappinfo-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/109-uenux2-cappinfo.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/109-uenux2-cappinfo-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/109-uenux2-cappinfo-roots.o
