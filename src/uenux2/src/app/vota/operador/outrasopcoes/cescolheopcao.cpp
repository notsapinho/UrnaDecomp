// vota::CEscolheOpcao (/home/rubio/tse/uenux2/src/app/vota/operador/outrasopcoes/cescolheopcao.cpp). This comment is
// the reconstruction's. The file's records are StartState's, lines 150 to 152. Written here: the statics, the four
// texts of the options, AdicionaCampoNumerico (fn 1151), GetInst (fn 2753) with the constructor and its two helpers
// (CriaOpcoes and MontaTela, chosen), whose lines are a choice before the destructor's, in their use bands' order; the
// destructor (fns 2752 and 10691), whose line is a choice before the records; StartState (fn 10690) at its records;
// ProcessInput (fn 10689) and ConfirmaOpcao, which binaryen inlines into it; and COpcaoDS's call operator, which has no
// record and no target function of its own: binaryen inlined it into fn 10685, CDataText<COpcaoDS>::GetText. The lines
// after the records are a choice. Unit 121's fragment gives the evidence.
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

#include <algorithm>
#include <cctype>
#include <format>
#include <syslog.h>

#include "api/gui/cinputfieldmt.h"
#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/cnumbervalidation.h"
#include "api/gui/iscreenmt.h"
#include "api/hwil/iurna.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/comparecimentomesario/estados/cregistrarmesarios.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/clocal.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"
#include "app/vota/operador/outrasopcoes/cconfirmaaudio.h"
#include "app/vota/operador/outrasopcoes/ccontadoresbiometria.h"
#include "app/vota/operador/outrasopcoes/chabilitacaoaudionaopermitida.h"
#include "app/vota/operador/outrasopcoes/chorariovotacaoterminou.h"
#include "app/vota/operador/outrasopcoes/ciniciafinalizacao.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace vota {

std::unique_ptr<CEscolheOpcao> CEscolheOpcao::s_inst;
std::mutex CEscolheOpcao::s_mutex;

std::string TextoAudio()
{
    if (IsAudioAtivadoMesario()) {
        return "Desativar áudio";
    }
    return "Ativar áudio";
}

std::string TextoEncerrarVotacao()
{
    return "Encerrar votação";
}

std::string TextoRegistrarMesarios()
{
    return "Registrar mesários";
}

std::string TextoExibirContadores()
{
    return "Exibir contadores";
}

std::shared_ptr<api::IInputField<api::IScreenMT>> AdicionaCampoNumerico(api::CMTFormBuilder& builder, size_t tamanho,
                                                                       bool confirmaAoCompletar, const api::SPoint& posicao)
{
    const std::shared_ptr<api::IInputValidation> validacao(new api::CNumberValidation);
    api::CMTFormBuilder::SharedInput campo(new api::CInputFieldMT(validacao, tamanho, confirmaAoCompletar, posicao));
    builder.AddField(campo);
    return campo;
}

namespace {

std::map<int, CEscolheOpcao::SOpcao> CriaOpcoes()
{
    std::map<int, CEscolheOpcao::SOpcao> opcoes;
    int numero = 1;
    opcoes.emplace(numero, CEscolheOpcao::SOpcao(1, CEscolheOpcao::COpcaoDS(numero, &TextoAudio)));
    ++numero;
    opcoes.emplace(numero, CEscolheOpcao::SOpcao(2, CEscolheOpcao::COpcaoDS(numero, &TextoEncerrarVotacao)));
    ++numero;
    if (RegistraMesarios()) {
        opcoes.emplace(numero, CEscolheOpcao::SOpcao(3, CEscolheOpcao::COpcaoDS(numero, &TextoRegistrarMesarios)));
        ++numero;
    }
    if (comum::CLocal::GetInst().UrnaBiometrica() && !comum::CAppInfo::EhTreinamentoEleitor()) {
        opcoes.emplace(numero, CEscolheOpcao::SOpcao(4, CEscolheOpcao::COpcaoDS(numero, &TextoExibirContadores)));
    }
    return opcoes;
}

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela(const std::map<int, CEscolheOpcao::SOpcao>& opcoes)
{
    api::CMTFormBuilder builder;
    builder.AddClock(api::SPoint{33, 1});
    builder.AddTextField("Selecione a opção: ", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    int coluna = 1;
    int linha = 2;
    for (const auto& opcao : opcoes) {
        builder.AddTextField(opcao.second.m_ds, api::SPoint(coluna, linha));
        if (linha == 3) {
            coluna = 20;
            linha = 2;
        } else {
            linha = 3;
        }
    }
    builder.AddTextField("CORRIGE: retornar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: prosseguir", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    AdicionaCampoNumerico(builder, 1, true, api::SPoint{20, 1});
    return builder.GetInteractiveForm("", true);
}

} // namespace

CEscolheOpcao::CEscolheOpcao()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_opcoes(CriaOpcoes())
    , m_form(MontaTela(m_opcoes))
{
}

CEscolheOpcao& CEscolheOpcao::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEscolheOpcao());
    }
    return *s_inst;
}

