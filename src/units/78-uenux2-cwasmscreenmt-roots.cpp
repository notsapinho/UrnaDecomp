// DRAFT
extern "C" {
extern const char cwasmscreenmt_vt[] __asm__("_ZTVN9simulador13CWasmScreenMTE");
extern const char cbeepfieldmt_vt[] __asm__("_ZTVN3api12CBeepFieldMTE");
extern const char cbuzzfieldmt_vt[] __asm__("_ZTVN3api12CBuzzFieldMTE");
extern const char cclockfieldmt_vt[] __asm__("_ZTVN3api13CClockFieldMTE");
int string_assign_fill(int, int, int) __asm__("_ZNSt3__212basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6assignEmc");
}

namespace {

const void* volatile cwasmscreenmt_sink;

struct SCWasmScreenMTRoots {
    SCWasmScreenMTRoots()
    {
        cwasmscreenmt_sink = cwasmscreenmt_vt;
        cwasmscreenmt_sink = cbeepfieldmt_vt;
        cwasmscreenmt_sink = cbuzzfieldmt_vt;
        cwasmscreenmt_sink = cclockfieldmt_vt;
        cwasmscreenmt_sink = reinterpret_cast<void*>(&string_assign_fill);
    }
} cwasmscreenmt_roots;

} // namespace
