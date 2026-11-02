# uenux2 comum::md::CVersoesContratos and CDependenciasContratos (app/comum/gravadores/md/, the files the records
# name, each class header beside its file): GetValor, target fns 3825 and 3826, and their merged body, fn 6044; and
# api::hash::ListaHashesArquivos (fn 5358, written, not matched) in api/hash/cmontadorhash.cpp, the file of its band
# (below), with the header cmontadorhash.h beside it. Paths relative to src/uenux2. Members of the same work that live
# in other units' files: IGravador's Slot4 and Slot5 (unit 122, iresultado.cpp), api::CIniStrings::FindKey and EndKey
# (unit 215, cinistrings.cpp) and ecourna::api::io::CFile::Write (fn 5180, ecourna's api/io/cfile.cpp, unit 03's
# source), whose callers' stand-ins are this fragment's roots.
#
# GetValor (records cversoescontratos.cpp:42 and cdependenciascontratos.cpp:59, `const std::string ...::GetValor(const
# std::string &)`): the INI object's key map's find (fn 10877, CIniStrings::FindKey) and end (fn 5481), and when the key
# is not there CUeComumGravadoresError 8697 (8663) "Propriedade inexistente: {}" with the key; else a copy of the
# CIniKey's value. The two bodies differ only in their record and code, so binaryen merged them into fn 6044, which
# takes the two as parameters, and keeps each GetValor as a thunk (3825, 3826) that passes its own. Our link forms the
# same merge, byn$mgfn-shared$ over CDependenciasContratos::GetValor's name (step 9 matches 6044 under it; the name is
# our link's, docs/how-to-decompile.md step 9 "Hand edits"). FindKey and EndKey stay calls: they are defined in
# cinistrings.cpp, and each had two callers before the merge; EndKey's body (this plus 16) is the one fn 5481 the
# target and our link keep for boost's sp_counted_impl_pd::get_untyped_deleter too (matched before, now named `call
# by:6044`). Measured in this link before step 8 (pnpm wasm score against the target): 6044 14 over 246 rows, 3825 and
# 3826 3 over 8, 10877 0 over 7, every row that differs an operand: a call, a data address, the format string's packed
# address, the format buffer's table slot and the exception's destructor slot.
#
# ListaHashesArquivos (fn 5358): a CHashDiretorio's files as CHashArquivo with the directory's name before each file's,
# then its subdirectories' lists, recursively, appended with vector::insert. It scores 20 over 603 rows in this link,
# every row a call's or a data address's operand, and reads no-candidate: no record names it and the census pairs it
# with no target function. Its one callee that differs is the range insert, fn 5854: ours comes from cmontadorhash.cpp's
# object, built with strict aliasing (src/api is in UENUX2_TBAA_DIRS), and scores 84 over 921 rows (14 inserted, 7
# deleted: the circular buffer's swap loads in another order). With cmontadorhash.cpp built without strict aliasing (one
# variant object in the whole link, docs/reference/facts/workflow.md W13) 5854 scores 20 over 907 and 5358 20 over 603,
# operands only both. The target's copy reads as comum::CGravadorHashes::GravaResultado's (fn 11620,
# cgravadorhashes.cpp, comum/gravadores, built without it; a reading): in the uses-2 band 5854 sat among
# comum/gravadores' rows (the stubs' clusters of 5852 and 5854 named cgravadorhashes.cpp and md/centidadehashes.cpp),
# and those rows (5855 to 5875) link ahead of api/hash's (5358 to 5364). So 5854 waits for 11620, and 5358's name, a
# reading, for 5854's (the census pairs a body by its callees' shapes too). 5852, the insert's
# __insert_assign_n_unchecked, matches from cmontadorhash.cpp's object (step 8 names it by pair-addr). In the band 5358
# and 5359 link right after 5360, whose records are cmontadorhash.cpp's (lines 49, 78, 91, 98, 121) and
# chashdiretorio.cpp's, and before api/ipc's objects: so the file.
#
# ecourna::api::io::CFile::Write (fn 5180, matched; step 9 found it by the census's pair) is written in ecourna's
# api/io/cfile.cpp, unit 03's source, and declared in cfile.hpp, whose comment has its evidence and the forms measured;
# this fragment's roots stand for its two callers. Unit 03's fragment and row name it at the landing.
#
# Not written, and what each waits for:
# - fn 5359 (calls CMontadorHash::CriaHashesDiretorio, fn 5360, then 5358, and destroys the directory): 5360 (9613 B).
# - fn 5869, which collects a contract's dependencies through CDependenciasContratos::GetValor, CStringUtils::Split on
#   ',' and two inserts into a std::set<std::string>, recursively, and returns a copy of the set (its one target
#   caller, fn 12098, passes it comum::CGeracaoVersoesContratos's singleton, whose +0 is the CDependenciasContratos).
#   Written as that class's member in app/comum/gravadores/cgeracaoversoescontratos.cpp (5869's band lies between
#   ccopiadormr.cpp's and md/cversoesarquivos.cpp's rows) it scored 14 over 211 rows: the set's copy called the hinted
#   emplace (__emplace_hint_unique_key_args: tree, hint, key, value) where the target calls fn 1163, three parameters
#   and no result; and its insert (fn 5868) scored 10 over 189, the reload of the inserted node after the begin-node
#   store that strict aliasing removes. With that object built with strict aliasing (a variant object in the whole
#   link), clang kept __emplace_hint_unique_extract_key out of line instead, the emplace inlined into it (1163's
#   shape), 5868 scored 2 over 184, operands only, and 5869 91 over 284, since binaryen inlined that wrapper into its
#   one caller in our link (1163's other target callers, 5360 and 11620, are not written). So 5869 needs strict
#   aliasing, which comum/gravadores is built without (docs/reference/facts/app-flags.md F6), and a second caller of
#   the wrapper: not written, and 1163 and 5868 with it.
# - CGeracaoVersoesContratos's destructor (fn 5866, the four trees from +36 down, fns 1397 and 2859): not written; its
#   band place, after md/cversoesarquivos.cpp's rows, is not that file's.
#
# Chosen (each header marks its own): the classes' members and parameter names; that each md class holds its INI object
# as a member (a base would give the same layout; not measured); ListaHashesArquivos's name, its being a free function
# and its header; the lines of the functions with no record. One form of each was measured, none listed as the same.
#
# Roots: 227-uenux2-contratos-cmontadorhash-roots.cpp stands in for the callers not written (12098 for both GetValor,
# 5869 for CDependenciasContratos's, 5359 for 5358, 11620 for 5854, 5371 and 11587 for 5180); each stand-in names
# them. No census pair falls on a function the roots object defines (step 7's check).
W227_SRCS := src/api/hash/cmontadorhash.cpp \
    src/app/comum/gravadores/md/cdependenciascontratos.cpp src/app/comum/gravadores/md/cversoescontratos.cpp
UENUX2_SRCS += $(W227_SRCS)
# The roots read uenux2 headers, and through them ecourna's.
W227_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/227-uenux2-contratos-cmontadorhash-roots.o: $(ROOT)/src/units/227-uenux2-contratos-cmontadorhash-roots.cpp \
    $(ROOT)/src/Makefile $(ROOT)/src/units/227-uenux2-contratos-cmontadorhash.mk $(W227_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/227-uenux2-contratos-cmontadorhash-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/227-uenux2-contratos-cmontadorhash-roots.o
