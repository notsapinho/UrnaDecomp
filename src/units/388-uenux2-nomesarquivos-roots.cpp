// Roots of fragment 388 (src/units/388-uenux2-nomesarquivos.mk): the references the target keeps its members by while
// their callers are not in the link. Each stand-in's body is no target function's, and each builds what it gets in
// place, so this TU emits no destructor of a library template (src/units/README.md "Companion files").
// - comum::NomesArquivosEleicao (fn 3744): fns 2811 and 7787 call it once each, and neither is written;
//   w388_eleicao calls it twice, with no argument one constant at both calls, so binaryen folds none. The target's
//   table holds it (slot 2463), so its address is taken too.
// - comum::md::CPleito::GetEleicoesMunicipio (fn 5649): fns 2811 and 3713 call it once each; 3713 is in the link, and
//   w388_eleicoes calls it once for 2811.
// - comum::md::CPleito::FiltraMunicipio (fn 3713): fn 7787 calls it three times, its one target caller; w388_filtra
//   calls it twice.
// - std::filesystem::__remove (fn 2135, libc++.a's operations.o): fn 7787 calls it four times, with a null error_code,
//   and the target's table holds it (slot 6046), so dead-argument elimination keeps that parameter there. w388_remove
//   calls it twice through an __asm__ label with the archive symbol's signature, and its address is taken.
#include <new>
#include <string>

#include "app/comum/nomearquivo/cnomearquivo.h"

extern "C" {
// bool std::filesystem::__remove(const path&, std::error_code*), libc++.a's operations.o
int w388_remove_fs(const void* caminho, void* erro) __asm__(
    "_ZNSt3__210filesystem8__removeERKNS0_4pathEPNS_10error_codeE");
}

namespace {

// stands for fns 2811 and 7787
__attribute__((noinline)) void w388_eleicao(void* destino, const comum::SIdentificacaoArquivo& identificacao,
    const comum::md::CPleito& pleito, comum::TMunicipioID municipio, comum::md::TEleicaoID eleicao,
    const std::string& tipo, const std::string& extensao)
{
    ::new (destino) std::map<comum::md::ETipoAbrangencia, std::string>(
        comum::NomesArquivosEleicao(identificacao, pleito, municipio, eleicao, tipo, extensao));
    ::new (static_cast<char*>(destino) + 12) std::map<comum::md::ETipoAbrangencia, std::string>(
        comum::NomesArquivosEleicao(identificacao, pleito, municipio + 388, eleicao + 1, extensao, tipo));
}

// stands for fn 2811 (3713 is in the link)
__attribute__((noinline)) void w388_eleicoes(void* destino, const comum::md::CPleito& pleito, uedword municipio)
{
    ::new (destino) comum::md::TVectorEleicaoPE(pleito.GetEleicoesMunicipio(municipio + 388));
}

// stands for fn 7787
__attribute__((noinline)) void w388_filtra(void* destino, const comum::md::CPleito& pleito, uedword municipio)
{
    ::new (destino) comum::md::CPleito(pleito.FiltraMunicipio(municipio));
    ::new (static_cast<char*>(destino) + 60) comum::md::CPleito(pleito.FiltraMunicipio(municipio + 388));
}

// stands for fn 7787
__attribute__((noinline)) int w388_remove(const void* primeiro, const void* segundo)
{
    return w388_remove_fs(primeiro, nullptr) * 3 + w388_remove_fs(segundo, nullptr);
}

const void* volatile w388_sink;

struct SW388Roots {
    SW388Roots()
    {
        w388_sink = reinterpret_cast<const void*>(&w388_eleicao);
        w388_sink = reinterpret_cast<const void*>(&w388_eleicoes);
        w388_sink = reinterpret_cast<const void*>(&w388_filtra);
        w388_sink = reinterpret_cast<const void*>(&w388_remove);
        w388_sink = reinterpret_cast<const void*>(&comum::NomesArquivosEleicao);
        w388_sink = reinterpret_cast<const void*>(&w388_remove_fs);
    }
} w388_roots;

} // namespace
