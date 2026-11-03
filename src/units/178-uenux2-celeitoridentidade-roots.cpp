// Roots: keep what the unit reaches in the skeleton link the way the target reaches it. Most of its target callers are
// not reconstructed. Each function has direct callers in the target and gets two call sites here, which vary what the
// callers vary, so dead-argument elimination folds nothing in:
// - CEleitorIdentidade's constructor (fn 566): 13 direct callers, which use the returned `this`, so the stand-ins use it
//   too. Eleven are in the link (3766, 11542, 10401 and 10402, unit 91; 11410, unit 98; 2264, unit 110; 10586 and 2225,
//   unit 50; 11407, fragment 225; 10313, unit 71; 10337, unit 135), and the first five, 11407, 10313 and 10337 pass the
//   type as a constant or a column's value; the stand-ins stay for the two that wait (10425, 11411), which pass it as a
//   variable.
// - FormataIdentidade (fn 2798): callers 3616, 10420 (in the link, unit 142, which passes the type as the constant 1)
//   and 10631 (in the link, unit 104); the stand-ins stay for 3616.
// - CValidadorIdentidade::EhValida (fn 2803): callers 2225 (unit 50), 10420 (unit 142's validatitulosuspensao.cpp,
//   binaryen-inlined there), 10313 (unit 71) and 10721 (unit 277), all in the link: its stand-ins went.
// - IRegraIdentidade::EhValida (fn 3723): callers 2803 and 10627 (vota::CValidaIdentidade's slot 2, unit 278's, which
//   holds CValidadorIdentidade::TiposValidos inlined), both in the link: its stand-in went.
// - FormataIdentificador (fn 1924): callers 10586, in the link (unit 50), 11233 (comum::(anonymous
//   namespace)::SituacaoEleitor, record cgeradorrellistaeleitores.cpp:100) and 12105 (records of
//   vota::CGeraRelatorios::StartState and comum::CGeradorBUJ::GeraBUJ), which DuasFormatacoesIdentificador stands for.
// CValidadorIdentidade::Valida and IRegraIdentidade::Valida get no root: the target inlines each into its one caller (fn
// 566), and our link has that one call too. The stand-ins differ from each other and call two things or add an offset,
// so none is a target function's body. Declared through asm labels with the object's signatures (a constructor returns
// `this`), so this TU needs no uenux2 header and instantiates nothing.
extern "C" {
int r178_identidade(int, int, int) __asm__("_ZN5comum2md18CEleitorIdentidadeC1ENSt3__212basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEN7ecourna3app5dados25ETipoIdentificadorEleitorE");
void r178_formata(int, int, int) __asm__("_ZN5comum2md17FormataIdentidadeENSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEN7ecourna3app5dados25ETipoIdentificadorEleitorE");
void r178_formata_identificador(int, int) __asm__("_ZN5comum2md20FormataIdentificadorERKNS0_18CEleitorIdentidadeE");
}

namespace {

__attribute__((noinline)) int DuasIdentidades(int destino, int identificador, int tipo)
{
    return r178_identidade(destino, identificador, tipo) + r178_identidade(destino + 16, identificador + 12, tipo + 1);
}

__attribute__((noinline)) void DuasFormatacoes(int destino, int identificador, int tipo)
{
    r178_formata(destino, identificador, 1);
    r178_formata(destino + 12, identificador + 12, tipo);
}

__attribute__((noinline)) void DuasFormatacoesIdentificador(int destino, int identidade)
{
    r178_formata_identificador(destino, identidade);
    r178_formata_identificador(destino + 12, identidade + 16);
}

const void* volatile r178_sink;

struct SRoots178 {
    SRoots178()
    {
        r178_sink = reinterpret_cast<const void*>(&DuasIdentidades);
        r178_sink = reinterpret_cast<const void*>(&DuasFormatacoes);
        r178_sink = reinterpret_cast<const void*>(&DuasFormatacoesIdentificador);
    }
} roots178;

} // namespace
