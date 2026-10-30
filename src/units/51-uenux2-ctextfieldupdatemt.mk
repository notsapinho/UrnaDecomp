# uenux2 api::CTextFieldUpdateMT::~CTextFieldUpdateMT: the base-object destructor (target fn 5411, slot 0 of the vtable
# @1590476) and the deleting one (fn 10549, slot 1), with Show and Hide (fns 10546 and 10545, slots 3 and 4), in
# src/uenux2/src/app/vota/operador/comum/ctextfieldupdatemt.cpp. No record names the class's files, so the path is
# chosen: the file name is the class's in lower case (the label of clusters 309 and 757 in ledger/tu-clusters.tsv,
# class-convention), and the directory is the one the recorded stretches beside those clusters give
# (docs/how-to-decompile.md step 3, rule 2). The D0 calls the D2 (13 B), so the destructor is defined out of line and
# the class's D0, Draw, Show and Hide (cluster 309, band 1) and D2 (cluster 757, band 2) are strong functions of the
# class's own object, not linkonce copies. Cluster 309 starts right after the last functions of
# app/vota/operador/comum/cinformacaothreadoperador.cpp (stretch 310, records) and comes before
# app/vota/operador/confirmaidentidade/ccontrolareconhecimento.cpp (304); cluster 757 sits between
# api/util/itimerscheduler.cpp (759) and the same confirmaidentidade file (756). api/gui's own fields
# (ctextfieldupdate.cpp, ctextfieldmt.cpp, ...) link in other runs (band 1 stretches 366-400, band 2 768-772), so the
# namespace's directory, api/gui/, is not where the object was; app/vota/operador/comum/, after
# cinformacaothreadoperador.cpp in name order, fits both clusters. No record puts any other api:: class's member in an
# app/ file, so this is the reconstruction's reading of the link order, not a record's. The header (ctextfieldupdatemt.h beside it, chosen) has the layout the constructor (inlined into
# fn 652), Draw (fn 10548) and the destructor give; the member names are chosen and the timer at +48 is a
# std::shared_ptr to a forward-declared api::ITimer, whose Start and Stop (chosen names, api/util/itimer.h) Show and
# Hide call. The destructor is user-declared and defined out of line, declared first among the class's virtual
# members, so it is the key function and ctextfieldupdatemt.o emits the vtable, the D2 and the D0; GetTypeName (slot 7,
# fn 11051) is IFormField<IScreenMT>'s inline one. The constructor is not reconstructed: it calls
# api::ITimerScheduler::GetInst (fn 1259), which has no body of ours, and binaryen inlined it into fn 652, so it has no
# target function and no stub. Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every
# uenux2 header.
CTEXTFIELDUPDATEMT_SRCS := src/app/vota/operador/comum/ctextfieldupdatemt.cpp
UENUX2_SRCS += $(CTEXTFIELDUPDATEMT_SRCS)
# Draw (10548) is not reconstructed: 51-uenux2-ctextfieldupdatemt-pending.cpp gives the vtable a trapping body,
# compiled with the unit's flags; it reads the class header and the api/gui headers it includes
$(ROOT)/$(APP)/51-uenux2-ctextfieldupdatemt-pending.o: $(ROOT)/src/units/51-uenux2-ctextfieldupdatemt-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/51-uenux2-ctextfieldupdatemt.mk $(ROOT)/src/uenux2/src/app/vota/operador/comum/ctextfieldupdatemt.h $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/51-uenux2-ctextfieldupdatemt-pending.cpp -o $(R)
# the constructor, the vtable's only user in the target, is not reconstructed: 51-uenux2-ctextfieldupdatemt-roots.cpp
# takes the vtable's address, which keeps the destructors, Show and Hide in the table as the target has them
$(ROOT)/$(APP)/51-uenux2-ctextfieldupdatemt-roots.o: $(ROOT)/src/units/51-uenux2-ctextfieldupdatemt-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/51-uenux2-ctextfieldupdatemt.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/51-uenux2-ctextfieldupdatemt-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/51-uenux2-ctextfieldupdatemt-pending.o $(APP)/51-uenux2-ctextfieldupdatemt-roots.o
