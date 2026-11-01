// Roots: keep fragment 172's converters in the skeleton link the way the target keeps them. A converter's slots have no
// direct caller: the target reaches them through the vtable, whose vptr the functions that build the converter store.
// Where those are not written, the sink holds the vtable, the reference the target has:
// - comum::asn::CConversorEstadoGeralVota, vtable @1568960 (slots 2 and 3: fns 11390, 11391); fns 5329 and 7787 store
//   its vptr.
// Declared through an asm label, so this TU needs no uenux2 or ASN.1 header and instantiates nothing.
extern "C" {
extern const char w172_estadogeralvota_vt[] __asm__("_ZTVN5comum3asn25CConversorEstadoGeralVotaE");
}

namespace {

const void* volatile w172_sink;

struct SRoots172 {
    SRoots172()
    {
        w172_sink = w172_estadogeralvota_vt;
    }
} w172_roots;

} // namespace
