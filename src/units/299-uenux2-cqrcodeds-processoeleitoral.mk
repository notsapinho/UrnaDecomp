# uenux2 comum::CQRCodeDS, the QR code content of the urna's state, in src/uenux2/src/app/comum/dados/cqrcodeds.{h,cpp}
# (new; paths chosen, below), and two comum processo eleitoral converters' DoDesconverte in
# src/uenux2/src/app/comum/dados/asn/processoeleitoral/: CConversorDetalheCandidato's in cconversordetalhecandidato.cpp
# (its records' file, new: the stub-only file went with unit 159) and CConversorEleicaoPE's in cconversoreleicaope.cpp
# (new, beside its header, a chosen path). The traps of both left unit 159's -pending.cpp. The callers and callees these
# need are added to their landed files and noted in those fragments: comum::CRelatorioTesteImpressora::GetConteudoQRCode
# (11200, unit 123), CEstadoGeral::GetDadosQRCode (5636, unit 215), api::CStringUtils::JuntaTags (3646, unit 196),
# CConversorCargo's constructor (unit 191), md::CEleicaoPE's constructor, ValidaNome and ValidaCargos (unit 88), and
# CConversorProcessoEleitoral::DoDesconverte (11363, unit 140), which matches with the form 11371 showed.
#
# Matched (scores are `pnpm wasm score` against the plain link before steps 7 to 9, default depth; all rows that differ
# are operand-only, the operands no call and no data address being table slots, .bss addresses and, in the converters,
# the packed format string of IConversorASN's inlined Desconverte):
# - CQRCodeDS::SetOrigem (target fn 5783, 8 over 106 rows) and operator() (5782, 68 over 1096), which holds
#   MontaConteudo and ExtraiVersao, both inlined by binaryen; CQRCodeDS's constructor, a thunk over std::vector's copy
#   constructor that binaryen inlines into its callers; and the instances this object brings:
#   std::vector<std::pair<std::string, std::string>>'s copy constructor (1300, 4 over 113), its __emplace_back_slow_path
#   from a 5-character literal and a moved string (5780, 6 over 182) or a copied one (5781, 7 over 195: VERS's const
#   temporary and DTPL's lvalue are two instances of one body), and the pair's constructor from two string literals
#   (1348, 3 over 120).
# - CConversorDetalheCandidato::DoDesconverte (11375, 78 over 1218) and the move of a std::vector<md::CCargo>'s
#   elements, std::__uninitialized_allocator_relocate (3816, 2 over 243), from cconversoreleicaope.cpp.o.
# Written, `unresolved`: CConversorEleicaoPE::DoDesconverte (11371, 84 over 1509), on the address of "impressão" at
# +0xad3 (`an address of ours: string tail occurs 4098 times`): the target's is the tail of "em caso de falha na
# impressão" (123919, ledger/strings.tsv), which only fn 7787 (not written) loads. With a scratch object that keeps that
# literal (a static constructor's store into a volatile sink, linked after this unit's roots in a copy of link.cmd; its
# bytes are in that wasm), `pnpm wasm splat-remap … --against 11371` prints `target 11371: IDENTICAL`; on the plain link
# `UNRESOLVED (1)` on that operand (docs/how-to-decompile.md step 5, "A written body that does not match yet"). It waits
# for that literal, a prediction. "aquisição", the other tail, is "Já foi marcado o fim da aquisição"'s, which
# cestadogeralvota.cpp holds.
#
# Evidence and choices, CQRCodeDS (cqrcodeds.h has the class's):
# - Where. No record names a function of the class. In use band 2 (ledger/ordinals.tsv) 5783 to 5780 link after
#   cconfiguracaoeleicao.cpp.o's functions (5784 to 5792) and before carregaprocessoeleitoral.cpp.o's (5777), both in
#   app/comum/dados/, so the class goes there (how-to step 3, rule 2), in its own lower-case file (rule 4). In our link
#   SetOrigem's ld_index (5337) is below operator()'s (5338) and 5781's below 5780's, the order the band asks
#   (build/out/wasm-map/vota_web/names.tsv). ExtraiVersao's line, before the constructor, is a choice.
# - SetOrigem builds each pair in its frame and calls push_back(&&) (fn 625); "T" for 0, "I" for 1. Measured on a TU
#   that holds SetOrigem alone, object code: `{"ORIG", "T"}` and `std::make_pair("ORIG", "T")` call the pair's
#   constructor out of line, where the target stores the strings in place; `{"ORIG", std::string("T")}` stores them in
#   place in another order (store16 at +19 last; in the whole link 18 over 112 rows, 6 inserted, 6 deleted);
#   `std::make_pair("ORIG", std::string("T"))`, `{"ORIG", std::string(1, 'T')}` and `{"ORIG", "T"s}` store the second
#   string with an i64; `std::make_pair(std::string("ORIG"), std::string("T"))`, written, and `{std::string("ORIG"),
#   std::string("T")}` give the target's order and the same SetOrigem in the whole TU (its disassembly compared with
#   call indices masked).
# - operator()'s target body runs CConfiguracaoEleicao::GetInst() and the add of the pleito's offset (+28) before its
#   only stack-pointer prologue: a frameless function whose callee binaryen inlined (how-to step 3). So operator()
#   passes the pleito to MontaConteudo, a separate function, out of line in this TU (clang keeps the call: the object's
#   disassembly). MontaConteudo copies m_tags (the copy inlined), then emplace_backs VERS, DTAG, HRAG, DTPL and HRVR on
#   the copy and calls JuntaTags (3646). Its locals' order follows the frame (agora at +68, the formatted date of the
#   pleito at +56, the copy at +40). VERS's value is copied into the pair from a temporary destroyed right after:
#   ExtraiVersao returns a const std::string. The HRVR flag is read before the copy (the CHV::GetInst() call precedes
#   the copy's allocation) and the select tests the loaded byte where it is used: a reference to the ternary's array,
#   `const auto&`, gives that (68 over 1096); a bool local adds `& 1` before the select (70 over 1098, 2 inserted); a
#   `const char* const` local stores the pointer in the frame (object code), where the target passes the array's address
#   to fn 1348.
# - ExtraiVersao's target code sits behind a second prologue (176 bytes) inside 5782: a function with one caller that
#   binaryen inlined, with external linkage (clang keeps the call in this TU: the object). It builds a std::regex of
#   "[0-9]+.[0-9]+.[0-9]+.[0-9]+", a std::sregex_iterator over the string (the frame holds begin, end and the regex's
#   address at +8, +12, +16, the iterator's layout) and returns the first match's str().c_str() as a string (the strlen
#   call), else "0.0.0.0". Measured in the whole link: std::smatch with std::regex_search, 231 over 1137 rows (41
#   inserted, 43 deleted, with the bool HRVR local); the iterator over api::CApplication::s_versao read in the function,
#   135 over 1108 (12, 15): the target loads s_versao's three words right after the regex's parse and before the
#   iterator's zero stores, ours at their uses; the string as a parameter, the form written, 70 over 1098 (2, 0, the
#   bool local's `& 1`). Our reading: the loads through an argument cannot pass stores to the iterator, which escapes.
#   With strict aliasing on the TU the helper's loads and stores keep their order (object compared).
# - Chosen: the file and its directory's choice (above), every name but CQRCodeDS's and operator()'s, ExtraiVersao's
#   being a free function of comum (it reads no class state) and its parameter, MontaConteudo's being a private member
#   taking the pleito, the locals' names.
#
# Evidence and choices, the converters:
# - CConversorDetalheCandidato::DoDesconverte: the three throws on their records' lines (29, 34, 39, column 15, so each
#   directly inside a top-level if), with ModuloEleicao::DetalheCargo's fields; a local CConversorNomesCargo (its
#   Desconverte out of line, fn 5688) and, per substitute, a CConversorSuplencia built in the loop (its vptr stored
#   there) whose Desconverte binaryen inlines. The result is a named local emplaced by copy (construct_at<CSuplencia,
#   CSuplencia&>, fn 2341, on the slow path). The compare of the third check is `quantidade != size()`: the other order
#   gave 80 over 1219 (1 inserted, 1 deleted). md::CDetalheCandidato gets a constructor for it (cdetalhecandidato.h).
# - CConversorEleicaoPE::DoDesconverte: md::CEleicaoPE's constructor sits behind a second prologue (16 bytes), with
#   ValidaNome inlined and ValidaCargos behind a third (96 bytes): both out of line in celeicaope.cpp, on their records'
#   lines (63; 79, 87, 92). The cargos are converted by a CConversorCargo on the frame. Measured in the whole link (each
#   with the rest as written): range-for loops over the cargos and the municipios, 549 over 1590 (81 inserted, 80
#   deleted: our frame holds the converter and the vector above the Desconverte result, the target below it);
#   std::transform with std::back_inserter and a lambda for both, 149 over 1516 (7, 7): an inlined callee's locals come
#   above the caller's (how-to step 3), so the result is the lambda's; the vector declared before the converter, 91 over
#   1512 (3, 3); CConversorCargo's constructor out of line in cconversorcargo.cpp (unit 191), 84 over 1509, all
#   operand-only: the target reloads the entity's fields pointer after the converter is built, which a call there forces
#   (our reading: binaryen inlined that call). The optional idEleicaoPleito2 read as a ternary gives the same wasm as
#   the if (sha256 compared). The form of ValidaNome's test (empty or longer than 38) and the three ValidaOrdem calls'
#   order follow the target's code. Without the roots' stand-in for fn 3818, 3816 has one caller and binaryen inlines
#   it: 742 over 1806 (297 inserted, 55 deleted, with the range-for loops).
# - Chosen: cconversoreleicaope.cpp's path, both functions' lines but the records', the lambdas, the locals' names, and
#   the constructors' parameters and their being inline (CDetalheCandidato's) or not (CEleicaoPE's, CConversorCargo's,
#   as the inlining above shows).
#
# Roots (299-uenux2-cqrcodeds-processoeleitoral-roots.cpp): stand-ins for target callers not in our link, each going
# when they are: QRCodeTela for fn 3059 (the constructor, so 1300 keeps two call sites, and SetOrigem); ConteudoQRCode
# for fn 12553 (operator()); ParDeTextos for fn 4625 (1348: with HRVR's calls alone binaryen folds the constant first
# argument into the body, `(i32 i32)->(i32)`, 41 over 124 rows, 4 inserted, 4 deleted); CargosRealocados for fn 3818
# (3816). The census pairs no target function with a stand-in (step 7's check). Stand-ins of other units that my rows
# end went (fragments 88, 107, 124 and 232 say which).
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CQRCODEDS_SRCS := src/app/comum/dados/cqrcodeds.cpp
CONVERSORES299_SRCS := src/app/comum/dados/asn/processoeleitoral/cconversordetalhecandidato.cpp \
                       src/app/comum/dados/asn/processoeleitoral/cconversoreleicaope.cpp
UENUX2_SRCS += $(CQRCODEDS_SRCS) $(CONVERSORES299_SRCS)
# cconfiguracaoeleicao.h reaches ecourna's chorariosurna.hpp, which includes Boost (units 88 and 123 add the path the
# same way)
$(addprefix $(ROOT)/$(APP)/uenux2/,$(addsuffix .o,$(CQRCODEDS_SRCS))): UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# the roots declare what they call through asm labels, so their rule needs no header
$(ROOT)/$(APP)/299-uenux2-cqrcodeds-processoeleitoral-roots.o: $(ROOT)/src/units/299-uenux2-cqrcodeds-processoeleitoral-roots.cpp $(ROOT)/src/Makefile \
    $(ROOT)/src/units/299-uenux2-cqrcodeds-processoeleitoral.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/299-uenux2-cqrcodeds-processoeleitoral-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/299-uenux2-cqrcodeds-processoeleitoral-roots.o
