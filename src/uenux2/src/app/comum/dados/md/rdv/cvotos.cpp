#include "app/comum/dados/md/rdv/cvotos.h"

#include <algorithm>
#include "app/comum/dados/euerdverror.h"
namespace comum::md {

TQtdVoto CVotos::Conta(TCriterio criterio) const
{
    return std::count_if(m_votos.begin(), m_votos.end(), criterio);
}

TQtdVoto CVotos::Candidato(const std::string& numero) const
{
    return Conta([&numero](const CVoto& voto) { return voto.GetTipo() == CVoto::NOMINAL && voto.GetNumero() == numero; });
}

TQtdVoto CVotos::Legenda(const std::string& numero) const
{
    return Conta([&numero](const CVoto& voto) {
        return voto.GetTipo() == CVoto::LEGENDA && voto.GetNumero().compare(0, numero.size(), numero) == 0;
    });
}

TQtdVoto CVotos::Partido(const std::string& numero) const
{
    return Conta([&numero](const CVoto& voto) {
        return (voto.GetTipo() == CVoto::LEGENDA || voto.GetTipo() == CVoto::NOMINAL) &&
               voto.GetNumero().compare(0, numero.size(), numero) == 0;
    });
}

TQtdVoto CVotos::TotalQue(bool (CVoto::*criterio)() const) const
{
    return Conta([&criterio](const CVoto& voto) { return (voto.*criterio)(); });
}

void CVotos::Insere(const CVoto& voto, size_t posicao)
{
    if (posicao > m_votos.size()) {
        ErroPosicao(posicao);
    }
    m_votos.insert(m_votos.begin() + posicao, voto);
}

void CVotos::ErroPosicao(const size_t posicao, const std::source_location local) const
{
    throw api::CUeRdvError(api::EUE_RDV_POSICAO_FORA_DO_LIMITE,
                           "Posição (" + std::to_string(posicao) + ") fora do limite (" + std::to_string(Total()) + ")",
                           local);
}

CVotos::CVotos(std::vector<CVoto> votos) : m_votos(std::move(votos))
{
    m_votos.reserve(1000);
}

} // namespace comum::md
