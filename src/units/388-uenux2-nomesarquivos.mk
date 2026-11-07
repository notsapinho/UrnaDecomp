# uenux2 comum: the package-name and pleito helpers vota::CTelasVota's constructor (target fn 7787) calls, written into
# three landed units' files. This fragment holds their notes and their callers' stand-ins and builds its roots file only
# (src/units/README.md "Landing a unit"); paths relative to src/uenux2/src/app/comum.
# - comum::NomesArquivosEleicao (target fn 3744) in unit 279's nomearquivo/cnomearquivoeleitores.cpp, after
#   NomeArquivoEleitoresTTE, declared in nomearquivo/cnomearquivo.h.
# - comum::CNomeArquivo::NomeArquivoAbrangencia (no index: binaryen inlines it into 3744) and the anonymous-namespace
#   ajustaAbrangenciaUFMunicipio (record cnomearquivo.cpp:208, code 8953, clang inlines it) in unit 131's
#   nomearquivo/cnomearquivo.cpp.
# - comum::md::CPleito::GetEleicoesMunicipio and FiltraMunicipio (fns 5649 and 3713), with the private
#   GetSituacoesMunicipio (no index: clang inlines it into 3713) in unit 88's dados/md/processoeleitoral/cpleito.cpp,
#   and comum::md::CEleicaoPE::PossuiMunicipio (no index, inline in celeicaope.h), which both hold.
# - libc++.a's std::filesystem::__remove (fn 2135, operations.o), which the roots' stand-in for fn 7787 brings.
# Matched: 3744, 5649, 3713 and 2135. In the whole link before steps 7 to 9 (`pnpm wasm score`, default depth): 3744 50
# over 1143 rows, 5649 4 over 130, 3713 9 over 221, 2135 6 over 65, every row an operand (calls, data addresses, the
# thrown error's destructor slot).
#
# Where they are, evidence and readings:
# - 3744 is not cnomearquivo.cpp's own function. Its record (:208, ajustaAbrangenciaUFMunicipio) lies behind a second
#   stack prologue, `i32.sub(g0, 528)` after 3744's own 80-byte one (pnpm wasm fn), with the calls of cnomearquivo.cpp's
#   anonymous-namespace FormataFase (2828), FormataNumero (1161) and FormataUF (3773): so that frame is a function of
#   cnomearquivo.cpp (docs/reference/facts/placing.md P2) that binaryen inlined into its one caller, written as
#   NomeArquivoAbrangencia, external, since clang would inline an internal function with one call. 3744 itself lies in
#   use band 3 (ledger/ordinals.tsv) next to 3745 (NomeArquivoEleitores), after crdvvota.cpp's 3747 to 3750 and before
#   cjustificador.cpp's 3743 to 3741 in link order, with 27 functions of the band, crdvvota.cpp's, cpartidos.cpp's,
#   clocal.cpp's and chv.cpp's among them, between it and cnomearquivo.cpp's 3772 and 3773; 2811 lies in band 4 between
#   crespostas.cpp's 2812 and cjustificador.cpp's 2809. The table agrees: slots 2461 and 2462 are crespostas.cpp's exit
#   destructors (11481, 11480), 2463 is 3744, 2464 3745, and 2465 and 2466 are cjustificador.cpp's (11477, 11476)
#   (`wasm-objdump -x -j Elem target/vota_web_wasm.wasm`). That 3744 shares 3745's object is a reading; the file is unit
#   279's chosen one, and 3744 follows 3745 there, as band 3 orders them (ld_index 6043 and 6045 in
#   build/out/wasm-map/vota_web/names.tsv). No target function loads slot 2463 or 2464 (`/usr/bin/grep -rlE 'i32\.const
#   2463($|[^0-9])' build/out/splat/pieces/asm` prints nothing): the table's entry is the reference, as for 3745.
# - 5649 lies in band 2 between cpleito.cpp's GetEleicao (5651) and GetSituacoesEleicoes (5648), after 5650 (a
#   std::format argument store the link keeps from the executable TU), so it is cpleito.cpp's, defined between those
#   two records' functions (ld_index 7749, 7750, 7752). The lines between them were GetEleicao's end, ExisteEleicao
#   (no index, a chosen line) and two 5-line gaps, so ExisteEleicao moved above GetEleicao, a choice; 3775, which holds
#   it inlined, still matches. 5649's lines (142 to 151) are a choice.
# - 3713 lies in band 3 between celeicaope.cpp's 3714 and md/municipiozona/cmunicipio.cpp's 3712, the place of
#   cpleito.cpp and of md/processoeleitoral's later files in the data's run (cpleito.cpp, cprocessoeleitoral.cpp,
#   cprocessoeleitoraldto.cpp, crespostaconsulta.cpp). It builds a CPleito (5652) from the id, name and date at +0, +4
#   and +16 of its argument, GetEleicoesMunicipio's copy, the version map at +36 and the situations it gathers through
#   GetSituacoesEleicoes (5648) or copies from +48: private state, so a member (how-to step 3), in its class's file; its
#   line, after GetSituacoesEleicoes, is a choice.
# - 2135 is libc++.a's: `llvm-nm` of the sysroot's libc++.a(operations.o) defines
#   _ZNSt3__210filesystem8__removeERKNS0_4pathEPNS_10error_codeE, and the scan matches it from that object.
#
# The bodies (evidence the target's code gives):
# - 3744 returns a std::map keyed by md::ETipoAbrangencia (32-byte nodes, the key at +16 compared signed, the string at
#   +20): it copies the CEleicaoPE that CPleito::GetEleicao returns (52 bytes, the cargos' 140-byte elements with both
#   optional details, the municipalities' words), and when PossuiCargoCandidato (5653) is true inserts the election's
#   abrangencia (+24) with the builder's name, moving the string into a pair before the tree's search and freeing it
#   when the key is there. 7787 passes CConfiguracaoEleicao's +620 (SIdentificacaoArquivo), the pleito at +640, the
#   municipality at +644, an election id, "ca" and "dat" (the tail of "dadoscarga.dat" at 60735).
# - The builder copies the UF (+8 of the identification) into its own frame, then ajustaAbrangenciaUFMunicipio: for
#   ABRANGENCIA_ESTADUAL (1) the municipality becomes 0, for ABRANGENCIA_FEDERAL (2) 0 and the UF "BR", for
#   ABRANGENCIA_MUNICIPAL (0) nothing, else the throw at :208, column 11 (the body's indent), with "Abrangência
#   inválida: {}" (6567, 24 bytes) and one int (the i64 constant's argument code 3, as FiltraPorAbrangencia's in
#   ccargos.cpp). Then FormataFase(fase) + FormataNumero(election, 5) + FormataUF(UF) + FormataNumero(municipality,
#   5) + ("-" + tipo) + "." + extensao, NomeArquivoSecao's parts. The record's parameter types (TMunicipioID &,
#   std::string &, const md::ETipoAbrangencia &) are its spelling; TMunicipioID is comum's alias, repeated in
#   cnomearquivo.h.
# - 5649: a copy of m_eleicoes for the municipality 0 (fn 1953, the CEleicaoPE copy), else the elections whose
#   municipalities hold it or 0, each through std::vector<CEleicaoPE>::push_back (5777). The test is a std::find over
#   the words (wmemchr, 736) and a loop comparing each with 0, the code std::find with an int 0 gives over the unsigned
#   words; 3713 holds the same test, which reads as clang's inlining in this TU: CEleicaoPE::PossuiMunicipio, inline in
#   the class.
# - 3713 loads the id before it calls 5649, so the constructor's arguments are written in order with the two
#   collections built in the call; the situations are a copy of m_situacoes for 0, else GetSituacoesEleicoes of each
#   election that PossuiMunicipio keeps, pushed through fn 760.
#
# Forms, compared function by function on objects with call and global indices masked (docs/how-to-decompile.md step 3):
# - same bytes: the switch and an if chain in ajustaAbrangenciaUFMunicipio, and its cases in the order FEDERAL,
#   ESTADUAL, MUNICIPAL (6 lines differ against a control of a shorter file name, three data addresses each way: the
#   longer path moves the data; at paths of one length the two objects differ only in the record path's directory
#   name); `std::string ufArquivo(uf)` and `= uf`; insert({...}) and insert(std::make_pair(...)) in 3744;
#   std::copy_if with std::back_inserter and a range-for with push_back in 5649.
# - differ (so the written form is evidence): the UF set before the municipality in the federal case (822 lines);
#   emplace and try_emplace in 3744 (180 lines each), the CEleicaoPE bound by reference instead of copied (587 lines);
#   in 3713 the elections or the situations in a named local before the constructor call (6 and 54 lines).
# - the builder's parameters: the phase by value (3744 loads it before the second prologue), the UF by reference and
#   copied inside, the municipality by value (the helper writes it), the abrangencia by value; chosen beside that
#   reading, not compiled otherwise.
# Chosen: every name above (NomesArquivosEleicao, NomeArquivoAbrangencia, GetEleicoesMunicipio, FiltraMunicipio,
# GetSituacoesMunicipio, PossuiMunicipio, the parameters'), the builder's being a static member of CNomeArquivo, 3744's
# being a free function of comum, 5649's and 3713's and the helper's being members, PossuiMunicipio's being inline in
# the class, the parameter types where no record prints them (uedword, md::TEleicaoID), the order of
# ajustaAbrangenciaUFMunicipio's cases, and every line but :208.
#
# Not matched, and what each waits for:
# - fn 2811 (678 B, 7787 x4, stub in src/uenux2/unplaced.cpp) is not written. For each election GetEleicoesMunicipio
#   keeps, it takes 3744's map and pushes each name whose abrangencia a post with a candidate's detail has (a loop over
#   the cargos at +28 that binaryen inlined from a function of another TU: a bool built as `if (result i32) ... else 0
#   end` and tested again), then frees the map (fn 2839) and the elections (fn 730); 7787 passes "pa", "fe", "fo" and
#   "ca". Written so (a range-for over the copy and the map, the test as a CEleicaoPE member in celeicaope.cpp,
#   `std::any_of` with the flag at +84 tested first and the key a const reference captured by value, of the forms tried
#   the one that gives the target's `i32.and` and the key's load after the empty test), it scored 138 over 354 rows (12
#   inserted, 14 deleted) in the whole link, every other row the target's but its locals: the target copies the
#   identification parameter into a local before the loop (`local.get 1; local.set 16`) and reuses local 1. Its object
#   code was the same with a named map, the pair's members, emplace_back, a named copy of the elections, 3744 in another
#   TU, strict aliasing and the identification by value, the link the same with 2811 defined before 3744, and clang at
#   -O2, -Os and -Oz copies no parameter either.
#   Written as a forwarder to an out-of-line body of one caller (binaryen inlines the body into it), it scored 95 over
#   349 (7 inserted, 8 deleted), the frame and the rows to the loop the target's, the copied parameter the result
#   pointer (local 0) where the target's is local 1. The remainder is not explained, so the body stays unwritten
#   (how-to step 5); the roots stand in for its calls of 3744 and 5649.
# - fn 2839 (57 B), the std::map<md::ETipoAbrangencia, std::string>'s tree destroy that 2811 and 7787 call (and itself,
#   twice): the scan pairs it with carquivossavd.cpp.o's ESavdNomePacote twin (3841's body), and a name comes only
#   from a caller's call vote, so it waits for 2811's match.
#
# 388-uenux2-nomesarquivos-roots.cpp stands for fn 7787's calls of 3713 and std::filesystem::remove and for 2811's and
# 7787's calls of 3744 and 2811's of 5649; it takes the addresses of 3744 and 2135, which the target's table holds.
# Without 2135's address, binaryen's dead-argument elimination folds the null error_code every call passes:
# `(i32)->(i32)`, 28 over 67 rows, where the target keeps `(i32 i32)->(i32)` (measured on a link with that line out).
# With 3744, 5649 and 3713 in the link these stand-ins went (steps 6 to 10 moved no other row): unit 88's
# SomaEleicoesDoPleito (5651's calls for 3744), SomaSituacoes (5648's for 3713) and ContaCandidatos's call of 5653 for
# 3744 (its other stays for 7787), and unit 280's w280_pleito (CPleito's constructor, 5652, for 3713) and w280_eleicoes
# (std::vector<CEleicaoPE>::push_back, 5777, for 5649).
$(ROOT)/$(APP)/388-uenux2-nomesarquivos-roots.o: $(ROOT)/src/units/388-uenux2-nomesarquivos-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/388-uenux2-nomesarquivos.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/388-uenux2-nomesarquivos-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/388-uenux2-nomesarquivos-roots.o
