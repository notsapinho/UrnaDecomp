# uenux2 api::CTextFieldMultiLine in src/uenux2/src/api/gui/ctextfieldmultiline.cpp, its class head in
# ctextfieldmultiline.h, with the gui headers it needs (primitives.h, itext.h, iformfield.h, eueguierror.h, cfixedtext.h,
# iscreen.h, api/pattern/cpolysingleton.h); paths relative to src/uenux2. Every member of the class's vtable is written:
#   5498  the constructor (its throw is the record 71:15); GetTypeName (10921, in the class: the header says why) and the
#         implicit D0 and D2 (10922, 10923), emitted with the vtable; Move (one of the four functions of fn 2783,
#         90-uenux2-api-gui.mk).
#   10925 Draw (slot 2) and 10924 Rect (slot 8) match. Their one call each, of GetTextLines, re-points through the hand
#         line of splat/symbol_addrs.txt for func:5497 (callers+content), whose comment says what it rests on: no
#         generated route names 5497, since Draw and Rect are named by vtable evidence, which casts no vote, and 5497's
#         body is not ours. Without the line both read unresolved (call of GetTextLines has no target function).
#         Draw advances y before SRect::Union: the target reads m_alturaLinha for the sum before that call and again at
#         the loop's test after it. With the sum after the union Draw scores 12 over 276 rows at --depth 0, before it 2
#         over 270, both operand rows (the CFixedText vtable's address).
#   5497  GetTextLines is written and differs: 153 over 950 rows (40 inserted, 12 deleted; pnpm wasm score against
#         build/out/wasm/vota_web after make -C src link-map). What differs, read from the rows: the space search's loop
#         carries linha's size byte (masked with 255) and reloads its long data pointer at each pass, where the target's
#         carries the size and the pointer computed for the previous find; and after the character search ours tests
#         tamanho < linha.size() again (a select), where the target's loop leaves to corte = tamanho - 1 with no test.
#         The other rows are local numbers. The form written is the one these measurements chose (scores at the
#         default depth, in the order they were taken, each on the form the line before it left):
#         - find(' ') where the earlier draft had find(" "), since the target calls memchr and subtracts, the char
#           overload's code, together with the width read before GetText, since the target loads m_rect.left and
#           .right before its first call: 606 over 1158 to 494 over 1064.
#         - return linhas when not even one character fits (corte == 0): the target's br_table sends that case out of
#           both loops to the function's exit. With a break (the earlier draft's), clang inlines
#           push_back(std::string&&) at -O3's hot call site threshold (try-tu.sh --symbols --flags '-Rpass=inline
#           -Rpass-missed=inline': cost 300, threshold 525); with the return its threshold is 250 and the call stays,
#           as the target's call of fn 376 does: 353 over 954. With the break, six other shapes of the inner loop kept
#           the call hot (corte declared before the loop, espaco declared at the top of its body, do-while, for(;;)
#           with the test at the end, the empty-line case without continue, the corte == 0 test first), and so did the
#           loop in a free function, which clang inlines and then weighs push_back again at the hot site.
#         - the width as m_rect.right - m_rect.left + 1: through a local esquerda read first, m_rect.right loads before
#           m_rect.left (353 over 954; 349 over 952 without the local).
#         - each prefix's width through a lambda, larguraPrefixo: the target keeps the substr temporaries' slot (which
#           the locale of getline's widen shares) at the top of its frame, above texto, where a callee clang inlined
#           puts it (docs/reference/facts/codegen.md C5); written in place it is at the bottom: 349 to 232, the operand
#           rows 275 to 159. A free function of the anonymous namespace, LarguraPrefixo(IScreen&, const std::string&,
#           size_t, const SFont&), gives a byte-identical body (the two links' disassembly compared, on the final form):
#           which of the two the source had is a choice.
#         - the character search as while (tamanho < linha.size() && larguraPrefixo(tamanho) <= largura) ++tamanho,
#           then corte = tamanho - 1 when tamanho < linha.size(): 232 to 153 over 952. On that form, a for loop with
#           corte set before a break, the same with continue, != for the last test, corte == npos in the loop's test
#           read 232, 232, 153 and 294 over 975. The whole search for the cut in a lambda or in a free function, each
#           with returns, measured on the form before the lambda, read 196 over 979 and 209 over 959.
#         - const int largura = m_rect.Width(): as an int its sign extension sits where the target's does, 153 over 950;
#           const TPosition largura = m_rect.Width() scores as the expression written out, 153 over 952. On this form,
#           the character search as a lambda returning the cut read 156 over 956, and the space search as a for loop, a
#           while with a break, the next find from corte + 1, or the lambda taking the string read 170 over 958, 153,
#           153 and 153.
#         At -O2 (this object only, a measurement on the draft with the break), push_back(std::string&&) stays a call
#         (threshold 225), but GetTextLines read 449 over 955 and std::getline's copy differed (131 over 421): the level
#         is not the cause. What gives the target's two loops is not found.
#   GetTextLines instantiates std::getline (fn 1917) in this object, which links ahead of app/asn1/AVNDecoder.o, the
#   object 1917 matched from before. At uenux2's -O3 with strict aliasing (api/ is in UENUX2_TBAA_DIRS) the copy is
#   byte-identical, so 1917 still matches, from this object now, and so do its callers 2649, 5055, 8877, 8878, 8883 and
#   8884 (splat/scan.tsv's rows unchanged): the earlier note that this instance cost seven matches no longer holds.
#   Draw's CFixedText likewise brings CFixedText's GetText (1139), D0 (7666) and D2 (7706) from this object, ahead of
#   app/uenux2/src/app/vota/operador/outrasopcoes/cinputfieldmt.cpp.o, whose copies they were; all three still match.
# Chosen, as no evidence gives them: every local and parameter name, the data members' names (ctextfieldmultiline.h),
# the lambda and its name (or the free function above), Move's place in the file, and Draw and Rect after
# GetTextLines, whose line its record fixes. Draw before Rect is the band's order (ledger/ordinals.tsv, uses 1).
UENUX2_SRCS += src/api/gui/ctextfieldmultiline.cpp
# two callers of the ctor plus two more CUeGuiError throw sites (14-uenux2-ctextfieldmultiline-roots.cpp) so binaryen
# neither inlines the ctor nor the CBaseError<EUeGuiError> ctor thunk, and drops the two constant TColor arguments as the
# target's wasm-opt did
$(ROOT)/$(APP)/14-uenux2-ctextfieldmultiline-roots.o: $(ROOT)/src/units/14-uenux2-ctextfieldmultiline-roots.cpp $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h $(ROOT)/src/ecourna/api/exception/*.hpp)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/14-uenux2-ctextfieldmultiline-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/14-uenux2-ctextfieldmultiline-roots.o
