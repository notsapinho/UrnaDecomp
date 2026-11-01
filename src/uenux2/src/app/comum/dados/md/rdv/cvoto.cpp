#include "app/comum/dados/md/rdv/cvoto.h"

#include "app/comum/dados/euerdverror.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum::md {

namespace {

std::string Valida(CVoto::ETipo tipo, const std::string& digitado)
{
    std::string nome;
    bool comDigitado = false;
    switch (tipo) {
        case CVoto::LEGENDA:
            nome = std::string("de legenda");
            comDigitado = true;
            break;
        case CVoto::NOMINAL:
            nome = std::string("nominal");
            comDigitado = true;
            break;
        case CVoto::BRANCO:
            nome = std::string("em branco");
            break;
        case CVoto::NULO:
            return "";
        case CVoto::BRANCO_APOS_SUSPENSAO:
            nome = std::string("suspenso branco");
            break;
        case CVoto::NULO_APOS_SUSPENSAO:
            nome = std::string("suspenso nulo");
            break;
        case CVoto::NULO_POR_REPETICAO:
            nome = std::string("repetido nulo");
            break;
        case CVoto::NULO_CARGO_SEM_CANDIDATO:
            nome = std::string("em cargo sem candidato");
            break;
        case CVoto::NULO_APOS_SUSPENSAO_CARGO_SEM_CANDIDATO:
            nome = std::string("suspenso em cargo sem candidato");
            break;
        default:
            return "CVoto - tipo de voto invalido " + std::to_string(tipo);
    }
    if (comDigitado) {
        if (digitado.empty()) {
            return "CVoto - voto " + nome + " com digitado vazio";
        }
    } else if (!digitado.empty()) {
        return "CVoto - voto " + nome + " com digitado nao vazio";
    }
    return "";
}

} // namespace

// (original lines 58-75: content not recovered)
#line 76
CVoto::CVoto(ETipo tipo, const std::string& numero) : m_tipo(tipo), m_numero(ecourna::api::util::CStringUtils::Trim(numero))
{
    const std::string erro = Valida(m_tipo, m_numero);
    if (!erro.empty()) {
        throw api::CUeRdvError(api::EUE_RDV_VOTO_INVALIDO, erro);
    }
}

bool CVoto::EhNulo(ETipo tipo)
{
    return tipo == NULO || tipo == NULO_APOS_SUSPENSAO || tipo == NULO_POR_REPETICAO;
}

bool CVoto::EhNominal() const
{
    return m_tipo == NOMINAL;
}

bool CVoto::EhLegenda() const
{
    return m_tipo == LEGENDA;
}

bool CVoto::EhBranco() const
{
    return m_tipo == BRANCO || m_tipo == BRANCO_APOS_SUSPENSAO;
}

std::strong_ordering CVoto::operator<=>(const CVoto& outro) const = default;

} // namespace comum::md
