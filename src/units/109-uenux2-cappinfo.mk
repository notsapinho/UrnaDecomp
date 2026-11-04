# uenux2 comum::CAppInfo (src/app/comum/appinfo/), its md::estadoaplicacao heads, and the singletons comum::CFotos and
# comum::CPartidos (src/app/comum/dados/). CLocal's and CCandidaturas's singletons are in unit 89, whose files they share.
#
# Matched. CAppInfo: the accessor (target fn 185), its static destructors (11573, 11574), the constructor (5813), GetGeral and
# its const overload (291, 457, thunks of binaryen's merge 6040, the shared body, which the two form here too), GetVota and
# its const overload (261, 903), GetCodigosCarga (3788), EhTreinamentoEleitor (697), GetIdentificacaoUrna (1942), TemVota
# (2841, below), IndiceTurno (1553, below), and CBaseError<EUeComumAppInfoError>'s constructor (1710, a thunk of 710). CFotos and CPartidos: the accessors (2819, 819), the
# static destructors (11512, 11513, 11502, 11503), the constructors (3756, 3751), the destructors (2818, 2815) and their
# __tree::destroy (1934, 1932). 376, vector<string>::push_back(&&), comes with GetCodigosCarga.
# GetGap's non-const overload has no index of its own: vota::IQRCodeBUDS::GeraPartes (inlined into fn 1956, unit 37's)
# holds it, and with it GetEstado's non-const instance for CEstadoGeralGap (record line 42), inlined by binaryen with
# GetGap's frame. Its place beside the const overload is a choice.
# cestadogeralgap.cpp also holds md::estadoaplicacao::CEstadoGeralGap's constructor (fn 5626), which unit 93's fragment
# describes with its converter.
#
# CAppInfo::TemVota (2841) passes the literal "TemVota" and its turn to IndiceTurno and returns whether that turn's
# m_vota holds a state (the byte at +380 + 104 * index, the optional's flag). Its name is the literal's, as GetVota's
# is; that it is const and its line in cappinfo.cpp are chosen. Its callers (11242, 12105, 12110) are not written, and
# the roots' Votos stands for them. It matched with the plain body; nothing else was tried.
# CAppInfo::SalvaVotaInterno and SalvaVotaExterno (3790, 3789, thunks of binaryen's merge 6039, which the two form here
# too; its match line names our merge body, a name our link derives): each passes its literal ("SalvaVotaInterno",
# "SalvaVotaExterno") and TURNO_ATUAL to IndiceTurno and, when that turn's m_vota holds a state, saves it through a
# CServicoEstadoGeralVota of its origin (FLASH_INTERNA, FLASH_EXTERNA) and TURNO_ATUAL (3787, unit 206) with
# IServicoEstado's save (5329), passing the state itself. The names are the literals', as TemVota's is. Both go through
# a file-static helper, SalvaVota (a chosen name), which clang inlines: in 6039's 32-byte frame the service sits above
# the literal's std::string (+20 and +8), which lives until the save returns (a reading: written in place, with the
# string a temporary of the index's statement, it would be freed before the save; that form was not compiled). That the
# two are const, their order (Interno first, as the target's 3790 above 3789 reads), their lines, and the helper's
# being a free function and its linkage are chosen. Their
# callers 491 (unit 205), 7174 and 10590: the roots' SalvaVotas stands for the last two, a second call site of each
# (a reading of docs/reference/facts/tool-traps.md X1: with 491 their one caller, binaryen would inline both into it
# and form no merge; not linked without it).
# CAppInfo::SalvaGeralInterno and SalvaGeralExterno, added with unit 277: SincronizaEstadoGeral (3333, unit 205), their
# one caller, holds each behind a 16-byte frame of its own, binaryen's inlining of an out-of-line function
# (docs/reference/facts/reading.md R10): when m_geral holds a value (its flag at +180, read with no call), a
# comum::CServicoEstadoGeral of the origin (fn 1941, 0 then 1) saves it (fn 3592). They read the private m_geral, so
# they are members, and go through a file-static helper, SalvaGeral, as the vota pair goes through SalvaVota; 3333
# matches with them. Their names (after SalvaVotaInterno's), their being const, their order and lines, and the helper's
# name and linkage are chosen.
# CAppInfo::LeGeralInterno (2273, a chosen name), added for unit 296, whose fragment and roots have it: the general
# state read anew from the internal flash, after SalvaGeralExterno.
# CPartidos is an api::CDataMap<ueword, md::CPartido>, its base (cpartidos.h says why), and its constructor builds the
# base from the name "CPartidos": cpartidos.cpp's object is cmp-equal to the one compiled with the layout written out as
# members, the form before (both built at the tree's flags, before and after the change).
#
# Names from evidence: GetGeral, GetVota and GetGap are the literals the three pass to their throws; IndiceTurno and
# GetEstado<ESTADO> are records (cappinfo.cpp:472, :42, :57); EUeComumAppInfoError and its limits are RTTI; CFotos and
# CPartidos are the literals their constructors store as the set's name (CFotos is also the record cfotos.cpp:111).
# CAppInfo::GetInst is the text of an Assert the target holds, `comum::CAppInfo::GetInst().GetVota().GetEstadoVota() ==
# EAVENCERRADA` (ledger/strings.tsv, 401161). GetVota's default argument: that text and nine like it call it with no
# argument, and all 86 direct calls of 261, in 60 functions, pass 51; the slot keeps 261's parameter, and 903's is folded.
#
# CAppInfo::~CAppInfo (3792) matches at the tree's -O3. The two vector loops of m_gap hold CDadoCorrespondencia's
# destructor inlined, the one of m_geral calls it. At -O2 all three stay calls, at cost 385 against threshold 325, and
# ours is 343 B against 702. At -O3 one loop site goes in at threshold 525 and the member's site stays out, which is the
# target's split; that compile keeps one loop's call, so the array's form is not settled. -Rpass=inline
# -Rpass-missed=inline on cappinfosingleton.cpp prints it. The call drops the this that 857 returns, so the row matches
# only while a function of our link reads that result: src/app/roots_vector.cpp's copies of 5532 and 9873 do
# (docs/reference/facts/splat.md §S10 item 17). With no reader it differs by that drop alone, 19 over 348 rows (one
# deleted, the rest operand-only).
#
# CAppInfo::IndiceTurno (1553) differed by one operand, `+0x3f target i32.const 474`, until
# mock/app/comum/cappinfobuilder.cpp linked ahead of this object at the executable TU's rule (unit 253). Slot 474 is
# 9868, EUrnaTurno's format handle, which the target keeps apart from the 31 slots of 536 because its copy has parse and
# format out of line (calls 1558 and 5906): an -Oz copy, which that object gives every user of the handle now. Before,
# our link merged the handle into 536's body, 1553's anchor voted 9868 and the other anchors 536, which dropped the
# generated name of 536 and 24 matches with it (275, 680, 1712, 1919, 2253, 2668, 2828, 3702, 3801, 5633, 5689, 5765,
# 5900, 10260, 10262, 10271, 10283, 10287, 11355, 11390, 11392, 11397, 11405 and 11858), and a hand line kept it. With
# the turn's handle a body of its own the votes no longer split: step 8 writes 536's line again (`table`), and the hand
# line went (unit 253's fragment has the measurement). That line names our link's survivor of the handle bodies 536
# merges, the first in link order (cdefinerotaposreinicio.cpp.o's, of const comum::EEstadoVota), so a unit that adds an
# enum's handle ahead of it renames it, as a generated line.
# CDadoCorrespondencia's destructor (857) and CIdentificadorGeradorMidia's (2240) match too, from cappinfobuilder.cpp.o,
# which instantiates both ahead of the other objects: the target's copies call ~basic_string out of line, 38 and 26 B,
# and a compile of the class at -Oz -fexceptions gives their calls in order (2240, the vector, two strings; three
# strings). This fragment read that shape as the executable TU's copy (levels.md V1) while src/app/roots_vector.o's copy
# of 857, at the tree's flags, was the link's and differed. The hand line that named 2240 went with it.
#
# 1903's singleton is unit 307's (vota::CParametrosImagemDigital, a chosen class). CJustificador's (1391, 2810, 11476,
# 11477) is unit 113's, with its constructor 3742. cfotos.h's inline ExisteFoto is held by fn 5746 (unit 98's fragment).
# 5635 stays a stub in md/estadoaplicacao/cestadogeral.cpp. 436, which calls
# CPath::GetPathTrab (358), is unit 190's and matches.
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
#   push_back(c.GetCodigoCarga()), a getter by value: emplace_back gives 268 rows for 111. The getter returns a reference
#   now (comum::asn::CConversorDadoCorrespondencia::DoConverte, fn 11399, fragment 172, reads the member with no copy),
#   and GetCodigosCarga copies it into a std::string temporary before push_back: the same function at the tree's flags
#   (masked object compare), and 3788 still matches; a plain push_back over the reference differs (fragment 172 has
#   the rows).
#
# Chosen, no evidence names them: every data member's name but those the ASN.1 fields give; every parameter's; GetInst for
# CLocal, CCandidaturas, CFotos and CPartidos (the records give it to CRespostas and CEleitores); GetCodigosCarga,
# EhTreinamentoEleitor and GetIdentificacaoUrna, from their bodies and the literal "Codigo identificacao UE"; the getters GetTurno,
# GetFase, GetNumeroInternoUrna, GetCodigoCarga, GetTreinamentoEleitor, GetDadoCarga and GetCorrespondencia, from the members
# they read, which no target string names; cappinfosingleton.cpp, cestadogeralgap.cpp, cpartidos.*, cfotos.h, cappinfo.h,
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
# CAppInfo::GetGeralInterno (no index, a chosen name), inline in cappinfo.h for comum::CLocal's loader (5740, unit 89),
# which holds it with no frame of its own: m_geral copied through GetGeral (291) when set and the word at +528 is 0, else
# LeGeralInterno (2273) called. Written out of line in cappinfo.cpp first, clang inlined 2273 into it (a 16-byte frame
# and CServicoEstadoGeral's two calls among 5740's inserted rows, where the target calls 2273); inline in the header, 2273
# stays a call and 5740 matches. cappinfo.h says what is chosen.
CAPPINFO_SRCS := src/app/comum/appinfo/cappinfo.cpp src/app/comum/appinfo/cappinfosingleton.cpp \
  src/app/comum/dados/md/estadoaplicacao/cestadogeralgap.cpp src/app/comum/dados/cfotos.cpp \
  src/app/comum/dados/cpartidos.cpp
UENUX2_SRCS += $(CAPPINFO_SRCS)
$(ROOT)/$(APP)/109-uenux2-cappinfo-roots.o: $(ROOT)/src/units/109-uenux2-cappinfo-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/109-uenux2-cappinfo.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/109-uenux2-cappinfo-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/109-uenux2-cappinfo-roots.o
