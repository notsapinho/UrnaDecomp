// Reconstruction: comum::asn::CConversorDedo's slot 3 (target fn 11416), its static DesconverteTipo (record line 159,
// which binaryen inlines into 11416) and the minutiae decoder 11416 calls twice (target fn 5702); fragment 335 has the
// evidence, the forms measured and the choices. Every line but the two records' is chosen.
#include "app/comum/dados/asn/eleitor/cconversordedo.h"

#include <format>

#include "app/comum/asn/util.h"
#include "app/comum/dados/asn/eleitor/cminuciascompactadas.h"
#include "app/comum/dados/euecomumdadoserror.h"
#include "ecourna/api/util/cbitarray.hpp"

namespace comum::asn {

// (original lines 15-54: content not recovered)
#line 55
std::vector<api::SXYT> DesconverteMinucias(const ASN1::OCTET_STRING& minucias)
{
    std::vector<uebyte> bytes;
    const uebyte* const dados = reinterpret_cast<const uebyte*>(minucias.data());
    bytes.assign(dados, dados + minucias.size());
    ecourna::api::util::CBitArray bits(bytes);
    const ueword xMinimo = bits.GetValor(10);
    const ueword bitsX = bits.GetValor(4);
    const ueword yMinimo = bits.GetValor(10);
    const ueword bitsY = bits.GetValor(4);
    const ueword quantidadeAngulos = bits.GetValor(8);
    std::vector<CMinuciasCompactadas::SPar> pares;
    for (uebyte i = 0; i < quantidadeAngulos; ++i) {
        const ueword angulo = bits.GetValor(9);
        const ueword quantidade = bits.GetValor(8);
        pares.push_back({angulo, quantidade});
        for (uebyte j = 0; j < quantidade; ++j) {
            const ueword x = bits.GetValor(bitsX) + xMinimo;
            const ueword y = bits.GetValor(bitsY) + yMinimo;
            pares.push_back({x, y});
        }
    }
    const CMinuciasCompactadas compactadas(pares);
    return compactadas.GetMinucias();
}

// (original lines 81-134: content not recovered)
#line 135
md::CDedo::TipoDedo CConversorDedo::DesconverteTipo(ModuloTiposEleitorais::TipoDedo::NamedNumber tipo)
{
    switch (tipo) {
        case ModuloTiposEleitorais::TipoDedo::polegarDireito:
            return static_cast<md::CDedo::TipoDedo>(1);
        case ModuloTiposEleitorais::TipoDedo::indicadorDireito:
            return static_cast<md::CDedo::TipoDedo>(2);
        case ModuloTiposEleitorais::TipoDedo::medioDireito:
            return static_cast<md::CDedo::TipoDedo>(3);
        case ModuloTiposEleitorais::TipoDedo::anelarDireito:
            return static_cast<md::CDedo::TipoDedo>(4);
        case ModuloTiposEleitorais::TipoDedo::minimoDireito:
            return static_cast<md::CDedo::TipoDedo>(5);
        case ModuloTiposEleitorais::TipoDedo::polegarEsquerdo:
            return static_cast<md::CDedo::TipoDedo>(6);
        case ModuloTiposEleitorais::TipoDedo::indicadorEsquerdo:
            return static_cast<md::CDedo::TipoDedo>(7);
        case ModuloTiposEleitorais::TipoDedo::medioEsquerdo:
            return static_cast<md::CDedo::TipoDedo>(8);
        case ModuloTiposEleitorais::TipoDedo::anelarEsquerdo:
            return static_cast<md::CDedo::TipoDedo>(9);
        case ModuloTiposEleitorais::TipoDedo::minimoEsquerdo:
            return static_cast<md::CDedo::TipoDedo>(10);
        default:
            throw CUeComumDadosError(EUE_COMUM_DADOS_7896, std::format("Tipo inválido: {}", tipo));
    }
}

md::CDedo CConversorDedo::DoDesconverte(const TEntidade& entidade) const
{
    const std::vector<api::SXYT> minucias = DesconverteMinucias(entidade.get_minucias());


    if (static_cast<size_t>(entidade.get_qtdMinucias().getValue()) != minucias.size()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7897, "Campo qtdMinucias não confere com quantidade de minúcias enviadas.");
    }

    return md::CDedo(DesconverteTipo(entidade.get_tipo()), entidade.get_qtdMinucias().getValue(), DesconverteMinucias(entidade.get_minucias()));
}

} // namespace comum::asn
