# uenux2 api::CMenuValidation::isValidChar (target fn 10899, slot 3 of the vtable @1583300) in
# src/uenux2/src/api/gui/cinputmenufield.cpp, the file the class's records name, with the class header
# api/gui/cinputmenufield.h (its path chosen), which reads the text at +24 of IInputField<IScreen> through
# api/gui/cinputfield.h and iinputfield.h, unit 92's. The body inlines IInputValidation::isValidChar (the memchr) and then builds the text plus the character:
# `text + std::string(1, c)`, libc++'s operator+(const string&, string&&), whose insert(0, ...) is fn 499 and whose
# move the words at +16 show. isValid (10900) is the key function, so cinputmenufield.cpp emits the vtable and the implicit
# deleting destructor (one body with the other validations', 2980); slot 0 is the base's destructor. It holds
# matchesExactly and matchesPartially, the records' at 198:5 and 210:5: the first inlined by clang, in its frame, the second
# by binaryen, with its second stack prologue. Each searches with std::find_if and tests the iterator: the target tests
# `it != end` after the loop. std::any_of scored 63 over 326 rows, and a for loop that returns differs in 19 lines; an
# if on `it == end` around the beep gives the same object code. The prefix test is rfind(text, 0) == 0: its min of the two
# sizes and its reverse search are in the body, and starts_with and compare differ in 184 and 183 lines. What the two helpers read
# of the menu is CMenuItem's +65 and +68 and the list at +140, cinputmenufield.h has the head; its names are chosen.
# Forms that give 10899's object code, by the function's disassembly in a compile with the unit's flags: an early `return
# false` before the call, an `if` around it, and `m_validChars.find(c) == std::string::npos` for the base's member. So
# those are choices. Forms that do not: the text in a named local (another frame), `text + c`, `text + digito` with a named
# string, `texto += c`. The roots' make_shared also brings the control block's D0 and D2 (10891, 10892), which match from
# there until fn 3675 lands.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CINPUTMENUFIELD_SRCS := src/api/gui/cinputmenufield.cpp
UENUX2_SRCS += $(CINPUTMENUFIELD_SRCS)
# fn 3675, the vtable's only user in the target, is not reconstructed: the roots file does its make_shared
$(ROOT)/$(APP)/84-uenux2-cinputmenufield-roots.o: $(ROOT)/src/units/84-uenux2-cinputmenufield-roots.cpp $(ROOT)/src/units/84-uenux2-cinputmenufield.mk $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/84-uenux2-cinputmenufield-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/84-uenux2-cinputmenufield-roots.o
