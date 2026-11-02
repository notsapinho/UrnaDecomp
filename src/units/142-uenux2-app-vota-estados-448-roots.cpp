// Roots: keep the vtables of the five classes of src/units/142-uenux2-app-vota-estados-448.mk, and with them their slots
// (target fns 448, 765, 1718, 11794, 10594, 10490, 10426, 10421 and the pending traps), in the skeleton link the way
// the target keeps them.
//
// Each vtable is referenced in the target only by its class's constructor, inlined into the function that creates the
// singleton (fns 11797, 10500 and 10415, none reconstructed). Taking the vtables' addresses keeps every slot.
// vota::CJustificativaEfetuada's GetInst (fn 2747), which holds its constructor inlined, is in the link (its caller
// 10587, unit 152, calls it twice), so no sink keeps that vtable.
// vota::CMostraEleitorVotando's vtable needs no root: its GetInst (fn 1150) is written and stores it, and our link keeps
// that GetInst through two callers, CPerguntaEleitorVotando::ProcessKey and CSuspensaoAutomaticaEleitor::ProcessInput
// (unit 152's sources). The other direct callers of the destructor (fn 448: the resets of the four creators above and fn
// 763, the static std::unique_ptr's destructors' body) are not stood in for: it is in the table, so binaryen keeps it out
// of line with the callers our link gives it, the deleting destructor and fn 1150's reset.
//
// comum::CEleitorDadosHabilitacao's constructor (target fn 2733, in cmostraeleitorvotando.cpp) has one target caller,
// vota::CMostraEleitorVotando::ProcessKey (fn 10425, slot 6, pending: its records are SalvaHabilitacaoEleitor's, which
// it holds inlined). It calls the constructor four times, with the kinds 1, 2, 2 and 0 and every other argument a local,
// and keeps the returned `this` each time (`local.set` after the call). DuasHabilitacoes stands in for it: two call sites
// that vary each argument and read both results, so binaryen neither inlines the constructor, nor folds an argument,
// nor drops the result (with the results dropped, the constructor lost its i32 result: one row against the target's
// 2733); it adds offsets, so it is no target function's body.
//
// Declared through asm labels (the constructor with its object's signature: it returns `this`), so this TU needs no
// uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char curnainspecionada_vt[] __asm__("_ZTVN4vota17CUrnaInspecionadaE");
extern const char cpedeanonascimentosembiometria_vt[] __asm__("_ZTVN4vota30CPedeAnoNascimentoSemBiometriaE");
extern const char cperguntacodigosuspensao_vt[] __asm__("_ZTVN4vota24CPerguntaCodigoSuspensaoE");
int r142_habilitacao(int, int, int, int, int, int) __asm__("_ZN5comum24CEleitorDadosHabilitacaoC1ERKNS_2md18CEleitorIdentidadeENS0_16ETipoHabilitacaoEiRKNS1_34CEleitorDadosHabilitacaoBiometricaERKN7ecourna3app5dados24CApresentacaoFotoEleitorE");
}

namespace {

// stands for fn 10425
__attribute__((noinline)) int DuasHabilitacoes(int destino, int identidade, int audio, int biometria, int foto)
{
    return r142_habilitacao(destino, identidade, 1, audio, biometria, foto) +
           r142_habilitacao(destino + 64, identidade + 16, 2, audio + 1, biometria + 32, foto + 8);
}

const void* volatile estados448_sink;

struct SEstados448Roots {
    SEstados448Roots()
    {
        estados448_sink = curnainspecionada_vt;
        estados448_sink = cpedeanonascimentosembiometria_vt;
        estados448_sink = cperguntacodigosuspensao_vt;
        estados448_sink = reinterpret_cast<const void*>(&DuasHabilitacoes);
    }
} estados448_roots;

} // namespace
