// Reconstruction: comum::md::estadoaplicacao::CEstadoGeralGap's constructor (target fn 5626, a chosen line, no record:
// 93-uenux2-estadoaplicacao.mk describes it) and GetCodigosCarga, which binaryen inlines into its one caller
// (target fn 3788 opens a second frame after CAppInfo's own code). No record names it, so its name and this file are chosen.
// The copy into a std::string temporary is a form chosen for the code it gives: CDadoCorrespondencia::GetCodigoCarga
// returns a reference (the converter's fn 11399 reads the member with no copy), and with it a plain push_back gives
// another object; a getter that returns the string by value with a plain push_back gives the same object as this.
#include "app/comum/dados/md/estadoaplicacao/cestadogeralgap.h"

#include <utility>

namespace comum::md::estadoaplicacao {

CEstadoGeralGap::CEstadoGeralGap(std::vector<CDadoCorrespondencia> correspondencias, EUrnaAplicativo appId,
                                 EUrnaAplicativo appAnteriorId, bool executadoRED, bool identificadoATUE, bool audio,
                                 bool data2T, CNumViasImpressasRelatorios numViasImpressasRelatorios1T,
                                 CNumViasImpressasRelatorios numViasImpressasRelatorios2T,
                                 std::optional<api::CDate> dataSegundoTurno)
    : m_correspondencias(std::move(correspondencias)),
      m_appId(appId),
      m_appAnteriorId(appAnteriorId),
      m_executadoRED(executadoRED),
      m_identificadoATUE(identificadoATUE),
      m_audio(audio),
      m_data2T(data2T),
      m_numViasImpressasRelatorios1T(numViasImpressasRelatorios1T),
      m_numViasImpressasRelatorios2T(numViasImpressasRelatorios2T),
      m_dataSegundoTurno(dataSegundoTurno)
{
    const api::CDate hoje;
    m_data2T = m_dataSegundoTurno && (*m_dataSegundoTurno == hoje || *m_dataSegundoTurno < hoje);
}

std::vector<std::string> CEstadoGeralGap::GetCodigosCarga() const
{
    std::vector<std::string> codigos;
    codigos.reserve(m_correspondencias.size());
    for (const CDadoCorrespondencia& correspondencia : m_correspondencias) {
        codigos.push_back(std::string(correspondencia.GetCodigoCarga()));
    }
    return codigos;
}

} // namespace comum::md::estadoaplicacao
