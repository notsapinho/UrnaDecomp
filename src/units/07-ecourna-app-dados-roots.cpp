// Roots: keep the app/dados units' functions in the skeleton link the way the target keeps them (their callers
// - the dados/asn converters, comum, vota - are not reconstructed yet). Target call shapes (ledger/callgraph.tsv + the
// elem segment): the CRegistroIdentificacaoEleitor ctors/getters, CSerialMidia's ctor, CFederacao's ctor and
// CConfiguracaoMunicipios' ctor are reached through invoke_* (table slots 6901 6900 6892 6896 6733 6697 6850) and
// address-taken here; CErroLeituraBiometria's ctor (fn 2668) has direct callers (9066, 11616) and is address-taken too.
// CBaseType<ETipoIdentificadorEleitor, 1, 3, 40>'s ctor (fn 2666) is not rooted: its two direct callers in the target,
// 3939 and 9116, are in the link. CBaseType<..., 34>'s ctor is not rooted either: the target inlines it into fn 2668,
// its only caller. Declared through asm labels with the wasm-level
// signatures, so this TU instantiates nothing (its own COMDAT copy would compete with tiposbasicos.o's).
extern "C" {
int rdados_registro_1(int, int) __asm__("_ZN7ecourna3app5dados29CRegistroIdentificacaoEleitorC2ENSt3__210shared_ptrINS1_21IIdentificadorEleitorEEE");
int rdados_registro_2(int, int, int) __asm__("_ZN7ecourna3app5dados29CRegistroIdentificacaoEleitorC2ENSt3__210shared_ptrINS1_21IIdentificadorEleitorEEES6_");
void rdados_registro_hab(int, int) __asm__("_ZNK7ecourna3app5dados29CRegistroIdentificacaoEleitor27GetIdentificadorHabilitacaoEv");
void rdados_registro_pri(int, int) __asm__("_ZNK7ecourna3app5dados29CRegistroIdentificacaoEleitor25GetIdentificadorPrincipalEv");
int rdados_serial(int, int) __asm__("_ZN7ecourna3app5dados12CSerialMidiaC2ERKNSt3__212basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEE");
int rdados_erro_biometria(int, int) __asm__("_ZN7ecourna3app5dados21CErroLeituraBiometriaC2ENS1_21EErroLeituraBiometriaE");
// a library helper the target keeps out of line because other (unreconstructed) callers share it: std::regex's
// (const char*, flags) ctor (fn 2416, 4 uses)
int rdados_regex_ctor(int, int, int) __asm__("_ZNSt3__211basic_regexIcNS_12regex_traitsIcEEEC2B8ne210108EPKcNS_15regex_constants18syntax_option_typeE");
}

namespace {

void* volatile rdados_sink;

__attribute__((noinline)) int UsaBibliotecas(int a)
{
    return rdados_regex_ctor(a, a + 40, 16);
}

struct SRdadosRoots {
    SRdadosRoots()
    {
        rdados_sink = reinterpret_cast<void*>(&rdados_registro_1);
        rdados_sink = reinterpret_cast<void*>(&rdados_registro_2);
        rdados_sink = reinterpret_cast<void*>(&rdados_registro_hab);
        rdados_sink = reinterpret_cast<void*>(&rdados_registro_pri);
        rdados_sink = reinterpret_cast<void*>(&rdados_serial);
        rdados_sink = reinterpret_cast<void*>(&rdados_erro_biometria);
        rdados_sink = reinterpret_cast<void*>(&UsaBibliotecas);
    }
} rdados_roots;

} // namespace
