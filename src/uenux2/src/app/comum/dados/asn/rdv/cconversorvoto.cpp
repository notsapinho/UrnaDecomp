#include "app/comum/dados/asn/rdv/cconversorvoto.h"

#include "app/comum/asn/util.h"
#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::asn {

// (original lines 8-19: content not recovered)
#line 20
ModuloRegistroDigitalVoto::TipoVoto CConversorVoto::ConverteTipo(md::CVoto::ETipo tipo)
{
    switch (tipo) {
        case md::CVoto::LEGENDA:
            return ModuloRegistroDigitalVoto::TipoVoto::legenda;
        case md::CVoto::NOMINAL:
            return ModuloRegistroDigitalVoto::TipoVoto::nominal;
        case md::CVoto::BRANCO:
            return ModuloRegistroDigitalVoto::TipoVoto::branco;
        case md::CVoto::NULO:
            return ModuloRegistroDigitalVoto::TipoVoto::nulo;
        case md::CVoto::BRANCO_APOS_SUSPENSAO:
            return ModuloRegistroDigitalVoto::TipoVoto::brancoAposSuspensao;
        case md::CVoto::NULO_APOS_SUSPENSAO:
            return ModuloRegistroDigitalVoto::TipoVoto::nuloAposSuspensao;
        case md::CVoto::NULO_POR_REPETICAO:
            return ModuloRegistroDigitalVoto::TipoVoto::nuloPorRepeticao;
        case md::CVoto::NULO_CARGO_SEM_CANDIDATO:
            return ModuloRegistroDigitalVoto::TipoVoto::nuloCargoSemCandidato;
        case md::CVoto::NULO_APOS_SUSPENSAO_CARGO_SEM_CANDIDATO:
            return ModuloRegistroDigitalVoto::TipoVoto::nuloAposSuspensaoCargoSemCandidato;
        default:
            break;
    }
    throw CUeComumDadosError(EUE_COMUM_DADOS_7973, std::format("Valor inválido para tipo voto eleitor: {}", tipo));
}

// (original lines 47-48: content not recovered)
#line 49
md::CVoto::ETipo CConversorVoto::DesconverteTipo(ModuloRegistroDigitalVoto::TipoVoto tipo)
{
    switch (tipo) {
        case ModuloRegistroDigitalVoto::TipoVoto::legenda:
            return md::CVoto::LEGENDA;
        case ModuloRegistroDigitalVoto::TipoVoto::nominal:
            return md::CVoto::NOMINAL;
        case ModuloRegistroDigitalVoto::TipoVoto::branco:
            return md::CVoto::BRANCO;
        case ModuloRegistroDigitalVoto::TipoVoto::nulo:
            return md::CVoto::NULO;
        case ModuloRegistroDigitalVoto::TipoVoto::brancoAposSuspensao:
            return md::CVoto::BRANCO_APOS_SUSPENSAO;
        case ModuloRegistroDigitalVoto::TipoVoto::nuloAposSuspensao:
            return md::CVoto::NULO_APOS_SUSPENSAO;
        case ModuloRegistroDigitalVoto::TipoVoto::nuloPorRepeticao:
            return md::CVoto::NULO_POR_REPETICAO;
        case ModuloRegistroDigitalVoto::TipoVoto::nuloCargoSemCandidato:
            return md::CVoto::NULO_CARGO_SEM_CANDIDATO;
        case ModuloRegistroDigitalVoto::TipoVoto::nuloAposSuspensaoCargoSemCandidato:
            return md::CVoto::NULO_APOS_SUSPENSAO_CARGO_SEM_CANDIDATO;
        case ModuloRegistroDigitalVoto::TipoVoto::unknownEnumeration_:
            throw CUeComumDadosError(EUE_COMUM_DADOS_7974, std::format("Valor inválido para tipo voto eleitor: {}", tipo.asInt()));
        default:
            break;
    }
    throw CUeComumDadosError(EUE_COMUM_DADOS_7975, std::format("Valor inválido para tipo voto eleitor: {}", tipo.asInt()));
}

CConversorVoto::TEntidade CConversorVoto::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_tipoVoto(ConverteTipo(dado.GetTipo()));
    if (dado.GetNumero().empty()) {
        entidade.omit_digitacao();
    } else {
        entidade.set_digitacao(dado.GetNumero());
    }
    return entidade;
}

CConversorVoto::TDado CConversorVoto::DoDesconverte(const TEntidade& entidade) const
{
    const md::CVoto::ETipo tipo = DesconverteTipo(entidade.get_tipoVoto());
    const std::string digitacao =
        entidade.digitacao_isPresent() ? entidade.get_digitacao() : TEntidade::digitacao::value_type("");
    return TDado(tipo, digitacao);
}

} // namespace comum::asn
