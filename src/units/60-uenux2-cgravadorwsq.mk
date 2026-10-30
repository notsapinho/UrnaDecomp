# uenux2 comum::CGravadorWSQ's implicit destructors (target fns 11576 and 11575, vtable @1557292 slots 0 and 1) and
# comum::IResultado's destructor (fn 12090, slot 0 of IResultado's vtable @1541020), the compiler's code for the class
# definitions in src/app/comum/gravadores/cgravadorwsq.h and iresultado.h. CGravadorWSQ is final (its destructors store
# no vptr of its own) and destroys its two std::string members at +72 and +56; IGravador's destructor adds nothing
# (an empty body, no member) and IResultado's, defined in the class, stores its vptr and destroys the file name at +20.
# The destructor is not declared (implicit): the deleting one holds the base-object body inlined, as does the libc++
# deleter of the std::shared_ptr<IGravador> (fn 12092); one defined in the class gives the same bytes, one defined out
# of line a call (docs/reference/facts/reading.md R5). IResultado's destructor is defined in the class, since
# CGravadorWSQ's inlines it (out of line in iresultado.cpp, measured in a try link, it is a call there and 11576 does
# not match); it is emitted with IResultado's vtable, which the inlined vptr store keeps.
# With it: the comum::IGravador and comum::IResultado interfaces (igravador.h and iresultado.h beside it),
# EExtensaoArquivoResultado (iresultado.h), EUrnaFase (app/comum/eurnafase.h), ESavdArquivoUE (app/comum/iinterfacesavd.h,
# beside ESavdAplic) and the layouts of api::CDateTime and api::CDate (src/api/util/cdatetime.h and cdate.h, beside
# their records' cdatetime.cpp and cdate.cpp). The headers go beside the files the classes' records name
# (cgravadorwsq.cpp, iresultado.cpp); no record names igravador.h, which goes with them, a choice. No evidence names
# IResultado's two pure slots or IGravador's slots 2 to 6: they are named after their slot (SlotN), and every member
# name is chosen (the headers say what each holds).
# The unit has no source of its own yet: CGravadorWSQ's Slot2 (its key function), Slot3 and Slot6 are pending, so the
# vtable and with it the implicit destructors are emitted in the pending object (as unit 26's are); they move to
# cgravadorwsq.o when Slot2 moves there. The file's other functions keep their stubs in the stub-only
# cgravadorwsq.cpp: the constructor (fn 3796, with ValidaTipoBiometria inlined, record line 73) and fn 5821 (records
# of GetCaminhoCorretoInternal/External, lines 175 and 192). Paths relative to src/uenux2.
# CGravadorWSQ's Slot2, Slot3 and Slot6 (fns 11579, 11577, 11578) and IGravador's five members (fns 11632, 11630,
# 11634, 11633, 11631, which IGravador's typeinfo needs) are not reconstructed:
# 60-uenux2-cgravadorwsq-pending.cpp defines them with trapping bodies, compiled with the unit's flags, and its header
# names each with its target function. Its prerequisites are every header of both trees, as the generic rules' are
# ($(UENUX2_HDRS) is still empty when the fragments are read).
$(ROOT)/$(APP)/60-uenux2-cgravadorwsq-pending.o: $(ROOT)/src/units/60-uenux2-cgravadorwsq-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/60-uenux2-cgravadorwsq.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/60-uenux2-cgravadorwsq-pending.cpp -o $(R)
# nothing calls the destructors directly in the target, which reaches them through the vtable only:
# 60-uenux2-cgravadorwsq-roots.cpp keeps the vtable, as the constructor's vptr store in fn 12098's call does
$(ROOT)/$(APP)/60-uenux2-cgravadorwsq-roots.o: $(ROOT)/src/units/60-uenux2-cgravadorwsq-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/60-uenux2-cgravadorwsq.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/60-uenux2-cgravadorwsq-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/60-uenux2-cgravadorwsq-pending.o $(APP)/60-uenux2-cgravadorwsq-roots.o
