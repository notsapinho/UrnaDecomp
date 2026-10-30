// Roots: keep unit 81's device classes in the skeleton link, reached the way the target reaches them. Every member of
// the five classes is reached through its vtable only (none has a direct caller: each `fn` readout says `uses 0`). The
// one reference to each vtable is a vptr store: fn 8302, simulador's init, for CWasmInputKbd, CWasmInputMT, CWasmNullSound
// and CWasmSystemDateTime, and fn 1155, ISystemDateTime::GetInst, for CSystemDateTime; neither is reconstructed. So this
// file takes each vtable's address, the reference those stores give, which keeps every slot; no constructor is called,
// and none has a function of its own in the target. Declared through asm labels, so this TU needs no uenux2 header
// and instantiates nothing.
extern const char cwasminputkbd_vt[] __asm__("_ZTVN9simulador13CWasmInputKbdE");
extern const char cwasminputmt_vt[] __asm__("_ZTVN9simulador12CWasmInputMTE");
extern const char cwasmnullsound_vt[] __asm__("_ZTVN9simulador14CWasmNullSoundE");
extern const char cwasmsystemdatetime_vt[] __asm__("_ZTVN9simulador19CWasmSystemDateTimeE");
extern const char csystemdatetime_vt[] __asm__("_ZTVN3api15CSystemDateTimeE");

namespace {

const void* volatile device_sink;

struct SDeviceRoots {
    SDeviceRoots()
    {
        device_sink = cwasminputkbd_vt;
        device_sink = cwasminputmt_vt;
        device_sink = cwasmnullsound_vt;
        device_sink = cwasmsystemdatetime_vt;
        device_sink = csystemdatetime_vt;
    }
} device_roots;

} // namespace
