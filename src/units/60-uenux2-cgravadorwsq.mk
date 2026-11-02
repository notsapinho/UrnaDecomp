# uenux2 comum::CGravadorWSQ's implicit destructors (target fns 11576 and 11575, vtable @1557292 slots 0 and 1) and
# comum::IResultado's destructor (fn 12090, slot 0 of IResultado's vtable @1541020), the compiler's code for the class
# definitions in src/app/comum/gravadores/cgravadorwsq.h and iresultado.h. CGravadorWSQ is final (its destructors store
# no vptr of its own) and destroys its two std::string members at +72 and +56; IGravador's destructor adds nothing
# (an empty body, no member) and IResultado's, defined in the class, stores its vptr and destroys the file name at +20.
# The destructor is not declared (implicit): the deleting one holds the base-object body inlined, as does the libc++
# deleter of the std::shared_ptr<IGravador> (fn 12092); one defined in the class gives the same bytes, one defined out
# of line a call (docs/reference/facts/reading.md R5). IResultado's destructor is defined in the class, since
# CGravadorWSQ's inlines it (out of line in iresultado.cpp, measured in a try link, it is a call there and 11576 does
# not match); it is emitted with IResultado's vtable, which the inlined vptr store keeps. Fn 12090's copy in the link is
# unit 122's iresultado.cpp.o's, which emits the vtable with IResultado's constructor, the same code: uenux2's sources
# link ahead of every companion object.
# With it: the comum::IGravador and comum::IResultado interfaces (igravador.h and iresultado.h beside it),
# EExtensaoArquivoResultado (iresultado.h), EUrnaFase (app/comum/eurnafase.h), ESavdArquivoUE (app/comum/iinterfacesavd.h,
# beside ESavdAplic) and the layouts of api::CDateTime and api::CDate (src/api/util/cdatetime.h and cdate.h, beside
# their records' cdatetime.cpp and cdate.cpp). The headers go beside the files the classes' records name
# (cgravadorwsq.cpp, iresultado.cpp); no record names igravador.h, which goes with them, a choice. No evidence names
# IResultado's two pure slots or IGravador's slots 2 to 6: they are named after their slot (SlotN), and every member
# name is chosen (the headers say what each holds).
# The unit has no source of its own: CGravadorWSQ's members are unit 122's, in cgravadorwsq.cpp, which unit 122 compiles.
# Slot2 (fn 11579), the class's key function, is written there with Slot6 and Slot3 (fns 11578, 11577, which binaryen
# merges into fn 6041), so cgravadorwsq.cpp.o emits the vtable and the implicit destructors now, where this unit's
# pending object did until those three were written (src/units/122-uenux2-app-comum-gravadores.mk has them), under the
# same symbols, and they still match. IGravador's key function Slot2, and Slot3, Slot4, Slot5 and Slot6 (fns 11632,
# 11630, 11634, 11633, 11631), are unit 122's too, in iresultado.cpp, whose object emits IGravador's vtable and
# typeinfo, which CGravadorWSQ's typeinfo names. Paths relative to src/uenux2.
# nothing calls the destructors directly in the target, which reaches them through the vtable only:
# 60-uenux2-cgravadorwsq-roots.cpp keeps the vtable, as the constructor's vptr store in fn 12098's call does
$(ROOT)/$(APP)/60-uenux2-cgravadorwsq-roots.o: $(ROOT)/src/units/60-uenux2-cgravadorwsq-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/60-uenux2-cgravadorwsq.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/60-uenux2-cgravadorwsq-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/60-uenux2-cgravadorwsq-roots.o
