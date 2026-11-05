// Roots: keep the singletons' GetInst, the destructors of their classes and the members written with them in the skeleton
// link the way the target reaches them. Each has direct callers and needs two call sites in the link, the reconstructed
// callers counted, and this file adds what the link lacks. Stand-ins and the target callers they stand for:
//   TodasAsInstancias   GetInst: fns 187, 273, 326, 407, 555, 1073, 1926, 2812, 2817 have 4 to 105 direct callers each
//   DestroiTodos        each class's destructor, beside the exit destructor in the link: fn 7787 for 5671, 5730, 5734,
//                       5773, 5792, 6548 and ~CCargos 5805, and each goes when that caller lands;
//                       ~CProcessoEleitoral 2830: 7787 (2787 and 5598 are in the link);
//                       ~CParametrosUrna 2267: 7787, beside 5792's and 9171's calls in the link;
//                       ~CDetalheConsulta 267 and ~CDetalheCandidato 242: their optionals' owners; CCargos::Reset 2269:
//                       11209, 12098, 12110 (7377, unit 197's StartState, and 5604, unit 155's written Gera, are in
//                       the link)
//   DestroiDecoradores  ~CEleitor 379, the D2 md::CEleitorDecorator's destruction calls (the decorator adds no member
//                       with a destructor, so it has no D2 of its own): 15 callers, some read its result, so this
//                       stand-in reads it (R18)
//   ConsultaTodos       GetCurrent 332, GetCurrentEleicao 2836, GetCargo 861 (12 callers), CHV::GetHorarioVerao 5745
//   ValidaEleitores     CEleitores::ValidaIdentidadesEleitor 5765: fns 6734 and 7787
//   QuantidadesAptos    CEleitores::QuantidadeAptos 2823: fn 12110 (652, 2881 and 11242 are in the link)
//   ConsultaDinamicos   CEleitorDetalhe::GetDinamico 1271: fn 7174 (2822, 2825, 6034, 10210, 10635 and 11616 are
//                       in the link)
//   s11479              comum::RespostaCorrente, which the target reaches only by table slot 1096 (fn 6652 passes it):
//                       its address is taken
//   s11478              comum::LinhaRespostaCorrente, which the target reaches only by table slot 3051 (fn 11946 passes
//                       it): its address is taken
//   LeImpedidos         CEleitores::GetEleitoresImpedidos 5767: fns 6734 and 7787
//   MontaListas         comum::MontaCaminhos 1936: fns 6734 and 7787 (5772, GetEleitoresEstaticos, is in the link)
//   LeEstaticos         CEleitores::GetEleitoresEstaticos 5772: fns 6734 and 7787
//   CarregaDetalhes     CEleitores::LoadEleitorDetalhe 5764: fns 6734 and 7787, one call without dynamic data and one
//                       with
//   vt_CEleitores       comum::CEleitores's vtable (@1559112), whose one slot is QuantidadeAptosPorAbrangencia (fn 2824):
//                       the target stores its vptr in fn 7787 alone (a constructor inlined there), which is not
//                       written; the sink goes when 7787 lands
// LocalizaEleitores, for CEleitores::LocalizaEleitor(const std::string&, ETipoIdentificadorEleitor) (fn 2264), went: its
// last target caller not in the link, fn 3616 (unit 319's), is. HabilitaEleitores, for
// CEleitores::MarcaEleitorFoiHabilitado (fn 2825), went too: its one target caller, fn 10425 (unit 142's), is in the link.
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

int d379(int) __asm__("_ZN5comum2md8CEleitorD2Ev");
void w2269(int) __asm__("_ZN5comum7CCargos5ResetEv");
int w332(int) __asm__("_ZNK5comum7CCargos10GetCurrentEv");
int w2836(int) __asm__("_ZNK5comum7CCargos17GetCurrentEleicaoEv");
int w861(int, int) __asm__("_ZNK5comum20CConfiguracaoEleicao8GetCargoEh");
int w5745(int) __asm__("_ZNK5comum3CHV15GetHorarioVeraoEv");
int d2830(int) __asm__("_ZN5comum2md18CProcessoEleitoralD2Ev");
int d5671(int) __asm__("_ZN5comum2md20CValidadorIdentidadeD1Ev");
int d5730(int) __asm__("_ZN5comum10CRespostasD1Ev");
int d5734(int) __asm__("_ZN5comum8CRdvVotaD1Ev");
int d5773(int) __asm__("_ZN5comum10CEleitoresD1Ev");
int d5792(int) __asm__("_ZN5comum20CConfiguracaoEleicaoD1Ev");
int d5805(int) __asm__("_ZN5comum7CCargosD1Ev");
int d6548(int) __asm__("_ZN4vota10CTelasVotaD1Ev");

