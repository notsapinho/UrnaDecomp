# uenux2 comum::CRdv's file (src/app/comum/dados/crdv.cpp, new; declarations in crdv.h) and two functions of
# comum::CEleitores's file (src/app/comum/dados/celeitores.cpp, which unit 110's list compiles; declarations in
# celeitores.h): the paths of "rdv.dat" and "uenux.db" in the two flashes' work directories, which binaryen merges in
# pairs, and the CRdv members that save the RDV encrypted. Paths relative to src/uenux2.
#
# Target functions:
#   1551  comum::GetArquivoRdvInterno()          crdv.cpp        `f6036(p0, "rdv.dat" end, "rdv.dat")`, a thunk
#   1701  comum::GetArquivoRdvExterno()          crdv.cpp        `f6035(p0, "rdv.dat" end, "rdv.dat")`
#   2826  comum::GetArquivoBancoDadosInterno()   celeitores.cpp  `f6036(p0, "uenux.db" end, "uenux.db")`
#   5762  comum::GetArquivoBancoDadosExterno()   celeitores.cpp  `f6035(p0, "uenux.db" end, "uenux.db")`
#   6036, 6035  the bodies binaryen merged from 1551 and 2826, and from 1701 and 5762; our link forms the same two
#         merges, byn$mgfn-shared$_ZN5comum27GetArquivoBancoDadosInternoEv and ...ExternoEv (the first member in our
#         link order gives the name), which match those indices
#   5737  void comum::CRdv::SalvaInterno() const   crdv.cpp, by the content pass
#   5736  void comum::CRdv::SalvaExterno() const   crdv.cpp, by the content pass
# and, written and not matched, api::CEncryptedFile's constructor (1692, unit 128's file), named by a hand line (below):
# it scores 5 over 30 rows (pnpm wasm score: 2 replaced, 3 deleted, the target's three zero stores, i32 +16, i64 +8 and
# i32 +20, against our two i64 stores), and every form measured stores +16 and +20 as one (fragment 128 lists them).
#
# What the target fixes.
# - The four path functions: 6036 calls CPath::GetPathTrab(EFlashOrigem) (fn 436) with 0, 6035 with 1, builds a path
#   from the name (string::append, fn 178), copies GetPathTrab's path (fn 138 when it is long) and appends the name
#   (path::operator/=, fn 183), copies the result's string into the result (a std::string: fn 6737 passes the results
#   to CSystem::RemoveFile, fn 2760, and CEleitores::DynamicCreate, fn 5761, and 5736 and 5737 to CEncryptedFile::Save,
#   each `const std::string&`), and destroys the three temporaries in reverse. The two bodies differ in one place
#   only, the order of the two stores that zero the name's path (6036: i32 +16, i64 +8; 6035 the other way), and one
#   form gives both, by GetPathTrab's constant alone: `(CPath::GetPathTrab(o) / "x").string()` compiled at
#   app/comum/dados's flags gives 6036's order with FLASH_INTERNA and 6035's with FLASH_EXTERNA, for both names (a
#   probe of the four, wasm-objdump -d of its object).
#   So the four are one form, and the two of each flash are the ones binaryen can merge. Same object: the implicit
#   conversion (`return CPath::GetPathTrab(o) / "x";`). Different: a named `const` path then `.string()` (it destroys
#   the temporaries before the copy).
# - Their files, a reading of their bands (docs/how-to-decompile.md step 3, rule 5), which allow other files too. 5762
#   lies in celeitores.cpp's band-2 run
#   (5765 and 5764 link before it, 5761, DynamicCreate, after it), and 2826 heads its band-4 run (2825 to 2821 after it;
#   cnomearquivo.cpp's 2827 and 2828 before it); CEleitores::CompleteLoad()'s 48 bytes, which fn 6734 holds
#   (fragment 386), call 2826.
#   1551 lies right before crdvvota.cpp's 1550 in band 8, 1701 right after clocal.cpp's 1702 in band 7, and 5737 and
#   5736 between clocal.cpp's 5738 and crdvvota.cpp's 5734 in band 2: where the target's data hold crdv.cpp's records
#   (@1559956 to @1560024, CRdv's constructor and GetCifradorCryptoTable, inlined into fn 7787), after clocal.cpp's
#   (@1559876) and before crdvvota.cpp's (@1560132). 2826's file is its pair with 5762 and CompleteLoad's call (the data
#   put celeitordetalhe.cpp and celeitordinamicodao.cpp between cnomearquivo.cpp and celeitores.cpp), and crdv.cpp over
#   clocal.cpp's tail for 1551 and 1701 is 5737's and 5736's, CRdv's. That they are free functions (they read no class
#   state), their names and their declarations' headers are chosen.
# - 5737 and 5736: on GetArquivoRdvInterno's or GetArquivoRdvExterno's string, a CEncryptedFile built over this+8 (the
#   cipher, CRdv::m_cifrador), the bytes of slot 11 (CRdv::Converte) called through the vtable, Write (2766), Save
#   (2767), then the bytes, the file and the string destroyed. The call through the vtable on `this`, whose class is
#   not final (CRdvVota, the one derived class, is), and the read of m_cifrador make them CRdv's members; non-virtual
#   (CRdv's vtable has 14 slots, all pure). fn 6737 calls each twice on CRdvVota::GetInst()'s object. Their frame
#   puts the string at +0, the bytes at +12 and the file at +24: the file and the bytes above the string, as the locals
#   of a callee clang inlined sit above the caller's own (docs/reference/facts/codegen.md C5). So the save is written
#   as CRdv::Salva(const std::string&), private, which both call with the path (a reading the scores support); in
#   place (the path a named local, then the file and the bytes) they scored 24 over 68 rows (5 inserted, 5 deleted:
#   the string at +36, the file at +12, the bytes at +0), with Salva 7 over 63, every row a call operand (pnpm wasm
#   score on links of this unit before steps 7 to 9).
#   Salva has no target function: our link drops its out-of-line copy (no line in names.tsv). Its name, const and
#   being private, SalvaInterno's and SalvaExterno's names and const are chosen.
# - Their order: band 2 links 5737 before 5736, and crdv.cpp defines SalvaInterno first (ld_index 7018 and 7019).
#   Lines in crdv.cpp: the records' lines 60, 78, 90 and 93 are blank (functions not written); the file's five
#   functions (the two paths, Salva, SalvaInterno, SalvaExterno) follow them, from line 96, a choice.
# - Lines in celeitores.cpp, chosen: GetArquivoBancoDadosInterno at 278, between CompleteLoad's last record (238) and
#   DynamicCreate's first (301); GetArquivoBancoDadosExterno at 744, after ValidaIdentidadesEleitor, where it adds no
#   inverted pair to band 2 (docs/reference/facts/placing.md P9; names.tsv's ld_index before unit 383 landed: 5765 2692,
#   5764 2690, 5762 2694, 5757 2700; 5765/5764 inverted already). The band suggests the two were defined together after
#   CompleteLoad, whose calls would put 5765 and 5764 first (a reading): there 5762 would sit before 5765 and 5764 in
#   our object while CompleteLoad is not written. With DynamicCreate (5761) written at its records' lines (unit 383),
#   5762's line, below it, inverts that pair: 5762 links before 5761 in the target (ledger/ordinals.tsv's ordinals 4434
#   and 4435), after it in ours (ld_index 2605 against 2586 at c97e48e1; 5765 2603, 5764 2601, 5757 2611, so 5761 also
#   links before 5765 and 5764, the pairs unit 383's fragment names). Since fragment 386 wrote CompleteLoad, 5765 and
#   5764 link before 5761 (ld_index 2603, 2604 and 2613) and 5762 after it (2627): that one pair stays inverted.
#
# Names. The census pairs 1551, 1701, 2826, 5762, 6035 and 6036 at the shape tier only (moved: none -> shape), so step 8
# names none of them, and step 9's scan matches all six from those pairs (source `ledger`). 5737 and 5736 have no census
# pair (their call of the constructor differs) and match by the content pass once 1692 has a name. No generated route
# names 1692: a callers+content hand line in splat/symbol_addrs.txt does, from its own rows (the only target function
# with its depth-0 fingerprint, addr and shape hashes, a shared_ptr copied to +0 and +4, +8 to +24 zeroed, `this`
# returned) and from what every target caller does with the object (CEncryptedFile's matched Write and Save, or Load and
# Read, then ~CEncryptedFile, fn 1691). Weighed by removal (docs/reference/splat.md "Reviewing a match"): a scan, run
# twice, on copies without the line and without the match lines of 5736 and 5737 leaves 12798 match rows (5736 and 5737
# no-candidate, 1692 no-candidate) where the control on the same match copy with every name leaves 12800 (1692 differs),
# and splat-build on either copy gives the target's sha256: the line carried 5736 and 5737 alone. Since fragment 386,
# 6734's call names 1692 too (`call by:6734`), and the line carries nothing (removed, alone or with 5769's, every row
# stays and splat-build gives the target's sha256); it goes in a commit of its own with docs/reference/splat.md section
# 2, which cites it.
#
# Roots (381-uenux2-crdv-roots.cpp): stand-ins for 6737 and 7787, the target callers not written that give each function
# its second call site; 6734 (in the link since fragment 386) and 7174 need none. Unit 128's stand-ins for 5736's and
# 5737's calls of Write and Save went (their callers are in the link). It compiles at the tree's flags, as the
# functions' directory does.
CRDV_SRCS := src/app/comum/dados/crdv.cpp
UENUX2_SRCS += $(CRDV_SRCS)
$(ROOT)/$(APP)/381-uenux2-crdv-roots.o: $(ROOT)/src/units/381-uenux2-crdv-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/381-uenux2-crdv.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/381-uenux2-crdv-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/381-uenux2-crdv-roots.o
