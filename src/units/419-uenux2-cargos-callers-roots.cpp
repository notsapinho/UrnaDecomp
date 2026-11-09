// Roots: stand-ins for fn 7787, the one target caller of comum::CargosPorEleicao (fn 5735, unit 13's crdvvota.cpp) and
// of comum::CConfiguracaoEleicao::GetTodosCargos (fn 5790, unit 88's cconfiguracaoeleicao.cpp), neither of which is in
// the target's table or exports. 7787 calls each twice (`call 5735` and `call 5790` each count 2 in its piece) and is
// not written, and nothing else in our link calls 5735, so its stand-in calls it twice (src/units/README.md
// "Companion files": the callee's only target caller calls it more than once); with one call binaryen inlines the
// callee into it (src/units/419-uenux2-cargos-callers.mk has the measurement). 7787's second call of 5790 (+0x1c18c)
// is in CTelasVota's constructor, which unit 443 writes (linked through unit 441's roots): the stand-in's call for it
// went, the link without it moving no row, and one call stays for the first (+0x11aaf). Each goes when 7787 is in the
// link. Declared through asm labels with the objects' signatures and address-taken from a static
// constructor; the file includes no header, so it emits no TSE code and no match comes from this object.
extern "C" {
int w419_187() __asm__("_ZN5comum20CConfiguracaoEleicao7GetInstEv");
void w419_5735(int) __asm__("_ZN5comum16CargosPorEleicaoEv");
void w419_5790(int, int) __asm__("_ZNK5comum20CConfiguracaoEleicao14GetTodosCargosEv");
}

namespace {

const void* volatile w419_sink;

// Stands for 7787, which calls comum::CargosPorEleicao (fn 5735) twice: both calls stand for it.
__attribute__((noinline)) void CargosPorEleicaoDuas(int destino)
{
    w419_5735(destino);
    w419_5735(destino + 12);
}

// Stands for 7787's first call of CConfiguracaoEleicao::GetTodosCargos (fn 5790), on GetInst()'s result (fn 187), as
// this call passes it.
__attribute__((noinline)) void TodosCargosPrimeira(int destino)
{
    w419_5790(destino + 16, w419_187());
}

struct S419Roots {
    S419Roots()
    {
        w419_sink = reinterpret_cast<const void*>(&CargosPorEleicaoDuas);
        w419_sink = reinterpret_cast<const void*>(&TodosCargosPrimeira);
    }
} w419_roots;

} // namespace
