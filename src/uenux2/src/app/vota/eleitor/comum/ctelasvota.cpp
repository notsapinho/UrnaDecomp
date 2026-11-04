#include "app/vota/eleitor/comum/ctelasvota.h"

#include <format>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "api/gui/capplication.h"
#include "api/gui/cformbuilder.h"
#include "api/gui/cinteractiveformbuilder.h"
#include "api/gui/cqrcodeimage.h"
#include "api/gui/ctextfield.h"
#include "api/gui/ctextfieldmultiline.h"
#include "api/hwil/iurna.h"
#include "api/pattern/cpolysingleton.h"
#include "app/vota/comum/cpreshowformvota.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/igeradorteclas.h"
#include "app/vota/euevotaerror.h"
#include "ecourna/api/pattern/singleton.hpp"

namespace vota {

// (original lines 26-290: content not recovered)
#line 291
// <stubs>
// f13101 · 217 B · unmatched · name unknown
// void f13101(i32) { ... }
// </stubs>

// (original lines 296-483: content not recovered)
#line 484
// <stubs>
// f4184 · 610 B · unmatched · name unknown
// void f4184(i32, i32) { ... }

// f4181 · 427 B · unmatched · name unknown
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
// f6678 · 192 B · unmatched · name unknown
// void f6678(i32, i32, i32) { ... }
// </stubs>

// (original lines 824-849: content not recovered)
#line 850
// <stubs>
// f6671 · 363 B · unmatched · name unknown
// void f6671(i32, i32, i32, i32) { ... }
// </stubs>

// (original lines 855-886: content not recovered)
#line 887
// <stubs>
// f6660 · 514 B · unmatched · name unknown
// void f6660(i32, i32, i32, i32) { ... }
// </stubs>

// (original lines 892-960: content not recovered)
#line 961
// <stubs>
// f6646 · 264 B · unmatched · name unknown
// void f6646(i32, i32, i32) { ... }
// </stubs>

// (original lines 966-989: content not recovered)
#line 990
// <stubs>
// f6641 · 272 B · unmatched · name unknown
// void f6641(i32, i32, i32) { ... }
// </stubs>

// (original lines 995-1045: content not recovered)
#line 1046
// <stubs>
// f6608 · 473 B · unmatched · name unknown
// void f6608(i32, i32, i32, i32, i32, i32) { ... }
// </stubs>

// (original lines 1051-1071: content not recovered)
#line 1072
// <stubs>
// f6605 · 557 B · unmatched · name unknown
// void f6605(i32, i32, i32) { ... }
// </stubs>

// (original lines 1077-1097: content not recovered)
#line 1098
// <stubs>
// f6603 · 436 B · unmatched · name unknown
// void f6603(i32, i32, i32) { ... }
// </stubs>

// (original lines 1103-1122: content not recovered)
#line 1123
// <stubs>
// f6602 · 374 B · unmatched · name unknown
// void f6602(i32, i32, i32) { ... }
// </stubs>

// (original lines 1128-1289: content not recovered)
#line 1290
namespace {

struct SLayoutTecla {
    api::SPoint posicao;
    api::SPoint tamanho;
    api::TFontSize tamanhoFonte;
    char tecla;
};

const auto GetKeyboardLayout()
{
    if (api::CPolySingleton<api::IUrna>::instance().Modelo() <= 2019) {
        return std::map<std::string, SLayoutTecla>{
            {TECLAS_TESTE_TECLADO[0], {{245, 140}, {41, 36}, 25, '1'}},
            {TECLAS_TESTE_TECLADO[1], {{320, 140}, {41, 36}, 25, '2'}},
            {TECLAS_TESTE_TECLADO[2], {{395, 140}, {41, 36}, 25, '3'}},
            {TECLAS_TESTE_TECLADO[3], {{245, 195}, {41, 36}, 25, '4'}},
            {TECLAS_TESTE_TECLADO[4], {{320, 195}, {41, 36}, 25, '5'}},
            {TECLAS_TESTE_TECLADO[5], {{395, 195}, {41, 36}, 25, '6'}},
            {TECLAS_TESTE_TECLADO[6], {{245, 250}, {41, 36}, 25, '7'}},
            {TECLAS_TESTE_TECLADO[7], {{320, 250}, {41, 36}, 25, '8'}},
            {TECLAS_TESTE_TECLADO[8], {{395, 250}, {41, 36}, 25, '9'}},
            {TECLAS_TESTE_TECLADO[9], {{320, 305}, {41, 36}, 25, '0'}},
            {TECLAS_TESTE_TECLADO[10], {{201, 360}, {85, 36}, 15, 'B'}},
            {TECLAS_TESTE_TECLADO[11], {{320, 360}, {85, 36}, 15, 'D'}},
            {TECLAS_TESTE_TECLADO[12], {{439, 345}, {85, 51}, 15, 'C'}},
        };
    }
    return std::map<std::string, SLayoutTecla>{
        {TECLAS_TESTE_TECLADO[0], {{185, 140}, {41, 36}, 25, '1'}},
        {TECLAS_TESTE_TECLADO[1], {{260, 140}, {41, 36}, 25, '2'}},
        {TECLAS_TESTE_TECLADO[2], {{335, 140}, {41, 36}, 25, '3'}},
        {TECLAS_TESTE_TECLADO[3], {{185, 195}, {41, 36}, 25, '4'}},
        {TECLAS_TESTE_TECLADO[4], {{260, 195}, {41, 36}, 25, '5'}},
        {TECLAS_TESTE_TECLADO[5], {{335, 195}, {41, 36}, 25, '6'}},
        {TECLAS_TESTE_TECLADO[6], {{185, 250}, {41, 36}, 25, '7'}},
        {TECLAS_TESTE_TECLADO[7], {{260, 250}, {41, 36}, 25, '8'}},
        {TECLAS_TESTE_TECLADO[8], {{335, 250}, {41, 36}, 25, '9'}},
        {TECLAS_TESTE_TECLADO[9], {{260, 305}, {41, 36}, 25, '0'}},
        {TECLAS_TESTE_TECLADO[10], {{433, 140}, {85, 36}, 15, 'B'}},
        {TECLAS_TESTE_TECLADO[11], {{433, 195}, {85, 36}, 15, 'D'}},
        {TECLAS_TESTE_TECLADO[12], {{433, 250}, {85, 91}, 15, 'C'}},
    };
}

} // namespace

// (original lines 1337-1388: content not recovered)
#line 1389
// <stubs>
// f7787 · 148912 B · unmatched · name unknown
// void f7787() { ... }
// </stubs>

// (original lines 1394-1581: content not recovered)
#line 1582
// <stubs>
// f3064 · 1307 B · unmatched · name unknown
// void f3064(i32, i32) { ... }
// </stubs>

// (original lines 1587-3369: content not recovered)
#line 3370
namespace {

const api::SFont FONTE_TITULO{30, 0};
const api::SFont FONTE_INSTRUCAO_TESTE_TECLADO{20, 0};
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
    AdicionaTelaAguarde(builder, "Votação encerrada");
    return GetFormulario(builder, "telaVotacaoEncerrada");
}

std::shared_ptr<api::IForm<api::IScreen>> TelaCopiaResultadoParaMR()
{
    api::CFormBuilder builder;
    AdicionaTelaAguarde(builder, "Gravando o resultado na mídia");
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
    builder.AddTextField("realização de uma nova tentativa", api::SPoint(320, 220), fonteTexto, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("de execução do teste.", api::SPoint(320, 270), fonteTexto, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    return GetFormulario(builder, "telaEsperaRepetirTesteTeclado");
}

// (original lines 3432-3433: content not recovered)
#line 3434
SINGLETON_IMPL_GET_INST(CTelasVota, s_mutex, s_instancia)

std::unique_ptr<CTelasVota> CTelasVota::s_instancia;
std::mutex CTelasVota::s_mutex;

const std::vector<std::string> TECLAS_TESTE_TECLADO{"1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "BRANCO", "CORRIGE", "CONFIRMA"};

std::pair<CFormInterativoTelaVota, TTeclasTesteTeclado> TelaTesteTeclado()
{
    api::CInteractiveFormBuilder builder;
    const auto layout = GetKeyboardLayout();
    TTeclasTesteTeclado teclas;
    for (const std::string& nome : TECLAS_TESTE_TECLADO) {
        const SLayoutTecla& tecla = layout.at(nome);
        const auto caixa = AdicionaCaixaTecla(builder, nome, tecla.posicao, api::SFont{tecla.tamanhoFonte, 0}, tecla.tamanho);
        teclas.insert({nome, {tecla.tecla, caixa}});
    }
    AdicionaCabecalhoTesteTeclado(builder);
    const std::string instrucao = "Pressione a tecla destacada";
    builder.AddTextField(instrucao, api::SPoint(320, 440), FONTE_INSTRUCAO_TESTE_TECLADO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    return {GetFormularioInterativo(builder, "telaTesteTeclado"), teclas};
}

std::vector<std::string> SorteiaTeclasTesteTeclado(testeteclado::impl::IGeradorTeclas& gerador)
{
    return gerador.GeraSequencia(TECLAS_TESTE_TECLADO);
}

CTelasVota::~CTelasVota() = default;

namespace {

const api::SFont FONTE_VERSAO{15, 0};
const api::SFont FONTE_TECLA{20, 1};

api::SRect AreaTela()
{
    return api::CApplication::s_areaTela;
}

} // namespace

api::CFormBuilder::SharedField AdicionaTextoMultiLinha(api::CFormBuilder& builder, std::function<std::string()> fonte,
                                                      const api::SRect& rect, const api::SFont& font,
                                                      api::ETextAlignment alinhamento)
{
    const auto texto = std::make_shared<api::CDataText<std::function<std::string()>>>(fonte, alinhamento);
    api::CFormBuilder::SharedField campo = std::make_shared<api::CTextFieldMultiLine>(
        rect, texto, font, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddField(campo);
    return campo;
}

api::CFormBuilder::SharedField AdicionaTexto(api::CFormBuilder& builder, std::function<std::string()> fonte,
                                            const api::SPoint& posicao, const api::SFont& font,
                                            api::ETextAlignment alinhamento)
{
    const auto texto = std::make_shared<api::CDataText<std::function<std::string()>>>(fonte, alinhamento);
    api::CFormBuilder::SharedField campo = std::make_shared<api::CTextField>(
        posicao, texto, font, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddField(campo);
    return campo;
}

// (original lines 3499-3529: content not recovered)
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

CFormInterativoTelaVota CTelasVota::CriaTelaQRCodeBU(std::function<std::string()> ajuda,
                                                     std::function<std::string()> qrcode,
                                                     std::function<std::string()> pagina) const
{
    api::CInteractiveFormBuilder builder;
    const api::SRect area = AreaTela();
    builder.AddStatusHeader(api::CFormBuilder::STATUS_DATA_HORA | api::CFormBuilder::STATUS_ICONE_BATERIA);
    const api::TPosition altura = area.bottom + 1;
    const api::TPosition linha = area.bottom - 49;
    const api::TPosition linhaPagina = area.bottom - 109;
    const api::TPosition linhaTecla9 = area.bottom - 27;
    const api::TPosition linhaVersao = area.bottom - 79;
    const auto imagem = std::make_shared<api::CQRCodeImage>(380, qrcode);
    builder.AddImage(imagem, api::SPoint(630, 35));
    const api::SPoint posicaoConfirma(area.right - 20, altura - 48);
    const api::SPoint posicaoContinuar(area.right - 20, altura - 27);
    builder.AddLine(api::SPoint(area.left, linha), api::SPoint(area.right, linha), static_cast<api::TColor>(3));
    builder.AddTextField("Versao: " + api::CApplication::s_versao, api::SPoint(10, linhaVersao), FONTE_VERSAO,
                         api::ALINHAMENTO_ESQUERDA, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("BU digital", api::SPoint(10, 45), FONTE_TITULO, api::ALINHAMENTO_ESQUERDA,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    AdicionaTextoMultiLinha(builder, ajuda, api::SRect(10, 95, 230, altura - 115), FONTE_INSTRUCAO_TESTE_TECLADO,
                            api::ALINHAMENTO_ESQUERDA);
    builder.AddInputControl(5);
    AdicionaTexto(builder, pagina, api::SPoint(230, linhaPagina), FONTE_INSTRUCAO_TESTE_TECLADO,
                  api::ALINHAMENTO_DIREITA)
        ->SetName("Pagina");
    const auto tecla9 = builder.AddTextField("9", api::SPoint(10, linhaTecla9), FONTE_TECLA, api::ALINHAMENTO_ESQUERDA,
                                             static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    tecla9->SetName("9");
    builder.AddTextField("para próxima parte", api::SPoint(tecla9->Rect().right + 4, linhaTecla9),
                         FONTE_INSTRUCAO_TESTE_TECLADO, api::ALINHAMENTO_ESQUERDA, static_cast<api::TColor>(2),
                         static_cast<api::TColor>(1))
        ->SetName("Acao9");
    builder.AddTextField("3", api::SPoint(10, area.bottom - 48), FONTE_TECLA, api::ALINHAMENTO_ESQUERDA,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1))
        ->SetName("3");
    builder.AddTextField("para parte anterior", api::SPoint(tecla9->Rect().right + 4, area.bottom - 48),
                         FONTE_INSTRUCAO_TESTE_TECLADO, api::ALINHAMENTO_ESQUERDA, static_cast<api::TColor>(2),
                         static_cast<api::TColor>(1))
        ->SetName("Acao3");
    builder.AddTextField("Continuar", posicaoContinuar, FONTE_INSTRUCAO_TESTE_TECLADO, api::ALINHAMENTO_DIREITA,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1))
        ->SetName("AcaoConfirma");
    builder.AddTextField("CONFIRMA", posicaoConfirma, FONTE_INSTRUCAO_TESTE_TECLADO, api::ALINHAMENTO_DIREITA,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1))
        ->SetName("Confirma");
    builder.AddLabeledKey('B', "Ver certificado", api::ALINHAMENTO_CENTRO);
    return GetFormularioInterativo(builder, "telaQRCodeBU");
}

} // namespace vota
