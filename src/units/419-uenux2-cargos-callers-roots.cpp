// Roots: stand-ins for fn 7787, the one target caller of comum::CargosPorEleicao (fn 5735, unit 13's crdvvota.cpp) and
// of comum::CConfiguracaoEleicao::GetTodosCargos (fn 5790, unit 88's cconfiguracaoeleicao.cpp), neither of which is in
// the target's table or exports. 7787 calls each twice (`call 5735` and `call 5790` each count 2 in its piece) and is
// not written, and nothing else in our link calls them, so each stand-in calls its callee twice
// (src/units/README.md "Companion files": the callee's only target caller calls it more than once); with one call
// binaryen inlines the callee into it (src/units/419-uenux2-cargos-callers.mk has the measurement). Each goes when 7787
// is in the link. Declared through asm labels with the objects' signatures and address-taken from a static
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

// Stands for 7787, which calls CConfiguracaoEleicao::GetTodosCargos (fn 5790) twice, each time on GetInst()'s result
// (fn 187), as these calls pass it: both calls stand for it.
__attribute__((noinline)) void TodosCargosDuas(int destino)
{
    w419_5790(destino, w419_187());
    w419_5790(destino + 16, w419_187());
}

struct S419Roots {
    S419Roots()
    {
        w419_sink = reinterpret_cast<const void*>(&CargosPorEleicaoDuas);
        w419_sink = reinterpret_cast<const void*>(&TodosCargosDuas);
    }
} w419_roots;

} // namespace
