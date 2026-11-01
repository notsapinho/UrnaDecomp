# uenux2 api::IObservable<std::shared_ptr<api::IImage>>'s destructors: target fn 11651, the D2 in slot 0 of the vtable
# @1551944, and fn 11650, the deleting one in slot 1. Both are code src/uenux2/src/api/pattern/iobservable.h (unit 55's
# header) defines: the class's only virtual member is `virtual ~IObservable() = default;` in the class, so it has no key
# function, and the D0 holds the D2's body and then frees this, the shape of an inline destructor (docs/how-to-decompile.md
# step 5). The D2 destroys the mutex at +24, the vector at +12 and the shared_ptr at +4, the layout iobservable.h
# already had.
#
# No source and no companion of its own (src/units/README.md "What a fragment holds" item 2): in the target only
# binaryen's shared destructor body of api::BatteryIconDataSource<Horizontal> and <Vertical> (fn 6049, over the thunks
# 3837 and 5510) stores the vptr, and unit 164's roots object emits those destructors, with IObservable's vtable, D2 and
# D0, at UENUX2_CXXFLAGS. Both match from that object. Until unit 164, this fragment's roots file built an IObservable in
# a function the link dropped and kept the vtable, a stand-in for 6049, which went when 6049 came into the link.
