// Roots of unit 441 (src/units/441-uenux2-ctelasvota-bases.mk): a caller stand-in for fn 7787, the target function
// that holds vota::CTelasVota::CreateInst and the class's constructor inlined (not written), the one target caller of
// the fourteen post screens this unit adds to unit 110's ctelasvota.cpp. 7787 holds each screen behind a prologue of its
// own, inlined by binaryen into its one caller: so the stand-in calls each once, and binaryen inlines each into it as it
// does into 7787. The screens are the only callers of the seven anonymous-namespace builders (target fns 6602, 6603,
// 6605, 6641, 6652, 6660 and 6671, two screens each), which a roots file cannot name: with the screens in the link they
// have their call sites and stay out of line. It goes when 7787, or the constructor that 7787 holds, is in the link.
//
// Declared through asm labels with the objects' signatures (the std::shared_ptr result through its address first), so
// this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
void w441_legenda(void* resultado, const void* cargo)
    __asm__("_ZN4vota10CTelasVota19CriaTelaVotoLegendaERKN5comum2md6CCargoE");
void w441_conferencia_legenda(void* resultado, const void* cargo)
    __asm__("_ZN4vota10CTelasVota30CriaTelaConferenciaVotoLegendaERKN5comum2md6CCargoE");
void w441_inexistente(void* resultado, const void* cargo)
    __asm__("_ZN4vota10CTelasVota28CriaTelaCandidatoInexistenteERKN5comum2md6CCargoE");
void w441_conferencia_inexistente(void* resultado, const void* cargo)
    __asm__("_ZN4vota10CTelasVota39CriaTelaConferenciaCandidatoInexistenteERKN5comum2md6CCargoE");
void w441_inapto(void* resultado, const void* cargo)
    __asm__("_ZN4vota10CTelasVota23CriaTelaCandidatoInaptoERKN5comum2md6CCargoE");
void w441_conferencia_inapto(void* resultado, const void* cargo)
    __asm__("_ZN4vota10CTelasVota34CriaTelaConferenciaCandidatoInaptoERKN5comum2md6CCargoE");
void w441_completa_com1(void* resultado, const void* cargo)
    __asm__("_ZN4vota10CTelasVota29CriaTelaCompletaCandidatoCom1ERKN5comum2md6CCargoE");
void w441_conferencia_com1(void* resultado, const void* cargo)
    __asm__("_ZN4vota10CTelasVota32CriaTelaConferenciaCandidatoCom1ERKN5comum2md6CCargoE");
void w441_completa_com2(void* resultado, const void* cargo)
    __asm__("_ZN4vota10CTelasVota29CriaTelaCompletaCandidatoCom2ERKN5comum2md6CCargoE");
void w441_conferencia_com2(void* resultado, const void* cargo)
    __asm__("_ZN4vota10CTelasVota32CriaTelaConferenciaCandidatoCom2ERKN5comum2md6CCargoE");
void w441_completa_consulta(void* resultado, const void* cargo)
    __asm__("_ZN4vota10CTelasVota24CriaTelaCompletaConsultaERKN5comum2md6CCargoE");
void w441_conferencia_consulta(void* resultado, const void* cargo)
    __asm__("_ZN4vota10CTelasVota27CriaTelaConferenciaConsultaERKN5comum2md6CCargoE");
void w441_branco_consulta(void* resultado, const void* cargo)
    __asm__("_ZN4vota10CTelasVota26CriaTelaVotoBrancoConsultaERKN5comum2md6CCargoE");
void w441_conferencia_branco_consulta(void* resultado, const void* cargo)
    __asm__("_ZN4vota10CTelasVota37CriaTelaConferenciaVotoBrancoConsultaERKN5comum2md6CCargoE");
}

namespace {

// Stands for fn 7787's one call of each screen, in 7787's order (the screens' prologues at body +0x1d602 to +0x232c9:
// the proportional post's six, the Com1 and Com2 posts' two each, the consult's four), each over its post.
__attribute__((noinline)) int TelasCargos(char* telas, const char* proporcional, const char* com1, const char* com2,
                                          const char* consulta)
{
    w441_legenda(telas, proporcional);
    w441_conferencia_legenda(telas + 8, proporcional);
    w441_inexistente(telas + 16, proporcional);
    w441_conferencia_inexistente(telas + 24, proporcional);
    w441_inapto(telas + 32, proporcional);
    w441_conferencia_inapto(telas + 40, proporcional);
    w441_completa_com1(telas + 48, com1);
    w441_conferencia_com1(telas + 56, com1);
    w441_completa_com2(telas + 64, com2);
    w441_conferencia_com2(telas + 72, com2);
    w441_completa_consulta(telas + 80, consulta);
    w441_conferencia_consulta(telas + 88, consulta);
    w441_branco_consulta(telas + 96, consulta);
    w441_conferencia_branco_consulta(telas + 104, consulta);
    return telas[441 % 7] + consulta[1];
}

const void* volatile w441_sink;

struct S441Roots {
    S441Roots() { w441_sink = reinterpret_cast<const void*>(&TelasCargos); }
} w441_roots;

} // namespace
