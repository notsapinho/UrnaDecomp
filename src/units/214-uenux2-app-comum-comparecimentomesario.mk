# uenux2 comum's comparecimentomesario leftovers, in app/comum/comparecimentomesario/, paths relative to src/uenux2.
# Target fns matched:
# - comum::CImprimirIdentificacaoMesariosFinal::GetNomeMesario (5385) in estados/cimprimiridentificacaomesariosfinal.cpp,
#   its record's file (229:84, the ASSERT's), with the code 3409 in api/util/eueasserterror.h; the class head is in
#   cimprimiridentificacaomesariosfinal.h, the file of the record of GetPrinter (line 41, which fn 12105 holds inlined,
#   not written).
# - the libc++ code of the std::sort in comum::ListaArquivosNaoRegistrados (5374, written, not matching: below), in
#   ccontroladorreconhecimetomesario.cpp: std::__introsort (5373), __insertion_sort_incomplete (5370) and __sort4 (2726)
#   over std::filesystem::path*, and the comparator (310). 5374 also brings into the link more of libc++.a's
#   directory_iterator.o, and ten of its functions match with it (703, 845, 3370, 4784, 4790, 4792, 4794, 5968, 8078,
#   8080): library code, which no source of ours writes.
#
# Evidence:
# - 5385: the record's text names a member and has neither `static` nor `const`; the wasm type has no `this`, which
#   binaryen's dead-argument elimination drops as the body never reads it (here too). The body calls CEleitores::GetInst
#   (fn 326) and LocalizaEleitor (fn 2264) with the type 1 (TipoIDInscricaoEleitoral), and throws api::CUeAssertError
#   with the code 3409 and the text "Assert (mesario)", so the macro's argument is spelled `mesario`; then it copies at
#   most 40 characters of the voter's string at +36 (GetNomeUrna) when that is not empty, else of the one at +24
#   (GetNome), each in a copy path of its own, so each path has its own substr call.
# - 5374: it takes the directory from fn 3793 (unit 122's GetPathWsqNaoRegistrado, pathwsq.h), iterates it with
#   std::filesystem::directory_iterator (fn 3373, libc++'s constructor with no error_code and no options), skips the
#   entries whose file_type is 2 (directory) and moves each other entry's path().filename() into a vector of 12-byte
#   elements that its callers (fns 1149, 10451) destroy as strings: a std::vector<std::filesystem::path>, built in the
#   result. Then it calls __introsort(first, last, 2 * log2(n), true). The comparator copies both arguments' strings and
#   returns whether the first copy compares greater than the second: a.string() > b.string() over two const paths.
# - Order: inside the use band of 5370, 5373 and 5374 (ledger/ordinals.tsv) and the object, a higher index has the lower
#   ld_index in build/out/wasm-map/vota_web/names.tsv (5374, 5373, 5370), as docs/how-to-decompile.md step 3 wants. 5385,
#   in the same band, comes before 5374 in the target, so its source is listed first here, a choice the data allow.
#
# Measured, with pnpm wasm score against the target in the plain link, then the scan:
# - 310, 2726, 5370 and 5373 scored 4 over 144, 7 over 252, 17 over 651 and 95 over 3582 rows, all operand-only: the
#   callee of a call, and in 5373 one constant the score reads as a data address at the same offset on both sides.
#   They match.
# - 5385, as written, scored 11 over 182 rows, all operand-only: six callees, four constants read as data addresses (the
#   code 3409 at the same offset on both sides, the message, the record, the typeinfo) and the table slot of the
#   destructor __cxa_throw takes. It matches.
#
# Written, not matching: 5374, 102 over 505 rows (pnpm wasm score against the target, before step 8), 403 over 753
# before 5821 was written. Its callees 3373 and 3372 (libc++'s directory_iterator constructor and __increment) have one
# other direct caller in the target, fn 11584 (comum::CGravadorLog's slot 7, not written), and fn 5821 (unit 122's
# CompactaWsq) passes both by table slot to invoke_ thunks: with 5821 in the link both stay out of line here
# (names.tsv holds them, from libc++.a's directory_iterator.o), and neither has a target name yet, so 5374 calls two
# unnamed functions. Measured before 5821 was written, with a stand-in for 11584's two calls and both addresses taken,
# not kept: 115 over 516 rows (inserted 37, deleted 13). Fn 3793, its first callee, matches as the target's thunk
# (unit 122's fragment). The rest of the remainder is not explained.
#
# Chosen: ListaArquivosNaoRegistrados and its being a free function (it takes no object; a static member of
# CControladorReconhecimentoMesario would fit as well); its file, by its band's
# neighbours (cluster 748 of src/uenux2/unplaced.cpp names ccontroladorreconhecimetomesario.cpp, from ComparaDigitais's
# records); the comparator as a lambda and `.string()` for its copies; `continue` over is_directory() and push_back; the
# class head's access and that it declares nothing else; the enumerator's name, to the record's column; the lines of
# 5374 (above ComparaDigitais's records at lines 65 and 76) and of GetNomeMesario's first lines; every local's name;
# the if and the second return around GetNomeMesario's two substr calls, where one ternary over them was not compiled.
# No other spelling was measured, so no form here is listed as giving the same bytes.
#
# Not written, and what each waits for:
# - CControladorReconhecimentoMesario::ComparaDigitais (5372, records 65 and 76): not tried; its callers are fns 3614
#   and 10451.
# - 5376, a hinted emplace into a std::map of a string key and a 68-byte value: its one caller, fn 10451, calls it twice
#   and holds the instance's only use.
#
# The generic uenux2 rule depends on the source and every uenux2 header.
COMPARECIMENTOMESARIO_SRCS := src/app/comum/comparecimentomesario/estados/cimprimiridentificacaomesariosfinal.cpp \
    src/app/comum/comparecimentomesario/ccontroladorreconhecimetomesario.cpp
UENUX2_SRCS += $(COMPARECIMENTOMESARIO_SRCS)
# the functions' callers (fns 1149, 10451 and 12105) are not reconstructed:
# 214-uenux2-app-comum-comparecimentomesario-roots.cpp stands for them
$(ROOT)/$(APP)/214-uenux2-app-comum-comparecimentomesario-roots.o: $(ROOT)/src/units/214-uenux2-app-comum-comparecimentomesario-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/214-uenux2-app-comum-comparecimentomesario.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/214-uenux2-app-comum-comparecimentomesario-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/214-uenux2-app-comum-comparecimentomesario-roots.o
