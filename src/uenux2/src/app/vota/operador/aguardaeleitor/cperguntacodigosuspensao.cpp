// vota::CPerguntaCodigoSuspensao
// (/home/rubio/tse/uenux2/src/app/vota/operador/aguardaeleitor/cperguntacodigosuspensao.cpp).
// The reconstruction's note, not TSE's text: no record names a line of this file, so every line is a choice;
// src/units/142-uenux2-app-vota-estados-448.mk says what the bytes decide.
#include "app/vota/operador/aguardaeleitor/cperguntacodigosuspensao.h"

#include <string>
#include <utility>

#include "api/gui/cinteractiveform.h"
#include "api/util/csystem.h"
#include "app/comum/dados/md/cvalidadoridentidade.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/aguardaeleitor/cmostraeleitorvotando.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"

namespace vota {

CPerguntaCodigoSuspensao::~CPerguntaCodigoSuspensao() = default;

void CPerguntaCodigoSuspensao::StartState()
{
    m_pNextState = this;
    CLogVota::GetInst().LogaPedidoTituloSuspensao();
    m_form->Slot2();
    m_bLido = false;
}

void CPerguntaCodigoSuspensao::ProcessInput()
{
    const api::EInputResult resultado = m_form->Read();
    if (m_bLido) {
        return;
    }
    switch (resultado) {
    case api::INPUT_CORRIGE:
        CLogVota::GetInst().LogaSuspensaoAbortada();
        CThreadEleitor::GetInst().GetMensagens().Post(4);
        m_pNextState = &CMostraEleitorVotando::GetInst();
        break;
    case api::INPUT_CONFIRMA: {
        const std::string texto = m_form->GetEntradas().at(0)->GetTexto();
        if (!texto.empty()) {
            CLogVota::GetInst().LogaTituloSuspensaoDigitado();
            const std::pair<bool, std::string> validacao = ValidaTituloSuspensao(texto);
            if (!validacao.first) {
                CLogVota::GetInst().LogaTituloSuspensaoInvalido(validacao.second);
                m_formConfirmacao->Slot2();
                api::CSystem::Dorme(3000);
                m_form->Slot2();
            } else {
                CLogVota::GetInst().LogaTituloSuspensaoValido(validacao.second);
                CThreadEleitor::GetInst().GetMensagens().Post(2);
                m_bLido = true;
            }
        }
        break;
    }
    default:
        break;
    }
}

} // namespace vota
