# uenux2 comum::IServicoEstado<ESTADO, CONVERSOR> (src/app/comum/appinfo/servicos/iservicoestado.h) and the four classes
# derived from its instances, comum::CServicoEstadoGeral, -Vota, -Gap and -SA (servicos/cservicoestadogeral*.{h,cpp}),
# with three codes of EUeComumAppInfoError (src/app/comum/appinfo/euecomumappinfoerror.h).
#
# Matched: CServicoEstadoGeral's constructor (target fn 1941) and GetPathArquivo (11569, its vtable's slot 2), and
# CServicoEstadoGeralVota's, -Gap's and -SA's GetPathArquivo (11568, 11567, 11565), thunks of binaryen's merge 3896,
# which the three form in our link too. 3896's match line names our merge body, byn$mgfn-shared$ and the first member, a
# name our link derives and that moves with link order (docs/how-to-decompile.md step 9, "Hand edits").
#
# Evidence:
# - RTTI (ledger/classes.json): each class's only base is its own instance of comum::IServicoEstado<ESTADO, CONVERSOR>,
#   whose arguments are an estado class and its converter; ledger/vtables.json gives the four vtables as [174, 144, slot
#   2]. No vtable of the template is in the target's data: a search of the data segments for the four template
#   typeinfos' addresses (1558048, 1558104, 1558160, 1558216) finds each once, at its class's typeinfo + 8.
# - The three records (servicos/cservicoestadogeral{vota,gap,sa}.cpp, line 32, column 15) give the derived classes'
#   files, GetPathArquivo's name, `virtual`, the std::filesystem::path result and no parameter. The throws' codes are
#   what the thunks pass to 3896 (7607, 7605, 7606), with "Urna sem turno em contexto onde turno era esperado", when the
#   turn at +8 is 48 (SEM_TURNO, eurnaturno.h); else 3896 returns CPath::GetPathTrab (358) of the origin at +4 and the
#   turn, with "vota.bin", "gap.bin" or "sa.bin". 11569 returns GetPathDinamico (1082) of the origin at +4 with
#   "eg.bin".
# - 1941 stores its parameter at +4 and the vptr 1558024 (CServicoEstadoGeral's vtable + 8) and returns the object; the
#   member is written as the class's own and the constructor matches so. That the template holding it would store it
#   after the vptr (docs/reference/facts/codegen.md C1) is not measured in this shape.
# - Place: no record names CServicoEstadoGeral's file. In the data its vtable, its typeinfo and its base's (1558016,
#   1558036, 1558048) lie just before -Vota's vtable (1558056), and the four classes' run in the order base, Vota, Gap,
#   SA (vtables 1558016, 1558056, 1558112, 1558168, each derived class's record and typeinfos after its vtable); in
#   code, use band 1 (ledger/ordinals.tsv) links 11569 just before 11568, 11567 and 11565. So the class is placed in
#   servicos/ beside them (how-to step 3, rule 2) and named by rule 4; ledger/tu-clusters.tsv's label
#   app/comum/dados/cservicoestadogeral.cpp for 11569 is a class-convention guess. The sources are listed in the
#   target's order, base, Vota, Gap, SA, not their names'; no other order was linked.
#
# Scores before step 8 (pnpm wasm score against the link): 11569 8 over 83, 3896 11 over 106, 11565, 11567 and 11568 5
# over 9 each, 1941 1 over 9, all operand rows.
#
# Not written, with what each waits for:
# - The derived classes' constructors, 3787, 5812 and 11566, thunks of 3897 that pass each class's vptr. 3897 stores the
#   turn, the origin and the vptr and, when the turn is 51 (TURNO_ATUAL), builds a CServicoEstadoGeral (1941) and calls
#   3791 on it, taking the turn at +32 of the state it returns. 3791 (3956 B, its stub in api/io/asn/cfileasn.h) reads
#   the file, with CFileASN's reading inlined (a reading of its strings, "ReadFromFile de " and "O arquivo [{}] não
#   existe"), and calls 518 and 679, both no-candidate: 518 is ~CoderEnv at -Oz and 679 holds CoderEnv::decode
#   (docs/reference/facts/asn1.md A10). The headers declare the constructors with the types of the members they store.
# - The template's save, 2894 (thunks 3592, 5329, 10089, 10112), and what it calls through the table slots its thunks
#   pass: IConversorASN<E, D>::Converte, merged as 2893 (thunks 9997, 10019, 10051, 10170, which pass the records
#   iconversorasn.h:56 and the entities' typeid names), with 9843, a format-argument store whose only caller is 2893;
#   and CFileASN's writer, merged as 2892 (thunks 9985, 10008, 10040, 10168), which opens a CFile "wb" through slot 445
#   (fn 517) and calls a second merge, 2891 (thunks 9820, 9703, 9701, 9684), over CFileASN::CodeObjectFunction (9801,
#   9702, 9695, 9673, records cfileasn.h 161 and 171), with CFile's inline destructor 3564 (callers 2892 and 9538). Each
#   has landing pads, an -fexceptions TU's copies. The target calls the four saves through invoke_* only in
#   mock/app/comum/cappinfobuilder.cpp's 10243 (slot 422) and 10212 (slots 433, 436, 440); 3333 and 6039 call 3592 and
#   5329 directly. A probe object that instantiates the save for two of the classes (the path, a copy of its string, the
#   converter on the stack, Converte, then a CFileASN writer declared only), read before binaryen, which is a lead and
#   no verdict (docs/reference/facts/levels.md V4: the writer and the other merge members are not there to link), holds
#   2894's calls in its order (call_indirect, invoke_iii of the string's copy, invoke_viii, invoke_vii, then the
#   entity's, the string's and the path's destructors) and its 80-byte frame at -Oz -fexceptions -fPIC -std=c++23
#   -DNDEBUG -fno-strict-aliasing, the executable TU's flags, with the path a named local; a temporary path is destroyed
#   right after the copy, and at -O3 and -Os the copy is no invoke_iii of its own. So these wait for cfileasn.h's
#   writer, which no unit writes, and for a TU that instantiates the save for the four classes ahead of the trees'
#   copies, at those flags by the lead above.
#
# Chosen, no evidence names them: m_origem and m_turno, the template's parameter names, the paths of iservicoestado.h,
# of CServicoEstadoGeral's header and source and of the derived classes' headers, the destructor's spelling, that
# GetPathArquivo is pure in the template, the three enumerators' names, the constructors' parameter types, the lines of
# every member but the three throws, and the order of CServicoEstadoGeral's two members.
#
# Roots (206-uenux2-app-comum-appinfo-servicos-roots.cpp): two stand-ins give 1941 three call sites that read its
# result, for its five target callers (2273, 3333, 3897, 10243, 11572), none in the link; and the three derived classes'
# vtables, which only their unwritten constructors reference in the target, have their addresses taken.
# CServicoEstadoGeral's own vtable needs no root: its constructor stores it. The roots declare what they use through asm
# labels and emit no TSE code, so they compile at APP_CXXFLAGS.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
SERVICOS_SRCS := src/app/comum/appinfo/servicos/cservicoestadogeral.cpp \
                 src/app/comum/appinfo/servicos/cservicoestadogeralvota.cpp \
                 src/app/comum/appinfo/servicos/cservicoestadogeralgap.cpp \
                 src/app/comum/appinfo/servicos/cservicoestadogeralsa.cpp
UENUX2_SRCS += $(SERVICOS_SRCS)
# nothing reconstructed calls CServicoEstadoGeral's constructor or references the three derived classes' vtables yet:
# 206-uenux2-app-comum-appinfo-servicos-roots.cpp stands in for the callers and takes the vtables' addresses
$(ROOT)/$(APP)/206-uenux2-app-comum-appinfo-servicos-roots.o: $(ROOT)/src/units/206-uenux2-app-comum-appinfo-servicos-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/206-uenux2-app-comum-appinfo-servicos.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/206-uenux2-app-comum-appinfo-servicos-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/206-uenux2-app-comum-appinfo-servicos-roots.o
