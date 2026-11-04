#include "app/vota/operador/confirmaidentidade/cpedeanonascimentosembiometria.h"

#include <string>

#include "api/gui/cinteractiveform.h"
#include "app/comum/dados/celeitores.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/confirmaidentidade/cinformaanonascimentoerrado.h"
#include "app/vota/operador/confirmaidentidade/cinformaeleitorpodevotar.h"
#include "app/vota/operador/leidentidade/ccancelahabilitacaoeleitor.h"

namespace vota {

CPedeAnoNascimentoSemBiometria::~CPedeAnoNascimentoSemBiometria() = default;

void CPedeAnoNascimentoSemBiometria::StartState()
{
    m_pNextState = this;
    m_bPrimeira = true;
    m_tentativas = 0;
    m_form->Slot2();
}

void CPedeAnoNascimentoSemBiometria::LeAnoDigitado()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA: {
        const std::string ano = m_form->GetEntradas().at(0)->GetTexto();
        if (ano.size() >= 4) {
            const unsigned long digitado = std::stoul(ano);
            if (comum::CEleitores::GetInst().GetCurrent()->GetEleitor().GetAnoNascimento() == digitado) {
                CLogVota::GetInst().LogaAnoNascimentoIgualCadastro();
                m_pNextState = &CInformaEleitorPodeVotar::GetInst();
            } else {
                CLogVota::GetInst().LogaAnoNascimentoDiferenteCadastro();
                if (++m_tentativas <= 1) {
                    m_bPrimeira = false;
                    m_formErro->Slot2();
                } else {
                    m_pNextState = &CInformaAnoNascimentoErrado::GetInst();
                }
            }
        }
        break;
    }
    case api::INPUT_CORRIGE:
        CLogVota::GetInst().LogaHabilitacaoCanceladaConfirmacaoDado();
        m_pNextState = &CCancelaHabilitacaoEleitor::GetInst();
        break;
    default:
        break;
    }
}

void CPedeAnoNascimentoSemBiometria::ProcessInput()
{
    if (m_bPrimeira) {
        LeAnoDigitado();
    } else if (m_formErro->Read() == api::INPUT_CONFIRMA) {
        m_bPrimeira = true;
        m_form->Slot2();
    }
}

} // namespace vota
