# uenux2 helpers the vota threads and operator states call, in two new sources, and one template instance the roots emit:
# - comum::CAppStateContext (src/app/comum/cappstatecontext.cpp; its head, app/comum/cappstatecontext.h, is unit 116's,
#   grown here, with the head of its base api::CStateContext<STATE> in the new api/pattern/cstatecontext.h): the
#   constructor (target fn 3844), ProcessKey (3843), ProcessInput (5911), ProcessTick (5910), AcceptsKey (3842),
#   AcceptsInput (5909) and AcceptsTick (5908), which read the state's flags at +8, +9 and +10 as CAppState's friend (a
#   line of app/comum/cappstate.h), and the inline accessor GetState;
# - vota::EhTreinamento (src/app/vota/comum/votadefs.cpp, declared in the new app/vota/comum/votadefs.h): fn 1485;
# - api::CPolySingletonList::has<vota::IAjusteInicial> (fn 2450), the template of api/pattern/cpolysingletonlist.h, which
#   in both links is a 19-B thunk into the has<T> merge body 2924, as unit 100's has<T> 1654, 2160 and 2469 are.
# Paths relative to src/uenux2.
#
# What the target fixes.
# - 3844 stores its argument at +4, then CAppStateContext's vptr (vtable @1551304), and returns this: the constructor,
#   over one pointer member. 3843 calls slot 6 of +4's object, CAppState::ProcessKey(uebyte), when +4 is not null, and
#   passes its argument unmasked: with an int parameter the object adds `i32.const 255; i32.and` before the call, so the
#   parameter is 8 bits wide, the slot's uebyte. 3842 returns +4's byte at +8 (CAppState's first flag, which its
#   constructor sets from bit 0 of its argument), or false when +4 is null. 5911 and 5910 have 3843's shape over slots 7
#   and 8, and 5909 and 5908 have 3842's over +9 and +10. 5910 passes its second argument unmasked, as 3843 does; that
#   its parameter is the slot's uebyte too is read from 3843's measurement, not measured again. The class's typeinfo
#   (@1551320) is a
#   __si_class_type_info over api::CStateContext<comum::CAppState>'s (@1551332): declaring that base leaves both
#   functions as they were and gives our typeinfo the same kind. Same bytes, listed: the base empty and the virtual
#   destructor in CAppStateContext alone; the base's inline virtual destructor (cstatecontext.h) is chosen.
# - The seven are out of line, in a file of their own: their callers keep the calls (all but 3844: 4349 and 10204,
#   whose records are cthreadeleitor.cpp:134 and cthreadoperador.cpp:87; 3844: 4713, 7061 and 10204), and clang inlines
#   members this small in a TU that defines them, so a reading: no caller's file defines them. The file: in use band 3
#   (ledger/ordinals.tsv) 3844, 3843 and 3842 lie between cinformacaoeleicao.cpp's 3847 and cinfomtlcd.cpp's 3836
#   (records informacao/cinformacaoeleicao.cpp:40, cinfomtlcd.cpp:84), and the class's vtable lies after
#   comum::CAppState's typeinfo (@1551284) and before app/comum/carquivosresultado.cpp's first record (1551340), the run
#   of app/comum/'s own files in name order (docs/reference/facts/placing.md P5). The name cappstatecontext.cpp is the
#   class-name convention, which that order fits and does not single out. Each band's order is the definition order
#   (how-to step 3, "The order of two members"): band 3 runs 3844, 3843, 3842, and band 2 runs 5911, 5910, 5909, 5908,
#   after cinformacaoeleicao.cpp's 5914 (record :40). How the two runs interleave is not in the target: the Process
#   members before the Accepts members is a choice.
# - GetState: fn 4705 (slot 9 of vota::CExecucaoVota and of vota::CExecucaoVotaCooperativa) reads +4 of the context the
#   thread holds at +32, `p ? p->+4 : 0`, and fn 4713 reads +4 of the context it has just built, so code outside the
#   class reads the state, and no target function is such a reader of its own. That it is a public inline accessor, and
#   its name, are chosen; neither caller is written here.
# - 1485 is CAppInfo::GetInst().GetGeral().GetDadoCarga().GetFase() == FASE_TREINAMENTO ('3', 51). It calls fn 291, the
#   non-const GetGeral (splat/symbol_addrs.txt: _ZN5comum8CAppInfo8GetGeralEv); through a const CAppInfo& the object
#   calls _ZNK5comum8CAppInfo8GetGeralEv instead. Its four callers (10425, 10566, 10680, 12098: CMostraEleitorVotando,
#   CInformacaoThreadOperador, CPedeIdentidade and CGravaResultado) each keep the call, so a reading: it is defined in
#   none of their files, where clang would inline a body this small.
# - 2450 passes the three 8-byte pieces of the type name "N4vota14IAjusteInicialE" to 2924: a constant name, so
#   vota::IAjusteInicial has no key function, as app/vota/eleitor/iajusteinicial.h declares it.
#
# Chosen, no evidence names them: the names of ProcessInput, ProcessTick, AcceptsInput, AcceptsTick and GetState, after
# the CAppState slot each calls (the overriders' records' names, app/comum/cappstate.h) or the flag each reads; 1485's
# name, after the tree's spelling of the same test
# (comum::CAppInfo::EhTreinamentoEleitor, comum::CRelatorioTesteImpressora::EhTreinamento), and its file and line:
# votadefs.cpp is the file whose records name free functions of namespace vota (VerificaAssinaturaMI,
# VerificaAssinaturaMV, GetQuantidadeMaximaBUsAdicionais, lines 103, 110 and 135, not written), and the function stands
# after its last record; no record, slot or string names 1485, and its neighbours in use band 8 (1484, 1486) are
# OpenSSL's. votadefs.h's and cstatecontext.h's paths; ProcessKey's, AcceptsKey's and m_estado's names, and that the
# derived class, not its base, holds m_estado; cappstatecontext.cpp's name (above); that AcceptsKey reads the flag as
# CAppState's friend and not through an accessor of CAppState's (cappstate.h says so).
# The same functions, compared between objects compiled with the tree's flags, object-local numbers masked: the
# constructor assigning m_estado in its body; `m_estado != nullptr` in ProcessKey. Measured before CStateContext's head
# was declared: for AcceptsKey, a public inline accessor of the flag in CAppState, `m_estado ? m_estado->m_bTecla :
# false` and an if with two returns.
#
# Same bytes, not measured as variants: 5908 to 5911 are written in the forms of 3842 and 3843 above.
#
# How the matches are named: 3843, 3844, 2450 and 3842 by symbol-file lines (pair-fingerprint, vptr-anchor,
# content-anchor and pair-fingerprint), and 5908 to 5911 by pair-fingerprint lines; 1485 by the scan's content pass
# alone while none of its callers was in the link, and since unit 50's slot 19 (fn 10566) is, by that caller's `call`
# vote (splat/symbol_addrs.txt: `evidence:call by:10566`).
#
# vota::AdicionaSeparador (fn 1387, 169 B), at the end of votadefs.cpp: std::string(38, '-') (operator new of 40 and
# the dashes stored eight at a time) passed to api::CPaperFormBuilder::AddTextField (fn 193) with IPaper's style 1 and
# the caller's alignment, then the string freed. Its callers are four vota states' slot 2, none written: 11908
# (CImpressaoListaEleitores), 11946 (CGeraZeresimaBase, CGeraZeresima, CRegerarZeresima), 12105 (CGeraRelatorios) and
# 12110 (CGeraBU), nine call sites passing 0 or 2; the roots give it two, with both values. `pnpm wasm score` before
# step 8: 3 over 56 rows, all operand-only; the scan matched it by its content. It has no record and reads only its
# parameters, so it is a free function of vota, its callers' namespace (how-to step 3's member rule). Chosen: the name,
# the file (votadefs.cpp, the file whose records name vota's free functions, as for 1485 above; chosen against use
# band 9, where the target's 1387 lies between md/processoeleitoral/ccargo.cpp's 1388 and 1386, comum code not
# written, and then api/gui/cframedtext.cpp's 1385, none of them app/vota/ code), the line after EhTreinamento, and
# static_cast<api::IPaper::EStyle>(1), as cgeradorrelpu.cpp spells it.

