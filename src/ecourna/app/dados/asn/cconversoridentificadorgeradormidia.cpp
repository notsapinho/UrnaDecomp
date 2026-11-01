#include "ecourna/app/dados/asn/cconversoridentificadorgeradormidia.hpp"

namespace ecourna::app::dados::asn {

CConversorIdentificadorGeradorMidia::~CConversorIdentificadorGeradorMidia() {}

ModuloTiposEcoUrna::IdentificadorGeradorMidia CConversorIdentificadorGeradorMidia::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_nome(dado.GetNome());
    entidade.set_serialCertificadoTPM(dado.GetSerialCertificadoTPM());
    entidade.set_serialInstalacao(dado.GetSerialInstalacao());
    return entidade;
}

CIdentificadorGeradorMidia CConversorIdentificadorGeradorMidia::DoDeconverte(const TEntidade& entidade) const
{
    const auto nome = entidade.get_nome();
    const auto serialCertificadoTPM = entidade.get_serialCertificadoTPM();
    const auto serialInstalacao = entidade.get_serialInstalacao();
    return CIdentificadorGeradorMidia(nome, serialCertificadoTPM, serialInstalacao);
}

} // namespace ecourna::app::dados::asn
