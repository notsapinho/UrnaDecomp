// Roots of unit 173. api::CGrayedFramedText's vtable (@1578744) is stored only by its constructor, fn 5535, which is not
// written; the target reaches MaskText (fn 5534) through that vtable and by one direct call, from
// CMaskedTextField<CGrayedFramedText>::Draw (fn 12708). The vtable's address is the reference the target has; with the
// table holding 5534, binaryen keeps it out of line beside its one direct caller (src/units/README.md "Companion files").
extern "C" {
extern const char w173_vt_grayed[] __asm__("_ZTVN3api17CGrayedFramedTextE");
}

namespace {

const void* volatile w173_sink;

struct SW173Roots {
    SW173Roots() { w173_sink = w173_vt_grayed; }
} w173_roots;

} // namespace
