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
# content-anchor and pair-fingerprint), and 5908 to 5911 by pair-fingerprint lines; 1485 by the scan's content pass alone
# (source `content` in splat/scan.tsv): no line of the symbol file names it, since none of its callers is in the link.
APP_HELPERS_SRCS := src/app/comum/cappstatecontext.cpp src/app/vota/comum/votadefs.cpp
UENUX2_SRCS += $(APP_HELPERS_SRCS)
# nothing in the link calls these functions yet: 168-uenux2-app-helpers-roots.cpp gives each two call sites. It compiles
# at the tree's flags, so the has<T> instance it emits is the code a uenux2 object gives, and no match rests on a flag
# the tree lacks
$(ROOT)/$(APP)/168-uenux2-app-helpers-roots.o: $(ROOT)/src/units/168-uenux2-app-helpers-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/168-uenux2-app-helpers.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/168-uenux2-app-helpers-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/168-uenux2-app-helpers-roots.o
