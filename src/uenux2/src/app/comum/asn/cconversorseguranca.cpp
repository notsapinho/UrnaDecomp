#include "app/comum/asn/cconversorseguranca.h"

namespace comum::asn {

CConversorSeguranca::TEntidade CConversorSeguranca::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_idTipoArquivo(dado.GetIdTipoArquivo());
    entidade.set_idCriptografia(dado.GetIdCriptografia());
    entidade.set_idArquivoChave() = std::vector<char>(dado.GetChave().begin(), dado.GetChave().end());
    return entidade;
}

CConversorSeguranca::TDado CConversorSeguranca::DoDesconverte(const TEntidade& entidade) const
{
    const auto& chave = entidade.get_idArquivoChave();
    return TDado(entidade.get_idTipoArquivo().getValue(), entidade.get_idCriptografia().getValue(), std::vector<uebyte>(chave.begin(), chave.end()));
}

} // namespace comum::asn
