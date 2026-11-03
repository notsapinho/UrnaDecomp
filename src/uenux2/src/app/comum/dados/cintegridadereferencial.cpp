// comum::CIntegridadeReferencial::Lanca (the record at line 344 col 15) and the free functions above and below it. The
// reconstruction's own note; the blank lines stand for text not recovered, and where each function starts is chosen.
#include "app/comum/dados/cintegridadereferencial.h"

#include <format>

#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/ccargos.h"
#include "app/comum/dados/cfotos.h"
#include "app/comum/dados/cpartidos.h"
#include "app/comum/dados/crdvvota.h"
#include "app/comum/dados/crespostas.h"
#include "app/comum/dados/euecomumdadoserror.h"
#include "app/comum/dados/md/candidatura/ccandidatura.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum {

using ecourna::api::util::CStringUtils;

// (original lines 21-288: content not recovered)
#line 289
CIntegridadeReferencial::TResultado VerificaCargoCandidatura(const md::CCandidatura& candidatura,
                                                            const std::map<md::TCargoID, md::CCargo>& cargos,
                                                            std::map<md::TCargoID, md::CCargo>::const_iterator& cargo)
{
    const md::TCargoID idCargo = candidatura.GetCargoID();
    cargo = cargos.find(idCargo);
    if (cargo == cargos.end()) {
        const std::string mensagem = std::format("o cargo ({}) da candidatura ({}) não foi encontrado", idCargo,
            candidatura.GetCandidatoID());
        return {false, mensagem};
    }
    if (!cargo->second.HasDetalheCandidato()) {
        const std::string mensagem = std::format("o cargo ({}) da candidatura ({}) não é de candidato", idCargo,
            candidatura.GetCandidatoID());
        return {false, mensagem};
    }
    if (cargo->second.GetDetalheCandidato().GetSuplentes().size() != candidatura.GetSuplentes().size()) {
        const std::string mensagem = std::format(
            "o cargo ({}) e a candidatura ({}) não têm a mesma quantidade de suplentes", idCargo,
            candidatura.GetCandidatoID());
        return {false, mensagem};
    }
    return {true, ""};
}

// (original lines 314-319: content not recovered)
#line 320
CIntegridadeReferencial::TResultado VerificaFotoCandidatura(const md::CCandidatura& candidatura, uebyte ordem,
                                                           const CFotos& fotos)
{
    if (candidatura.GetTitular().GetSituacao() != 0) {
        return {true, ""};
    }
    const std::string codigo = (ordem == 0 ? candidatura.GetTitular() : candidatura.GetSuplente(ordem)).GetCodigo();
    if (!fotos.ExisteFoto(codigo)) {
        const std::string mensagem = "a foto (" + codigo + ")" +
            std::format(" da candidatura ({}[{}]) não foi encontrada", candidatura.GetCandidatoID(), ordem);
        return {false, mensagem};
    }
    return {true, ""};
}

// (original lines 335-340: content not recovered)
#line 341
void CIntegridadeReferencial::Lanca(const TResultado& resultado)
{
    if (!resultado.first) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7871, std::format("Integridade referencial: {}", resultado.second));
    }
}

