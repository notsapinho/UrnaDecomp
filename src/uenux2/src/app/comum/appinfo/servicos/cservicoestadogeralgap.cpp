// Reconstruction: comum::CServicoEstadoGeralGap's constructor (thunk 5812 of target fn 3897, binaryen's merge of
// the three classes' constructors) and GetPathArquivo (fn 11567, a thunk of the merge 3896; the record at line 32).
// Where each function starts is a choice (src/units/206-uenux2-app-comum-appinfo-servicos.mk).
#include "app/comum/appinfo/servicos/cservicoestadogeralgap.h"

#include "app/comum/appinfo/euecomumappinfoerror.h"
#include "app/comum/appinfo/servicos/cservicoestadogeral.h"
#include "app/comum/cpath.h"

namespace comum {

CServicoEstadoGeralGap::CServicoEstadoGeralGap(EFlashOrigem origem, EUrnaTurno turno) : m_origem(origem), m_turno(turno)
{
    if (m_turno == TURNO_ATUAL) {
        CServicoEstadoGeral servicoEstadoGeral(origem);
        m_turno = servicoEstadoGeral.Carrega().GetDadoCarga().GetTurno();
    }
}

// (original lines 20-28: content not recovered)
#line 29
std::filesystem::path CServicoEstadoGeralGap::GetPathArquivo()
{
    if (m_turno == SEM_TURNO) {
        throw CUeComumAppInfoError(EUE_APPINFO_SEM_TURNO_GAP, "Urna sem turno em contexto onde turno era esperado");
    }
    return CPath::GetPathTrab(m_origem, m_turno) / "gap.bin";
}

} // namespace comum
