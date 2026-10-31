#include "app/comum/dados/asn/candidatura/cindexadorfotos.h"

#include "app/comum/asn/cconversorabrangencia.h"

namespace comum::asn {

CIndexadorFotos::TDado CIndexadorFotos::DoDesconverte(const TEntidade& entidade, const TVisitor& visitante) const
{
    std::vector<md::CIndiceFoto> indices;
    const std::vector<md::CIndiceFoto>& fotos = visitante.GetIndices();
    for (size_t i = 0; i < fotos.size(); ++i) {
        indices.push_back(md::CIndiceFoto(fotos[i].GetCodigo(), fotos[i].GetIndice()));
    }
    CConversorAbrangencia conversor;
    const md::CAbrangencia abrangencia = conversor.Desconverte(entidade.get_abrangencia());
    return TDado(abrangencia.GetMunicipio(), indices);
}

} // namespace comum::asn
