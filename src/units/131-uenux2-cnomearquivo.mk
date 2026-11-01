# uenux2 comum::CNomeArquivo over comum::EUeComumNomeArquivoError, in src/app/comum/nomearquivo/ (paths relative to
# src/uenux2): cnomearquivo.cpp, the header cnomearquivo.h and the error header euecomumnomearquivoerror.h beside it.
# - CBaseError<comum::EUeComumNomeArquivoError, SErrorLimits{8950, 9000}>'s constructor (target fn 2827, a thunk of fn
#   710 that passes the vptr 1558772), which the helpers' throws instantiate through the error header's alias; the
#   symbol file names it by that vptr.
# - The anonymous-namespace helpers, at their records' lines: FormataFase (target fn 2828, record :38), FormataNumero
#   (fn 1161, record :48, matched since fn 11973's literal is in the link: below) and FormataUF (fn 3773, record :73).
# - Two name builders, CNomeArquivo::NomeArquivoUF (fn 1705) and NomeArquivoSecao (fn 3772), matched at the tree's -O3
#   (below). They are the helpers' callers in the object: FormataFase and FormataUF have two call sites there and
#   FormataNumero five, and all three are functions of their own in the link (build/out/wasm-map/vota_web/names.tsv), as
#   in the target, where 2828 has 4 callers, 1161 5 and 3773 3 (ledger/callgraph.tsv).
#
# Evidence: the records give the helpers' names, file, lines, columns and signatures; the typeinfo of CBaseError<...>
# gives the enum's name, namespace and limits, and the codes are the ones the four throwers pass to fn 2827. 1705 and
# 3772 call the file-static helpers in their own stack frame, so their code is cnomearquivo.cpp's
# (docs/reference/facts/reading.md R8). The builders' order is measured in part: the target's band 3 holds FormataUF
# (3773) ahead of NomeArquivoSecao (3772) in link order, and with NomeArquivoSecao defined first a scratch compile holds
# it ahead of FormataUF, which reads as the file defining a caller of FormataUF before NomeArquivoSecao (reading.md R9,
# a deferred function sits after its first caller); of the two written, that is NomeArquivoUF.
# Chosen: the class (from the file's name) and that the builders are its static members, the builders' names, their
# lines (after the helpers, before the record at :208) and their parameter types (uedword for the numbers), the
# enumerators' names, the two header paths, the include that gives EUrnaFase's formatter
# (app/comum/dados/md/estadoaplicacao/eurna.h; the target's handle is fn 536, formatter<unsigned int>), and every
# parameter name.
#
# Forms that give the same code, from scratch compiles of cnomearquivo.cpp at the tree's flags with the landed file's
# record paths, compared per function with call and global indices masked, and by the Data section:
# - FormataFase's cases in the order FASE_TREINAMENTO, FASE_SIMULADO, FASE_OFICIAL: a cmp-equal object;
# - FormataFase with a char set per case and `return std::string(1, letra);` after the switch: the same function
#   bodies and data, in an object that differs only in the numbers of its .L.str labels;
# - ('-' + tipo) for ("-" + tipo) in the builders, at -O2 and at -O3: the same bodies and data, likewise.
# No other spelling was measured.
#
# - 1161 FormataNumero matches since fn 11973 (CDataSourcesRelatorio<CRdvVota, CEleitores>::DetalheCandidatoZE,
#   src/units/183-uenux2-relatorios.mk) is in the link, its body unchanged. It loads the end of "{:0{}}", which the
#   target holds as the tail of 11973's literal "  {}{}{:0{}}" at 1042; until 11973 landed, the scan read it
#   `unresolved` at that one operand, `ours +0x69 i32.const 1040: an address of ours: string tail occurs 4098 times`
#   (with a scratch object that held the literal, tools/round/try-tu.sh, splat-remap printed `target 1161: IDENTICAL`).
#
# Not matched, and what each waits for:
# - 1705 and 3772 call std::string::append(const char*, size_t) (fn 160) 5 and 8 times in the target, as the tree's -O3
#   does, and match there; the scan pairs them by content, since nothing else names them. At -O2 clang inlines append
#   and the objects call __grow_by_and_replace instead: in the -O2 link they scored 551 over 805 rows and 877 over 1285,
#   and with cnomearquivo.cpp.o compiled at -O3 in a copy of the link command (docs/reference/facts/workflow.md W13)
#   14 over 370 and 23 over 566, all operand-only, splat-remap printing IDENTICAL for both.
# - Not written: fn 3744, which holds the record at :208 (ajustaAbrangenciaUFMunicipio, code 8953) and the helpers'
#   calls inside a second stack frame, under code that copies what comum::md::CPleito::GetEleicao (fn 5651) returns and
#   inserts what reads as the name into a std::map keyed by a word (32-byte nodes, rebalanced by fn 152); it calls
#   append (fn 160) six times, comum::md::CEleicaoPE::PossuiCargoCandidato (fn 5653, unit 88), and fns 365 and 374
#   (374 has no name; 365, comum::md::CDetalheCandidato's copy constructor, matches since fragment 191).
NOMEARQUIVO_SRCS := src/app/comum/nomearquivo/cnomearquivo.cpp
UENUX2_SRCS += $(NOMEARQUIVO_SRCS)
# nothing reconstructed calls the builders yet: 131-uenux2-cnomearquivo-roots.cpp stands in for the target's callers,
# two call sites each
$(ROOT)/$(APP)/131-uenux2-cnomearquivo-roots.o: $(ROOT)/src/units/131-uenux2-cnomearquivo-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/131-uenux2-cnomearquivo.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/131-uenux2-cnomearquivo-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/131-uenux2-cnomearquivo-roots.o
