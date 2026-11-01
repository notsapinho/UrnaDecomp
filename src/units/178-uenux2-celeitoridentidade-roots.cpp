// Roots: keep what the unit reaches in the skeleton link the way the target reaches it. None of its target callers is
// reconstructed. Each function has direct callers in the target and gets two call sites here, which vary what the
// callers vary, so dead-argument elimination folds nothing in:
// - CEleitorIdentidade's constructor (fn 566): 13 direct callers, which use the returned `this`, so the stand-ins use it
//   too. Three are in the link (3766 and 11542, unit 91; 11410, unit 98) and pass the type as a constant or a column's
//   value; the stand-ins stay for the ten that wait (2225, 2264, 10313, 10337, 10401, 10402, 10425, 10586, 11407, 11411),
//   which pass it as a variable.
// - FormataIdentidade (fn 2798): callers 3616, 10420 and 10631, which pass the type as a constant (10420, 1) or a
//   variable.
// - CValidadorIdentidade::EhValida (fn 2803): callers 2225, 10313, 10420 and 10721.
// - IRegraIdentidade::EhValida (fn 3723): callers 2803, in the link, and 10627, vota::CValidaIdentidade's slot 2, which
//   one stand-in stands for.
// CValidadorIdentidade::Valida and IRegraIdentidade::Valida get no root: the target inlines each into its one caller (fn
// 566), and our link has that one call too. The stand-ins differ from each other and call two things or add an offset,
// so none is a target function's body. Declared through asm labels with the object's signatures (a constructor returns
// `this`), so this TU needs no uenux2 header and instantiates nothing.
extern "C" {
int r178_identidade(int, int, int) __asm__("_ZN5comum2md18CEleitorIdentidadeC1ENSt3__212basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEN7ecourna3app5dados25ETipoIdentificadorEleitorE");
void r178_formata(int, int, int) __asm__("_ZN5comum2md17FormataIdentidadeENSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEN7ecourna3app5dados25ETipoIdentificadorEleitorE");
int r178_validador_eh_valida(int, int, int) __asm__("_ZNK5comum2md20CValidadorIdentidade8EhValidaEN7ecourna3app5dados25ETipoIdentificadorEleitorERKNSt3__212basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEE");
int r178_regra_eh_valida(int, int) __asm__("_ZNK5comum2md16IRegraIdentidade8EhValidaERKNSt3__212basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE");
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

__attribute__((noinline)) int DuasValidacoes(int validador, int tipo, int numero)
{
    return r178_validador_eh_valida(validador, tipo, numero) * 2 + r178_validador_eh_valida(validador, tipo + 1, numero + 12);
}

__attribute__((noinline)) int ValidaRegra(int regra, int numero)
{
    return r178_regra_eh_valida(regra, numero + 8) + 3;
}

const void* volatile r178_sink;

struct SRoots178 {
    SRoots178()
    {
        r178_sink = reinterpret_cast<const void*>(&DuasIdentidades);
        r178_sink = reinterpret_cast<const void*>(&DuasFormatacoes);
        r178_sink = reinterpret_cast<const void*>(&DuasValidacoes);
        r178_sink = reinterpret_cast<const void*>(&ValidaRegra);
    }
} roots178;

} // namespace