namespace {

CIntegridadeReferencial::TResultado VerificaVotosCargo(const md::CCargo& cargo, const md::CVotos& votos,
                                                       const CCandidaturas& candidaturas, const CPartidos& partidos,
                                                       const CRespostas& respostas)
{
    const md::TCargoID idCargo = cargo.GetID();
    for (const md::CVoto& voto : votos.GetVotos()) {
        const std::string& numero = voto.GetNumero();
        switch (voto.GetTipo()) {
        case md::CVoto::LEGENDA: {
            if (!cargo.IsProporcional()) {
                const std::string mensagem = std::format(
                    "um voto do cargo ({}) no RDV está com voto de legenda ({}) com cargo que não é proporcional",
                    idCargo, numero);
                return {false, mensagem};
            }
            if (numero.size() < 2) {
                const std::string mensagem = std::format(
                    "um voto do cargo ({}) no RDV está com voto de legenda ({}) com conteúdo insuficiente",
                    idCargo, numero);
                return {false, mensagem};
            }
            const TPartidoID partido = CStringUtils::ToWord(numero.substr(0, 2));
            if (!partidos.Existe(partido)) {
                const std::string mensagem = std::format(
                    "um voto do cargo ({}) no RDV está com voto de legenda ({}) para partido não encontrado",
                    idCargo, numero);
                return {false, mensagem};
            }
            if (numero.size() == cargo.GetNumeroDigitos()) {
                const TCandidatoID candidato = CStringUtils::ToDWord(numero);
                if (candidaturas.Existe(ChaveCandidatura(cargo.GetID(), candidato))) {
                    const std::string mensagem = std::format(
                        "um voto do cargo ({}) no RDV está com voto de legenda ({}), mas o candidato existe",
                        idCargo, numero);
                    return {false, mensagem};
                }
            }
            break;
        }
        case md::CVoto::NOMINAL: {
            const TCandidatoID candidato = CStringUtils::ToDWord(numero);
            if (cargo.IsConsulta()) {
                if (!respostas.Existe(ChaveResposta(cargo.GetID(), candidato))) {
                    const std::string mensagem = std::format(
                        "um voto do cargo ({}) no RDV está com voto nominal ({}) para resposta não encontrada",
                        idCargo, numero);
                    return {false, mensagem};
                }
            } else {
                const md::CCandidatura* candidatura = candidaturas.Procura(ChaveCandidatura(cargo.GetID(), candidato));
                if (candidatura == nullptr) {
                    const std::string mensagem = std::format(
                        "um voto do cargo ({}) no RDV está com voto nominal ({}) para candidatura não encontrada",
                        idCargo, numero);
                    return {false, mensagem};
                }
                if (candidatura->GetTitular().GetSituacao() != 0) {
                    const std::string mensagem = std::format(
                        "um voto do cargo ({}) no RDV está com voto nominal ({}) para candidatura inapta",
                        idCargo, numero);
                    return {false, mensagem};
                }
            }
            break;
        }
        default:
            if (md::CVoto::EhNulo(voto.GetTipo()) && voto.GetTipo() != md::CVoto::NULO_POR_REPETICAO &&
                numero.size() == cargo.GetNumeroDigitos()) {
                const TCandidatoID candidato = CStringUtils::ToDWord(numero);
                if (cargo.IsConsulta()) {
                    if (respostas.Existe(ChaveResposta(cargo.GetID(), candidato))) {
                        const std::string mensagem = std::format(
                            "um voto do cargo ({}) no RDV está com voto nulo ({}), mas a resposta existe",
                            idCargo, numero);
                        return {false, mensagem};
                    }
                } else {
                    const md::CCandidatura* candidatura =
                        candidaturas.Procura(ChaveCandidatura(cargo.GetID(), candidato));
                    if (candidatura != nullptr && candidatura->GetTitular().GetSituacao() == 0) {
                        const std::string mensagem = std::format(
                            "um voto do cargo ({}) no RDV está com voto nulo ({}) para candidatura apta",
                            idCargo, numero);
                        return {false, mensagem};
                    }
                }
            }
            break;
        }
    }
    return {true, ""};
}

} // namespace

CIntegridadeReferencial::TResultado VerificaVotos(const CRdv& rdv, const std::map<md::TCargoID, md::CCargo>& cargos,
                                                  const CCandidaturas& candidaturas, const CPartidos& partidos,
                                                  const CRespostas& respostas)
{
    for (const auto& [idCargo, votos] : rdv.GetVotos()) {
        const auto cargo = cargos.find(idCargo);
        if (cargo == cargos.end()) {
            const std::string mensagem =
                std::format("o cargo ({}) no RDV não foi encontrado na lista de cargos", idCargo);
            return {false, mensagem};
        }
        CIntegridadeReferencial::TResultado resultado =
            VerificaVotosCargo(cargo->second, votos, candidaturas, partidos, respostas);
        if (!resultado.first) {
            return resultado;
        }
    }
    return {true, ""};
}

void VerificaIntegridadeVotos()
{
    CIntegridadeReferencial::Lanca(VerificaVotos(CRdvVota::GetInst(), CCargos::GetInst().GetMapaCargos(),
                                                 CCandidaturas::GetInst(), CPartidos::GetInst(),
                                                 CRespostas::GetInst()));
}

} // namespace comum
