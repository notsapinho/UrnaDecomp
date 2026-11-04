# uenux2 the state report's printing chain: comum::CImprimirExtratoCarga::Imprime (target fn 5591, in unit 123's
# app/comum/relatorios/cimprimirextratocarga.cpp) and its caller vota::CImpressaoEstadoUrna::StartState (11911, unit
# 176's auxiliares/cimpressaoestadourna.cpp); comum::CGeradorRelVersaoPacoteDados::ImprimeRodape (5596, unit 287's
# cgeradorrelversaopacotedados.cpp); the reports' helpers in app/comum/relatorios/auxiliaresrelatorio.{h,cpp} (1156,
# 2252, 2792 and three functions 5591 holds inlined); api::CQRCodeImagePaper's constructor (2772) and MontaImagem in
# api/gui/cqrcodeimagepaper.cpp, with api::CStringUtils::SetBit's two overloads in unit 196's api/util/cstringutils.cpp;
# comum::CDataSourcesRelatorio<CRdvVota, CEleitores>::LinhaPartido (11261) in unit 183's cdatasourcesrelatorio.h;
# comum::asn::CConversorLocal::DoDesconverte (11452) in unit 157's asn/cconversorlocal.cpp and comum::CAppInfo::
# LeGeralInterno (2273) in unit 109's appinfo/cappinfo.cpp, the two of CLocal's loader (5740, matched since in unit
# 89's clocal.cpp, which calls both) that landed before it. Paths relative to src/uenux2. This fragment compiles the two new files; the others extend their units,
# whose fragments point here, and this unit's roots keep its stand-ins.
#
# Matched: 1156, 2252, 2273, 2792, 5591 and 11261 (the scan's content pass, then their match names them), 5596 and 11911
# (vtable) and 11452 (srcloc-anchor, record cconversorlocal.cpp:70). Scores before steps 7 to 9 (pnpm wasm score against
# this link's names.tsv), all operand-only: 1156 3 over 56 rows, 2252 31 over 1130, 2792 7 over 248, 5596 37 over 356,
# 11911 22 over 243, 5591 262 over 3779, 11261 23 over 320, 11452 39 over 721, 2273 2 over 18. 11261 (LinhaPartido) is
# written for its literal as much as for itself: its one user, fn 12110 (vota::CGeraBU's slot 2, not written), passes
# its address (table slot 2921), and the target holds 5591's "{}\n" as the tail of 11261's "{}: {} - {}\n" (@445555).
# While that literal was not in the link, 5591 stayed `no-candidate` (splat-remap: `+1559 i32.const 370742: an address
# of ours: string tail occurs 4098 times`) and 11911 `unresolved` on 5591's name.
#
# Written, not matched:
# - 2772, the constructor, `differs` in local numbers alone: 97 over 696 rows, 7 inserted and 7 deleted, every one a
#   local.get/set/tee whose index the target and ours swap (the frame pointers' and, at the copy of the result's vector,
#   the size's and the new block's). Not explained. Measured on whole links with one object swapped
#   (docs/reference/facts/workflow.md W13) and on this link: the constructor above or below MontaImagem in the .cpp,
#   `return {imagem, ...}` against a named QrcodeData, the bit's index in one expression, and the copy as
#   `std::vector<uebyte>(imagem.begin(), imagem.end())` each give the same module (shasum -a 256 of the wasm);
#   cqrcodeimagepaper.cpp.o linked before cstringutils.cpp.o (docs/reference/facts/codegen.md C4) gives the same score.
#   Its name holds by its records (srcloc-anchor), so 5591's two calls re-point.
#
# What the bytes decide (the same score, measured on the whole link unless said):
# - 5591 calls the slots of cimprimirextratocarga.h through the vtable at +36 (slot 9) and so on, in the order of that
#   header's names; the correspondencia (slot 9) and the location's lines (slot 15) are copied first and destroyed last,
#   then the builder, then the pleito's date, a named local the target frees after Show. The additional QR codes' loop
#   reloads the vector's end at each turn: an iterator loop against .end(); a range-for keeps the end in a local, 3 rows
#   inserted and 3 deleted. "Ver: {}" formats the version literal itself (packed argument type 13, a string, 27 bytes).
# - 5591 holds three functions behind frames of their own, the shape binaryen gives a function of another TU with one
#   caller (docs/reference/facts/reading.md R10): the "ASSINATURAS" block and the two dates of the daylight-saving
#   period, each CDate::Format("DD/MM/YYYY") of +0 and +8 of the CHorarioVerao. Two functions, since one called twice
#   would keep its index. They are ImprimeAssinaturas, FormataInicioHorarioVerao and FormataFimHorarioVerao in
#   auxiliaresrelatorio.cpp (that they are in another TU is the reading; their file and names are chosen).
# - 11911 is 11905's shape (unit 176): the report's constructor (5586), the log member LogaImprimindoRelatorioEstadoUrna
#   (5880), 5591 with "estado da urna" and "{}ª via" over the byte at +73 of GetVota()'s copies, which it then
#   increments (cnumviasimpressasrelatorios.h's IncrementaNumViasEstadoUrna, a name chosen), 491 and CMaisInformacoes.
# - 5596 prints the separator (1156) twice around the load's code (2252, over CAppInfo::GetGeral's correspondencia),
#   then "Ver: {}" over api::CStringUtils::GetVersionNumber (1539) of the version literal. It is defined above Imprime:
#   in use band 2 of ledger/ordinals.tsv 5596 is above 5592, so its ld_index must be lower. Since unit 183's
#   comum::CGeradorRelPU::ImprimeRodape, the same text, links (cgeradorrelpu.cpp sorts first), binaryen keeps that
#   copy for both, and 5596's match line names it (a rename, splat-match).
# - 2772 returns its first parameter (a constructor's this) and zeroes the vector at +0 first. MontaImagem's records,
#   35:15 ("Criação de QRCode com texto vazio.", code 4949) and 49:15 (the width test, code 4951, both unsigned), fix
#   their lines; the record's text shows neither `static` nor `const`: declared static, check_srcloc.py --strict listed
#   the three records as MOVED and the scan read `an address of ours: source_location not in the target`. The record at
#   38:15 no function loads: a test of the width every caller passes (400), folded with it (reading.md R1); its test,
#   its message, "Criação de QRCode com largura 0." (the one literal of that sense no target piece loads, `/usr/bin/grep
#   -rlE 'i32\.const 377469($|[^0-9])' build/out/splat/pieces/asm` prints nothing) and its code (4950, between the two)
#   are chosen. The image is built with `imagem.resize(n)` on an empty vector: the object fills the block, then stores
#   the end of storage, the end and the begin, as the target does; `std::vector<uebyte> imagem(n, 0)`, `imagem(n)` and
#   `assign(n, 0)` store the begin before the fill (wasm-objdump -d of each variant's object, as for the next two
#   points). The scale is a local uebyte computed after the width test: the division then sits there and the min at the
#   store, and the result's scale is stored before its size, as in the target; computed at the return, the size is
#   stored first. The constructor assigns the three members one by one: `m_dados = dados` copies the byte before the
#   size (the implicit copy assignment copies the two scalars as one block), the target the size first; AddQRCode's copy
#   (2775, unit 53's constructor) is that block's order, so QrcodeData stays a struct.
# - SetBit (api/util/cstringutils.cpp, records 71:15 and 83:15): the vector overload throws 7027 with "Bit fora dos
#   limites ({}) do vetor ({})" (2772 loads that record) and calls the byte overload, which binaryen inlines (a frame of
#   480 bytes nothing reads). The byte overload's test of the bit is folded (the vector overload passes bit % 8): its
#   message, "Bit fora dos limites ({})" (@378829, which no target piece loads), and its code 7026 are chosen.
# - 11452 copies the location's id, country and state strings, then converts the municipality and its complement with
#   converter objects on the stack (vptrs @1569680, @1569480, stored before each call), then reads the municipality's
#   comBiometria from the entity itself (its isPresent, then the field), builds the CInfoMunicipio without the
#   daylight-saving period and, when the complement has one, assigns the one with it; then switches on the id CHOICE:
#   the section (its converter, vptr @1561712) or the contingency urn (CIdentificacaoUrnaContingencia's constructor, fn
#   5888, whose urn type 50 binaryen folded), each building the md::CLocal in place through its constructor, which
#   binaryen inlines (md/clocal.cpp, unit 89: the two constructors have no index of their own); the default throws 7887
#   at its record's line, 70:15, with the target's literal ("CHOICE de id inválida."). The order of the statements is
#   the target's; the names of the locals and where the function begins are chosen.
# - 2273 is `CServicoEstadoGeral(FLASH_INTERNA).Carrega()` (fns 1941 and 3791). Its target callers call
#   CAppInfo::GetInst() first (1543 discards that result right before the call): a member whose unused this binaryen
#   dropped, a reading (docs/how-to-decompile.md step 3's member rule names such a caller-passed object).
# - 11261 formats the party's number as an int (packed types 13421: a string, an int, a string); a ueword local gives
#   13517 (unsigned).
#
# Chosen, no evidence names them: Imprime's name, parameters and const, and its being a member (a free function over a
# const CImprimirExtratoCarga& gives the same bytes: it reads only the object's vptr); the names, the file and the
# free-function form
# of auxiliaresrelatorio.cpp's six functions (the directory by the use bands: 2792 in band 4 links right before
# ccabecalhoqrcodebuilder.cpp's 2791 and after md/rdv/cvotos.cpp's 2794, 2252 in band 5 between cdadocarga.cpp's 2253
# and cgeradorbuqrcode.cpp's 2251, 1156 in band 11 between ccargo.cpp's 1157 and isystemdatetime.cpp's 1155, a reading;
# the file's name sorts ahead of every app/comum/relatorios/ file but unit 287's adicionaparametro.cpp, itself a
# chosen name); CQRCodeImagePaper's constructor's parameter, its GetDados and
# m_dados, MontaImagem's being private; LinhaPartido's name and its place in the class (its instance,
# CDataSourcesRelatorio<CRdvVota, CEleitores>, is the evidence's: all six records of cdatasourcesrelatorio.h name it,
# 11261 calls CRdvVota::GetInst, fn 555, and band 1 runs 11259, 11260 and 11261, 11260 being that instance's recorded
# TrailerProporcionalPartido); CPleito::GetNome (the string at
# +4, which 5591 prints); the enumerators' names (api/gui/eueguierror.h, api/util/eueutilerror.h).
#
# Roots: 296-uenux2-relatorios-impressao-roots.cpp stands for 5591's caller 11869 (11911 is in the link) and for 2792's
# callers 3059 and 7787 (5591 and 1541 are in the link), and for 2273's caller 12110 (1543, 5740, 11902 and, since
# fragment 317, 11223 are in the link). 11261's
# address is taken in unit 183's roots, beside the other text sources'. Unit 204's roots, which stood for 2772's call of
# api::CQRCodeGuard's constructor, went.
RELATORIOS_IMPRESSAO_SRCS := src/app/comum/relatorios/auxiliaresrelatorio.cpp src/api/gui/cqrcodeimagepaper.cpp
UENUX2_SRCS += $(RELATORIOS_IMPRESSAO_SRCS)
# cqrcodeimagepaper.cpp includes api/gui/cqrcodeguard.h, which includes libqrencode's qrencode.h, and UENUX2_CXXFLAGS
# has no path to it. An include path is not a flag of the code (asmlift-wasm/benchmark/README.md "The compile setups").
$(ROOT)/$(APP)/uenux2/src/api/gui/cqrcodeimagepaper.cpp.o: UENUX2_CXXFLAGS += -Ithird_party/libqrencode
# nothing in the skeleton gives some of these functions their target's call sites: the roots stand for those callers,
# through asm labels, so the rule needs no header
$(ROOT)/$(APP)/296-uenux2-relatorios-impressao-roots.o: $(ROOT)/src/units/296-uenux2-relatorios-impressao-roots.cpp \
    $(ROOT)/src/Makefile $(ROOT)/src/units/296-uenux2-relatorios-impressao.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/296-uenux2-relatorios-impressao-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/296-uenux2-relatorios-impressao-roots.o
