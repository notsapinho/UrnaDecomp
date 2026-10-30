# uenux2 api::CImageField ctor (target fn 2242) in src/uenux2/src/api/gui/cimagefield.cpp, the class header
# cimagefield.h and the IImage / SharedIImage / EAnchorPoint declarations it takes (iimage.h); paths relative to
# src/uenux2. No record names the ctor: it is the class's because it stores CImageField's vptr over the IFormFieldBase
# members, and the file is the class's (record cimagefield.cpp:52:12 of Rect). Its parameter types are taken from the
# records of the CImageFieldUpdate and CDSImageField ctors (const SPoint &, const SharedIImage &, EAnchorPoint); they
# and the parameter and member names are not in the bytes. No record names the header of IImage or EAnchorPoint, so
# iimage.h is chosen (see its header comment). Move (one of the five functions of target fn 2241, see
# 27-uenux2-ctextfield.mk, which lists the forms) is in cimagefield.cpp, below Rect's line 52, a choice; api::CDSImageField
# inherits it.
UENUX2_SRCS += src/api/gui/cimagefield.cpp
# the class's members not reconstructed yet (trapping bodies the vtable needs; GetTypeName is the key function, so the
# vtable and the implicit destructors, target fns 11099 and 11098, are emitted there; see the file header), and two
# callers of the ctor (29-uenux2-cimagefield-roots.cpp, two make_shared<CImageField> as the target's callers do) so
# binaryen neither inlines it nor folds its anchor argument; the control block they instantiate,
# __shared_ptr_emplace<CImageField> (target fns 12639, 12640), matches from the roots object until its callers land
$(ROOT)/$(APP)/29-uenux2-cimagefield-pending.o: $(ROOT)/src/units/29-uenux2-cimagefield-pending.cpp $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/29-uenux2-cimagefield-pending.cpp -o $(R)
$(ROOT)/$(APP)/29-uenux2-cimagefield-roots.o: $(ROOT)/src/units/29-uenux2-cimagefield-roots.cpp $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/29-uenux2-cimagefield-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/29-uenux2-cimagefield-pending.o $(APP)/29-uenux2-cimagefield-roots.o
