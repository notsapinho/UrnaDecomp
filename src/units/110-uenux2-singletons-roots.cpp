// Roots: keep the singletons' GetInst, the destructors of their classes and the members written with them in the skeleton
// link the way the target reaches them. Each has direct callers and needs two call sites in the link, the reconstructed
// callers counted, and this file adds what the link lacks. Stand-ins and the target callers they stand for:
//   TodasAsInstancias   GetInst: fns 187, 273, 326, 407, 555, 1073, 1926, 2812, 2817 have 4 to 105 direct callers each
//   DestroiTodos        each class's destructor, beside the exit destructor in the link: fn 2787 for 5598, fn 7787 for
//                       5671, 5730, 5734, 5773, 5792, 6548 and ~CCargos 5805, and each goes when that caller lands;
//                       ~CProcessoEleitoral 2830: 2787, 5598, 7787;
//                       ~CParametrosUrna 2267: 7787, beside 5792's and 9171's calls in the link;
//                       ~CDetalheConsulta 267 and ~CDetalheCandidato 242: their optionals' owners; CCargos::Reset 2269:
//                       5604, 7377, 11209, 12098, 12110
//   DestroiDecoradores  ~CEleitorDecorator 379: 15 callers, some read its result, so this stand-in reads it (R18)
//   ConsultaTodos       GetCurrent 332, GetCurrentEleicao 2836, GetCargo 861 (12 callers), CHV::GetHorarioVerao 5745
//   ValidaEleitores     CEleitores::ValidaIdentidadesEleitor 5765: fns 6734 and 7787
//   HabilitaEleitores   CEleitores::MarcaEleitorFoiHabilitado 2825: fn 10425
//   ConsultaDinamicos   CEleitorDetalhe::GetDinamico 1271: fns 2822, 6034, 7174, 10635 and 11616 (2825 and 10210 are in the
//                       link)
//   LocalizaEleitores   CEleitores::LocalizaEleitor(const std::string&, ETipoIdentificadorEleitor) 2264: fns 3616, 5385,
//                       10631, 10789 and 10790
//   t11526 to t11529    the four CEleitorDado*::Text, which the target reaches only by table slot (fn 5401 passes all
//                       four): their addresses are taken
//   s11479              comum::RespostaCorrente, which the target reaches only by table slot 1096 (fn 6652 passes it):
//                       its address is taken
// 273, 332 and 407 hold table slots 84, 86 and 108, so their addresses are taken. A destructor returns `this` in the object;
// DestroiTodos drops it, which lets binaryen remove the result as the target's did. Bodies differ from every target
// function's. Declared through asm labels with the object's signatures, so this TU instantiates nothing.
extern "C" {
int w187(void) __asm__("_ZN5comum20CConfiguracaoEleicao7GetInstEv");
int w273(void) __asm__("_ZN5comum7CCargos7GetInstEv");
int w326(void) __asm__("_ZN5comum10CEleitores7GetInstEv");
int w407(void) __asm__("_ZN4vota10CTelasVota7GetInstEv");
int w555(void) __asm__("_ZN5comum8CRdvVota7GetInstEv");
int w1073(void) __asm__("_ZN5comum3CPE7GetInstEv");
int w1926(void) __asm__("_ZN5comum2md20CValidadorIdentidade7GetInstEv");
int w2812(void) __asm__("_ZN5comum10CRespostas7GetInstEv");
int w2817(void) __asm__("_ZN5comum3CHV7GetInstEv");

int d267(int) __asm__("_ZN5comum2md16CDetalheConsultaD2Ev");
int d242(int) __asm__("_ZN5comum2md17CDetalheCandidatoD2Ev");
int d2267(int) __asm__("_ZN7ecourna3app5dados15CParametrosUrnaD2Ev");

int d379(int) __asm__("_ZN5comum2md17CEleitorDecoratorD2Ev");
void w2269(int) __asm__("_ZN5comum7CCargos5ResetEv");
int w332(int) __asm__("_ZNK5comum7CCargos10GetCurrentEv");
int w2836(int) __asm__("_ZNK5comum7CCargos17GetCurrentEleicaoEv");
int w861(int, int) __asm__("_ZNK5comum20CConfiguracaoEleicao8GetCargoEh");
int w5745(int) __asm__("_ZNK5comum3CHV15GetHorarioVeraoEv");
int d2830(int) __asm__("_ZN5comum2md18CProcessoEleitoralD2Ev");
int d5598(int) __asm__("_ZN5comum3CPED1Ev");
int d5671(int) __asm__("_ZN5comum2md20CValidadorIdentidadeD1Ev");
int d5730(int) __asm__("_ZN5comum10CRespostasD1Ev");
int d5734(int) __asm__("_ZN5comum8CRdvVotaD1Ev");
int d5773(int) __asm__("_ZN5comum10CEleitoresD1Ev");
int d5792(int) __asm__("_ZN5comum20CConfiguracaoEleicaoD1Ev");
int d5805(int) __asm__("_ZN5comum7CCargosD1Ev");
int d6548(int) __asm__("_ZN4vota10CTelasVotaD1Ev");

void w5765(int, int) __asm__("_ZNK5comum10CEleitores24ValidaIdentidadesEleitorERKNS_2md17CEleitorDecoratorE");
void t11529(int, int) __asm__("_ZN5comum24CEleitorDadoNomeParaUrna4TextERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void t11528(int, int) __asm__("_ZN5comum22CEleitorDadoSequencial4TextERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void t11527(int, int) __asm__("_ZN5comum17CEleitorDadoSecao4TextERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void t11526(int) __asm__("_ZN5comum15CEleitorDadoTTE4TextEv");
void w2825(int, int) __asm__("_ZN5comum10CEleitores25MarcaEleitorFoiHabilitadoERKNS_24CEleitorDadosHabilitacaoE");
int w1271(int) __asm__("_ZNK5comum15CEleitorDetalhe11GetDinamicoEv");
void s11479(int) __asm__("_ZN5comum16RespostaCorrenteEv");
int w2264(int, int, int) __asm__("_ZN5comum10CEleitores15LocalizaEleitorERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEN7ecourna3app5dados25ETipoIdentificadorEleitorE");
}

namespace {

__attribute__((noinline)) int TodasAsInstancias()
{
    return (w187() ^ w187()) + (w273() ^ w273() * 3) + (w326() ^ w326() * 5) + (w407() ^ w407() * 7) +
           (w555() ^ w555() * 9) + (w1073() ^ w1073() * 11) + (w1926() ^ w1926() * 13) + (w2812() ^ w2812() * 15) +
           (w2817() ^ w2817() * 17);
}

__attribute__((noinline)) void DestroiTodos(int p)
{
    d5598(p);
    d5671(p + 4);
    d5730(p + 8);
    d5734(p + 12);
    d5773(p + 16);
    d5792(p + 20);
    d6548(p + 24);
    d2830(p + 28);
    d2267(p + 32);
    d267(p + 36);
    d242(p + 40);
    w2269(p + 44);
    d5805(p + 48);
}

__attribute__((noinline)) int ConsultaTodos(int cargos, int configuracao, int hv)
{
    return (w332(cargos) ^ w332(cargos + 28) * 3) + (w2836(cargos) ^ w2836(cargos + 28) * 5) +
           (w861(configuracao, 1) ^ w861(configuracao, 2) * 7) + (w5745(hv) ^ w5745(hv + 28) * 9);
}

__attribute__((noinline)) int DestroiDecoradores(int p)
{
    return d379(p) + d379(p + 108) * 3;
}

__attribute__((noinline)) void ValidaEleitores(int eleitores, int eleitor)
{
    w5765(eleitores, eleitor);
    w5765(eleitores, eleitor + 108);
}

__attribute__((noinline)) void HabilitaEleitores(int eleitores, int dados)
{
    w2825(eleitores, dados);
    w2825(eleitores, dados + 64);
}

__attribute__((noinline)) int ConsultaDinamicos(int detalhe)
{
    return w1271(detalhe) + w1271(detalhe + 204) * 3;
}

__attribute__((noinline)) int LocalizaEleitores(int eleitores, int identificador)
{
    return w2264(eleitores, identificador, 1) + w2264(eleitores, identificador + 12, 3) * 5;
}

const void* volatile singletons_sink;

struct SSingletonsRoots {
    SSingletonsRoots()
    {
        singletons_sink = reinterpret_cast<const void*>(&TodasAsInstancias);
        singletons_sink = reinterpret_cast<const void*>(&DestroiTodos);
        singletons_sink = reinterpret_cast<const void*>(&ConsultaTodos);
        singletons_sink = reinterpret_cast<const void*>(&DestroiDecoradores);
        singletons_sink = reinterpret_cast<const void*>(&w273);
        singletons_sink = reinterpret_cast<const void*>(&w332);
        singletons_sink = reinterpret_cast<const void*>(&w407);
        singletons_sink = reinterpret_cast<const void*>(&ValidaEleitores);
        singletons_sink = reinterpret_cast<const void*>(&t11529);
        singletons_sink = reinterpret_cast<const void*>(&t11528);
        singletons_sink = reinterpret_cast<const void*>(&t11527);
        singletons_sink = reinterpret_cast<const void*>(&t11526);
        singletons_sink = reinterpret_cast<const void*>(&HabilitaEleitores);
        singletons_sink = reinterpret_cast<const void*>(&ConsultaDinamicos);
        singletons_sink = reinterpret_cast<const void*>(&s11479);
        singletons_sink = reinterpret_cast<const void*>(&LocalizaEleitores);
    }
} singletons_roots;

} // namespace
