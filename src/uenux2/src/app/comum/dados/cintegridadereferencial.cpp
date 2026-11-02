// comum::CIntegridadeReferencial: Lanca, the record at line 344 col 15. The reconstruction's own note; the blank lines
// stand for text not recovered.
#include "app/comum/dados/cintegridadereferencial.h"

#include <format>

#include "app/comum/dados/cfotos.h"
#include "app/comum/dados/euecomumdadoserror.h"
#include "app/comum/dados/md/candidatura/ccandidatura.h"

namespace comum {

// (original lines 13-288: content not recovered)
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

} // namespace comum
