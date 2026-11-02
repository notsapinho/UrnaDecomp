#include "app/vota/eleitor/iniciovotacao/testeteclado/ctesteteclado.h"

#include <algorithm>
#include <random>
#include <tuple>

#include "api/gui/cformbuilder.h"
#include "api/pattern/polysingletongetinst.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/cgeradorteclasaleatorio.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/log/clogvota.h"

namespace vota::testeteclado {

CTesteTeclado& CTesteTeclado::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CTesteTeclado());
    }
    return *s_inst;
}

std::unique_ptr<CTesteTeclado> CTesteTeclado::s_inst;
std::mutex CTesteTeclado::s_mutex;

CTesteTeclado::~CTesteTeclado() = default;

void CTesteTeclado::StartState()
{
    CLogVota::GetInst().LogaInicioTesteTeclado();
    m_pNextState = this;
    std::tie(m_form, m_teclas) = TelaTesteTeclado();
    m_sequencia = SorteiaTeclasTesteTeclado(impl::IGeradorTeclas::GetInst());
    m_indice = 0;
    if (m_sequencia.empty()) {
        throw CUeVotaError(EUE_VOTA_TESTE_TECLADO_SEM_TECLAS, "Sem teclas para testar");
    }
    const auto it = m_teclas.find(m_sequencia[m_indice]);
    if (it == m_teclas.end()) {
        throw CUeVotaError(EUE_VOTA_TESTE_TECLADO_TECLA_NAO_ENCONTRADA,
                           "Tecla não encontrada: " + m_sequencia.at(m_indice));
    }
    m_form->Slot2();
    it->second.second->SetStatus(api::TEXTSTATUS_PREENCHIDO);
}

// (original lines 49-88: content not recovered)
#line 89
CTesteTeclado::CTesteTeclado()
    : CEstadoComDesligamentoAutomatico(EVENTO_ENTRADA)
    , m_indice(0)
    , m_pEstadoPassouNoTeste(nullptr)
{
}

} // namespace vota::testeteclado

namespace vota::testeteclado::impl {

std::vector<std::string> CGeradorTeclasAleatorio::GeraSequencia(std::vector<std::string> teclas)
{
    static std::mt19937 gerador(std::random_device{}());
    std::shuffle(teclas.begin(), teclas.end(), gerador);
    return teclas;
}

// (original lines 107-120: content not recovered)
#line 121
POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO(IGeradorTeclas, CGeradorTeclasAleatorio)

} // namespace vota::testeteclado::impl

namespace vota {

std::shared_ptr<api::CTextBox> AdicionaCaixaTecla(api::CFormBuilder& builder, const std::string& texto, api::SPoint posicao,
                                                  api::SFont fonte, api::SPoint tamanho)
{
    const api::TFontSize tamanhoFonte = fonte.size;
    auto caixa = std::make_shared<api::CTextBox>(texto, api::TEXTSTATUS_CONTORNO, posicao, tamanhoFonte,
                                                 api::ALINHAMENTO_CENTRO, tamanho, static_cast<api::TColor>(1),
                                                 static_cast<api::TColor>(2));
    builder.AddField(caixa);
    return caixa;
}

} // namespace vota
