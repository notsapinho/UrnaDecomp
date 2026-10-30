# uenux2 api::CMenuValidation::isValidChar (target fn 10899, slot 3 of the vtable @1583300) in
# src/uenux2/src/api/gui/cinputmenufield.cpp, the file the class's records name, with the class header
# api/gui/cinputmenufield.h (its path chosen), which reads the text at +24 of IInputField<IScreen> through
# api/gui/cinputfield.h and iinputfield.h, unit 92's. The body inlines IInputValidation::isValidChar (the memchr) and then builds the text plus the character:
# `text + std::string(1, c)`, libc++'s operator+(const string&, string&&), whose insert(0, ...) is fn 499 and whose
# move the words at +16 show. isValid is the key function, so the vtable and the implicit deleting destructor (one body
# with the other validations', 2980) are emitted in the pending object until it lands; slot 0 is the base's destructor.
# Forms that give 10899's object code, by the function's disassembly in a compile with the unit's flags: an early `return
# false` before the call, an `if` around it, and `m_validChars.find(c) == std::string::npos` for the base's member. So
# those are choices. Forms that do not: the text in a named local (another frame), `text + c`, `text + digito` with a named
# string, `texto += c`. The roots' make_shared also brings the control block's D0 and D2 (10891, 10892), which match from
# there until fn 3675 lands.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CINPUTMENUFIELD_SRCS := src/api/gui/cinputmenufield.cpp
UENUX2_SRCS += $(CINPUTMENUFIELD_SRCS)
# isValid (10900) is not reconstructed: 84-uenux2-cinputmenufield-pending.cpp gives the vtable a trapping body, compiled
# with the unit's flags. Its headers are all in api/gui/ ($(UENUX2_HDRS) is still empty when the fragments are read)
$(ROOT)/$(APP)/84-uenux2-cinputmenufield-pending.o: $(ROOT)/src/units/84-uenux2-cinputmenufield-pending.cpp $(ROOT)/src/units/84-uenux2-cinputmenufield.mk $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/84-uenux2-cinputmenufield-pending.cpp -o $(R)
# fn 3675, the vtable's only user in the target, is not reconstructed: the roots file does its make_shared
$(ROOT)/$(APP)/84-uenux2-cinputmenufield-roots.o: $(ROOT)/src/units/84-uenux2-cinputmenufield-roots.cpp $(ROOT)/src/units/84-uenux2-cinputmenufield.mk $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/84-uenux2-cinputmenufield-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/84-uenux2-cinputmenufield-pending.o $(APP)/84-uenux2-cinputmenufield-roots.o
