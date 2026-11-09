// Roots of unit 441 (src/units/441-uenux2-ctelasvota-bases.mk): a caller stand-in for fn 7787, the target function
// that holds vota::CTelasVota::CreateInst and the class's constructor inlined after the vote's data load (not
// written). It calls CreateInst once, as 7787 does, so that binaryen inlines it into the stand-in as into 7787, with
// the constructor and every screen the constructor builds (each one caller, in unit 110's ctelasvota.cpp: the
// fourteen post screens over this unit's anonymous-namespace builders, target fns 6602, 6603, 6605, 6641, 6652, 6660
// and 6671, among them, src/units/443-uenux2-ctelasvota-construtor.mk). It goes when 7787 is in the link.
//
// Declared through an asm label with the object's signature, so this TU needs no uenux2 header and instantiates
// nothing; compiled with APP_CXXFLAGS.
extern "C" {
void w441_cria_inst() __asm__("_ZN4vota10CTelasVota10CreateInstEv");
}

namespace {

// Stands for fn 7787's one call of CreateInst (at its body +0x1674f, behind CreateInst's own 16-byte prologue).
__attribute__((noinline)) int CriaTelasVota(int valor)
{
    w441_cria_inst();
    return valor * 441;
}

const void* volatile w441_sink;

struct S441Roots {
    S441Roots() { w441_sink = reinterpret_cast<const void*>(&CriaTelasVota); }
} w441_roots;

} // namespace
