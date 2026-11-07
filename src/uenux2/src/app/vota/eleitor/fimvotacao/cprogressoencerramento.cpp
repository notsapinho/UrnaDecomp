#include "app/vota/eleitor/fimvotacao/cprogressoencerramento.h"

#include "api/gui/cprogressbar.h"
#include "api/gui/iform.h"
#include "api/gui/iscreen.h"
#include "app/vota/eleitor/comum/ctelasvota.h"

namespace vota {

CProgressoEncerramento::CProgressoEncerramento()
{
    const auto tela = TelaProgressoEncerramento();
    m_form = tela.first;
    m_barra = tela.second;
}

CProgressoEncerramento::~CProgressoEncerramento() = default;

void CProgressoEncerramento::Inicia()
{
    std::lock_guard<std::mutex> trava(m_mutex);
    m_barra->SetValor(m_barra->GetLimiteInferior());
    m_form->Slot2();
}

void CProgressoEncerramento::Finaliza()
{
    std::lock_guard<std::mutex> trava(m_mutex);
    m_barra->SetValor(m_barra->GetLimiteSuperior());
}

void CProgressoEncerramento::Incrementa()
{
    std::lock_guard<std::mutex> trava(m_mutex);
    m_barra->Incrementa();
}

} // namespace vota