// (original lines 135-139: content not recovered)
#line 140
CEscolheOpcao::~CEscolheOpcao() = default;

// (original lines 142-145: content not recovered)
#line 146
void CEscolheOpcao::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
    syslog(LOG_INFO, "%s:%d> %d", __func__, __LINE__, api::CPolySingleton<api::IUrna>::instance().Modelo() >= 2020);
    if (api::CPolySingleton<api::IUrna>::instance().Modelo() >= 2020) {
        api::CPolySingleton<api::IScreenMT>::instance().Slot19(1);
    }
}

void CEscolheOpcao::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA:
        if (comum::CAppState* proximo = ConfirmaOpcao()) {
            m_pNextState = proximo;
        }
        break;
    case api::INPUT_CORRIGE:
        m_pNextState = &CPedeIdentidade::GetInst();
        break;
    default:
        break;
    }
}

comum::CAppState* CEscolheOpcao::ConfirmaOpcao()
{
    const std::string texto = m_form->GetEntradas().at(0)->GetTexto();
    if (texto.empty() || !std::all_of(texto.begin(), texto.end(), ::isdigit)) {
        return nullptr;
    }
    const auto opcao = m_opcoes.find(ecourna::api::util::CStringUtils::ToInt32(texto));
    if (opcao == m_opcoes.end()) {
        return nullptr;
    }
    switch (opcao->second.m_codigo) {
    case 1:
        CLogVota::GetInst().LogaOperadorSelecionou(TextoAudio());
        if (IsVotacaoBloqueadaPorHorario()) {
            m_form->LimpaEntradas();
            return &CHorarioVotacaoTerminou::GetInst();
        }
        if (!comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetPermitirHabManualAudio()) {
            return &CHabilitacaoAudioNaoPermitida::GetInst();
        }
        return &CConfirmaAudio::GetInst();
    case 2:
        CLogVota::GetInst().LogaOperadorSelecionou(TextoEncerrarVotacao());
        return &CIniciaFinalizacao::GetInst();
    case 3:
        CLogVota::GetInst().LogaOperadorSelecionou(TextoRegistrarMesarios());
        return &comum::CRegistrarMesarios::GetInst();
    case 4:
        CLogVota::GetInst().LogaOperadorSelecionou(TextoExibirContadores());
        if (comum::CLocal::GetInst().UrnaBiometrica()) {
            return &CContadoresBiometria::GetInst();
        }
        break;
    default:
        break;
    }
    return nullptr;
}





CEscolheOpcao::COpcaoDS::COpcaoDS(int numero, std::function<std::string()> texto)
    : m_numero(numero)
    , m_texto(std::move(texto))
{
}

CEscolheOpcao::SOpcao::SOpcao(int codigo, COpcaoDS ds)
    : m_codigo(codigo)
    , m_ds(std::move(ds))
{
}

std::string CEscolheOpcao::COpcaoDS::operator()() const
{
    return std::format("{}-{}", m_numero, m_texto());
}

} // namespace vota
