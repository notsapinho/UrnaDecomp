# uenux2: votaInit's callees that this tree did not have (target fn 7840, CVotaWebEngine::Init inlined, written in
# wasm/vota_web/vota_web_wasm.cpp, unit 170's TU, whose fragment has votaInit's own evidence and measurements). This
# fragment holds the trap below and the notes of the members written for votaInit in other units' files, each named
# with its unit; their rows' matches are listed in unit 170's fragment.
#
# The trap (440-uenux2-votainit-pending.cpp): vota::CTelasVota::CreateInst (target fn 7787, records ctelasvota.cpp:3435
# and the constructor's :3502, 148,912 B), which votaInit invokes through table slot 39 and which is not written; and
# in src/units/158-uenux2-api-pending.cpp, the RHVoice text-to-speech's constructor (fn 10842, 23,822 B, slot 45). They
# hold the place of votaInit's two calls, which need definitions our link has; each goes when its function is written.
# Neither is a vtable slot: src/units/README.md "Pending members" traps none such ("never trapped"), and a member the
# link must hold whose unwritten callee is one stays pending itself. votaInit is written instead, with these two
# traps, a shape those words do not give (a docs question). Their effects, measured on this link:
# - votaInit cannot match while they are traps: their target names (7787, 10842) would rest on votaInit's own table
#   votes. 7840 reads `unresolved` (pnpm wasm score against target 7840: 1262 over 2937 rows, its landing pads' block
#   order the rest).
# - The RHVoice trap constructs its base, api::ITextToSpeech, through a call clang leaves out of line (the trap's code
#   ends at `unreachable`), so ITextToSpeech's constructor has two callers in our link and binaryen keeps it out of
#   simulador::CWasmNullTextToSpeech's (fn 13877), where the target, whose 10842 inlines it, holds every store in 13877.
#   13877 waits for 10842 (50 over 54 rows).
# The trap compiles at ctelasvota.cpp's flags, as CreateInst will.
#
# Members written in other units' files for votaInit (each a body read from its target function; names, places and
# linkages chosen unless said):
# - unit 253, mock/app/comum/cappinfobuilder.{h,cpp}: comum::teste::CAppInfoBuilder's constructor (10268) and setters
#   SetFase, SetTurno, SetTipoUrna, SetLocalidade (10197, 10188, 10181, 10176), SetUF and PreparaVotacao (inline:
#   votaInit holds their stores), SalvaTudo (10256), SalvaAppsTurno1 and SalvaAppsTurno2 (10242, 10239, thunks of
#   binaryen's 6004), and TodosApps (10286). The members write the states' members directly, a friendship each md class
#   below declares (chosen). The header's comment has the evidence.
# - md/estadoaplicacao (the classes' units, headers only): default constructors read from what fn 10268 stores with no
#   call (CEstadoGeral, CDadoLocal, CLocalidadeEleitoral, CDadoCarga, CAjusteDataHora, CEstadoGeralSA, CEstadoGeralVota,
#   CNumViasImpressasRelatorios, inline) and from fns 10261 (CDadoCorrespondencia, with AssinaturaSimulada, fn 9963) and
#   10278 (CEstadoGeralGap), which have landing pads, so the builder's object's code, read as inline in their headers;
#   ecourna's CIdentificadorGeradorMidia (fn 9952) the same. CEstadoGeralVota::SetEstadoVota (11266) was written and
#   matches now that votaInit takes its slot.
# - unit 109, app/comum/appinfo/cappinfo.{h,cpp}: CAppInfo::CarregaGeral (11572).
# - app/vota/log/clogvota.{h,cpp}: CLogVota::LogaInicioAplicacao (11641) and LogaVersaoAplicacao (11642).
# - api/gui/instrucaomenu.h (new, path chosen): api::INSTRUCAO_PADRAO_MENU, moved out of cinputmenufield.cpp (unit 84)
#   so that the executable TU emits it without api/gui/iform.h; cinputmenufield.cpp includes it.
# - api/audio/itexttospeech.h (units 82 and 237): a user-provided ITextToSpeech(), since votaInit invokes fn 13877.
# - declarations: CTelasVota::CreateInst in ctelasvota.h (unit 110), CRHVoiceTextToSpeech's constructor taking a
#   std::filesystem::path in crhvoicetexttospeech.h (unit 158), both trapped above.
$(ROOT)/$(APP)/440-uenux2-votainit-pending.o: $(ROOT)/src/units/440-uenux2-votainit-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/440-uenux2-votainit.mk $(UENUX2_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(call uenux2_cxxflags,src/app/vota/eleitor/comum/ctelasvota.cpp) -c src/units/440-uenux2-votainit-pending.cpp -o $(R)
override EXTRA_OBJS += $(APP)/440-uenux2-votainit-pending.o
