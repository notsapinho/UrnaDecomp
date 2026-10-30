# uenux2 api::IInputValidation and api::COptionValidation, the class headers src/uenux2/src/api/gui/iinputvalidation.h
# and coptionvalidation.h, and the four functions the compiler emits from them: IInputValidation::isValidChar (target
# fn 12473, slot 3 of IInputValidation's own vtable @1538696 and of its four derived classes'), COptionValidation::
# isValid (target fn 4022, slot 2 of COptionValidation's vtable @1550952 and of CNumberValidation's and
# CControlValidation's, one body binaryen kept for the three), IInputValidation's destructor (target fn 12502, slot 0 of
# all five vtables: the derived classes add no data member) and COptionValidation's deleting destructor (target fn
# 2980, slot 1 of the four derived classes' vtables). Neither class has a key function in the target:
# IInputValidation's typeinfo and vtable lie among the data of vota/eleitor/comum/ctelasvota.cpp, the TU that builds a
# CNumberValidation, its typeinfo before its vtable and right after CNumberValidation's, and COptionValidation's vtable
# among the data of the TU that builds one (fn 5913). So every virtual member is inline or pure
# (docs/reference/facts/reading.md §R6), and the derived deleting destructor holds the base destructor's body (an inline
# one, §R5). 12502 and 2980 are merge thunks in the target (into 1723 and 1722, the shared bodies of RHVoice
# destructors of the same shape), and binaryen merges ours into the same two bodies. The unit is two headers and has no
# source of its own: no record names a file of either class, and the TUs that build the objects are not
# reconstructed, so the roots file below builds a COptionValidation the way fn 5913 does, which emits the vtables and
# their members, and keeps both vtables (see its header). The headers' paths (the class names in lower case, beside the
# recorded api/gui/cinputmenufield.cpp, which defines the fourth derived class CMenuValidation), the member names
# isValid and isValidChar, their const, the data member's name and the constructors' explicit are chosen; each header
# says why. Not reconstructed: CNumberValidation and CControlValidation (their slot 2 is the same body as 4022).
# CMenuValidation (10900, 10899 in cinputmenufield.cpp) is unit 84's.
# Every header the roots file includes is in src/uenux2/src/api/gui/, which the wildcard below names ($(UENUX2_HDRS) is
# set after src/Makefile reads the fragments: here it would be empty).
$(ROOT)/$(APP)/67-uenux2-iinputvalidation-roots.o: $(ROOT)/src/units/67-uenux2-iinputvalidation-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/67-uenux2-iinputvalidation.mk $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/67-uenux2-iinputvalidation-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/67-uenux2-iinputvalidation-roots.o
