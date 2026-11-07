# uenux2 comum::CGeradorBUQRCode (app/comum/relatorios/cgeradorbuqrcode.cpp, its records' file, and a chosen
# cgeradorbuqrcode.h) and comum::CGeradorBUQRCodeVota (cgeradorbuqrcodevota.{h,cpp}, chosen paths; the headers say what
# the data show of them). Paths relative to src/uenux2.
#
# Matched:
# - CGeradorBUQRCode's D2 (target fn 2251), its key function, with the two destructors it calls: the destroy of the tree
#   of the map at +404 (fn 1405, std::map<md::ETipoAbrangencia, SQtdeAptos>'s; in the target it calls itself and has
#   five more callers, 2251, 5603, 5857, 11968 and 12098, and before this unit our link's candidate for it was another
#   tree's) and CCabecalhoQRCodeBuilder's implicit destructor (fn 2885), which clang keeps out of line, a weak function
#   this object emits; the link takes it from vota's cmostraqrcodebu.cpp.o, the first object in link order to emit it.
# - GetCamposAptos (fn 3696), which formats the coverage counts of the current post; it calls GetQtdAptos (record
#   cgeradorbuqrcode.cpp:80), out of line in the object, and binaryen inlines that into its one caller, as the target's
#   second stack frame inside 3696 shows (docs/reference/facts/reading.md R10).
# - CGeradorBUQRCodeVota's D2 (fn 11244), which only calls the base's, its D0 (fn 11243), and Slot3 (fn 11241), which
#   returns an empty string.
# - GetCamposVotos (fn 5606, no record; its stub was in src/ecourna/unplaced.cpp), which formats the current post's
#   votes after GetCamposAptos's fields: it calls GetCamposAptos (fn 3696) on its own this and slots 6, 9, 8 and 10 of
#   the object at +400 (comum::CRdv's Nominais, Brancos, Nulos and Cargo, crdv.h) with the byte at +0 of
#   CCargos::GetCurrent()'s CCargo, and prints them as "NOMI:{} ", "BRAN:{} ", "NULO:{} " and "TOTC:{} " (argument type
#   6, unsigned: md::TQtdVoto is a ueword). Its one target caller is fn 5604, which calls it twice.
# - CGeradorBUQRCodeVota's constructor (fn 5603), with CGeradorBUQRCode's (inlined, of cgeradorbuqrcode.cpp: one caller,
#   no frame), and CCabecalhoQRCodeBuilder's implicit copy constructor (fn 5608, a weak function of this file's objects;
#   its callers 5603 and 5604 are both here). cgeradorbuqrcodevota.h says why the constructor takes two flags its
#   callers pass as false.
# - Of Gera (fn 5604, below): preBuild's lambda (fn 2791, record ccabecalhoqrcodebuilder.cpp:284, unit 93's file),
#   api::CPolySingleton<api::pkcs11::IPkcs11>::instance (fn 3704, a template instance; its records are the header's; the
#   link takes it from comum/dados/md/estadoaplicacao/cestadogeral.cpp.o, the first object in link order to emit it
#   since RecuperarCertificado, fn 5635, is written there (unit 215), as the target's data do: its record @1574788
#   follows 5635's @1574772), and std::sort's instances over the consulta's answers with GetCamposConsulta's comparator
#   lambda: __introsort (5605), __insertion_sort_incomplete (2790), __sort4 (1920) and iter_swap (248). 2790, 1920 and
#   248 serve fn 5610 too (unit 139's introsort of the same element over ImprimeConsulta's comparator, 11253's):
#   binaryen merges the identical instances, and the link takes them from unit 139's cgeradorbu.cpp.o, which links
#   first; 5605 is this object's.
# - CGeradorBUQRCodeVota's Slot2 (fn 11242, no record of its own; the vtable's slot 2 names it): it fills the QR code
#   header's fields of the builder Gera passes it, ORIG to HREM, with CEstadoGeralVota::GetDtHrInicioAquisicao and
#   GetDtHrFimAquisicao inlined from their header (records cestadogeralvota.h:90 and :106, in this object's data), and
#   sixteen setters of unit 93's ccabecalhoqrcodebuilder.cpp and CLocal::GetIdentificacoesAgregadas of unit 89's
#   clocal.cpp, each behind a frame of its own, so each is a function binaryen inlined into its one caller (a
#   reading; their headers say what each shows). What the bytes decided, measured with pnpm wasm score against the
#   target in the whole link, the forms below as written but the one compared:
#   - the objects' order. With this unit's two sources ahead of ccabecalhoqrcodebuilder.cpp (unit 93's) and
#     clocal.cpp (unit 89's), as this fragment listed them, 939 over 4456 rows (58 inserted, 73 deleted: the target
#     keeps the tails of three inlined setters in a block left by a `br 0`, ours none); with the builder's object
#     moved ahead of cgeradorbuqrcode.cpp, 751 over 4441 (43 inserted, 44 deleted, locals); with clocal.cpp's moved
#     alone, 1466 over 4510; with both moved, or with this unit's two objects moved after unit 93's list, 230 over
#     4398, every row operand-only and every operand a call, a data address, a table slot (the format buffer's 148
#     against our 43, the exception destructor's) or a packed string address (scratch links of the plain link.cmd
#     with the objects moved). The target's data put clocal.cpp's records @1559828, the builder's @1574996,
#     cgeradorbuqrcode.cpp's @1575936 and this class's vtable @1575976 in that order, so unit 93's list compiles the
#     two sources, at its end (src/units/README.md "Names"; right after the builder measured the same), which keeps
#     unit 93's other files, whose records lie at @1574836 to @1574932, ahead of them. Counted at 404e9c80 over every
#     uenux2 object with records or a strong vtable (ledger/source-locations.tsv, ledger/vtables.json), the two objects'
#     pairs out of the data's order are 257 at this unit's place, 246 with the builder and clocal.cpp moved into this
#     unit's list instead, and 232 at the end of unit 93's: the fewest among the places "Names" allows
#     (docs/reference/facts/codegen.md C4). The end of the uenux2 objects would give 199 and keeps the match too (a
#     scratch link), but lies in no unit's list, which "Names" rules out. The move from this unit's place fixes 157
#     pairs and inverts 132, whose objects' data lie after the pair's (@1575912 to @1575976): api/gui 40 and gui/reports
#     2; vota/operador's confirmaidentidade 19, outrasopcoes 12, justificativa 11 and leidentidade 5; comum/relatorios
#     8, among them unit 89's cpartecandidatos.cpp, cparteeleitores.cpp and cparterdv.cpp; api/util 6 and gravadores/asn
#     6, among them cassinavotavelbu.cpp; comparecimentomesario 6; validamidia, api/hash, api/io, vota/operador and
#     operador/comum 2 each; api/audio, alsa, api/hwil, api/ipc, uelog, iexecucaovota and aguardaeleitor 1 each. Gera's
#     rows moved with it (below).
#   - GetIdentificacoesAgregadas tests for no section first and returns the empty vector there: with the copy's
#     return first, 249 over 4406 (8 inserted, 9 deleted, the branch order).
#   - The acquisition's start and end are copies, two const api::CDateTime locals read before the first of their
#     setters (the target copies both after both tests): bound to references, 1532 over 4441.
#   - TemVota's turn is read through the const GetGeral (fn 457) on a second GetInst() whose result the target hands
#     to 457 directly: written with std::as_const, a choice; a static_cast to const CAppInfo& is the other spelling
#     (not measured).
#
# Written, not matching: Gera (fn 5604, 22805 B, `no-candidate`: its records name no body that differs, since
# srcloc-anchor pairs bodies of the same opcodes only, docs/reference/splat.md section 2).
# It builds the boletim's QR code: the header (GetCabecalho: a copy of the builder, eight setters of unit 93's file,
# Slot2, build), the body (GetCorpo: per post, in print order, "IDEL"/Slot3 when the election changes, "CARG", "TIPO",
# "VERC" from the candidacies' or the election's package version, and the coverage and vote fields of a proportional,
# majoritarian or consulta post), cut into parts of at most its argument less 277 bytes at a space (DivideEmBlocos),
# each part's SHA-512 chained over the earlier parts (CalculaHash), and the last part's hash signed through IPkcs11
# (RetornaBlocoAssinado, record cgeradorbuqrcode.cpp:405, the instance() call). Each helper is a frame of its own in
# 5604, so each is a function binaryen inlined into its one caller. The target's body holds 10253 instructions and ours
# 10255, with the same 470 direct and indirect calls in the same order (`pnpm wasm fn` of both, the calls paired one
# for one). Scored with pnpm wasm score on the whole link, this object swapped into a copy of link.cmd
# (docs/reference/facts/workflow.md W13), each form below added to the ones before it, from 1327 over 10331 rows (77
# inserted, 78 deleted) as it stood:
# - DivideEmBlocos holds the text's size in a local, tamanhoTotal, for its loop's bound: the target loads the size once
#   before the loop and compares it at the latch, while each substr reloads it; and MontaPartes reads blocos.size()
#   before it declares its vectors: the target loads the vector's bounds before it zeroes them. 1286 over 10314.
# - GetCamposCandidatosPartido, GetCamposMajoritario and GetCamposConsulta read the post's id (+0) and digit count
#   (+12) into locals right after GetCurrent(), before anything else, as the target's three loops do: the id declared
#   first, 1084 over 10302; the count first, 1098 over 10310.
# - GetCamposMajoritario and GetCamposConsulta hold the candidate's or answer's number in a local before
#   m_rdv.Candidato and skip a count of zero, as GetCamposCandidatosPartido does: the target tests the count and
#   branches past the format. 1070 over 10300.
# - MontaPartes joins the earlier blocks in a statement of its own: the target frees the " " separator right after
#   api::Join, before blocos.at(). 1031 over 10287.
# - DivideEmBlocos declares its vector before the size: the target zeroes the vector first. 962 over 10273.
# - CalculaHash takes std::min(conteudo.size(), posicao + 512): the target selects posicao + 512 when it is below the
#   size. 959 over 10272.
# - GetCorpo's post with a candidate detail and no candidates ends its iteration (continue): the target branches from
#   that arm past the consulta's VERC and the type chain, while the arm after it falls into the consulta's test.
#   976 over 10271 rows (17 inserted, 15 deleted, 943 of the 944 replaced rows operand-only), the score up but the
#   structural hunks down: diffed with local indices, callees, data addresses, packed strings and the format buffer's
#   table slot masked (Python difflib over the two `pnpm wasm fn` disassemblies), 50 hunks at the start and 3 here. An
#   else around the rest of the iteration gives the same object (cmp); `else if (cargo.IsConsulta())` in place of the
#   continue, 956 over 10273 with 8 hunks, made the arm before it jump past the consulta's test, as the target's does
#   not.
# What is left is local numbers and what they decide. Paired through that masked alignment, 442 of 3870 local
# operands differ: our local 14 holds both the target's 15 and its 28 (three uses, the capacity pointer of partes'
# push_back in MontaPartes), which shifts the numbers of the locals ranked after it, and our 3 and 4 trade places in
# stretches through the body; the three hunks are an operand order of GetCorpo's election compare and a zero set of our
# local 14 at MontaPartes' start that the target has not. MontaPartes defined above RetornaBlocoAssinado, and
# CalculaHash above DivideEmBlocos, each scored 976 over 10271 too. Not tried: the colouring of each helper's own
# object (docs/reference/facts/codegen.md C4, "Local numbers can come from clang's object too").
#
# Chosen: the names Slot2, Slot3, GetCamposAptos, GetCamposVotos, Gera and its helpers' (GetCabecalho, GetCorpo,
# GetCamposEleicao, GetCamposSecao, GetCamposProporcional, GetCamposCandidatosPartido, GetCamposLegenda,
# GetCamposVotosProporcional, GetCamposMajoritario, GetCamposConsulta, MontaPartes, DivideEmBlocos, CalculaHash), and
# every data member's (CGeradorBUQRCodeVota's two flags' after what Slot2 does with them); Slot2's locals and the
# order of its statements no call fixes; the helpers' being members where they read the object and free functions
# where they do not;
# Gera's std::pair result; SQtdeAptos's place and its members' names (from the labels 3696 prints); TEleicaoID for
# Slot3's parameter; the members' access; every line but the records' (80, 405); the "6.0" version and the 277 as
# literals; std::as_const in DivideEmBlocos, which picks CStringUtils::Trim's copying overload (fn 1374, as the target
# calls) on a string the loop assigns; md::CCargo::ETipo's std::formatter (comum::SFormatoEnum, as the other enums'), in
# cgeradorbuqrcode.cpp. md::CCargo gains the accessor GetAbrangencia (app/comum/dados/md/processoeleitoral/ccargo.h, a
# chosen name) for 3696's read of +8; api/pkcs11/ipkcs11.h is new (its header says what is chosen).
#
# Evidence, and what was measured (GetQtdAptos, Slot3, the destructors, GetCamposVotos):
# - The layouts and the destructors' forms are in the two headers. GetQtdAptos searches the map twice in the target, the
#   second time with map::at's out_of_range ("map::at:  key not found", fn 1239): a find tested against end() and then
#   at(). Its format argument is stored as type 3, an int, so the enum is cast. GetCamposAptos builds the string in the
#   result's place after GetQtdAptos returns (the target zeroes the result's 12 bytes after the inlined frame).
# - Forms that give the same function, compared by function with the object-local numbers masked: Slot3's
#   `return "";` and `return std::string("");` (`return std::string();` and `return {};` differ in 6 rows); `= default`
#   and `{}` for each class's destructor (CGeradorBUQRCode's D1 and D0, CGeradorBUQRCodeVota's D1 and D0). A test of
#   `m_qtdAptos.count(abrangencia) == 0` in place of find differs from the written GetQtdAptos in 72 rows.
# - The +400 member's type, from GetCamposVotos: the target calls the four slots through the vtable. As a reference to
#   CRdvVota, which crdvvota.h declares final, clang calls CRdvVota::Nominais and the others directly in the object
#   (tools/round/try-tu.sh --symbols, wasm-objdump -d: four `call`s); as a reference to the base CRdv the four are
#   `call_indirect`, as in the target. So the member is a `const CRdv&`, which the constructor stores
#   CRdvVota::GetInst()'s result in. GetCamposVotos matched by content when it landed.
#
# The two sources are compiled at the end of unit 93's list (src/units/93-uenux2-estadoaplicacao.mk): this fragment
# holds no source list (Slot2's bullet above says why).
# cgeradorbuqrcode.cpp includes cconfiguracaoeleicao.h, whose ecourna CConfiguracaoMunicipio holds a CHorariosUrna of
# Boost ptimes, and ecourna/api/security/csha.hpp, which includes OpenSSL's evp.h; UENUX2_CXXFLAGS has neither path
# (unit 88 gives ccargos.cpp the Boost one, unit 321 gravadores/asn/cassinavotavelbu.cpp the OpenSSL one). An include
# path is not a flag of the code (asmlift-wasm/benchmark/README.md "The compile setups").
$(ROOT)/$(APP)/uenux2/src/app/comum/relatorios/cgeradorbuqrcode.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR) $(OPENSSL_INCLUDES)
# the roots declare what they reach through __asm__ labels and include no header
$(ROOT)/$(APP)/155-uenux2-cgeradorbuqrcode-roots.o: $(ROOT)/src/units/155-uenux2-cgeradorbuqrcode-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/155-uenux2-cgeradorbuqrcode.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/155-uenux2-cgeradorbuqrcode-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/155-uenux2-cgeradorbuqrcode-roots.o