# Added since, in votadefs.cpp at the lines of their records (the file's other lines are a choice):
# - vota::VerificaAssinaturaMI and VerificaAssinaturaMV (fns 3290 and 3288, records 103:19 and 110:19): ValidarUE (fn
#   5890, unit 95) over CPolySingleton<IInterfaceSavd>::instance() and the file under CPath::GetPathTrab of the internal
#   (0) and the external (1) flash and the current turno, as one std::string. The target calls instance() first (its
#   default location is the record) and CAppInfo::GetInst() after it, through the const GetGeral (fn 457), so each is a
#   statement of its own: `auto& iSavd = …instance();`, a name chosen to give the record's column at four spaces, as
#   landed code's `auto& iurna = …` does, then `const CAppInfo& appInfo = CAppInfo::GetInst();`, then the call; the
#   path's temporaries are freed after ValidarUE, so the path is built in that call's arguments. ValidarUE's ESavdAplic
#   is 1 (its wasm type has lost it: every caller passes 1), SAVD_APLIC_VOTA, a chosen name.
# - vota::GetQuantidadeMaximaBUsAdicionais (fn 4582, record 135:97, the closing parenthesis of an ASSERT whose text is
#   "Assert (numImpresso >= numObrigatorias)", code 3449, api::EUA_QUANTIDADEMAXIMABUSADICIONAIS_IMPRESSO_MENOR, a name
#   chosen to the column's length): 1 when EhTreinamento and the vota state's +72 byte (GetTreinamentoEleitor) are set,
#   else the extra copies less those already printed past the obligatory ones. Its return type, comum::TQtdImpresso,
#   is the record's: 8 bits wide and unsigned (the result is masked with 255), declared in votadefs.h, a chosen place.
#   The target takes GetVota()'s reference before it builds the CInformacaoEleicao, and keeps (obligatory - printed) +
#   extras in that order, which a TQtdImpresso local for the difference gives. Measured in copies of link.cmd with
#   votadefs.cpp.o alone recompiled (pnpm wasm score): a TQtdImpresso local for the copies printed past the obligatory
#   ones (the one written, `numAdicionais - numAdicionaisImpressos`), or for the obligatory ones not printed
#   (`numRestantes + numAdicionais`, the extras a TQtdImpresso or an int), or a static_cast<TQtdImpresso> of that
#   difference: 16 over 72 rows, operand-only; the one line `numObrigatorias - numImpresso + numAdicionais`, the printed
#   count a TQtdImpresso, an int or bound to a const reference: 20 over 74 (2 inserted, 2 deleted: clang adds the extras
#   first).
# - The roots give each two call sites: 7174 (vota::impl::CSincronismoVotoEleitor's slot 2) calls 3288 and 3290 three
#   times each, 12081 and 12974 call 4582; none is written. votadefs.cpp includes app/comum/dados/cconfiguracaoeleicao.h,
#   which reaches Boost, hence the include path on its object.
APP_HELPERS_SRCS := src/app/comum/cappstatecontext.cpp src/app/vota/comum/votadefs.cpp
UENUX2_SRCS += $(APP_HELPERS_SRCS)
# votadefs.cpp includes app/comum/dados/cconfiguracaoeleicao.h, which reaches Boost through CHorariosUrna
$(ROOT)/$(APP)/uenux2/src/app/vota/comum/votadefs.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# nothing in the link calls these functions yet: 168-uenux2-app-helpers-roots.cpp gives each two call sites. It compiles
# at the tree's flags, so the has<T> instance it emits is the code a uenux2 object gives, and no match rests on a flag
# the tree lacks
$(ROOT)/$(APP)/168-uenux2-app-helpers-roots.o: $(ROOT)/src/units/168-uenux2-app-helpers-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/168-uenux2-app-helpers.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/168-uenux2-app-helpers-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/168-uenux2-app-helpers-roots.o
