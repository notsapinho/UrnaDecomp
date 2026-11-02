// Reconstruction: two free functions over comum::asn::CConversorCabecalhoPacote that convert the imported packages' list
// each way. CConversorDadosDisponiveisCarga's DoConverte (target fn 11424) and DoDesconverte (fn 11423) hold one each
// behind a stack-pointer prologue of its own (64 and 80 bytes), the sign of a function binaryen inlined
// (docs/how-to-decompile.md step 3). Measured: written in DoConverte's TU, ConvertePacotes is inlined there by clang and
// 11424 differs; here, 11424 matches. DesconvertePacotes in either TU leaves 11423 at the same score (145 operand-only
// rows over 2696, its names), so its file is chosen.
// No record names them; names and free functions chosen. The file (the class's own) is a reading for ConvertePacotes
// (Converte<CabecalhoPacote>'s record, 1562828, after this class's vtable) and chosen for DesconvertePacotes.
#include "app/comum/dados/asn/correspondencia/cconversorcabecalhopacote.h"

namespace comum::asn {

ASN1::SEQUENCE_OF<ModuloTiposEleitorais::CabecalhoPacote> ConvertePacotes(const std::vector<md::CCabecalhoPacote>& pacotes)
{
    ASN1::SEQUENCE_OF<ModuloTiposEleitorais::CabecalhoPacote> entidades;
    CConversorCabecalhoPacote conversor;
    for (size_t i = 0; i < pacotes.size(); ++i) {
        entidades.push_back(conversor.Converte(pacotes[i]));
    }
    return entidades;
}

std::vector<md::CCabecalhoPacote> DesconvertePacotes(
    const ModuloDadosDisponiveisCarga::DadosDisponiveisCarga::pacotesImportados::value_type& pacotesImportados)
{
    std::vector<md::CCabecalhoPacote> pacotes;
    CConversorCabecalhoPacote conversor;
    for (size_t i = 0; i < pacotesImportados.size(); ++i) {
        const md::CCabecalhoPacote pacote = conversor.Desconverte(pacotesImportados[i]);
        pacotes.push_back(pacote);
    }
    return pacotes;
}

} // namespace comum::asn
