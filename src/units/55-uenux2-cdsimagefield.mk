# uenux2 api::CDSImageField::~CDSImageField: the D2 (target fn 2778, vtable @1578860 slot 0), the D0 (fn 11095, slot 1)
# and their thunks at -44 in the IObserver<SharedIImage>-in-CDSImageField vtable @1578912 (fns 11096, 11094), with
# GetTypeName (fn 11091, slot 7), in src/api/gui/cdsimagefield.cpp, the file the record of the constructor's throw
# (line 29, column 15) names; the constructor is written there, out of line, with that throw (the 4923 enumerator of
# api/gui/eueguierror.h) on its line, and has no target function: binaryen inlines it into its one caller, fn 502,
# behind a second prologue, as the target holds it. The class (RTTI: a
# vmi_class of api::CImageField at +0 and api::IObserver<std::shared_ptr<api::IImage>> at +44) is declared in
# cdsimagefield.h beside it (the header's path is chosen), and the two observer templates in src/api/pattern/iobserver.h
# and iobservable.h: no record names their files, so the directory is chosen (the api pattern templates', beside
# cpolysingleton.h) and the file names are the classes'. The member names of all three are chosen too: only the layout
# (CDSImageField 56 B, IObservable's value +4, observers +12, mutex +24) reaches the bytes, with Detach, the
# erase-remove under the mutex that the D2 inlines (comum::CInfoMTLCD's D2, fn 5902, inlines the same). The destructor
# is defined out of line, so it is the class's key function and the vtable is emitted here: the D0 is D2(this);
# free(this) with the D2's result dropped (the D1 alias's call), not free(D2(this)) (in the class) nor the D2 inlined
# (implicit). GetTypeName's place (out of line, after Update) is chosen: the target's function order (Update and its
# thunk before GetTypeName) fits it and an in-class GetTypeName alike; the out-of-line form, which CTextField's and
# CImageField's GetTypeName take, is the one measured. Paths relative to src/uenux2; the generic uenux2 rule depends
# on the source and every uenux2 header.
CDSIMAGEFIELD_SRCS := src/api/gui/cdsimagefield.cpp
UENUX2_SRCS += $(CDSIMAGEFIELD_SRCS)
# Update (target fn 11093, slot 10) and its thunk (fn 11092) pass a copy of the image by value to CImageField::SetImage.
# The unit has no roots file: the constructor's one caller, fn 502 (api::CFormBuilder::AddStatusHeader, unit 31), is in
# the link, and the constructor's vptr stores keep the vtables the way the target keeps them.
