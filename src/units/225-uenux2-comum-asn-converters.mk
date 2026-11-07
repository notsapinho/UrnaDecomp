# uenux2 comum asn converters, continued:
# - comum::asn::CConversorDetalheConsulta::DoDesconverte (target fn 11377), in
#   src/app/comum/dados/asn/processoeleitoral/cconversordetalheconsulta.cpp beside its head (unit 159's, whose path is
#   chosen there), over FormataPergunta and the constructors of md::CDetalheConsulta and md::CRespostaConsulta in
#   md/processoeleitoral/cdetalheconsulta.cpp and crespostaconsulta.cpp, the files their records name (lines 29 and 32
#   of each, column 15). binaryen inlines all three: each opens a frame of its own inside 11377 (48, 32 and 32 bytes).
# - comum::asn::CVisitanteEleitor (src/app/comum/dados/asn/eleitor/cvisitanteeleitor.{h,cpp}, the path visit's record
#   names, line 91): its destructor out of line (D2 5698, D0 11408), visit (11407), and the two members of its
#   std::map<md::CEleitorIdentidade, md::CIndexer> the bodies call, destroy (2806, which calls itself) and
#   __emplace_unique_key_args (3728), from this object, whose copies the link keeps. Its constructor, out of line in
#   the same file, has no target function: fn 11523 (unit 310's chain, through carregaarquivo.cpp) holds it, and
#   src/units/310-uenux2-cconversorentidadeeleitores.mk has its evidence.
# - std::vector<md::CEleitor>::__swap_out_circular_buffer (5700), which this fragment's roots instantiated; its copy is
#   now that of fragment 310's cconversorentidadeeleitores.cpp, whose 11411, its one target caller, calls it twice.
#
# Evidence. 11377: the records (the four throws, codes 8146, 8147, 8167 and 8168 with their messages); the frames
# binaryen opened; the module's DetalhePergunta and RespostaPergunta (fields 0 to 3, the optional textoFonetico, read
# as `isPresent() ? get : GeneralString("")`, cconversorvoto.cpp's form); Split (1880) on '|', the copying Trim (1374) on
# each part and the parts joined by `+ '|' +`, then moved into the result (read as std::accumulate's by-value init).
# The visitor: RTTI and the vtable, the two paths visit compares (its constants spell them), the CHOICE of
# ModuloTiposEleitorais::IdentificadorEleitor read by selection, CEleitorIdentidade's constructor (566) with the types 1,
# 2 and 3, and the message 7905 at 91:11. The header gives the layout's evidence.
#
# Measured:
# - The answers' loop, in the object (try-tu.sh --symbols, wasm-objdump -d), against the target's order (the answer's
#   field, then the GeneralString built at frame +72, then the number, the CRespostaConsulta at +44): a range-for with
#   the GeneralString a temporary of the constructor's call reads the number first and puts the two at +8 and +28;
#   std::transform with a lambda that names the GeneralString gives +72 and +44 but reads the answer's field after it;
#   the same lambda with the GeneralString a temporary reads the number first; a range-for, a named lambda called in a
#   range-for, and a static helper, each naming a reference to the answer and then the GeneralString, give the order
#   with the CRespostaConsulta at +4. The form written, std::transform into a back_inserter with a lambda that names the
#   reference and then the GeneralString, gives both.
# - The order of 11377 and FormataPergunta in the file: helper first, 221 over 1206 rows in the whole link (pnpm wasm
#   score; 11 inserted, 11 deleted, with every local masked only operands differ); DoDesconverte first, 73 over 1195,
#   operand-only, and it matches. The md objects ahead of the converter in this list or after it: 221 over 1206 both ways (helper
#   first). A file-static FormataPergunta is inlined by clang (no function of its own in the object), where the target
#   holds it as binaryen's inlining; so it is external.
# - CRespostaConsulta's first check reads the parameter: the member gives a reload of +0 after the strings' copies (250
#   over 1210 rows, helper first, against 221 over 1206).
# - visit: a std::pair of size_t at +8 and as the map's value stores two i32 where the target stores one i64 (51 over 594
#   rows, 12 inserted); md::CIndexer with the constructor cindexer.h adds, 26 over 582, operand-only, and it matches.
# - 5700: at the flags of 11411's directory (asn/eleitor, with -fno-strict-aliasing) the instance is the target's;
#   without it (md/'s flags) one load of the vector moves (measured on the roots' object, wasm-objdump -d, indices
#   masked).
#
# Chosen, no evidence decides them: the names FormataPergunta (and its being an external function of comum::asn) and
# the lambdas' parameters; std::transform and std::accumulate as the spellings of FormataPergunta's two inlined loops
# (no hand-written loop was measured for them; the answers' loop's forms are measured above, and of those only
# std::transform matches); visit's insert({key, value}), which gives 3728 its template arguments (the key and
# std::pair<const md::CEleitorIdentidade, md::CIndexer>, from the braced pair; no evidence gives the spelling); where
# each function starts in its file and the blank lines above (the throws' lines are the
# records'); the constructors' parameter names and `numero > 99999` over `>= 100000`; the visitor's member names and the
# word at +4; md::CIndexer as the type of the two words (a reading, cindexer.h says why); the destructor `= default`
# ({} gives the same object, docs/reference/facts/reading.md R4).
#
# The list also compiles unit 159's two files, app/comum/dados/asn/candidatura/cconversorcandidatura.cpp and
# cconversorcandidaturas.cpp (comum::asn::CConversorCandidatura and CConversorCandidaturas), before
# cvisitanteeleitor.cpp: the place among those weighed with the fewest objects out of the target's data order
# (docs/reference/facts/codegen.md C4), where they also link after cconversorcargo.cpp, which then keeps
# Desconverte<CodigoCargoConsulta>'s copy, so cconversorcandidaturas.cpp's object holds the target's run of data;
# fragment 159 has the counts and the scores, which no place weighed moved.
#
# No roots: the instance of 5700 and its stand-in for fn 11411 went when 11411 was written (fragment 310), and the sink
# of CVisitanteEleitor's vtable, which stood for the constructor fn 11523 holds, went when 11523 was written (unit
# 110's celeitores.cpp, through carregaarquivo.cpp's LeEleitores).
COMUMASN225_SRCS := src/app/comum/dados/md/processoeleitoral/cdetalheconsulta.cpp \
  src/app/comum/dados/md/processoeleitoral/crespostaconsulta.cpp \
  src/app/comum/dados/asn/processoeleitoral/cconversordetalheconsulta.cpp \
  src/app/comum/dados/asn/candidatura/cconversorcandidatura.cpp \
  src/app/comum/dados/asn/candidatura/cconversorcandidaturas.cpp \
  src/app/comum/dados/asn/eleitor/cvisitanteeleitor.cpp
UENUX2_SRCS += $(COMUMASN225_SRCS)
# the converters include generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(filter %/asn/processoeleitoral/cconversordetalheconsulta.cpp %/asn/candidatura/cconversorcandidatura.cpp %/asn/candidatura/cconversorcandidaturas.cpp %/asn/eleitor/cvisitanteeleitor.cpp,$(COMUMASN225_SRCS)),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
