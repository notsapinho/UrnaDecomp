#include "app/vota/eleitor/comum/ctelasvota.h"

#include <algorithm>
#include <format>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "api/gui/capplication.h"
#include "api/gui/cdataimage.h"
#include "api/gui/cformbuilder.h"
#include "api/gui/cimagefield.h"
#include "api/gui/cinputmenufield.h"
#include "api/gui/cinteractiveformbuilder.h"
#include "api/gui/cprogressbar.h"
#include "api/gui/cqrcodeimage.h"
#include "api/gui/ctextfield.h"
#include "api/gui/ctextfieldmultiline.h"
#include "api/gui/iimagesurfaceops.h"
#include "api/hwil/iurna.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/cfotos.h"
#include "app/comum/dados/clocal.h"
#include "app/comum/dados/md/candidatura/ccandidatura.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/dados/md/parametrizacaourna/ctradutorfrase.h"
#include "app/vota/comum/cpreshowformvota.h"
#include "app/vota/eleitor/cestadoaudio.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/igeradorteclas.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/operador/outrasopcoes/citensmenuvota.h"
#include "ecourna/api/pattern/singleton.hpp"
#include "ecourna/api/util/cstringutils.hpp"

namespace vota {

// (original lines 43-290: content not recovered)
#line 291
// <stubs>
// f13101 · 217 B · unmatched · name unknown
// void f13101(i32) { ... }
// </stubs>

// (original lines 296-469: content not recovered)
#line 470
namespace {

template <typename SRCFT>
api::CFormBuilder::SharedField adicionaImagem(api::CFormBuilder& builder, SRCFT fonte, const api::SPoint& posicao)
{
    const auto imagem = std::make_shared<api::CDataImage<SRCFT>>(fonte);
    api::CFormBuilder::SharedField campo = std::make_shared<api::CImageField>(posicao, imagem, api::ANCHOR_TOP_RIGHT);
    builder.AddField(campo);
    return campo;
}

template <typename SRCFT>
api::SRect adicionaFotoEmoldurada(api::CFormBuilder& builder, const api::TPosition x, const api::TPosition y,
                                  const api::TPosition largura, const api::TPosition altura, SRCFT fonte)
{
    const api::SPoint posicao(x + 1, y + 1);
    adicionaImagem(builder, fonte, posicao);
    const api::SRect area = api::CPolySingleton<api::IScreen>::instance().GetImageSurfaceOps().ImageRect(
        largura, altura, posicao, api::ANCHOR_TOP_RIGHT);
    return area;
}

} // namespace

// (original lines 494-800: content not recovered)
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

// (original lines 1587-2999: content not recovered)
#line 3000
namespace {

const api::SFont FONTE_TITULO{30, 0};
const api::SFont FONTE_VERSAO{15, 0};

} // namespace

CFormInterativoTelaVota CTelasVota::CriaTelaMaisInformacoes()
{
    api::CInteractiveFormBuilder builder;
    builder.AddStatusHeader(api::CFormBuilder::STATUS_DATA_HORA | api::CFormBuilder::STATUS_ICONE_BATERIA);
    builder.AddTextField("Mais informações", api::SPoint(320, 100), FONTE_TITULO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    CMenuMaisInformacoesVota(builder).MontaMenu();
    const std::string processo =
        std::format("Processo eleitoral: {:05}", comum::CConfiguracaoEleicao::GetInst().GetProcessoEleitoral());
    const std::string pleito = std::format("Pleito: {:05}", comum::CConfiguracaoEleicao::GetInst().GetPleito().GetID());
    const std::string biometria = comum::CLocal::GetInst().UrnaBiometrica() ? "Sim" : "Não";
    builder.AddTextField(processo, api::SPoint(25, 360), FONTE_VERSAO, api::ALINHAMENTO_ESQUERDA,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField(pleito, api::SPoint(25, 380), FONTE_VERSAO, api::ALINHAMENTO_ESQUERDA,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("Local com biometria: " + biometria, api::SPoint(25, 400), FONTE_VERSAO,
                         api::ALINHAMENTO_ESQUERDA, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddLabeledInputControl({{'C', "Selecionar"}, {'D', "Retornar"}}, api::CApplication::s_areaTela, false);
    return GetFormularioInterativo(builder, "telaMaisInformacoes");
}

// (original lines 3028-3167: content not recovered)
#line 3168
namespace {

const api::SFont FONTE_INSTRUCAO_TESTE_TECLADO{20, 0};
const api::SFont FONTE_AGUARDE{25, 0};
const api::SFont FONTE_TECLA{20, 1};
const api::SFont FONTE_SUPLENTE{13, 0};

} // namespace

std::shared_ptr<api::IForm<api::IScreen>> TelaNeutra(const std::string& mensagem, const int16_t tamanho,
    const int opcoes)
{
    const std::vector<std::string> linhas = ecourna::api::util::CStringUtils::Split(mensagem, '&');
    api::CFormBuilder builder;
    builder.AddStatusHeader(api::CFormBuilder::STATUS_DATA_HORA | api::CFormBuilder::STATUS_ICONE_BATERIA);
    const ueword meio = tamanho / 2;
    const ueword altura = tamanho;
    const int passo = meio + altura;
    const ueword inicio = 240 - linhas.size() * altura + meio - tamanho / 4;
    for (size_t i = 0; i < linhas.size(); ++i) {
        builder.AddTextField(linhas[i], api::SPoint(320, inicio + i * passo), api::SFont{tamanho, 0},
                             api::ALINHAMENTO_CENTRO, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    }
    if (opcoes & 1) {
        AdicionaLocal(builder);
    }
    return GetFormulario(builder, "telaNeutra");
}

std::shared_ptr<api::IForm<api::IScreen>> TelaPorFavorAguarde()
{
    return TelaNeutra("Por favor, aguarde...", 35, 0);
}

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

CFormInterativoTelaVota CTelasVota::GetTelaTesteTecladoOpcional()
{
    return TelaTextoConfirmaCorrige("Quer testar o teclado?", "Testar", "Não testar");
}

CFormInterativoTelaVota CTelasVota::GetTelaTesteTecladoObrigatorio()
{
    return TelaTextoConfirmaCorrige("Por favor, teste o teclado", "Testar", std::nullopt);
}

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

CFormInterativoTelaVota CTelasVota::CriaTelaVisualizacaoCandidato(const comum::md::CCandidatura& candidatura,
                                                                  size_t pagina, size_t total)
{
    using api::TPosition;
    const comum::md::CCargo& cargo = comum::CConfiguracaoEleicao::GetInst().GetCargo(candidatura.GetCargoID());
    api::CInteractiveFormBuilder builder;
    auto limiteDireito = [&](const int topo, const int base) -> api::TPosition {
        const api::TPosition inicioFotos =
            644 - 111 * cargo.QtdSuplentes() - 5 * std::max<int>(cargo.QtdSuplentes(), 1);
        return std::min<api::TPosition>(topo < 287 ? 478 : inicioFotos, base < 287 ? 478 : inicioFotos);
    };
    auto adicionaLinha = [&](api::TPosition y, const std::string& rotulo, const std::string& valor) {
        const api::SRect area = builder
                                    .AddTextField(rotulo + ": ", api::SPoint(1, y), FONTE_INSTRUCAO_TESTE_TECLADO,
                                                  api::ALINHAMENTO_ESQUERDA, static_cast<api::TColor>(6),
                                                  static_cast<api::TColor>(1))
                                    ->Rect();
        const api::TPosition altura = (area.bottom - area.top) * 2 + 4;
        const api::TPosition base = area.top + altura;
        const api::SRect retangulo(area.right, area.top, limiteDireito(area.top, area.top + altura), base);
        return builder
            .AddTextFieldMultiLine(valor, retangulo, FONTE_INSTRUCAO_TESTE_TECLADO, api::ALINHAMENTO_ESQUERDA)
            ->Rect()
            .bottom;
    };
    auto textoSexo = [](const auto sexo) {
        switch (sexo) {
        case comum::md::CSexo::SEXO_MASCULINO:
            return "masculino";
        case comum::md::CSexo::SEXO_FEMININO:
            return "feminino";
        default:
            return "não informado";
        }
    };
    auto lerFotoCandidato = [](const comum::md::CDadosCandidato& dados) {
        return comum::CFotos::GetInst().GetImagem(dados.GetCodigo());
    };
    auto nomeSuplente = [&](const int suplente) {
        return cargo.GetNomeSuplente(suplente, candidatura.GetSuplente(suplente).GetSexo());
    };
    auto adicionaFotoSuplente = [&](const int suplente) {
        const api::TPosition x = suplente == cargo.QtdSuplentes() ? 639 : 523;
        const api::SRect foto = adicionaFotoEmoldurada(builder, x, 253, 111, 155,
                                                       std::bind(lerFotoCandidato, candidatura.GetSuplente(suplente)));
        builder.AddTextField(nomeSuplente(suplente), api::SPoint(foto.Width() / 2 + foto.left, foto.bottom + 1),
                             FONTE_SUPLENTE, api::ALINHAMENTO_CENTRO, static_cast<api::TColor>(2),
                             static_cast<api::TColor>(1));
    };

    // (original lines 3338-3360: content not recovered)
#line 3361
    std::function<void(TPosition, int)> adicionaSuplentes = [&](TPosition y, int suplente) {
        if (suplente > cargo.QtdSuplentes()) {
            return;
        }
        if (suplente > 2) {
            throw CUeVotaError(EUE_VOTA_VISUALIZACAO_CANDIDATO_SUPLENTES_DEMAIS, "Sem suporte a mais de 2 suplentes");
        }
        if (cargo.GetDetalheCandidato().GetSuplente(suplente).TemFoto()) {
            adicionaFotoSuplente(suplente);
        }
        y = adicionaLinha(y, nomeSuplente(suplente), candidatura.GetSuplente(suplente).GetNomeUrna());
        y = adicionaLinha(y, "Gênero", textoSexo(candidatura.GetSuplente(suplente).GetSexo()));
        adicionaSuplentes(y + 10, suplente + 1);
    };
    builder.AddFill(api::SPoint(0, 0), api::SPoint(250, 28), static_cast<api::TColor>(31));
    const comum::md::CDadosCandidato& titular = candidatura.GetTitular();
    auto adicionaFotoTitular = [&]() {
        const api::SRect foto = adicionaFotoEmoldurada(builder, 639, 1, 161, 225, std::bind(lerFotoCandidato, titular));
        if (cargo.QtdSuplentes() != 0) {
            builder.AddTextField(cargo.GetNome(titular.GetSexo()),
                                 api::SPoint(foto.Width() / 2 + foto.left, foto.bottom + 1),
                                 FONTE_INSTRUCAO_TESTE_TECLADO, api::ALINHAMENTO_CENTRO,
                                 static_cast<api::TColor>(2), static_cast<api::TColor>(1));
        }
    };
    api::TPosition y = builder
                           .AddTextField("VISUALIZAÇÃO", api::SPoint(125, 1), FONTE_TECLA, api::ALINHAMENTO_CENTRO,
                                         static_cast<api::TColor>(29), static_cast<api::TColor>(0))
                           ->Rect()
                           .bottom;
    y = builder
            .AddTextField(cargo.GetNome(titular.GetSexo()), api::SPoint(1, 30), FONTE_TITULO, api::ALINHAMENTO_ESQUERDA,
                          static_cast<api::TColor>(2), static_cast<api::TColor>(1))
            ->Rect()
            .bottom;
    y = adicionaLinha(y + 10, "Partido", std::to_string(candidatura.GetPartidoID()));
    y = adicionaLinha(y, "Número", std::format("{:0{}}", candidatura.GetCandidatoID(), cargo.GetNumeroDigitos()));
    y = adicionaLinha(y, "Nome", titular.GetNomeUrna());
    y = adicionaLinha(y, "Gênero", textoSexo(titular.GetSexo()));
    if (titular.GetSituacao() == 0) {
        if (cargo.TemFoto()) {
            adicionaFotoTitular();
        }
        adicionaSuplentes(y + 10, 1);
    } else {
        builder.AddTextField("Candidato não concorre.", api::SPoint(320, 250), FONTE_AGUARDE, api::ALINHAMENTO_CENTRO,
                             static_cast<api::TColor>(2), static_cast<api::TColor>(1));
        builder.AddTextField("Não há outras informações.", api::SPoint(320, 280), FONTE_AGUARDE,
                             api::ALINHAMENTO_CENTRO, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    }
    y = adicionaLinha(375, "Situação", titular.GetSituacao() != 0 ? "INAPTO" : "APTO");
    adicionaLinha(y, "Página", std::format("{}/{}", pagina, total));
    builder.AddLabeledInputControl({{'D', "Retornar"}}, api::CApplication::s_areaTela, false);
    if (total > 1) {
        builder.AddLabeledKey('4', pagina == 1 ? "Última página" : "Página anterior", api::ALINHAMENTO_ESQUERDA);
        builder.AddLabeledKey('6', pagina == total ? "Primeira página" : "Próxima página", api::ALINHAMENTO_CENTRO);
    }
    return GetFormularioInterativo(builder, "telaVisualizacaoCandidato");
}

// (original lines 3421-3433: content not recovered)
#line 3434
SINGLETON_IMPL_GET_INST(CTelasVota, s_mutex, s_instancia)

std::unique_ptr<CTelasVota> CTelasVota::s_instancia;
std::mutex CTelasVota::s_mutex;

const std::vector<std::string> TECLAS_TESTE_TECLADO{"1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "BRANCO", "CORRIGE", "CONFIRMA"};

// (original lines 3441-3472: content not recovered)
#line 3473
std::shared_ptr<api::IForm<api::IScreen>> CTelasVota::GetTelaContinuaVotacao()
{
    return TelaNeutra("CONTINUAÇÃO DA VOTAÇÃO&IDENTIFIQUE O ELEITOR", 40, 1);
}

CTelasVota::~CTelasVota() = default;

namespace {

// (original lines 3482-3484: content not recovered)
#line 3485
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

void CTelasVota::IncrementaBarraSincronismo()
{
    m_barraSincronismo->Incrementa();
}

// (original lines 3519-3529: content not recovered)
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

void AdicionaLocal(api::CFormBuilder& builder)
{
    comum::CLocal& local = comum::CLocal::GetInst();
    local.Carrega();
    std::string texto;
    if (local.TemSecao()) {
        texto = std::format("{}: {:05} - {}     {}: {:04}     {}: {:04}", comum::md::CTradutorFrase::Traduz("<MCSN>"),
                            local.GetMunicipio(), local.GetNomeMunicipio(), comum::md::CTradutorFrase::Traduz("<ZCSN>"),
                            local.GetZonaID(), comum::md::CTradutorFrase::Traduz("<SCSN>"), local.GetSecaoID());
    } else if (local.TemContingencia()) {
        texto = std::format("{}: {:05} - {}     {}: {:04}     {}", comum::md::CTradutorFrase::Traduz("<MCSN>"),
                            local.GetMunicipio(), local.GetNomeMunicipio(), comum::md::CTradutorFrase::Traduz("<ZCSN>"),
                            local.GetZonaID(), "CONTINGÊNCIA");
    }
    builder.AddFill(api::SPoint(0, 458), api::SPoint(640, 480), static_cast<api::TColor>(22));
    builder.AddTextField(texto, api::SPoint(320, 460), FONTE_VERSAO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(22));
}

namespace {

const api::SFont FONTE_TEXTO_CONFIRMA_CORRIGE{35, 0};

} // namespace

CFormInterativoTelaVota TelaTextoConfirmaCorrige(const std::string& texto, const std::optional<std::string>& confirma,
                                                 const std::optional<std::string>& corrige)
{
    api::CInteractiveFormBuilder builder;
    std::vector<std::pair<char, std::string>> teclas;
    if (confirma) {
        teclas.emplace_back('C', *confirma);
    }
    if (corrige) {
        teclas.emplace_back('D', *corrige);
    }
    builder.AddStatusHeader(api::CFormBuilder::STATUS_DATA_HORA | api::CFormBuilder::STATUS_ICONE_BATERIA);
    builder.AddTextField(texto, api::SPoint(320, 200), FONTE_TEXTO_CONFIRMA_CORRIGE, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddInputControl();
    builder.AddLabeledInputControl(teclas, api::CApplication::s_areaTela, false);
    return GetFormularioInterativo(builder, "telaTextoConfirmaCorrige");
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
    builder.AddTextField("Versão: " + api::CApplication::s_versao, api::SPoint(10, linhaVersao), FONTE_VERSAO,
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
























































std::shared_ptr<api::IForm<api::IScreen>> TelaRetireMR()
{
    api::CFormBuilder builder;
    builder.AddStatusHeader(api::CFormBuilder::STATUS_DATA_HORA | api::CFormBuilder::STATUS_ICONE_BATERIA);
    builder.AddTextField("Retire a mídia de resultado", api::SPoint(320, 170), FONTE_TITULO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("e faça a entrega", api::SPoint(320, 220), FONTE_TITULO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("conforme as instruções.", api::SPoint(320, 270), FONTE_TITULO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    return GetFormulario(builder, "telaRetireMR");
}

CFormInterativoTelaVota TelaLacreTampa()
{
    api::CInteractiveFormBuilder builder;
    builder.AddStatusHeader(api::CFormBuilder::STATUS_DATA_HORA | api::CFormBuilder::STATUS_ICONE_BATERIA);
    builder.AddTextField("Lacre a tampa do compartimento", api::SPoint(320, 145), FONTE_TITULO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("da mídia de resultado conforme", api::SPoint(320, 195), FONTE_TITULO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("as instruções", api::SPoint(320, 245), FONTE_TITULO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddLabeledInputControl({{'C', "Continuar"}}, api::CApplication::s_areaTela, false);
    return GetFormularioInterativo(builder, "telaLacreTampa");
}

CFormInterativoTelaVota TelaMRModoDemo()
{
    api::CInteractiveFormBuilder builder;
    builder.AddStatusHeader(api::CFormBuilder::STATUS_DATA_HORA | api::CFormBuilder::STATUS_ICONE_BATERIA);
    builder.AddTextField("Substitua a mídia de resultado por outra vazia", api::SPoint(320, 90), FONTE_AGUARDE,
                         api::ALINHAMENTO_CENTRO, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("para deixar a urna pronta para votação", api::SPoint(320, 130), FONTE_AGUARDE,
                         api::ALINHAMENTO_CENTRO, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("ou", api::SPoint(320, 210), FONTE_AGUARDE, api::ALINHAMENTO_CENTRO, static_cast<api::TColor>(2),
                         static_cast<api::TColor>(1));
    builder.AddTextField("Mantenha a mídia de resultado", api::SPoint(320, 290), FONTE_AGUARDE, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("para voltar para a verificação pré-eleição", api::SPoint(320, 330), FONTE_AGUARDE,
                         api::ALINHAMENTO_CENTRO, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddLabeledInputControl({{'C', "Prosseguir"}}, api::CApplication::s_areaTela, false);
    return GetFormularioInterativo(builder, "telaMRModoDemo");
}


std::shared_ptr<api::IForm<api::IScreen>> CTelasVota::GetTelaDestinoBUs()
{
    api::CFormBuilder builder;
    builder.AddStatusHeader(api::CFormBuilder::STATUS_DATA_HORA | api::CFormBuilder::STATUS_ICONE_BATERIA);
    builder.AddTextField("Imprimindo vias obrigatórias", api::SPoint(320, 60), FONTE_TITULO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("do Boletim de Urna", api::SPoint(320, 110), FONTE_TITULO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField(
        []() {
            const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
            return std::format("Via nº {}", static_cast<uebyte>(appInfo.GetVota().GetQtdBU() + 1));
        },
        api::SPoint(320, 170), FONTE_AGUARDE, api::ALINHAMENTO_CENTRO);
    builder.AddTextField("Por favor, aguarde...", api::SPoint(320, 200), FONTE_AGUARDE, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddLine(api::SPoint(0, 250), api::SPoint(639, 250), static_cast<api::TColor>(3));
    api::TPosition y = 275;
    for (const std::string& linha : ecourna::api::util::CStringUtils::Split(
             comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetTelaEmissaoBU(), '\n')) {
        if (!linha.empty()) {
            builder.AddTextField(linha, api::SPoint(10, y), FONTE_INSTRUCAO_TESTE_TECLADO, api::ALINHAMENTO_ESQUERDA,
                                 static_cast<api::TColor>(2), static_cast<api::TColor>(1));
            y += 25;
        }
    }
    return GetFormulario(builder, "telaDestinoBUs");
}

CFormInterativoTelaVota CTelasVota::GetTelaInspecionaUrna()
{
    return TelaTextoConfirmaCorrige("Por favor, inspecione cabina e urna.", "Continuar", std::nullopt);
}

std::shared_ptr<api::IForm<api::IScreen>> CTelasVota::GetTelaInspecaoTerminada()
{
    return TelaNeutra("Inspeção terminada.&Siga as instruções&no terminal do mesário.", 35, 0);
}

CFormInterativoTelaVota TelaTeclaErradaTesteTeclado()
{
    api::CInteractiveFormBuilder builder;
    AdicionaCabecalhoTesteTeclado(builder);
    builder.AddTextField("Teste Falhou", api::SPoint(320, 140), FONTE_TITULO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField(
        []() {
            const auto [esperada, pressionada] = CEstadoAudio::GetInst().GetTeclasTesteTeclado();
            return std::format("Falha: Esperada {}, pressionada {}", api::KeyName(esperada), api::KeyName(pressionada));
        },
        api::SPoint(320, 210), FONTE_AGUARDE, api::ALINHAMENTO_CENTRO);
    builder.AddLabeledInputControl({{'C', "Repetir teste"}, {'D', "Prosseguir"}}, api::CApplication::s_areaTela, false);
    builder.AddInputControl();
    return GetFormularioInterativo(builder, "telaTeclaErradaTesteTeclado");
}

CFormInterativoTelaVota TelaEnviarManutencaoTesteTeclado()
{
    api::CInteractiveFormBuilder builder;
    AdicionaCabecalhoTesteTeclado(builder);
    builder.AddTextField("Deseja enviar a urna para manutenção?", api::SPoint(320, 230), FONTE_TITULO,
                         api::ALINHAMENTO_CENTRO, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddLabeledInputControl({{'C', "Repetir teste"}, {'D', "Enviar para manutenção"}}, api::CApplication::s_areaTela,
                                   false);
    builder.AddInputControl();
    return GetFormularioInterativo(builder, "telaEnviarManutencaoTesteTeclado");
}

std::pair<CFormInterativoTelaVota, std::shared_ptr<api::CInputMenuField>> TelaFiltragemCandidatosPorCargo(
    const bool todos, const std::set<comum::md::CCargo>& cargos)
{
    api::CInteractiveFormBuilder builder;
    builder.AddStatusHeader(api::CFormBuilder::STATUS_DATA_HORA | api::CFormBuilder::STATUS_ICONE_BATERIA);
    builder.AddTextField("Visualização de candidatos", api::SPoint(320, 40), FONTE_TITULO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("Filtragem por cargo", api::SPoint(320, 75), FONTE_AGUARDE, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    std::shared_ptr<api::CInputMenuField> menu;
    if (cargos.empty()) {
        builder.AddTextField("Nenhum cargo disponível!", api::SPoint(320, 200), FONTE_AGUARDE, api::ALINHAMENTO_CENTRO,
                             static_cast<api::TColor>(2), static_cast<api::TColor>(1));
        builder.AddLabeledInputControl({{'D', "Retornar"}}, api::CApplication::s_areaTela, false);
    } else {
        menu = api::AddInputMenuField(builder, api::SPoint(10, 120), FONTE_INSTRUCAO_TESTE_TECLADO, "Selecione o cargo: ",
                                      310);
        if (todos) {
            menu->AddItem("Todos").SetDado(comum::md::TCargoID{0}).SetSearchText("0");
        }
        for (const comum::md::CCargo& cargo : cargos) {
            const std::string nome = cargo.GetDetalheCandidato().GetNomes().GetNomeMasculino();
            menu->AddItem(nome).SetDado(cargo.GetID());
        }
        builder.AddLabeledInputControl({{'C', "Confirmar seleção"}, {'D', "Retornar"}},
                                       api::CApplication::s_areaTela, false);
    }
    return {GetFormularioInterativo(builder, "telaFiltragemCandidatosPorCargo"), menu};
}

namespace {

const char TEXTO_ERRO_TESTE_TECLADO[] = "Erro no teste do teclado";
const char TEXTO_SOLICITE_AJUDA[] = "Por favor, solicite ajuda dos técnicos do TRE";
const char TEXTO_DEVIDAS_PROVIDENCIAS[] = "para as devidas providências.";

} // namespace

std::shared_ptr<api::IForm<api::IScreen>> TelaErroTesteTeclado()
{
    api::CFormBuilder builder;
    builder.AddStatusHeader(api::CFormBuilder::STATUS_DATA_HORA | api::CFormBuilder::STATUS_ICONE_BATERIA);
    builder.AddTextField(TEXTO_ERRO_TESTE_TECLADO, api::SPoint(320, 140), FONTE_TITULO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField(TEXTO_SOLICITE_AJUDA, api::SPoint(320, 220), FONTE_AGUARDE, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField(TEXTO_DEVIDAS_PROVIDENCIAS, api::SPoint(320, 260), FONTE_AGUARDE, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    return GetFormulario(builder, "telaErroTesteTeclado");
}

std::pair<CFormInterativoTelaVota, std::shared_ptr<api::CInputMenuField>> TelaMenuVisualizacaoCandidatos(
    TOpcaoMenuCandidatos porCargo, TOpcaoMenuCandidatos porPartido, TOpcaoMenuCandidatos candidato)
{
    api::CInteractiveFormBuilder builder;
    builder.AddStatusHeader(api::CFormBuilder::STATUS_DATA_HORA | api::CFormBuilder::STATUS_ICONE_BATERIA);
    builder.AddTextField("Visualização de candidatos", api::SPoint(320, 40), FONTE_TITULO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    const std::shared_ptr<api::CInputMenuField> menu =
        api::AddInputMenuField(builder, api::SPoint(40, 85), FONTE_AGUARDE, "Selecione um filtro: ", 32767);
    menu->AddItem("Por cargo").SetDado(porCargo);
    menu->AddItem("Por partido").SetDado(porPartido);
    menu->AddItem("Candidato específico").SetDado(candidato);
    builder.AddLabeledInputControl({{'C', "Executar opção"}, {'D', "Retornar"}}, api::CApplication::s_areaTela, false);
    return {GetFormularioInterativo(builder, "telaMenuVisualizacaoCandidatos"), menu};
}

} // namespace vota