void w5765(int, int) __asm__("_ZNK5comum10CEleitores24ValidaIdentidadesEleitorERKNS_2md17CEleitorDecoratorE");
void w2823(int, int) __asm__("_ZNK5comum10CEleitores15QuantidadeAptosEv");
int w1271(int) __asm__("_ZNK5comum15CEleitorDetalhe11GetDinamicoEv");
void s11479(int) __asm__("_ZN5comum16RespostaCorrenteEv");
void s11478(int) __asm__("_ZN5comum21LinhaRespostaCorrenteEv");
void w5767(int, int) __asm__("_ZN5comum10CEleitores21GetEleitoresImpedidosERKNSt3__26vectorINS1_12basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEENS6_IS8_EEEE");
void w1936(int, int, int) __asm__("_ZN5comum13MontaCaminhosERKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEERKNS0_6vectorIS6_NS4_IS6_EEEE");
void w5772(int, int, int) __asm__("_ZN5comum10CEleitores21GetEleitoresEstaticosERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void w5764(int, int, int, int, int, int) __asm__("_ZNK5comum10CEleitores18LoadEleitorDetalheERKNS_2md17CEleitorDecoratorERKNSt3__26vectorINS1_9CImpedidoENS5_9allocatorIS7_EEEERmPKNS1_16CEleitorDinamicoE");
extern const char vt_CEleitores[] __asm__("_ZTVN5comum10CEleitoresE");
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

// Stands for fn 12110, the target caller of CEleitores::QuantidadeAptos (fn 2823) not in the link (652, 2881 and
// 11242, unit 155's, are): one call, reading both counts the result's address receives. The call that stood for 11242
// went with it.
__attribute__((noinline)) int QuantidadesAptos(int eleitores)
{
    int quantidade[2];
    w2823(reinterpret_cast<int>(&quantidade[0]), eleitores);
    return (quantidade[0] & 0xffff) + (quantidade[1] >> 16);
}

__attribute__((noinline)) int ConsultaDinamicos(int detalhe)
{
    return w1271(detalhe + 204) * 3;
}

__attribute__((noinline)) void LeImpedidos(int resultado, int arquivos)
{
    w5767(resultado, arquivos);
    w5767(resultado + 12, arquivos + 24);
}

__attribute__((noinline)) void MontaListas(int resultado, int diretorio, int nomes)
{
    w1936(resultado, diretorio, nomes);
    w1936(resultado + 12, diretorio, nomes + 12);
}

__attribute__((noinline)) void LeEstaticos(int resultado, int eleitores, int diretorio, int outroResultado)
{
    w5772(resultado, eleitores, diretorio);
    w5772(outroResultado, eleitores, diretorio);
}

__attribute__((noinline)) void CarregaDetalhes(int resultado, int eleitores, int eleitor, int impedidos, int indice)
{
    w5764(resultado, eleitores, eleitor, impedidos, indice, 0);
    w5764(resultado + 204, eleitores, eleitor + 108, impedidos, indice, eleitor + 216);
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
        singletons_sink = reinterpret_cast<const void*>(&QuantidadesAptos);
        singletons_sink = reinterpret_cast<const void*>(&ConsultaDinamicos);
        singletons_sink = reinterpret_cast<const void*>(&s11479);
        singletons_sink = reinterpret_cast<const void*>(&s11478);
        singletons_sink = reinterpret_cast<const void*>(&LeImpedidos);
        singletons_sink = reinterpret_cast<const void*>(&MontaListas);
        singletons_sink = reinterpret_cast<const void*>(&LeEstaticos);
        singletons_sink = reinterpret_cast<const void*>(&CarregaDetalhes);
        singletons_sink = vt_CEleitores;
    }
} singletons_roots;

} // namespace
