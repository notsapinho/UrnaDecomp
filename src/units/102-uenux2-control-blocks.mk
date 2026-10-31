# std::shared_ptr control blocks over this tree's classes: the __shared_ptr_pointer<T*, ...> and __shared_ptr_emplace<T>
# members of 67 blocks, from 102-uenux2-control-blocks-roots.cpp (its header says how), with what a block's slot 2 said
# of its class's destructor. Each block below: the T, the function that stores its vptr in the target, and the members
# the unit matches. The vtable's other slots are shared bodies matched already (174, 144, 172, 411, 519, 1946, 2967).
# Pointer blocks (slot 3, __get_deleter; slot 2 too where it is listed):
#   IFormField<IPaper>: CTextFieldPaper 193, 604, 5613, 12105: 11997. CCutFieldPaper 1264: 10994.
#     CNewLineFieldPaper 198: 10993
#   IFormField<IScreen>: CDSImageField 502: 11116
#   IInputValidation: COptionValidation 5913: 11665. CNumberValidation 1151, 2383, 7787: 12463
#   IInputField<IScreenMT>: CInputFieldMT 1151: 10683
#   IText: CDataText<CPadDS<CToUpperDS<CCargoDSNome>>> 5613: 11246. CDataText<vota::CEscolheOpcao::COpcaoDS> 2753: 10684
#   IForm<IPaper>: IFormImpressao<IPaperRelatorios> 5515: 11001
#   IPreShow<IScreen>: vota::CPreShowFormVota 576, 886: 7660. CPreShowClearScreen 11140: 11138.
#     CPreShowNothing<IScreen> 11891: 11137
#   IPreShow<IPaper>: CPreShowNothing<IPaper> 5515: 11010
#   IDAO: IComparecimentoMesarioDAO 7787: 11664. IJustificadorDAO 7787: 11663
#   comum::IGravador, all 12098: CGravadorBU 12097, RDV 12096, RCSecao 12095, EnvelopeArquivo 12094, Hashes 12093,
#     VersoesArquivos 12089, Log 12088, and CGravadorWSQ 12091 with slot 2, 12092
#   comum::CItemMenu, all 6599: CItemImprimeEstadoUrnaVota 12209, CItemImprimeListaEleitoresVota 12202,
#     CItemVersoesPacotesVota 12194, CItemParametrosUrnaVota 12183, one slot 2 for the four, 2932;
#     CItemVisualizarCandidatosVota 12162 with slot 2, 12172
#   ISymmetricCipher: CBlockCipher<CAesCipher, CTrng> 9489: 9479 with slot 2, 9480
#   IHash: CSha512 3602: 10277 with slot 2, 10279
#   the block's own class: IForm<IScreen> 5550: 11127. CInteractiveForm<IScreen, IInputKbd> 554: 11073.
#     CInteractiveForm<IScreenMT, IInputMT> 301: 11027. CQRCodeImageFieldPaper 2775: 10992. CVisitanteFoto 7787: 11425.
#     CVisitanteEleitor 11523: 11435. CIdentificacaoSecao 12098: 11618. CIdentificacaoUrnaContingencia 12098: 11617.
#     IComparecimentoMesarioDAO 815: 10311. IJustificadorDAO 3742: 11463. CEleitorDinamico 11542: 11536 with slot 2,
#     11537. ecourna CIdentificacaoJustificativa 11470: 11465 with slot 2, 11466. comum::md::CComparecimentoMesario
#     10402: 10395, and std::string 10740: 10749, with their one slot 2, 5429
# Emplace blocks (slots 0 and 1, D2 and D0; slot 2 too where it is listed):
#   CMovie 1593, 3076: 12835, 12830, 12823. FormControlBlock 5515, 6024: 11131, 11130, 11128. CProgressoEncerramento
#   12098: 12087, 12086, 12085. CProgressBar 5545: 11111, 11110. CMovieField 5543: 11104, 11103. CTextFieldBlinking
#   1265: 11113, 11112. CTextFieldUpdate 502, 3058, 5936: 12316, 12314. CImageFieldUpdate 3059: 12541, 12535. CWavFile
#   10841: 10819, 10818. CFixedImage 1263, 8633: 8585, 8578. CPreShowProgressBar (ten builders, 1591 first): 12813,
#   12812. CCopiadorMR 12134: 12124, 12120. CCopiadorWSQMR 12134: 12117, 12116. CTimer 10846: 10844, 10843. api::Logger
#   10842: 10817, 10816. BatteryIconDataSource<Horizontal> 502: 11106, 11105. ecourna CTrng 6154: 9483, 9482.
#   CDataText<CCandidaturasDSNumero> 4185: 12760, 12752. <CCandidaturasDSNome> 4185: 12654, 12650.
#   <CCargoDSNomeSexoCandidato> 6528: 12637, 12636. <CRespostasDSNumero> 6652: 12625, 12622.
#   CDataImage<CCandidaturasDSFoto> 4129: 12643, 12642
# Members a block brought with it:
# - comum::CItemMenu's D2 (2937, a merge thunk over 1727, whose line now names the fifth item's symbol, one body with
#   it) and vota::CItemVisualizarCandidatosVota's D0 (12251), in the new citensmenuvota.cpp.
# - ecourna::app::dados: 3803, slot 2 of the three CNumero* blocks, with the D2 (3492) and D0 (3491) of those classes.
# - ecourna::api::security::CAesKey's D2 (3517).
# Landed headers this unit changes, and what says so:
# - CNumeroCPF, CNumeroInscricaoEleitoral and CNumeroIdentificacaoLivre are final and declare their destructor out of
#   line, and IIdentificadorEleitor's destructor is out of line. Evidence: 3803 is f778(p0 + 12), no call through the
#   vtable, which only final gives, and slot 0 of the three vtables is 3492, push f778(p0), a D2 of one call, which
#   only an out-of-line destructor over a base out of line in another object gives. At ecourna's -O3 the D0 of that form
#   has no drop: f136(f778(p0)), 3491, not the drop docs/reference/facts/reading.md R5 shows at -O2. A probe of every
#   base form and derived form at ecourna's flags gives these three shapes in this one form. IIdentificadorEleitor's
#   typeinfo (1122232) lies past its three derived classes', the place of its own object's copy (R6). The destructors'
#   places in their .cpp files are chosen: no record holds them.
# - CBlockCipher is final. Evidence: 9480 and the unwind path of 9489 hold the destructor inlined where an open class
#   calls through the vtable (172).
# - CAesKey's destructor is implicit, and unit 11's root of it is gone: 3517 is its D2, called by 1884, 9474 and 9495,
#   and 9480 holds it inlined, which the former out-of-line definition (62 B, in isymmetriccipher.cpp) could not give.
#   Two blank lines keep that file's records in place. ISymmetricCipher's constructor 9474 reads `differs` at last,
#   at its call 306, the executable TU's copy.
# - CSha's destructor is implicit and CSha512 is final. Evidence: 10279 holds CSha's destructor inlined. Measured: with
#   the destructor out of line, even in one TU with its builder at ecourna's flags, the block calls it. The destructor's
#   D2 and D0 (5175, 5176) stay matched, emitted with the vtable in csha.cpp, since Reset is now the first virtual
#   member out of line. Two blank lines keep the records in place.
# Choices, each measured to give the same bytes (by function, object-local numbers masked, except where it says):
# - final on the class, or on the destructor alone (`~X() final`): CNumeroCPF (object and roots_ecourna.o),
#   CBlockCipher, CSha512 (`~CSha512() final = default;`), CItemParametrosUrnaVota. Written on the class.
# - `= default` or `{}` for an out-of-line destructor: ~CNumeroCPF, ~IIdentificadorEleitor,
#   ~CItemVisualizarCandidatosVota. Written `= default`.
# - implicit, `~CAesKey() = default;` in the class, or `inline ~CAesKey() = default;`: the same objects (the classes'
#   functions in isymmetriccipher.cpp and in the roots object). Written implicit.
# - implicit, `virtual ~CSha() = default;`, `inline virtual ~CSha() = default;` or `virtual ~CSha() {}`: the same in
#   csha.cpp and in the roots object. Written implicit.
# - CItemMenu's `virtual ~CItemMenu() = default;`, `inline` with it, or `{}`: the same. Written `= default`.
# - every class head's path, each said in its header, and every name the head says is chosen; and that the three
#   CNumero* destructors are declared after the constructor. Not chosen: api::IFormImpressao's file and parameter, which
#   record 1581300 gives (api/gui/cpaperformbuilder.h, CLASS); the class's lines span that record's line 51.
# Flags: the roots object compiles with APP_CXXFLAGS, and with UENUX2_CXXFLAGS its 427 functions compare equal. The
# blocks of ecourna's classes: at ECOURNA_CXXFLAGS, brought into a private link ahead of the roots object, 9480 and
# 11466 give the target's rows (score 4 over 38 and 1 over 60, operand rows only), and 10279 does not (25 over 56, 19
# rows inserted). So 9480's and 11466's bodies do not depend on which of the two levels compiles them, and 10279's copy
# has uenux2's level. That reads as a builder (3602) in a uenux2 TU, which is why CSha's destructor is taken as inline
# there; 3602's file is not recovered, so it is a reading and not a measurement.
# Pending, each with what it waits for:
# - 12244, vota::CItemVisualizarCandidatosVota's slot 2, a trap in 102-uenux2-control-blocks-pending.cpp, the one slot
#   this unit leaves with no body, and no stub.
# - 11109, 11108, CDataText<AddStatusHeader's lambda>, and 12530, 12529,
#   CDataImage<__bind<CriaTelaVisualizacaoCandidato's lambda, ...>>: a lambda is spelled only in its function, so they
#   land with fns 502 and 6561.
# - 12592, 12591, CDataText<vota::(anonymous namespace)::DS_NomeCargoNeutroComEscolha>, and 10373, 10367, 10361, three
#   blocks of CDataTextFmt<comum::(anonymous namespace)::CComparecimentoMesariosDS>: no roots file can spell a T of
#   another TU's anonymous namespace, so they land with fns 6627 and 10388.
# 11070 and 11069, the D2 and D0 of __shared_ptr_emplace<api::CInputMenuField>, which waited here for a constructor to name
# in the builder, match since from unit 121's roots, which name the one cinputmenufield.h declares now.
# Paths relative to src/uenux2. citensmenuvota.cpp holds the out-of-line destructor the block of the fifth item needs.
W102_SRCS := src/app/vota/operador/outrasopcoes/citensmenuvota.cpp
UENUX2_SRCS += $(W102_SRCS)
# Both companions read headers of both trees, and the roots file the ASN.1 runtime's, OpenSSL's and RHVoice's.
W102_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp') $(wildcard $(ROOT)/src/asn1/*.h)
$(ROOT)/$(APP)/102-uenux2-control-blocks-pending.o: $(ROOT)/src/units/102-uenux2-control-blocks-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/102-uenux2-control-blocks.mk $(W102_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/102-uenux2-control-blocks-pending.cpp -o $(R)
$(ROOT)/$(APP)/102-uenux2-control-blocks-roots.o: $(ROOT)/src/units/102-uenux2-control-blocks-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/102-uenux2-control-blocks.mk $(W102_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) $(OPENSSL_INCLUDES) -Ithird_party/RHVoice/src/include -c src/units/102-uenux2-control-blocks-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/102-uenux2-control-blocks-pending.o $(APP)/102-uenux2-control-blocks-roots.o
