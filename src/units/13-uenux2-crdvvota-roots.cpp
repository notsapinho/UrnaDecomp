// Roots: keep comum::CRdvVota's members in the skeleton link the way the target keeps them. The target reaches the
// class's slots through its vtable (@1560164), whose vptr store sits in CreateInst (record crdvvota.cpp:92, inlined into
// fn 7787, not written), so the vtable's address stands in for that store and keeps every slot; the
// md::CVotosEleicoesVota totals slots 1 and 3 to 10 call have that slot as their one caller, and wasm-opt inlines them
// into it, as in the target. CRdvPosicionadorVota::Posicao (target fn 11496) is kept the same way: its vptr store sits in
// CreateInst too. CVoto::operator<=> is not rooted: its only caller is Posicao, which wasm-opt inlines it into.
// The stand-ins below give the md members their target callers' call sites, none of which is written:
// - w13_comparecimento calls md::CVotosEleicoesVota::Comparecimento (target fn 5639), standing for its target caller
//   1269 (not written; it takes the largest attendance over the elections fn 5791 returns, read on the object at +20 of
//   its parameter, CRdvVota's m_votos by its offset); CRdvVota's slot 2 (fn 11492) is the other call site.
// - w13_cria and w13_desconverte call md::CVotosCargos' and md::CVotosEleicoesVota's constructors (fns 5643, 5640),
//   standing for their two target callers, 7787 (CreateInst) and 11349 (CConversorEleicoesVota::DoDesconverte, trapped
//   in fragment 140's -pending.cpp).
// - w13_desconverte_rdv and w13_confere call md::CVotosEleicoesVota::Compativel (fn 5638), standing for its two target
//   callers, CRdvVota's Desconverte and Confere (fns 11487, 11486, trapped in this unit's -pending.cpp).
// - w13_voto calls md::CVoto's constructor (fn 2256), standing for its target callers 4442, 4454 and 4471;
//   comum::asn::CConversorVoto::DoDesconverte (fn 11354) is the other call site.
// - w13_escolhas calls md::CVotosCargos::QuantidadeEscolhas (fn 5642) twice, as its one target caller, 4454, does.
// - w13_nulo calls the static md::CVoto::EhNulo (fn 5645), standing for its target caller 11514; CVoto::EhNulo() const
//   (fn 11316) is the other call site.
// Declared through asm labels with the wasm-level signatures (a constructor returns this); compiled as uenux2 code.
extern "C" {
int w13_comparecimento_alvo(int, int) __asm__("_ZNK5comum2md18CVotosEleicoesVota14ComparecimentoEj");
int w13_votoscargos(void*, void*) __asm__(
    "_ZN5comum2md12CVotosCargosC1ENSt3__23mapINS1_10SCargoInfoENS0_6CVotosENS2_4lessIS4_EENS2_9allocatorINS2_4pairIKS4_S5_EEEEEE");
int w13_votoseleicoes(void*, void*) __asm__(
    "_ZN5comum2md18CVotosEleicoesVotaC1ENSt3__23mapIjNS0_12CVotosCargosENS2_4lessIjEENS2_9allocatorINS2_4pairIKjS4_EEEEEE");
int w13_compativel(const void*, const void*) __asm__("_ZNK5comum2md18CVotosEleicoesVota10CompativelERKS1_");
int w13_cvoto(void*, int, const void*) __asm__(
    "_ZN5comum2md5CVotoC1ENS1_5ETipoERKNSt3__212basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEE");
int w13_quantidade_escolhas(const void*) __asm__("_ZNK5comum2md12CVotosCargos18QuantidadeEscolhasEv");
int w13_eh_nulo(int) __asm__("_ZN5comum2md5CVoto6EhNuloENS1_5ETipoE");
}
extern const char w13_rdvvota_vt[] __asm__("_ZTVN5comum8CRdvVotaE");
extern const char w11496_vt[] __asm__("_ZTVN5comum20CRdvPosicionadorVotaE");

namespace {

__attribute__((noinline)) int w13_comparecimento(char* rdv, int eleicao)
{
    return w13_comparecimento_alvo(reinterpret_cast<int>(rdv + 20), eleicao + 1) * 7;
}

__attribute__((noinline)) int w13_cria(char* destino, char* mapas)
{
    w13_votoseleicoes(destino, mapas + 12);
    return w13_votoscargos(destino + 24, mapas) + 3;
}

__attribute__((noinline)) int w13_desconverte(char* destino, char* mapas)
{
    w13_votoseleicoes(destino + 4, mapas + 36);
    return w13_votoscargos(destino + 28, mapas + 48) * 5;
}

__attribute__((noinline)) int w13_desconverte_rdv(const char* rdv, const char* outro)
{
    return w13_compativel(rdv + 20, outro) + 9;
}

__attribute__((noinline)) int w13_confere(const char* rdv, const char* outro)
{
    return w13_compativel(rdv + 20, outro + 8) * 11;
}

__attribute__((noinline)) int w13_voto(char* destino, int tipo, const char* numero)
{
    return w13_cvoto(destino + 16, tipo ^ 1, numero) - 13;
}

__attribute__((noinline)) int w13_escolhas(const char* votos, const char* outros)
{
    return w13_quantidade_escolhas(votos) * 3 + w13_quantidade_escolhas(outros + 12);
}

__attribute__((noinline)) int w13_nulo(const int* tipos)
{
    return w13_eh_nulo(tipos[2]) + 2;
}

void* volatile w13_sink;

struct SW13Roots {
    SW13Roots()
    {
        w13_sink = const_cast<char*>(w13_rdvvota_vt);
        w13_sink = const_cast<char*>(w11496_vt);
        w13_sink = reinterpret_cast<void*>(&w13_comparecimento);
        w13_sink = reinterpret_cast<void*>(&w13_cria);
        w13_sink = reinterpret_cast<void*>(&w13_desconverte);
        w13_sink = reinterpret_cast<void*>(&w13_desconverte_rdv);
        w13_sink = reinterpret_cast<void*>(&w13_confere);
        w13_sink = reinterpret_cast<void*>(&w13_voto);
        w13_sink = reinterpret_cast<void*>(&w13_escolhas);
        w13_sink = reinterpret_cast<void*>(&w13_nulo);
    }
} w13_roots;

} // namespace
