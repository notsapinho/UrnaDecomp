#include "app/vota/eleitor/comum/ctelasvota.h"

#include <format>
#include <functional>
#include <string>

#include "api/gui/cformbuilder.h"
#include "app/vota/comum/cpreshowformvota.h"
#include "app/vota/euevotaerror.h"
#include "ecourna/api/pattern/singleton.hpp"

namespace vota {

// (original lines 14-290: content not recovered)
#line 291
// <stubs>
// f13101 З 217 B З unmatched З name unknown
// void f13101(i32) { ... }
// </stubs>

// (original lines 296-483: content not recovered)
#line 484
// <stubs>
// f4184 З 610 B З unmatched З name unknown
// void f4184(i32, i32) { ... }

// f4181 З 427 B З unmatched З name unknown
// void f4181(i32, i32, i32, i32, i32) { ... }
// </stubs>

// (original lines 492-800: content not recovered)
#line 801
std::string MensagemErroCargo(const std::string& tela, const comum::md::CCargo& cargo, const std::string& erro)
{
    return tela + " - cargo " + std::to_string(cargo.GetID()) + " (" + cargo.GetNomeMasculino() + ") - " + erro;
}

// (original lines 806-818: content not recovered)
#line 819
// <stubs>
// f6678 З 192 B З unmatched З name unknown
// void f6678(i32, i32, i32) { ... }
// </stubs>

// (original lines 824-849: content not recovered)
#line 850
// <stubs>
// f6671 З 363 B З unmatched З name unknown
// void f6671(i32, i32, i32, i32) { ... }
// </stubs>

// (original lines 855-886: content not recovered)
#line 887
// <stubs>
// f6660 З 514 B З unmatched З name unknown
// void f6660(i32, i32, i32, i32) { ... }
// </stubs>

// (original lines 892-960: content not recovered)
#line 961
// <stubs>
// f6646 З 264 B З unmatched З name unknown
// void f6646(i32, i32, i32) { ... }
// </stubs>

// (original lines 966-989: content not recovered)
#line 990
// <stubs>
// f6641 З 272 B З unmatched З name unknown
// void f6641(i32, i32, i32) { ... }
// </stubs>

// (original lines 995-1045: content not recovered)
#line 1046
// <stubs>
// f6608 З 473 B З unmatched З name unknown
// void f6608(i32, i32, i32, i32, i32, i32) { ... }
// </stubs>

// (original lines 1051-1071: content not recovered)
#line 1072
// <stubs>
// f6605 З 557 B З unmatched З name unknown
// void f6605(i32, i32, i32) { ... }
// </stubs>

// (original lines 1077-1097: content not recovered)
#line 1098
// <stubs>
// f6603 З 436 B З unmatched З name unknown
// void f6603(i32, i32, i32) { ... }
// </stubs>

// (original lines 1103-1122: content not recovered)
#line 1123
// <stubs>
// f6602 З 374 B З unmatched З name unknown
// void f6602(i32, i32, i32) { ... }
// </stubs>

// (original lines 1128-1388: content not recovered)
#line 1389
// <stubs>
// f7787 З 148912 B З unmatched З name unknown
// void f7787() { ... }
// </stubs>

// (original lines 1394-1581: content not recovered)
#line 1582
// <stubs>
// f3064 З 1307 B З unmatched З name unknown
// void f3064(i32, i32) { ... }
// </stubs>

// (original lines 1587-3369: content not recovered)
#line 3370
namespace {

const api::SFont FONTE_TITULO{30, 0};
const api::SFont FONTE_AGUARDE{25, 0};

} // namespace

void AdicionaTelaAguarde(api::CFormBuilder& builder, const std::string& mensagem)
{
    builder.AddStatusHeader(api::CFormBuilder::STATUS_DATA_HORA | api::CFormBuilder::STATUS_ICONE_BATERIA);
    builder.AddTextField(mensagem, api::SPoint(320, 160), FONTE_TITULO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("Por favor, aguarde...", api::SPoint(320, 240), FONTE_AGUARDE, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
}

void AdicionaCabecalhoTesteTeclado(api::CFormBuilder& builder)
{
    builder.AddStatusHeader(api::CFormBuilder::STATUS_DATA_HORA | api::CFormBuilder::STATUS_ICONE_BATERIA);
    builder.AddTextField("Teste de teclado", api::SPoint(320, 80), FONTE_TITULO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddLine(api::SPoint(0, 429), api::SPoint(640, 429), static_cast<api::TColor>(3));
}

std::shared_ptr<api::IForm<api::IScreen>> TelaPreparandoDadosEncerramento()
{
    api::CFormBuilder builder;
    AdicionaTelaAguarde(builder, "Preparando dados para encerramento");
    return GetFormulario(builder, "telaPreparandoDadosEncerramento");
}

std::shared_ptr<api::IForm<api::IScreen>> TelaVotacaoEncerrada()
{
    api::CFormBuilder builder;
    AdicionaTelaAguarde(builder, "Votaчуo encerrada");
    return GetFormulario(builder, "telaVotacaoEncerrada");
}

std::shared_ptr<api::IForm<api::IScreen>> TelaCopiaResultadoParaMR()
{
    api::CFormBuilder builder;
    AdicionaTelaAguarde(builder, "Gravando o resultado na mэdia");
    return GetFormulario(builder, "telaCopiaResultadoParaMR");
}

std::shared_ptr<api::IForm<api::IScreen>> TelaEsperaRepetirTesteTeclado(
    std::function<std::string(const std::string&)> fonte)
{
    api::CFormBuilder builder;
    AdicionaCabecalhoTesteTeclado(builder);
    const api::SFont fonteTexto{25, 0};
    const std::chrono::milliseconds intervalo(200);
    builder.AddTextFieldUpdate(fonte, api::SPoint(320, 170), intervalo, fonteTexto, "Por favor, espere {}s para a",
                               api::ALINHAMENTO_CENTRO);
    builder.AddTextField("realizaчуo de uma nova tentativa", api::SPoint(320, 220), fonteTexto, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("de execuчуo do teste.", api::SPoint(320, 270), fonteTexto, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    return GetFormulario(builder, "telaEsperaRepetirTesteTeclado");
}

// (original lines 3431-3433: content not recovered)
#line 3434
SINGLETON_IMPL_GET_INST(CTelasVota, s_mutex, s_instancia)

std::unique_ptr<CTelasVota> CTelasVota::s_instancia;
std::mutex CTelasVota::s_mutex;

CTelasVota::~CTelasVota() = default;

// (original lines 3441-3529: content not recovered)
#line 3530
CFormInterativoTelaVota CTelasVota::GetTelaCargo(const comum::TCargoID cargo, const ETelaVotacao tela) const
{
    const auto it = m_mapaTelas.find(cargo);
    if (it == m_mapaTelas.end()) {
        throw CUeVotaError(EUE_VOTA_CONJUNTO_TELAS_INEXISTENTE,
                           std::format("Nao existe o conjunto de telas associado ao cargo id {}", cargo));
    }
    return it->second.GetTela(tela);
}

} // namespace vota
