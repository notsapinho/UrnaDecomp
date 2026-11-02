# uenux2 data sources of api::CDataText, and control blocks of this tree's classes: vota::CEscolheOpcao (GetInst with its
# constructor, the four texts of its options, COpcaoDS's constructor and call operator, SOpcao's constructor) and
# vota::AdicionaCampoNumerico (src/app/vota/operador/outrasopcoes/cescolheopcao.cpp), comum::CCalculaCV's IncluiString, destructor,
# DestroyInst, Reinicia, CalculaCodigo and GeraMacHexa (src/app/comum/relatorios/ccalculacv.cpp), and the roots file 121-uenux2-datasources-roots.cpp, whose
# header says which vtables it keeps and from which dropped builders. Both files are the ones the classes' records name
# (cescolheopcao.cpp:150 to 152, StartState's; ccalculacv.cpp:58 to 74, the constructor's, and 109, IncluiString's).
# IncluiString's throw and StartState's three records are on their lines; the constructor is not written, and the lines
# of the functions here that have no record are a choice, after the records. Paths relative to src/uenux2.
#
# Target functions matched:
#   CDataText<vota::CEscolheOpcao::COpcaoDS>::GetText                 10685, with the source's call operator inlined
#   __shared_ptr_emplace<std::string> D2, D0, __on_zero_shared        10675, 10674, 10673, from cmostraeleitorvotando.cpp.o
#                                                                     (1150's std::make_shared)
#   __shared_ptr_emplace<api::CInputMenuField> D2, D0                 11070, 11069
#   comum::CCalculaCV's destructor, ~CCalculaCV (its D2)               5614, from ccalculacv.cpp.o
#   comum::CCalculaCV::IncluiString                                   942, from ccalculacv.cpp.o
#   comum::CCalculaCV::Reinicia                                       5615, from ccalculacv.cpp.o
#   comum::CCalculaCV::CalculaCodigo, with GeraMacHexa inlined        3700, from ccalculacv.cpp.o
#   vota::CEscolheOpcao's destructor and deleting destructor           2752, 10691, from cescolheopcao.cpp.o
#   the destroy of CEscolheOpcao's std::map                            3630, from cescolheopcao.cpp.o
#   vota::CEscolheOpcao::StartState                                    10690, from cescolheopcao.cpp.o
#   vota::CEscolheOpcao::GetInst, its constructor inlined               2753, from cescolheopcao.cpp.o
#   CEscolheOpcao::COpcaoDS's and SOpcao's constructors                 2751, 2750
#   the four option texts (TextoAudio, TextoEncerrarVotacao,           10695, 10694, 10693, 10692
#   TextoRegistrarMesarios, TextoExibirContadores)
#   CEscolheOpcao::s_inst's and s_mutex's static destructors           10697, 10696
#   vota::AdicionaCampoNumerico                                         1151, from cescolheopcao.cpp.o
#   std::__function::__func<std::string (*)(), std::string ()>'s       12043, 12044, 12046, 12047, from cescolheopcao.cpp.o
#   target_type, target and the two __clone, first instantiated here
# CCalculaCV::DestroyInst has no target function: unit 139's ~CGeradorBU (fn 3698) holds it inlined by binaryen, and
# that fragment has the evidence for its body and for its TU. It needs no root: its one caller is that destructor.
# Two forms of the operator give 10685 the same instructions in the whole link (`score 10 over 216 rows`, all
# operand-only, both): out of line in cescolheopcao.cpp, which binaryen inlines into its one caller, and defined in the
# class, with cescolheopcao.cpp.o left out of a copy of the plain link. Written out of line, a choice. The vtable
# (1588100) lies after CEscolheOpcao's typeinfo and before the next object's first record, which reads as
# cescolheopcao.cpp's object holding the GetText the target keeps; it does not tell the two forms apart.
#
# vota::CEscolheOpcao itself (cescolheopcao.h has the layout and what each part rests on): its destructor is out of line
# in cescolheopcao.cpp, at line 140, a choice before the records (10691 sits above 10690 and 10689 in their use band, so it
# links first); it is the class's key function, so the object emits the vtable, whose ProcessInput (10689) is trapped in
# 121-uenux2-datasources-pending.cpp (its header says what it waits for). Evidence:
# 10691 is `f2752(p0); drop; f136(p0)`, an out-of-line destructor (docs/reference/facts/reading.md R5), and 2752 stores
# no vptr first, a final class (R4); it releases the std::shared_ptr at +24 and then destroys the std::map at +12 with
# 3630, which destroys each node's std::function at +40 and nothing else of it. 2752, 10691 and 3630 matched as written;
# 3630's and 2752's match lines were renamed by step 9 (the map's mapped type is SOpcao now, and GetInst's delete calls
# the D1 alias, so the D2's symbol left the link). The members' names and the form's type are chosen.
#
# GetInst (2753) and what it calls, written in cescolheopcao.cpp before the destructor's line. Evidence, from the target's
# 2753 (pnpm wasm fn), each part measured in the whole link with pnpm wasm score:
# - GetInst is the project's singleton (lock_guard on s_mutex @1905284, reset of s_inst @1905308, unlock through fn
#   150). The constructor is a function of its own that binaryen inlined: its 272-byte frame opens after the `new` of 32
#   bytes and before the base constructor's call (fn 224 with comum::CAppState::EVENTO_ENTRADA, 2). It initializes the
#   map from a helper (the map's three words written in place at +12, NRVO) and the form from another (fn 301 writes its
#   result at +24 directly, with no zeroing of the member first, which an assignment in the body would need). Both
#   helpers have no frame of their own: clang inlines them, a reading that they are internal functions called once.
#   Chosen: the helpers' names (CriaOpcoes for the map, MontaTela for the form), their being in an anonymous namespace
#   and MontaTela's parameter.
# - The map: four emplace(numero, SOpcao(codigo, COpcaoDS(numero, &Texto))) whose find runs before the node is built
#   (libc++'s key-extracting emplace): key 1, 2, 3 (when vota::RegistraMesarios(), fn 2520, says so) and then the next
#   number when the urn is biometric (comum::CLocal::UrnaBiometrica, fn 820) and not in voter training (fn 697), with
#   the code 4 in SOpcao's int: 2751 is called with the number and 2750 with the code, and the node's key is the number.
# - 2751 and 2750 are out of line though cheap: at uenux2's -fPIC a call of an out-of-line constructor's C1 alias stays
#   a call in its own TU (docs/reference/facts/codegen.md C6). Written in the class (inline), clang inlined both into
#   the helper (-Rpass=inline: cost 20 and 25 against 250). Out of line they match byte for byte (score 0 over 41 and 47
#   rows). Their order in band 4 (2753, 2752, 2751, 2750: GetInst, the destructor, then the two constructors) is the
#   order of first mention when they are defined after the destructor's line, as written (ld_index 3096, 3097, 3103,
#   3104 at the first link).
# - By value: COpcaoDS's std::function and SOpcao's COpcaoDS are parameters by value. With `&&` both, the temporaries
#   of the four emplaces shared their stack slots and the frame was 144 bytes (2753: 461 over 1690 rows); by value, the
#   frame is the target's 272, each emplace's std::function and COpcaoDS in slots of their own, and the SOpcao
#   temporary shared (299 over 1687): a by-value class argument's temporary takes a new slot at each call, as
#   docs/reference/facts/codegen.md C10 measures.
# - The form: AddClock({33, 1}), "Selecione a opção: " at {1, 1}, one text per option through
#   api::CMTFormBuilder::AddTextField<COpcaoDS> (cmtformbuilder.h; binaryen holds it inlined behind a 48-byte frame)
#   at the column and line the loop keeps as two ints (1, 2; 1, 3; then 20, 2 and 20, 3), "CORRIGE: retornar" at {1, 4},
#   "CONFIRMA: prosseguir" at {40, 4} on the right, AdicionaCampoNumerico(builder, 1, true, {20, 1}) and
#   GetInteractiveForm("", true). The loop's coordinates as an api::SPoint kept in place gave 299 rows; as TPosition
#   (int16_t), a mask before each compare (74 over 1673, 6 inserted); as int with api::SPoint(coluna, linha),
#   operand-only (64 over 1667, all the statics' addresses and calls).
# - The texts are external functions defined after the statics: in band 1 the statics' destructors (10697, 10696)
#   link before the texts (10695 to 10692, in option order), which link before the destructor's D0 (10691). Internal
#   functions referenced only from the helpers would be emitted at the end of the object, after the D0 (clang defers
#   internal functions to the end of the TU: how-to step 3, "What a record's place says"). TextoAudio returns from two
#   branches, "Desativar áudio" or "Ativar áudio": a conditional expression gave one copy of a selected pointer (50 over
#   64); two returns, the target's two fixed copies. The names and the texts' being free functions of namespace vota
#   are chosen.
# - 1151, vota::AdicionaCampoNumerico(api::CMTFormBuilder&, size_t, bool, const api::SPoint&), returns the
#   std::shared_ptr<api::IInputField<api::IScreenMT>> it builds: a CNumberValidation (cnumbervalidation.h, its
#   constructor inlined, "0123456789" stored in place), a CInputFieldMT over it (cinputfieldmt.h's constructor inlined,
#   3673 called), AddField (3674) with a SharedField copy, the validation released last, so a named local. Its copy is
#   this object's: the control block it alone instantiates (@1588176) lies in cescolheopcao.cpp's data. A free function
#   of namespace vota, declared in cescolheopcao.h, external (9 target callers in several TUs), its name and its
#   parameters' names are chosen; its band (11) has no other function of this object.
# - The new names (step 8): 2753 and 1151 by vptr-anchor (CEscolheOpcao's and CInputFieldMT's vptrs), 2751 and 2750 by
#   pair-fingerprint, the texts by 2753's table slots (table), s_inst by the votes of 2753 and 10697 and s_mutex by
#   2753's (vote:1; its static destructor 10696 matches through it).
# The roots stand for GetInst's four target callers (fns 10677, 10698, 10740, 10754) and for 1151's other eight
# (12 and false, so that dead-argument elimination keeps the length and the flag); the vtable sinks of CEscolheOpcao and
# of CDataText<COpcaoDS> went, since 2753 stores both vptrs, and so did the builder of CDataText<COpcaoDS>.
# cescolheopcao.cpp.o now links ahead of unit 31's cmtformbuilder.cpp.o and gives the copies of what both instantiate:
# IInputField<IScreenMT>'s constructor (3673), its destructor and Read, and the vector's emplace_back (1400, renamed by
# step 9 to its IScreenMT twin), each re-pointing as before. Choices that give the same bytes: none measured. Not
# measured either: 1151 as the linkonce copy of an inline definition in a header, the other reading unit 31's fragment
# gave of where the target's copy comes from before 1151 was written.
#
# StartState (10690, slot 2) is written at its records' lines in cescolheopcao.cpp: it sets the next state to itself,
# shows the form at +24 (its slot 2), logs with musl's syslog(LOG_INFO, "%s:%d> %d", __func__, __LINE__, ...) whether
# IUrna's Modelo() (slot 0) is at least 2020, and when it is calls IScreenMT's slot 19 with 1. Evidence: the three
# records (150:55, the CPolySingleton<IUrna>::instance() call inside syslog's arguments, which `__func__, __LINE__,`
# written out put at that column; 151:9 and 152:9), the literals "%s:%d> %d" and "StartState", the 150 and the priority
# 6 the target passes. syslog is the C library's: binaryen inlines it into its one caller, its 16-byte frame holding the
# va_list, and the target's 10690 has that frame too around its call of __vsyslog (2946). Chosen: `>= 2020` spelled in
# both places, which gives the target's rows (the first as `i32.gt_s` of 2019; `> 2019` spelled there is not measured),
# and api:: written at each call. Before steps 7 to 9 it scored 14 over 96 rows, all operand-only (pnpm wasm score).
#
# Matched once a literal landed:
# - 12621, CDataText<comum::CRespostasDSNumero>::GetText, emitted by unit 102's roots object. Its operator is in
#   crespostas.cpp (unit 110's source; app/comum/dados/crespostasds.h says why it is there). clang leaves
#   CRespostas::GetInst out of the operator: `-Rpass-missed=inline` gives cost 230 against the threshold 225 at -O2, and
#   at -O3 it is inlined (threshold 250), as in the target. At the tree's -O3 it scored `20 over 190 rows`, all
#   operand-only, and stayed `unresolved` on one operand: the end of the format string "{:0{}}", which in the target is
#   the tail of "  {}{}{:0{}}" (address 1042, loaded by fn 11973) and in our link was a string of its own. It matches,
#   its body unchanged, since 11973 (CDataSourcesRelatorio<CRdvVota, CEleitores>::DetalheCandidatoZE,
#   src/units/183-uenux2-relatorios.mk) holds that literal in the link.
# Members the unit brings with no target body of their own:
# - 10688 and 10686, CDataText<COpcaoDS>'s D2 and D0: the implicit destructor cdatatext.h gives, as compiled here. In
#   the target each is a 12-B thunk into fns 6053 and 6052, binaryen's merges of them with the D2 and D0 of
#   __func<vota::IConfereVotoEmCargo::ExecutarAposAudioAtual(std::function<void ()>)::$_2, void (bool)> (11765, 11764).
#   They read `differs` until that lambda's function lands and our link forms the same merge.
#
# CCalculaCV's destructor, 5614, has two target callers, fn 11263 (the __on_zero_shared of the class's block,
# __shared_ptr_pointer<CCalculaCV*, std::default_delete<CCalculaCV>, ...>) and fn 12110; neither is in our link, and the
# roots file's stand-in calls it twice for them, so it stays a function of its own. The block itself, its __get_deleter
# 11262 and __on_zero_shared 11263, waits for its real builder in ccalculacv.cpp: push<CCalculaCV>, inlined into fn 12110,
# which holds the constructor's records and is not reconstructed (17349 B, `no-candidate` in splat/scan.tsv). A dropped
# builder in the roots file does not stand in for it. Measured with one: 11262 matched, and the
# block's __on_zero_shared, compiled where the destructor is only declared, freed what the destructor returns, so
# binaryen kept the destructor's result and 5614 scored `6 over 52 rows` (5 operand-only, 1 inserted) and did not match;
# without the builder, 5614 matches. A probe of `delete p` at -O2 frees the destructor's result when the TU only
# declares the destructor, and drops it and frees p when the TU defines it, which is the shape of the target's 11263 and
# of fn 12110's release of the std::unique_ptr, which reads as both compiled where the destructor is defined.
#
# IncluiString (942): its record (ccalculacv.cpp:109:15, `void comum::CCalculaCV::IncluiString(const std::string &)`)
# gives the name and signature, its throw code 9054 and message "String vazia" are the target's, and its body appends
# the argument to the string at +16 with fn 160, `append(const char*, size_t)`, after testing the size it passes there.
# `m_texto.append(str)` is what is written; `m_texto += str` and `m_texto.append(str.data(), str.size())` give the same
# function (compared in ccalculacv.cpp's object with the object-local numbers masked). Of its eight target callers (5967, 11253, 11254, 11255, 11256, 11260, 11980,
# 11981) unit 139's 11254, 11255 and 11256 are in our link: the roots file's stand-in calls it twice for the other five.
#
# Reinicia, CalculaCodigo and GeraMacHexa have no record, and their names are chosen: CalculaCodigo is the function
# CRelUtil::DSCodigoVerificador (fn 11182, unit 123) formats as the verification code. Scores are `pnpm wasm score`
# against the plain link, before steps 7 to 9.
# - Reinicia (5615; callers 3700 and 12110): the string at +16 assigned the byte at +12 (libc++'s operator=(char): the
#   short or long size set to 1, then the byte and a NUL), then appended the string at +0 and the argument, which is
#   then copied to +40. 0 over 124 rows. In band 2 (ledger/ordinals.tsv) it is above the destructor (5614), so it is
#   defined before it: in our link its ld_index (2402) is below 5614's (2403).
# - CalculaCodigo (3700; callers 11182, 11260, 11974) increments +52, appends its decimal text to +16, takes the text's
#   SipHash MAC under the key at +28 (GeraMacHexa), reads the MAC's hexadecimal text with
#   ecourna::api::util::CStringUtils::HexToQWord, hands the number's decimal text to Reinicia and returns "{:010}" of
#   the number modulo 10^10. GeraMacHexa builds an ecourna::api::security::CSiphashMac on the stack, copies the text to
#   a byte vector, calls IMacAlgorithm::Mac and appends "{:02x}" of each MAC byte, an index loop. 3700 holds GeraMacHexa,
#   Mac, HexToQWord and std::to_string(unsigned long long) inlined by binaryen, behind prologues of their own (frames of
#   416, 32, 32, and 48 and 16 bytes); the records of Mac (imacalgorithm.cpp:32, 35) and of HexToQWord
#   (cstringutils.cpp:754) are loaded by 3700 alone, and anchor its name. The two vptr stores, IMacAlgorithm's (1114744)
#   and then CSiphashMac's (1113604), say that the base's constructor was a call when clang compiled 3700: unit 11
#   defines it out of line. CSiphashMac's own, defaulted in its header, gives the same bytes out of line, a choice (unit
#   11's fragment). Measured:
#   - GeraMacHexa a free function over (text, key), defined before CalculaCodigo, the constructors inline in the
#     headers: 242 over 888 (21 inserted, 23 deleted); with the constructors out of line: 268 over 880 (13, 13), the two
#     vptr stores now there; as a const member that takes the text and reads the key: 222 over 875 (8, 8); as one that
#     reads both members: 238 over 891 (24, 23); the member over the text defined after CalculaCodigo, as written: 70
#     over 867, all operand-only. The operands that are no call and no data address: the address of emscripten's
#     __THREW__ (1936852 in the target, 18 rows), the format buffer's table slot (148), and the table slots of
#     __cxa_throw (49) and of the thrown object's destructor (69) in Mac's two throws.
#   - Mac and HexToQWord have one call site in our link, in 3700, so binaryen inlines them there as in the target: unit
#     11's roots no longer take Mac's address, nor CSiphashMac's DoMac and DoVerify (9498 and 9497 keep `match`, in the
#     link through the vtable 3700 stores), and src/app/roots_ecourna.cpp's UsaConversoes3 no longer calls HexToQWord.
#     Its other calls stay.
# The roots file's w121_reinicia stands for 12110, Reinicia's caller not in the link, and w121_codigo for 11260 and
# 11974, CalculaCodigo's: each goes when they land. 11260 and 11974 (CDataSourcesRelatorio<CRdvVota, CEleitores>'s
# TrailerProporcionalPartido and CodVerificador, records cdatasourcesrelatorio.h:188 and 348) wait for fn 5967, which
# loads IncluiString's record and calls fn 1281 (439 B, no body or name of ours).
#
# Choices measured to give the same bytes, by function with the object-local numbers masked: CCalculaCV's destructor
# `= default` or `{}` (ccalculacv.cpp.o). The roots object compiles with APP_CXXFLAGS; with UENUX2_CXXFLAGS its 27 functions
# compare equal. The names and types no evidence gives are marked as chosen where they are declared: crespostasds.h,
# cescolheopcao.h, ccalculacv.h, cinputmenufield.h's constructor and crespostaconsulta.h's GetNumero.
#
# Pending, with what each waits for: CGeracaoVersoesContratos's block (11635, 11636) waits for a class head in
# app/comum/gravadores/; the blocks and members over a lambda or another TU's anonymous namespace wait for the function that
# spells them (11107, 11109 and 11108 matched with fn 502, AddStatusHeader, cformbuilder.cpp): 12524, 12522, 12530, 12529, 12520 for fn
# 6561 (CTelasVota::CriaTelaVisualizacaoCandidato), 12587, 12588, 12589, 12592, 12591 for fn 6627 (ctelasvota.cpp's
# anonymous namespace, reached through fn 1192), 10373, 10367, 10361 for fn 10388.
W121_SRCS := src/app/comum/relatorios/ccalculacv.cpp src/app/vota/operador/outrasopcoes/cescolheopcao.cpp
UENUX2_SRCS += $(W121_SRCS)
# The roots file reads uenux2 headers, and through them ecourna's (uetypes.hpp, the error templates).
W121_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/121-uenux2-datasources-roots.o: $(ROOT)/src/units/121-uenux2-datasources-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/121-uenux2-datasources.mk $(W121_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/121-uenux2-datasources-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/121-uenux2-datasources-roots.o

# vota::CEscolheOpcao's pending slots (StartState and ProcessInput), trapped at the unit's flags so that the class links;
# the -pending.cpp says what each waits for. The rule depends on every header of both trees, as the roots rule does.
$(ROOT)/$(APP)/121-uenux2-datasources-pending.o: $(ROOT)/src/units/121-uenux2-datasources-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/121-uenux2-datasources.mk $(W121_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/121-uenux2-datasources-pending.cpp -o $(R)
override EXTRA_OBJS += $(APP)/121-uenux2-datasources-pending.o
