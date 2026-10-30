# uenux2 simulador::CWasmImageSurfaceOps, the wasm build's api::IImageSurfaceOps, in
# src/uenux2/mock/app/simulador/wasm/cwasmscreen.cpp (+ cwasmimagesurfaceops.h), with the api::IImageSurfaceOps
# interface (src/uenux2/src/api/gui/iimagesurfaceops.h) and IImage's third slot, GetData (iimage.h):
# - ImageRect(width, height, point, anchor), slot 14 (target fn 9289), and the class's other slots of its own: Slot2 to
#   Slot7 (9365, 9362, 9356, 9348, 9339, 9333), CopyBytes (slot 8, 9328), Slot9 (9322), Slot10 (9317), FreeBytes (slot
#   11, 9307). iimagesurfaceops.h says what each body shows.
# - the base's inline defaults, emitted with the vtable: ImageSize(const IImage&), slot 13 (8998), and ImageRect from
#   bytes, an IImage and a shared IImage, slots 15 to 17 (8994, 8991, 8985).
# - std::__shared_ptr_emplace<std::vector<unsigned char>> (D2 8833, D0 8823, __on_zero_shared 5047), libc++'s code for
#   the make_shared of slots 2, 5 and 9.
# ImageSize(const std::vector<uint8_t>&), slot 12 (3493), is pending: 69-uenux2-cwasmimagesurfaceops-pending.cpp. So are
# CWasmScreen's members; no reconstructed caller stores this class's vptr yet, so the roots file keeps the vtable.
#
# The file is a choice, and the TU is not: the class shares one object with simulador::CWasmScreen. No record names
# either class's file; ledger/tu-clusters.tsv's class-convention guess puts stretches 131, 206 and 956 in a
# cwasmimagesurfaceops.cpp and 130, 132 and 205 in a cwasmscreen.cpp. Three readings say one TU:
# - data order (docs/reference/facts/link-order.md L7 item 15): CWasmScreen's vtable @1528816, this class's vtable
#   @1528980, typeinfos 1529060 (this class), 1529072 (api::IImageSurfaceOps) and 1529080 (CWasmScreen). One object's
#   data lies together, so a separate object could not put this class's between CWasmScreen's vtable and typeinfo.
# - fns 9058 and 9079, CWasmScreen's members, call 3493 directly with `this` the frame's own local (9058: f3493(l5, l5,
#   l5 + 4)), not p0 + 44. LLVM's dead-argument pass replaces an unused argument with poison at the call sites of a
#   function whose body is the one the link keeps: a strong definition in the same module. A probe of that shape, in
#   the tree's flags, prints `ptr nonnull align 4 poison` in its IR and the frame's local in its object; the same caller
#   with the callee in another TU, or inline in the class, passes this + 4.
# - the uses-1 band: this class's strong members (9365 to 9307, then 9289) run before CWasmScreen's slots (9265 to
#   9004), and the inline defaults (8998 to 8985) after them, where clang defers inline functions
#   (docs/reference/facts/reading.md R8). The band has slot 14 before slot 13 for that reason.
# So these members are in cwasmscreen.cpp, the name those stretches give the object; the name itself is the guess's.
# cwasmimagesurfaceops.h is rule 4's chosen path (how-to step 3): nothing shows whether the class head has its own
# header or sits in CWasmScreen's. A separate cwasmimagesurfaceops.cpp gives the same bytes for this unit's functions;
# it would not for 9058 and 9079, whose `this` needs the callee in their TU.
#
# Names and types, all chosen (no record, symbol or string names a member, parameter or alias): every member of
# api::IImageSurfaceOps, IImage::GetData, the IImageSurfaceSource class of slots 3, 6 and 10's parameter, the
# SharedBytes alias, the unused parameters' `int`, and the uint8_t* of slots 3, 4, 6, 7, 9 and 10, whose bodies show
# one i32 (only slots 8 and 11 show a pointer, the `new` and the free). The class names are RTTI's. The members' const
# is chosen too: no body reads this, and without const every body compiles the same.
#
# IImageSurfaceSource is a class this unit invents. What the target shows: 9362, 9339 and 9317 call [vtable+12] on the
# object itself with it as `this`, type (i32)->(i32), so the parameter is a polymorphic object, and its slot 2 and
# destructors are not shown at all. Nothing calls slots 2 to 11, so no caller gives the argument's class, and no RTTI
# class fits by role, which is a reading, not a proof. Its destructor pair is a choice: three plain slots and no
# destructor give the same object.
#
# Forms measured, by the object's disassembly against this source's (call targets masked), or by the whole link where
# it says so:
# - ImageRect: width and height as int give the same object. Cases 4 and 8 give the same object with their two
#   statements either way round, and a `default:` label or none too, and so does a named SRect returned. Cases 5 and 7
#   are not free: x first, then y, gives the target's y, then x (docs/reference/facts/codegen.md C1), and the other
#   order differs. Hence x first in every case, a choice for 4 and 8. Width and height as int, or x and y as int with
#   TPosition parameters, give the same code; both int give the target's sums with their operands swapped, `(w / -2) +
#   x` for its `x + (w / -2)`, the shape of the int arithmetic in 9058. So one side at least is TPosition, and both is
#   chosen. The two sums in locals are a choice as well: written inside the aggregate, they give the same object.
#   std::min(x, direita) and std::max(x, direita) in that operand order are the target's: swapped, one or both, the
#   object differs, and with both swapped the whole link re-points with `differs` (at +0xb4).
# - the SRect aggregate stands in for a header that is not the original's: fns 1916 and 11067 end in the same
#   four-select store run, so the real SRect probably has a normalising constructor. One that takes left, top, right
#   and bottom and applies std::min and std::max in its initializers gives this object, cmp-identical, with `return
#   SRect(x, y, x + largura, y + altura);`, and so the operand order above would live there. primitives.h is not this
#   unit's, and every landed `SRect{...}` would go through that constructor, so it stays an aggregate.
# - CopyBytes: `if (!dados.empty())`, `if (dados.size() != 0)` around the std::copy, std::copy_n, std::copy over data()
#   pointers and a guarded std::memcpy give the same object; an unguarded std::memcpy does not.
# - slots 13 and 15 to 17 defined inline in CWasmImageSurfaceOps instead of the base give the same bodies.
# - the parameter types: `const X*` for every reference parameter, void* for the uint8_t* of slots 3, 4, 6, 7, 9 and 10,
#   and const SharedBytes& read with get() in slots 4 and 7 give the same code under other symbols.
# - the class's destructor defined in the class, `virtual ~CWasmImageSurfaceOps() = default;`, gives the same object.
# Paths relative to src/uenux2; the generic uenux2 rule compiles mock/ too and depends on the source and every uenux2
# header.
CWASMIMAGESURFACEOPS_SRCS := mock/app/simulador/wasm/cwasmscreen.cpp
UENUX2_SRCS += $(CWASMIMAGESURFACEOPS_SRCS)
# ImageSize (target fn 3493) is not reconstructed: 69-uenux2-cwasmimagesurfaceops-pending.cpp gives the vtable a trapping
# body, compiled with the unit's flags
$(ROOT)/$(APP)/69-uenux2-cwasmimagesurfaceops-pending.o: $(ROOT)/src/units/69-uenux2-cwasmimagesurfaceops-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/69-uenux2-cwasmimagesurfaceops.mk $(ROOT)/src/uenux2/mock/app/simulador/wasm/cwasmimagesurfaceops.h $(ROOT)/src/uenux2/src/api/gui/iimagesurfaceops.h $(ROOT)/src/uenux2/src/api/gui/iimage.h $(ROOT)/src/uenux2/src/api/gui/primitives.h
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/69-uenux2-cwasmimagesurfaceops-pending.cpp -o $(R)
# nothing reconstructed stores the vptr yet: 69-uenux2-cwasmimagesurfaceops-roots.cpp keeps the vtable, as the
# CWasmScreen constructor inlined into fn 8302 does
$(ROOT)/$(APP)/69-uenux2-cwasmimagesurfaceops-roots.o: $(ROOT)/src/units/69-uenux2-cwasmimagesurfaceops-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/69-uenux2-cwasmimagesurfaceops.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/69-uenux2-cwasmimagesurfaceops-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/69-uenux2-cwasmimagesurfaceops-pending.o $(APP)/69-uenux2-cwasmimagesurfaceops-roots.o
