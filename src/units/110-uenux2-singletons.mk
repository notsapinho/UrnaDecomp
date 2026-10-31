# uenux2 singletons over binaryen's body 1406: the nine GetInst (target fns 187, 273, 326, 407, 555, 1073, 1926, 2812,
# 2817), their mutexes' and pointers' exit destructors, and the classes' own destructors. Sources here are the files of
# CEleitores, CHV, CPE, CRespostas, CValidadorIdentidade and CTelasVota; ccargos.cpp and cconfiguracaoeleicao.cpp are unit
# 88's and crdvvota.cpp unit 13's, and their GetInst are described here. The macro is
# src/ecourna/api/pattern/singleton.hpp.
#
# What the target shows:
# - 1406 is formed, it has no source: every thunk is f1406(mutex, record, message, pointer). With the nine in the link
#   binaryen forms the same body, with the same four parameters in the same order, under the first GetInst in link order.
#   Its throw is CPatternError's 1303 through 331, and its 150 unlocks: `mutex::lock` leaves no call (R15) and uenux2's
#   flags leave no landing pad, so the throw path has no unlock.
# - The record's column is 46 or 47 plus the class name's length. In CHV, CPE, CRespostas and CRdvVota the next record is
#   CreateInst's throw five lines down, room for a blank line, its head, `{` and `if`, so GetInst's line is the whole
#   member; in CCargos and CTelasVota the next line is a second such record, CreateInst's. The +46 classes' next records
#   are further down and say nothing. __builtin_COLUMN reports the end of a macro's expansion, and each record here is the
#   target's with the column at the `)` of the invocation. A definition spelled out holds the class name twice before its
#   throw, so its column would grow by two per character of the name, not one. That is a reading of the arithmetic: no
#   bytes hold the macro.
# - The two forms of the column are the two orders of the statics: `.bss` holds the mutex 24 bytes below the pointer for
#   the +47 classes (CCargos, CHV, CPE, CRdvVota, CRespostas, CTelasVota) and the pointer 4 bytes below the mutex for the
#   +46 classes (CConfiguracaoEleicao, CEleitores, CValidadorIdentidade), and in all nine the pointer's exit destructor
#   comes first in link order (its index is the higher of each pair, 11561 over 11560). Measured in the object: GetInst above the
#   definitions `pointer; mutex;` gives mutex, pointer in `.bss` and the pointer's destructor first; the same definitions
#   above GetInst give pointer, mutex and the same destructor order (the object's segment list and the order of its
#   `__cxx_global_array_dtor`s).
# - The pointer is a std::unique_ptr: each exit destructor nulls it, then destroys and frees the old value.
# - Every destructor but CHV's is out of line in its class's .cpp: the exit destructor keeps a call of 37 bytes around
#   5805, 5792, 5773, 5730, 5671, 5598 or 6548, and a non-virtual class shows no D0 to read. Measured on CCargos: implicit,
#   clang inlines the D2 and the destructor is 114 B; defined in the .cpp the call goes through the D1 alias, which clang
#   does not inline, and it is 48 B, the target's. CHV's calls no destructor: f349(p0, 1838872) only frees.
# - CEleitores is final: fn 5773 opens with no vptr store (R4), though its vtable has one slot. Its tree at +52 is fn
#   1594, the function CConfiguracaoEleicao's tree at +604 calls, so the two share an element type.
# - The caller's object first: cconfiguracaoeleicao.cpp links right after ccargos.cpp, in unit 88's list, as the records'
#   addresses have it. With it in this fragment, which sorts ahead of 88, 2836 scores 100 over 283 rows, inserted 4 and
#   deleted 4, its locals swapped; with this order it matches (docs/reference/facts/codegen.md C4).
# - In 5745, with the caller above the callee as chv.cpp has it, binaryen inlines VerificaEntraEmHorarioVerao and
#   CHorarioVeraoMunicipio::GetHorarioVerao: its object calls both. binaryen inlines CConfiguracaoEleicao::GetEleicao into
#   2836, from another object. clang inlines the implicit ~CEleicaoPE into __destroy_at<CEleicaoPE> (730) and the in-class
#   predicates and accessors.
# - In CParteRdv::Imprime the predicates read the flag before the type: `has_value() && m_tipo == X` gives the target's
#   `!= 1` and `eqz`, the other order leaves `& 1` on the flag.
# - GetCurrent and GetCurrentEleicao read the cargo before calling GetInst: the target's order, which a local gives. In
#   the argument place the call comes first and the object has 60 rows against 62.
#
# Forms measured, function by function with object-local numbers masked, that give the same rows, so each spelling is a
# choice: for lock_guard, std::unique_lock, std::scoped_lock and the deduced lock_guard; for `!p`, `p == nullptr`, `!p.get()`;
# `= default` or `{}` on the destructor, compared on the D2; a copy of the whole pair for the local in GetCurrent;
# `!(a < b)` for IsFim's `a >= b`; a reference to the element in GetEleicao's loop, or the vector read through the accessor
# each time; in CParteCargos::Imprime a while loop for the for, and the two tests nested. Forms measured that give other
# rows: a reference for the local in GetCurrent, range-for in GetEleicao or in either loop of GetCargo, the two tests
# of Imprime swapped, and in CParteRdv::Imprime a pointer to the chosen part, or three separate ifs.
#
# Chosen, no evidence names them: the macro's name and path, its parameters, `s_instancia` and `s_mutex`, and the one
# character `s_instance` is shorter by for the +46 classes. The macro's name has the length that puts the `)` on the
# record's column, so its length is fitted to the record and not evidence. Enumerator EPE_SINGLETON_NAO_CRIADO, CCargos's
# Reset, IsFim and GetUltimaEleicaoID (fns 2269 and 602 have no record), CCargo's three predicates, the headers' paths
# beside the records' files, the map keys and element types the class heads say are chosen, and the lines of the statics,
# of each destructor and of Reset and IsFim. The statics sit below CreateInst's lines in the +47 files.
#
# Names: 407, 555, 187, 1073, 1926 and 2817 are srcloc-anchors. Their mutexes hold through their exit destructors, which
# the content pass pairs once the name is voted, and through the thunk. A record held by a function that inlines GetInst
# anchors nothing, so 273, 326 and 2812 have hand edits of `s_mutex` (and CRespostas's pointer, with 5730 and 1929, whose
# twins 2815 and 1932 stop the census). 555's and 2817's pointers have one voter and a destructor that cannot land, so they
# have hand edits too. Each line in splat/symbol_addrs.txt cites what the thunk's own body holds and the other holders.
#
# Not reconstructed:
# - 5734 and 11495: CRdvVota's destructor holds comum::asn::CConversorRegistroDigitalVoto<CConversorEleicoesVota> at +44
#   (vptr 1560304), and that class is not in this tree; its slots 2 and 3 are 11483 and 11482. ~CRdvVota here destroys the
#   members crdvvota.h has, 67 rows over 115 from fn 5734, and both rows are no-candidate.
# - 11510: f349(p0, 1838872). 349 is binaryen's merge of the exit destructors of pointers to trivial classes, and it needs
#   a second such destructor in the link; ours is a whole body until then.
# - 11206, CParteEleitores::Imprime, waits for api/io/cdatamap.h, whose Next is 5601; 11215, CParteCandidatos::Imprime, for
#   521 and 2271. Both stay traps in unit 77's pending file.
# - 242, ~CDetalheCandidato, is written (implicit) and differs: the target keeps vector<CSuplencia>'s fn 1135 out of line,
#   and ours inlines that loop around __destroy_at<CSuplencia>.
# - CEleitores's one slot, 2824, has no body and no vtable of ours: the stub went with the class (src/units/README.md
#   "Pending members"). CreateInst of each class is inlined into 7787 or 2787 and is not written.
SINGLETONS_SRCS := src/app/comum/dados/celeitores.cpp \
  src/app/comum/dados/chv.cpp src/app/comum/dados/cpe.cpp src/app/comum/dados/crespostas.cpp \
  src/app/comum/dados/md/cvalidadoridentidade.cpp src/app/vota/eleitor/comum/ctelasvota.cpp
UENUX2_SRCS += $(SINGLETONS_SRCS)
# the callers are not reconstructed yet: 110-uenux2-singletons-roots.cpp reaches them the way the target does
$(ROOT)/$(APP)/110-uenux2-singletons-roots.o: $(ROOT)/src/units/110-uenux2-singletons-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/110-uenux2-singletons.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/110-uenux2-singletons-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/110-uenux2-singletons-roots.o
