# uenux2 comum's comparecimentomesario leftovers, in app/comum/comparecimentomesario/, paths relative to src/uenux2.
# Target fns matched:
# - comum::CImprimirIdentificacaoMesariosFinal::GetNomeMesario (5385) in estados/cimprimiridentificacaomesariosfinal.cpp,
#   its record's file (229:84, the ASSERT's), with the code 3409 in api/util/eueasserterror.h; the class head is in
#   cimprimiridentificacaomesariosfinal.h, the file of the record of GetPrinter (line 41, which fn 12105 holds inlined,
#   not written).
# - comum::ListaArquivosNaoRegistrados (5374) in ccontroladorreconhecimetomesario.cpp, and the libc++ code of its
#   std::sort: std::__introsort (5373), __insertion_sort_incomplete (5370) and __sort4 (2726) over
#   std::filesystem::path*, and the comparator (310). 5374 also brings into the link more of libc++.a's
#   directory_iterator.o, and ten of its functions match with it (703, 845, 3370, 4784, 4790, 4792, 4794, 5968, 8078,
#   8080): library code, which no source of ours writes.
# - comum::CControladorReconhecimentoMesario::GetInst (1149), in the same file, with its constructor inlined and its
#   statics' exit destructors (10306, 10305), the class head in ccontroladorreconhecimetomesario.h, which says what the
#   layout and the name rest on.
#
# Evidence:
# - 5385: the record's text names a member and has neither `static` nor `const`; the wasm type has no `this`, which
#   binaryen's dead-argument elimination drops as the body never reads it (here too). The body calls CEleitores::GetInst
#   (fn 326) and LocalizaEleitor (fn 2264) with the type 1 (TipoIDInscricaoEleitoral), and throws api::CUeAssertError
#   with the code 3409 and the text "Assert (mesario)", so the macro's argument is spelled `mesario`; then it copies at
#   most 40 characters of the voter's string at +36 (GetNomeUrna) when that is not empty, else of the one at +24
#   (GetNome), each in a copy path of its own, so each path has its own substr call.
# - 5374: it takes the directory from fn 3793 (unit 122's GetPathWsqNaoRegistrado, pathwsq.h), iterates it with
#   std::filesystem::directory_iterator (fn 3373, libc++'s constructor with no error_code and no options, and fn 3372,
#   __increment), skips the entries whose file_type is 2 (directory) and moves each other entry's path().filename() into
#   a vector of 12-byte elements that its callers (fns 1149, 10451) destroy as strings: a
#   std::vector<std::filesystem::path>, built in the result. Then it calls __introsort(first, last, 2 * log2(n), true).
#   The comparator copies both arguments' strings and returns whether the first copy compares greater than the second:
#   a.string() > b.string() over two const paths. The frame says where the loop is: the directory at +12 and the
#   iterator at +4, below the loop's iterator copy (+24) and the entry's temporaries (+32 to +63), so the loop's locals
#   are an inlined callee's above the function's own (how-to step 3); the iterator's reference count is raised once and
#   one more copy is made and destroyed, which reads as a range's begin and end (a reading). Measured in the whole link
#   (pnpm wasm score, 5374 against ours): a range-for over the iterator, 102 over 505 rows (26 inserted, 12 deleted: the
#   loop's locals below the function's); std::for_each over begin and end of a named iterator, 126 over 523 (the frame
#   the target's, a reference copy more); a helper taking the iterator by value, 209 over 519; std::ranges::for_each
#   over the iterator and a lambda, 14 over 479, all operand-only, then a match at step 9 (scan source `content`). The
#   comparator's lambda is the function's second now, $_1 for $_0: steps 8 and 9 renamed the names and match lines of
#   310, 2726, 5370 and 5373.
# - 1149: CControladorReconhecimentoMesario::GetInst (ccontroladorreconhecimetomesario.h has the evidence). Its
#   constructor is out of line, as unit 104's singletons' (the frame opens after the new: binaryen inlined it); in the
#   class it is not tried. 11 over 114 rows before steps 8 and 9, all operand-only (the statics' addresses). No
#   generated route names 1149 or its statics: it has no record or vptr, the census pairs it with nothing (tier none),
#   and its one written caller, 10337 (unit 135), is named by vtable, which casts no vote. Its two statics take hand
#   lines in splat/symbol_addrs.txt, led by their other reader, each one's exit destructor (10306 `f349(p0, 1909960)`,
#   10305 `f150(1909936)`); with them the content pass matches 1149, 10306 and 10305. Weighed by removal (a copy of the
#   symbol file without the line, the match list without the rows it may carry, two scan passes beside a control, then
#   splat-build on the copies): the pointer's line carries 1149 and 10306, the mutex's 1149 and 10305.
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
# Chosen: ListaArquivosNaoRegistrados and its being a free function (it takes no object; a static member of
# CControladorReconhecimentoMesario would fit as well) declared in the class's header; its file, by its band's
# neighbours (cluster 748 of src/uenux2/unplaced.cpp names ccontroladorreconhecimetomesario.cpp, from ComparaDigitais's
# records); the comparator and the loop's body as lambdas, `.string()` for the comparator's copies, the lambda's capture
# and its `if` over is_directory(); GetInst's name and the statics' (the project's singleton), the constructor's member
# list; the class head's access (CImprimirIdentificacaoMesariosFinal's) and that it declares nothing else; the
# enumerator's name, to the record's column; the lines of 5374, the constructor and GetInst (above ComparaDigitais's
# records at lines 65 and 76) and of GetNomeMesario's first lines; every local's name; the if and the second return
# around GetNomeMesario's two substr calls, where one ternary over them was not compiled. Not chosen: the statics are
# defined below GetInst, which names s_mutex first, so the object puts the mutex 24 bytes below the pointer, the
# target's .bss order (@1909936 and @1909960); defined above the constructor, the pointer came first (no scan row moves
# either way, measured on the whole link). No other spelling was measured, so no form here is listed as giving the same
# bytes.
#
# Not written, and what each waits for:
# - CControladorReconhecimentoMesario::ComparaDigitais (5372, records 65 and 76): not tried; its callers are fns 3614
#   and 10451, which pass it 1149's result.
# - 5376, a hinted emplace into a std::map of a string key and a 68-byte value: its one caller, fn 10451, calls it twice
#   and holds the instance's only use.
#
# The generic uenux2 rule depends on the source and every uenux2 header.
COMPARECIMENTOMESARIO_SRCS := src/app/comum/comparecimentomesario/estados/cimprimiridentificacaomesariosfinal.cpp \
    src/app/comum/comparecimentomesario/ccontroladorreconhecimetomesario.cpp
UENUX2_SRCS += $(COMPARECIMENTOMESARIO_SRCS)
# the functions' callers not reconstructed (fns 3614, 5382, 10316, 10451 and 12105):
# 214-uenux2-app-comum-comparecimentomesario-roots.cpp stands for them
$(ROOT)/$(APP)/214-uenux2-app-comum-comparecimentomesario-roots.o: $(ROOT)/src/units/214-uenux2-app-comum-comparecimentomesario-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/214-uenux2-app-comum-comparecimentomesario.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/214-uenux2-app-comum-comparecimentomesario-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/214-uenux2-app-comum-comparecimentomesario-roots.o
