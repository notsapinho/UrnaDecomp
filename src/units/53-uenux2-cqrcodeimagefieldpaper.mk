# uenux2 api::CQRCodeImageFieldPaper's Draw (target fn 10963, vtable slot 2), which hands the paper the QR code's image,
# side and scale (api::IPaper's slot 12), and its implicit destructors (10962 and 10961, slots 0 and 1), the
# compiler's code for the class definition in src/uenux2/src/api/gui/cqrcodeimagefieldpaper.h: they free the
# std::vector of bytes of the CQRCodeImagePaper::QrcodeData member at +24, then IFormFieldBase<IPaper>'s name. The
# destructor is implicit: the deleting one holds the base-object body inlined. IFormFieldBase<IPaper>'s destructor
# (fn 11013), which binaryen merges with the other media's into one body taking the vptr (fn 1566), as the target's
# link did, is unit 39's, whose object links first. The unit also has the layout-only header of the member's type
# (src/uenux2/src/api/gui/cqrcodeimagepaper.h). No record names either header or a member of the class: the class
# header follows the class name beside the field classes of api/gui/ and the name of link-order cluster 376
# (src/uenux2/unplaced.cpp), and QrcodeData goes beside cqrcodeimagepaper.cpp, whose records name it (MontaImagem's
# return type).
# Draw (fn 10963) is the class's only member of its own, the key function, so src/uenux2/src/api/gui/
# cqrcodeimagefieldpaper.cpp (a file no record names; the name follows the class) emits the vtable and with it the
# implicit destructors. The constructor (inlined into fn 2775, not reconstructed) has no target function. The vtable
# also brings IFormField<IPaper>::GetTypeName (fn 11014, inline in api/gui/iformfield.h), which does not match yet: the
# target's is a thunk into fn 3891, the body binaryen merged from the three 18-character GetTypeName bodies, with
# api::CTextFieldBlinking's (10940) and api::CInputFieldControl<IScreen>'s (11155), neither in our link; its stub goes
# with the vtable (src/README.md "Stubs"). Paths relative to src/uenux2.
CQRCODEIMAGEFIELDPAPER_SRCS := src/api/gui/cqrcodeimagefieldpaper.cpp
UENUX2_SRCS += $(CQRCODEIMAGEFIELDPAPER_SRCS)
# nothing calls the destructors directly in the target, which reaches them through the vtable only:
# 53-uenux2-cqrcodeimagefieldpaper-roots.cpp keeps the vtable, as the constructor inlined into fn 2775 does
$(ROOT)/$(APP)/53-uenux2-cqrcodeimagefieldpaper-roots.o: $(ROOT)/src/units/53-uenux2-cqrcodeimagefieldpaper-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/53-uenux2-cqrcodeimagefieldpaper.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/53-uenux2-cqrcodeimagefieldpaper-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/53-uenux2-cqrcodeimagefieldpaper-roots.o
