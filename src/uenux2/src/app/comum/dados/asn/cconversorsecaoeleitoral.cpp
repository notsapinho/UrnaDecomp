#include "app/comum/dados/asn/cconversorsecaoeleitoral.h"

#include <algorithm>

#include "app/comum/asn/util.h"
#include "app/comum/dados/asn/cconversoridentificacaoagregada.h"

namespace comum::asn {

CConversorSecaoEleitoral::TEntidade CConversorSecaoEleitoral::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_tipo() = Utils::ConverteTipoLocalVotacao(dado.GetTipo());

    ModuloTiposEleitorais::IdentificacaoSecaoEleitoral secao;
    ModuloTiposEleitorais::MunicipioZona municipioZona;
    municipioZona.set_municipio(dado.GetIdentificacao().GetMunicipio());
    municipioZona.set_zona(dado.GetIdentificacao().GetZona());
    secao.set_municipioZona() = municipioZona;
    secao.set_local(dado.GetIdentificacao().GetLocal());
    secao.set_secao(dado.GetIdentificacao().GetSecao());
    entidade.set_secao() = secao;

    CConversorIdentificacaoAgregada conversor;
    const md::TVectorIdentificacaoAgregada agregadas = dado.GetAgregadas();
    if (agregadas.empty()) {
        entidade.omit_agregadas();
    } else {
        ASN1::SEQUENCE_OF<ModuloLocal::IdentificacaoAgregada> lista;
        for (const md::CIdentificacaoAgregada& agregada : agregadas) {
            lista.push_back(conversor.Converte(agregada));
        }
        static_cast<ASN1::SEQUENCE_OF<ModuloLocal::IdentificacaoAgregada>&>(entidade.set_agregadas()) = lista;
    }
    return entidade;
}

CConversorSecaoEleitoral::TDado CConversorSecaoEleitoral::DoDesconverte(const TEntidade& entidade) const
{
    const ModuloTiposEleitorais::IdentificacaoSecaoEleitoral& secao = entidade.get_secao();
    const md::CIdentificacaoSecao identificacao(eUrnaVota, secao.get_municipioZona().get_municipio().getValue(),
        secao.get_municipioZona().get_zona().getValue(), secao.get_local().getValue(), secao.get_secao().getValue());
    const ETipoLocalVotacao tipo = Utils::DesconverteTipoLocalVotacao(entidade.get_tipo());

    CConversorIdentificacaoAgregada conversor;
    md::TVectorIdentificacaoAgregada agregadas;
    if (entidade.agregadas_isPresent()) {
        for (size_t i = 0; i < entidade.get_agregadas().size(); ++i) {
            agregadas.emplace_back(conversor.Desconverte(entidade.get_agregadas()[i]));
        }
    }
    std::sort(agregadas.begin(), agregadas.end(),
        [](const md::CIdentificacaoAgregada& a, const md::CIdentificacaoAgregada& b) { return a.GetNumero() < b.GetNumero(); });
    return TDado(tipo, identificacao, agregadas);
}

} // namespace comum::asn
