// Roots: keep vota::CEleitorVotando's functions in the skeleton link the way the target keeps them.
// - GetInst (fn 3229) has three direct callers in the target, fns 7428, 7481 and 11754, of which 7428 (unit 150) and
//   11754 (unit 97) are reconstructed: Obtem stands for 7481, two call sites. GetInst holds the constructor inlined, whose vptr store
//   is the target's reference to the class's vtable, and so keeps every slot.
// - RegistraVoto (fn 4471) has two direct callers in the target, fns 7428 and 11754, each calling it right after
//   GetInst, both reconstructed (units 150 and 97): no stand-in.
// - AdicionaVoto (fn 4192) and the five CLogVota::LogaVoto* members (fns 3272, 4546, 4542, 4541 and 4537) have two
//   direct callers in the target each, RegistraVoto and suspenderEleitor (fn 4442), which makes RegistraVoto's calls;
//   FinalizaEleitor (fn 4454) has two too, NeedChangeState (fn 7352) and suspenderEleitor. All are in the link: no
//   stand-in.
// - comum::md::CEleitorDecorator::GetAbrangencia (fn 3721) has three direct callers in the target: fn 5761, not
//   written, and fn 7377 (StartState), which holds GetCurrentAbrangenciaEleitor inlined, and CEleitores' slot 0 (fn
//   2824, unit 110's), both in the link. Abrange stands for fn 5761.
// - comum::CCargos::OrdenaPorImpressao (fn 3782) has three direct callers in the target, fns 5604, 12098 and 12110,
//   none written: Imprime stands for them, two call sites.
// - The std::map<SCargoInfo, CVotos> copy of comum::md::CVotosCargos::InsereCedula (held by fn 4454) calls
//   __emplace_hint_unique_key_args (fn 5681), which calls __find_equal (fn 3251). 5681's other target caller is
//   fn 11349 (comum::asn::CConversorEleicoesVota::DoDesconverte), 3251's are fns 2386 (vota::CTelasCargo's
//   constructor) and 3266, none written: Converte stands for 11349 and Procura for 2386 and 3266.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
char* w197_inst() __asm__("_ZN4vota15CEleitorVotando7GetInstEv");
int w197_abrangencia(const void* eleitor, const void* uf, unsigned int municipio) __asm__(
    "_ZNK5comum2md17CEleitorDecorator14GetAbrangenciaERKNSt3__212basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEj");
void w197_ordena_impressao(void* cargos) __asm__("_ZN5comum7CCargos18OrdenaPorImpressaoEv");
void w197_emplace_hint(void* resultado, void* mapa, const void* dica, const void* chave, const void* valor) __asm__(
    "_ZNSt3__26__treeINS_12__value_typeIN5comum2md12CVotosCargos10SCargoInfoENS3_6CVotosEEENS_19__map_val"
    "ue_compareIS5_NS_4pairIKS5_S6_EENS_4lessIS5_EELb1EEENS_9allocatorISB_EEE30__emplace_hint_unique_key_"
    "argsIS5_JRKSB_EEENS9_INS_15__tree_iteratorIS7_PNS_11__tree_nodeIS7_PvEElEEbEENS_21__tree_const_itera"
    "torIS7_SP_lEERKT_DpOT0_");
int w197_find_equal(void* mapa, const void* dica, void* pai, void* auxiliar, const void* chave) __asm__(
    "_ZNSt3__26__treeINS_12__value_typeIN5comum2md12CVotosCargos10SCargoInfoENS3_6CVotosEEENS_19__map_val"
    "ue_compareIS5_NS_4pairIKS5_S6_EENS_4lessIS5_EELb1EEENS_9allocatorISB_EEE12__find_equalIS5_EERPNS_16_"
    "_tree_node_baseIPvEENS_21__tree_const_iteratorIS7_PNS_11__tree_nodeIS7_SK_EElEERPNS_15__tree_end_nod"
    "eISM_EESN_RKT_");
}

namespace {

const void* volatile celeitorvotando_sink;

// stands for fn 7481 (7428 and 11754 are in the link)
__attribute__((noinline)) int Obtem(int vezes)
{
    const char* primeiro = w197_inst();
    const char* segundo = w197_inst();
    return primeiro[vezes] - segundo[3];
}

// stands for fn 5761
__attribute__((noinline)) int Abrange(const char* registro, const char* eleitores)
{
    return w197_abrangencia(registro + 32, eleitores + 32, eleitores[44] + 197u);
}

// stands for fns 5604, 12098 and 12110
__attribute__((noinline)) void Imprime(char* cargos, int vezes)
{
    w197_ordena_impressao(cargos);
    if (vezes > 1) {
        w197_ordena_impressao(cargos);
    }
}

// stands for fn 11349
__attribute__((noinline)) void Converte(char* mapa, const char* no)
{
    char resultado[8];
    w197_emplace_hint(resultado, mapa, mapa + 4, no + 16, no + 16);
    celeitorvotando_sink = resultado[4] ? mapa : no;
}

// stands for fns 2386 and 3266
__attribute__((noinline)) int Procura(char* mapa, const char* chave)
{
    void* pai = nullptr;
    void* auxiliar = nullptr;
    return w197_find_equal(mapa, mapa + 8, &pai, &auxiliar, chave + 1) + 3266;
}

struct SCEleitorVotandoRoots {
    SCEleitorVotandoRoots()
    {
        celeitorvotando_sink = reinterpret_cast<const void*>(&Obtem);
        celeitorvotando_sink = reinterpret_cast<const void*>(&Abrange);
        celeitorvotando_sink = reinterpret_cast<const void*>(&Imprime);
        celeitorvotando_sink = reinterpret_cast<const void*>(&Converte);
        celeitorvotando_sink = reinterpret_cast<const void*>(&Procura);
    }
} celeitorvotando_roots;

} // namespace
