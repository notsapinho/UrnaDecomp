// Roots: keep the vtables of the five classes of src/units/142-uenux2-app-vota-estados-448.mk, and with them their slots
// (target fns 448, 765, 1718, 11794, 10594, 10490, 10426, 10421 and the pending traps), in the skeleton link the way
// the target keeps them.
//
// Each vtable is referenced in the target only by its class's constructor, inlined into the function that creates the
// singleton (fns 11797, 2747, 10500 and 10415, none reconstructed). Taking the vtables' addresses keeps every slot.
// vota::CMostraEleitorVotando's vtable needs no root: its GetInst (fn 1150) is written and stores it, and our link keeps
// that GetInst through two callers, CPerguntaEleitorVotando::ProcessKey and CSuspensaoAutomaticaEleitor::ProcessInput
// (unit 152's sources). The other direct callers of the destructor (fn 448: the resets of the four creators above and fn
// 763, the static std::unique_ptr's destructors' body) are not stood in for: it is in the table, so binaryen keeps it out
// of line with the callers our link gives it, the deleting destructor and fn 1150's reset.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char curnainspecionada_vt[] __asm__("_ZTVN4vota17CUrnaInspecionadaE");
extern const char cjustificativaefetuada_vt[] __asm__("_ZTVN4vota22CJustificativaEfetuadaE");
extern const char cpedeanonascimentosembiometria_vt[] __asm__("_ZTVN4vota30CPedeAnoNascimentoSemBiometriaE");
extern const char cperguntacodigosuspensao_vt[] __asm__("_ZTVN4vota24CPerguntaCodigoSuspensaoE");
}

namespace {

const void* volatile estados448_sink;

struct SEstados448Roots {
    SEstados448Roots()
    {
        estados448_sink = curnainspecionada_vt;
        estados448_sink = cjustificativaefetuada_vt;
        estados448_sink = cpedeanonascimentosembiometria_vt;
        estados448_sink = cperguntacodigosuspensao_vt;
    }
} estados448_roots;

} // namespace
