// Roots: keep vota::CControladorRegistraMesariosVota's vtable, the reference the target has: fn 7160 (not written) stores
// its vptr when it builds the object. That keeps every slot, and with them vota::CLogVota::GetInst (fn 184), which the
// slots call. Nothing else here: every other function of the unit has its callers in the unit.
namespace {

extern "C" const char w119_vtable[] __asm__("_ZTVN4vota32CControladorRegistraMesariosVotaE");

const void* volatile w119_sink;

struct SW119Roots {
    SW119Roots()
    {
        w119_sink = w119_vtable;
    }
} w119_roots;

} // namespace
