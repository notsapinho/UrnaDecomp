#include "app/vota/eleitor/comum/ctelasvota.h"

#include <algorithm>
#include <chrono>
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
#include "api/gui/cdatatext.h"
#include "api/gui/cformbuilder.h"
#include "api/gui/cframedtext.h"
#include "api/gui/cgrayedframedtext.h"
#include "api/gui/cimagefield.h"
#include "api/gui/cimagefieldupdate.h"
#include "api/gui/cinputfield.h"
#include "api/gui/cinputmenufield.h"
#include "api/gui/cinteractiveformbuilder.h"
#include "api/gui/cmaskedtextfield.h"
#include "api/gui/cmovie.h"
#include "api/gui/cnumbervalidation.h"
#include "api/gui/cprogressbar.h"
#include "api/gui/cqrcodeimage.h"
#include "api/gui/ctextfield.h"
#include "api/gui/ctextfielddoubleline.h"
#include "api/gui/ctextfieldmultiline.h"
#include "api/gui/iimagesurfaceops.h"
#include "api/gui/iresource.h"
#include "api/hwil/iurna.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/cfotos.h"
#include "app/comum/dados/clocal.h"
#include "app/comum/dados/cqrcodeds.h"
#include "app/comum/dados/md/candidatura/ccandidatura.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/dados/md/parametrizacaourna/ctradutorfrase.h"
#include "app/comum/dados/md/rdv/cvoto.h"
#include "app/comum/informacao/cinformacaoeleicao.h"
#include "app/comum/relatorios/auxiliaresrelatorio.h"
#include "app/vota/comum/cpreshowformvota.h"
#include "app/vota/eleitor/cestadoaudio.h"
#include "app/vota/eleitor/comum/cinformacaoeleitor.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/igeradorteclas.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/operador/outrasopcoes/citensmenuvota.h"
#include "ecourna/api/pattern/singleton.hpp"
#include "ecourna/api/util/cstringutils.hpp"

namespace vota {

// (original lines 59-265: content not recovered)
#line 266
void AdicionaGifCargo(const comum::md::CCargo& cargo, api::CFormBuilder& builder)
{
    static const std::map<comum::TCargoID, std::string> gifs = {
        {1, ":/resource/gifs/presidente.gif"},
        {3, ":/resource/gifs/governador.gif"},
        {5, ":/resource/gifs/senador.gif"},
        {6, ":/resource/gifs/depFederal.gif"},
        {7, ":/resource/gifs/depEstadual.gif"},
        {8, ":/resource/gifs/depDistrital.gif"},
        {25, ":/resource/gifs/conselheiroDistrital.gif"},
        {11, ":/resource/gifs/prefeito.gif"},
        {13, ":/resource/gifs/vereador.gif"},
    };
    const auto it = gifs.find(cargo.GetID());
    const std::string nome = it != gifs.end() ? it->second : "";
    if (!nome.empty()) {
        const api::CMovie gif = api::getResourceMovie(nome);
        const std::shared_ptr<api::CMovie> filme = std::make_shared<api::CMovie>(gif);
        builder.AddMovie(api::SPoint(640, 480), filme);
    }
}

// (original lines 288-290: content not recovered)
#line 291
// <stubs>
// f13101 · 217 B · unmatched · name unknown
// void f13101(i32) { ... }
// </stubs>

// (original lines 296-299: content not recovered)
#line 300
const std::string& NumeroDigitado()
{
    return g_numeroDigitado;
}

namespace {

const api::SFont FONTE_NUMERO{40, 0};
const api::SFont FONTE_TITULO{30, 0};
const api::SFont FONTE_INSTRUCAO_TESTE_TECLADO{20, 0};
const char TEXTO_CONFIRMAR_VOTO[] = "CONFIRMAR este voto";
const api::SFont FONTE_TEXTO_CONFIRMA_CORRIGE{35, 0};
const api::SFont FONTE_NOME_CARGO{30, 1};
const api::SFont FONTE_AGUARDE{25, 0};

CFormInterativoTelaVota GetFormularioProgresso(api::CInteractiveFormBuilder& builder, const std::string& nome)
{
    return builder.GetInteractiveForm(std::make_shared<CPreShowProgressBar>(), nome, true);
}

void AdicionaLinhaRodape(api::CFormBuilder& builder, const api::TPosition largura)
{
    builder.AddRect(api::SPoint(0, 400), api::SPoint(largura, 401));
}

void AdicionaInstrucaoContinuar(api::CFormBuilder& builder)
{
    builder.AddRect(api::SPoint(0, 400), api::SPoint(639, 401));
    builder.AddTextField("Aperte a tecla:", api::SPoint(1, 405), FONTE_INSTRUCAO_TESTE_TECLADO, api::ALINHAMENTO_ESQUERDA,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("CONFIRMA", api::SPoint(130, 430), FONTE_INSTRUCAO_TESTE_TECLADO, api::ALINHAMENTO_DIREITA,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField(" para continuar", api::SPoint(130, 430), FONTE_INSTRUCAO_TESTE_TECLADO,
                         api::ALINHAMENTO_ESQUERDA, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
}

void AdicionaTextoPiscante(api::CFormBuilder& builder, const std::string& texto, const api::SFont fonte,
                           const api::TPosition x, const api::TPosition y)
{
    builder.AddBlinkingTextField(texto, api::SPoint(x, y), fonte, api::ALINHAMENTO_CENTRO);
}

struct DS_NomeCargoNeutroComEscolha {
    std::string operator()() const
    {
        const std::string nome = m_cargo.GetNomeNeutro();
        if (m_cargo.GetQtdeEscolhas() == 1) {
            return nome;
        }
        return nome + " - " + m_cargo.GetOrdinalEscolha(g_escolhaAtual);
    }

    comum::md::CCargo m_cargo;
};

template <typename FONTE>
api::CFormBuilder::SharedField AdicionaTextoDuasLinhas(api::CFormBuilder& builder, FONTE fonte,
                                                      const api::SPoint& linha1, const api::SPoint& linha2,
                                                      api::TPosition maxX, const api::SFont& font, api::TColor corFundo)
{
    const auto texto = std::make_shared<api::CDataText<FONTE>>(fonte);
    api::CFormBuilder::SharedField campo = std::make_shared<api::CTextFieldDoubleLine>(
        linha1, linha2, maxX, texto, font, static_cast<api::TColor>(2), corFundo);
    builder.AddField(campo);
    return campo;
}

template <typename FONTE>
api::CFormBuilder::SharedField AdicionaTextoFonte(api::CFormBuilder& builder, FONTE fonte, const api::SPoint& posicao,
                                                 const api::SFont& font)
{
    const auto texto = std::make_shared<api::CDataText<FONTE>>(fonte);
    api::CFormBuilder::SharedField campo = std::make_shared<api::CTextField>(
        posicao, texto, font, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddField(campo);
    return campo;
}

} // namespace

template <typename MASCARA>
api::CFormBuilder::SharedField AdicionaCampoNumero(api::CFormBuilder& builder, size_t tamanho, const api::SPoint& posicao)
{
    const auto texto = std::make_shared<api::CDataText<const std::string& (*)()>>(&NumeroDigitado);
    api::CFormBuilder::SharedField campo = std::make_shared<api::CMaskedTextField<MASCARA>>(
        texto, tamanho, posicao, FONTE_NUMERO, api::ALINHAMENTO_ESQUERDA);
    builder.AddField(campo);
    return campo;
}

void AdicionaInstrucaoTeclas(api::CFormBuilder& builder, const std::string& acao, api::TPosition largura)
{
    AdicionaLinhaRodape(builder, largura);
    builder.AddTextField("Aperte a tecla:", api::SPoint(1, 405), FONTE_INSTRUCAO_TESTE_TECLADO, api::ALINHAMENTO_ESQUERDA,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("CONFIRMA", api::SPoint(130, 430), FONTE_INSTRUCAO_TESTE_TECLADO, api::ALINHAMENTO_DIREITA,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField(" para " + acao, api::SPoint(130, 430), FONTE_INSTRUCAO_TESTE_TECLADO, api::ALINHAMENTO_ESQUERDA,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("CORRIGE", api::SPoint(130, 455), FONTE_INSTRUCAO_TESTE_TECLADO, api::ALINHAMENTO_DIREITA,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField([]() -> std::string { return " para REINICIAR este voto"; }, api::SPoint(130, 455),
                         FONTE_INSTRUCAO_TESTE_TECLADO, api::ALINHAMENTO_ESQUERDA);
}

namespace {

void AdicionaInstrucaoConfirmarVoto(api::CFormBuilder& builder, const api::TPosition largura)
{
    AdicionaInstrucaoTeclas(builder, TEXTO_CONFIRMAR_VOTO, largura);
}

} // namespace

api::TPosition AdicionaPergunta(api::CFormBuilder& builder, const comum::md::CCargo& cargo)
{
    std::string pergunta = cargo.GetDetalheConsulta().GetPergunta();
    std::replace(pergunta.begin(), pergunta.end(), '|', '\n');
    const api::SRect area = builder
                                .AddTextFieldMultiLine(pergunta, api::SRect(10, 50, 629, 255),
                                                       FONTE_TEXTO_CONFIRMA_CORRIGE, api::ALINHAMENTO_CENTRO)
                                ->Rect();
    return area.bottom + 23;
}


namespace {

std::map<std::pair<std::string, bool>, std::shared_ptr<api::CMovie>> s_gifs;

std::shared_ptr<api::CMovie> CarregaGif(const std::string& nome, const bool conferencia)
{
    const std::pair<std::string, bool> chave(nome, conferencia);
    const auto it = s_gifs.find(chave);
    if (it != s_gifs.end()) {
        return it->second;
    }
    const api::CMovie gif = api::getResourceMovie(nome);
    const auto quadro = {gif.FrameAtual()};
    const std::shared_ptr<api::CMovie> filme =
        conferencia ? std::make_shared<api::CMovie>(quadro, gif.Tamanho()) : std::make_shared<api::CMovie>(gif);
    s_gifs.emplace(chave, filme);
    return s_gifs.at(chave);
}

} // namespace

void AdicionaGif(const comum::md::CVoto::ETipo tipo, api::CFormBuilder& builder, const bool conferencia)
{
    std::string nome;
    switch (tipo) {
    case comum::md::CVoto::BRANCO:
        nome = ":/resource/gifs/votoBranco.gif";
        break;
    case comum::md::CVoto::NULO:
        nome = ":/resource/gifs/votoNulo.gif";
        break;
    case comum::md::CVoto::LEGENDA:
        nome = ":/resource/gifs/votoLegenda.gif";
        break;
    default:
        return;
    }
    const std::shared_ptr<api::CMovie> filme = CarregaGif(nome, conferencia);
    builder.AddMovie(api::SPoint(640, 480), filme);
}

// (original lines 467-469: content not recovered)
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

// (original lines 494-776: content not recovered)
#line 777
namespace {

std::shared_ptr<api::IInputField<api::IScreen>> AdicionaCampo(api::CFormBuilder& builder,
    const std::shared_ptr<api::IInputValidation>& validacao, const size_t tamanho, const bool confirmaAoCompletar,
    const bool corrigeLimpa, const bool aceitaConfirma, const bool aceitaBranco, const bool corrigeSai,
    const api::SPoint& posicao, const api::SFont& fonte, const api::ETextAlignment alinhamento)
{
    std::shared_ptr<api::IInputField<api::IScreen>> campo(new api::CInputField<api::CFramedText>(validacao, tamanho,
        confirmaAoCompletar, corrigeLimpa, aceitaConfirma, aceitaBranco, corrigeSai, posicao, fonte, alinhamento));
    builder.AddField(campo);
    return campo;
}

} // namespace

std::shared_ptr<api::IInputField<api::IScreen>> AdicionaCampoNumerico(api::CFormBuilder& builder, const size_t tamanho,
    const bool confirmaAoCompletar, const bool corrigeLimpa, const bool aceitaConfirma, const bool aceitaBranco,
    const bool corrigeSai, const api::SPoint& posicao, const api::SFont& fonte, const api::ETextAlignment alinhamento)
{
    return AdicionaCampo(builder, std::shared_ptr<api::IInputValidation>(new api::CNumberValidation()), tamanho,
                         confirmaAoCompletar, corrigeLimpa, aceitaConfirma, aceitaBranco, corrigeSai, posicao, fonte,
                         alinhamento);
}

std::string MensagemErroCargo(const std::string& tela, const comum::md::CCargo& cargo, const std::string& erro)
{
    return tela + " - cargo " + std::to_string(cargo.GetID()) + " (" + cargo.GetNomeMasculino() + ") - " + erro;
}

void AdicionaNomeCargo(const comum::md::CCargo& cargo, api::CFormBuilder& builder, api::TPosition x, api::TPosition y)
{
    if (cargo.TemFoto()) {
        AdicionaTextoDuasLinhas(builder, DS_NomeCargoNeutroComEscolha{cargo}, api::SPoint(x, y), api::SPoint(x, y + 35),
                                639, FONTE_NOME_CARGO, static_cast<api::TColor>(1));
    } else {
        AdicionaTextoFonte(builder, DS_NomeCargoNeutroComEscolha{cargo}, api::SPoint(x, y), FONTE_NOME_CARGO);
    }
}

void AdicionaRodapeConfira(api::CFormBuilder& builder, api::TPosition largura)
{
    AdicionaLinhaRodape(builder, largura);
    builder.AddBlinkingTextField("CONFIRA O SEU VOTO", api::SPoint(largura / 2, 420), FONTE_TITULO, api::ALINHAMENTO_CENTRO);
}

// <stubs>
// f6678 · 192 B · unmatched · name unknown
// void f6678(i32, i32, i32) { ... }
// </stubs>

// (original lines 827-849: content not recovered)
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

// (original lines 892-957: content not recovered)
#line 958
namespace {

void adicionaBaseTelaVotoBrancoCandidato(api::CFormBuilder& builder, const std::string& tela,
                                         const comum::md::CCargo& cargo, api::TPosition x)
{
    if (!cargo.HasDetalheCandidato()) {
        throw CUeVotaError(EUE_VOTA_TELA_VOTO_BRANCO_CANDIDATO_CARGO_INVALIDO,
                           MensagemErroCargo(tela, cargo, "não é de candidato"));
    }
    AdicionaNomeCargo(cargo, builder, 10, 60);
    AdicionaTextoPiscante(builder, "VOTO EM BRANCO", FONTE_NUMERO, x, 200);
}

} // namespace

// (original lines 973-989: content not recovered)
#line 990
// <stubs>
// f6641 · 272 B · unmatched · name unknown
// void f6641(i32, i32, i32) { ... }
// </stubs>

// (original lines 995-1007: content not recovered)
#line 1008
namespace {

void adicionaBaseTelaVotoNuloConsulta(api::CFormBuilder& builder, const std::string& tela, const comum::md::CCargo& cargo,
                                      const std::string& texto)
{
    if (!cargo.IsConsulta()) {
        throw CUeVotaError(EUE_VOTA_TELA_VOTO_NULO_CARGO_INVALIDO, MensagemErroCargo(tela, cargo, "não é de consulta"));
    }
    const api::TPosition y = AdicionaPergunta(builder, cargo);
    const uebyte digitos = cargo.GetNumeroDigitos();
    AdicionaCampoNumero<api::CFramedText>(builder, digitos, api::SPoint(100 - 40 * digitos, y));
    builder.AddTextField(texto, api::SPoint(100, y + 3), FONTE_NUMERO, api::ALINHAMENTO_ESQUERDA,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    AdicionaTextoPiscante(builder, "VOTO NULO", FONTE_NUMERO, 320, 345);
}

} // namespace

// (original lines 1026-1041: content not recovered)
#line 1042
namespace {

void adicionaBaseTelaVotoNuloCandidato(api::CFormBuilder& builder, const std::string& tela, const comum::md::CCargo& cargo,
                                       const std::string& texto, uebyte digitos, api::TPosition x, api::TPosition yCampo,
                                       api::TPosition yTexto, api::TPosition& proximoX, const bool piscante)
{
    if (!cargo.HasDetalheCandidato()) {
        throw CUeVotaError(EUE_VOTA_TELA_VOTO_NULO_CARGO_INVALIDO, MensagemErroCargo(tela, cargo, "não é de candidato"));
    }
    AdicionaNomeCargo(cargo, builder, 10, 60);
    const api::CFormBuilder::SharedField campo = AdicionaCampoNumero<api::CGrayedFramedText>(
        builder, static_cast<uebyte>(cargo.GetNumeroDigitos() - digitos), api::SPoint(x, yCampo));
    proximoX = campo->Rect().right + 5;
    builder.AddTextField(texto, api::SPoint(x, yTexto), FONTE_AGUARDE, api::ALINHAMENTO_ESQUERDA,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    if (piscante) {
        AdicionaTextoPiscante(builder, "VOTO NULO", FONTE_NUMERO, 195, 345);
    }
}

} // namespace

// (original lines 1064-1071: content not recovered)
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

// (original lines 1394-1529: content not recovered)
#line 1530
CFormInterativoTelaVota CTelasVota::CriaTelaVotoNuloCandidato(const comum::md::CCargo& cargo, const std::string& confirma,
                                                             const std::string& mensagem, uebyte digitos,
                                                             api::TPosition x, api::TPosition yCampo,
                                                             api::TPosition yTexto)
{
    api::CInteractiveFormBuilder builder;
    AdicionaGif(comum::md::CVoto::NULO, builder, false);
    api::TPosition proximoX;
    adicionaBaseTelaVotoNuloCandidato(builder, "CriaTelaVotoNuloCandidato", cargo, mensagem, digitos, x, yCampo, yTexto,
                                      proximoX, true);
    AdicionaInstrucaoTeclas(builder, confirma, 389);
    if (digitos == 0) {
        builder.AddInputControl();
    } else {
        AdicionaCampoNumerico(builder, digitos, false, true, true, false, true, api::SPoint(proximoX, yCampo),
                              FONTE_NUMERO, api::ALINHAMENTO_ESQUERDA);
    }
    return GetFormularioProgresso(builder, "telaVotoNuloCandidato");
}

CFormInterativoTelaVota CTelasVota::CriaTelaConferenciaVotoNuloCandidato(const comum::md::CCargo& cargo,
                                                                        const std::string& mensagem, api::TPosition x,
                                                                        api::TPosition yCampo, api::TPosition yTexto)
{
    api::CInteractiveFormBuilder builder;
    AdicionaGif(comum::md::CVoto::NULO, builder, true);
    api::TPosition proximoX;
    adicionaBaseTelaVotoNuloCandidato(builder, "CriaTelaConferenciaVotoNuloCandidato", cargo, mensagem, 0, x, yCampo,
                                      yTexto, proximoX, true);
    AdicionaRodapeConfira(builder, 389);
    return GetFormularioProgresso(builder, "telaConferenciaVotoNuloCandidato");
}

// (original lines 1563-1569: content not recovered)
#line 1570
CFormInterativoTelaVota CTelasVota::CriaTelaConferenciaVotoBrancoCandidato(const comum::md::CCargo& cargo)
{
    api::CInteractiveFormBuilder builder;
    AdicionaGif(comum::md::CVoto::BRANCO, builder, true);
    adicionaBaseTelaVotoBrancoCandidato(builder, "CriaTelaConferenciaVotoBrancoCandidato", cargo, 195);
    AdicionaRodapeConfira(builder, 389);
    return GetFormularioProgresso(builder, "telaConferenciaVotoBrancoCandidato");
}

// (original lines 1579-1581: content not recovered)
#line 1582
CFormInterativoTelaVota CTelasVota::CriaTelaVotoCargoSemCandidato(const comum::md::CCargo& cargo, api::TPosition)
{
    if (!cargo.HasDetalheCandidato()) {
        throw CUeVotaError(EUE_VOTA_TELA_VOTO_CARGO_SEM_CANDIDATO_CARGO_INVALIDO,
                           MensagemErroCargo("CriaTelaVotoCargoSemCandidato", cargo, "não é de candidato"));
    }
    api::CInteractiveFormBuilder builder;
    AdicionaNomeCargo(cargo, builder, 10, 60);
    AdicionaTextoPiscante(builder, "NÃO HÁ CANDIDATOS CONCORRENDO", FONTE_TITULO, 320, 200);
    AdicionaInstrucaoContinuar(builder);
    builder.AddInputControl();
    return GetFormularioProgresso(builder, "telaVotoCargoSemCandidato");
}

// (original lines 1596-1602: content not recovered)
#line 1603
CFormInterativoTelaVota CTelasVota::CriaTelaVotoNuloConsulta(const comum::md::CCargo& cargo, const std::string& mensagem)
{
    api::CInteractiveFormBuilder builder;
    adicionaBaseTelaVotoNuloConsulta(builder, "CriaTelaVotoNuloConsulta", cargo, mensagem);
    AdicionaInstrucaoConfirmarVoto(builder, 639);
    builder.AddInputControl();
    return GetFormularioProgresso(builder, "telaVotoNuloConsulta");
}

CFormInterativoTelaVota CTelasVota::CriaTelaConferenciaVotoNuloConsulta(const comum::md::CCargo& cargo,
                                                                       const std::string& mensagem)
{
    api::CInteractiveFormBuilder builder;
    adicionaBaseTelaVotoNuloConsulta(builder, "CriaTelaConferenciaVotoNuloConsulta", cargo, mensagem);
    AdicionaRodapeConfira(builder, 639);
    return GetFormularioProgresso(builder, "telaConferenciaVotoNuloConsulta");
}


CFormInterativoTelaVota CTelasVota::CriaTelaVotoBrancoCandidato(const comum::md::CCargo& cargo)
{
    api::CInteractiveFormBuilder builder;
    AdicionaGif(comum::md::CVoto::BRANCO, builder, false);
    adicionaBaseTelaVotoBrancoCandidato(builder, "CriaTelaVotoBrancoCandidato", cargo, 195);
    AdicionaInstrucaoConfirmarVoto(builder, 389);
    builder.AddInputControl();
    return GetFormularioProgresso(builder, "telaVotoBrancoCandidato");
}

// (original lines 1632-2949: content not recovered)
#line 2950
std::shared_ptr<api::IForm<api::IScreen>> CTelasVota::CriaTelaFim(const std::string& texto,
                                                                    const api::TFontSize tamanhoFim,
                                                                    const api::TFontSize tamanhoTexto)
{
    const api::SFont fonteFim{tamanhoFim, 0};
    const api::SFont fonteTexto{tamanhoTexto, 0};
    api::CFormBuilder builder;
    builder.AddStatusHeader(api::CFormBuilder::STATUS_DATA_HORA | api::CFormBuilder::STATUS_ICONE_BATERIA);
    builder.AddTextField("FIM", api::SPoint(320, 140), fonteFim, api::ALINHAMENTO_CENTRO, static_cast<api::TColor>(2),
                         static_cast<api::TColor>(1));
    builder.AddTextField(texto, api::SPoint(629, 408), fonteTexto, api::ALINHAMENTO_DIREITA, static_cast<api::TColor>(5),
                         static_cast<api::TColor>(1));
    AdicionaLocal(builder);
    return GetFormulario(builder, "telaFim");
}

// (original lines 2966-2999: content not recovered)
#line 3000
namespace {


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

CFormInterativoTelaVota CTelasVota::CriaTelaAntesHorarioZeresima()
{
    const api::CDateTime horario = comum::CConfiguracaoEleicao::GetInst().GetDataHoraZeresima();
    const std::string hora = horario.GetHora().Format("h");
    const std::string minuto = horario.GetHora().Format("mm");
    const std::string data = horario.GetData().Format("DD/MM/YYYY");
    api::CInteractiveFormBuilder builder;
    AdicionaTelaQRCode(builder, "ATENÇÃO", "Esta urna eletrônica só funcionará a partir de",
                       hora + "h" + minuto + " do dia " + data + ".", comum::CQRCodeDS::eOrigemTela);
    const bool emiteEstado =
        comum::CInformacaoEleicao(comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna()).GetNumViasEstadoUrna() >
        comum::CAppInfo::GetInst().GetVota().GetNumViasImpressasRelatorios().GetNumViasEstadoUrna();
    std::vector<std::pair<char, std::string>> teclas;
    if (emiteEstado) {
        teclas.emplace_back('C', "Emissão do estado da urna");
    }
    teclas.emplace_back('B', "Mais informações");
    builder.AddLabeledInputControl(teclas, api::CApplication::s_areaTela, false);
    return GetFormularioInterativo(builder, "telaAntesHorarioZeresima");
}

namespace {

// (original lines 3072-3074: content not recovered)
#line 3075
template <typename IMAGEM>
api::CFormBuilder::SharedField AdicionaImagemAtualizada(api::CFormBuilder& builder, IMAGEM imagem,
                                                        const api::SPoint& posicao,
                                                        const std::chrono::milliseconds& intervalo,
                                                        api::EAnchorPoint ancora)
{
    api::CFormBuilder::SharedField campo = std::make_shared<api::CImageFieldUpdate>(posicao, imagem, intervalo, ancora);
    builder.AddField(campo);
    return campo;
}

} // namespace

void AdicionaTelaQRCode(api::CFormBuilder& builder, const std::string& titulo, const std::string& mensagem,
                        const std::string& detalhe, const comum::CQRCodeDS::EOrigem origem)
{
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    const comum::md::estadoaplicacao::CEstadoGeral& geral = appInfo.GetGeral();
    builder.AddStatusHeader(api::CFormBuilder::STATUS_DATA_HORA | api::CFormBuilder::STATUS_ICONE_BATERIA);
    AdicionaCabecalhoLocal(builder);
    builder.AddTextField("RESUMO DA CORRESPONDÊNCIA: " + comum::FormataCodigoCargaResumido(geral.GetCorrespondencia()),
                         api::SPoint(320, 200), FONTE_INSTRUCAO_TESTE_TECLADO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    comum::CQRCodeDS qrCode(comum::CAppInfo::GetInst().GetGeral().GetDadosQRCode());
    qrCode.SetOrigem(origem);
    const api::SharedIImage imagem(new api::CQRCodeImage(148, qrCode));
    AdicionaImagemAtualizada(builder, imagem, api::SPoint(626, 250), std::chrono::milliseconds(15000),
                             api::ANCHOR_TOP_RIGHT);
    builder.AddTextField(titulo, api::SPoint(25, 260), FONTE_TEXTO_CONFIRMA_CORRIGE, api::ALINHAMENTO_ESQUERDA,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    if (!mensagem.empty()) {
        builder.AddTextField(mensagem, api::SPoint(25, 310), FONTE_INSTRUCAO_TESTE_TECLADO, api::ALINHAMENTO_ESQUERDA,
                             static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    }
    if (!detalhe.empty()) {
        builder.AddTextField(detalhe, api::SPoint(25, 340), FONTE_INSTRUCAO_TESTE_TECLADO, api::ALINHAMENTO_ESQUERDA,
                             static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    }
    builder.AddTextField(std::format("Versão: {}", api::CApplication::s_versao), api::SPoint(25, 400), FONTE_VERSAO,
                         api::ALINHAMENTO_ESQUERDA, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField(std::format("Dados: {}", comum::CAppInfo::GetInst().GetGeral().GetResumoHashVersoesPacotes()),
                         api::SPoint(620, 400), FONTE_VERSAO, api::ALINHAMENTO_DIREITA, static_cast<api::TColor>(2),
                         static_cast<api::TColor>(1));
}


CFormInterativoTelaVota CTelasVota::CriaTelaConfirmaImpressaoZeresima(const std::string& texto)
{
    api::CInteractiveFormBuilder builder;
    AdicionaTelaQRCode(builder, ecourna::api::util::CStringUtils::ToUpper(texto), "", "",
                       static_cast<comum::CQRCodeDS::EOrigem>(2));
    builder.AddLabeledInputControl({{'C', texto}, {'B', "Mais informações"}}, api::CApplication::s_areaTela, false);
    return GetFormularioInterativo(builder, "telaConfirmaImpressaoZeresima");
}

// (original lines 3130-3188: content not recovered)
#line 3189
namespace {


const api::SFont FONTE_TECLA{20, 1};
const api::SFont FONTE_SUPLENTE{13, 0};

} // namespace

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

// (original lines 3559-3564: content not recovered)
#line 3565
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

CFormInterativoTelaVota TelaFiltragemCandidatosPorNumero(const comum::TCargoID idCargo)
{
    const comum::md::CCargo cargo = comum::CConfiguracaoEleicao::GetInst().GetCargo(idCargo);
    api::CInteractiveFormBuilder builder;
    builder.AddStatusHeader(api::CFormBuilder::STATUS_DATA_HORA | api::CFormBuilder::STATUS_ICONE_BATERIA);
    builder.AddTextField("Visualização de candidatos", api::SPoint(320, 40), FONTE_TITULO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("Filtragem por número do candidato", api::SPoint(320, 75), FONTE_AGUARDE,
                         api::ALINHAMENTO_CENTRO, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("Número do " + cargo.GetNome(comum::md::CSexo::SEXO_MASCULINO) + ": ", api::SPoint(320, 215),
                         FONTE_AGUARDE, api::ALINHAMENTO_CENTRO, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    AdicionaCampoNumerico(builder, cargo.GetNumeroDigitos(), true, false, false, true, false, api::SPoint(320, 265),
                          FONTE_TITULO, api::ALINHAMENTO_CENTRO);
    builder.AddLabeledInputControl({{'C', "Confirmar seleção"}, {'D', "Retornar"}}, api::CApplication::s_areaTela,
                                   false);
    return GetFormularioInterativo(builder, "telaFiltragemCandidatosPorNumero");
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


void AdicionaCabecalhoLocal(api::CFormBuilder& builder)
{
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    const comum::CConfiguracaoEleicao& configuracao = comum::CConfiguracaoEleicao::GetInst();
    const comum::md::estadoaplicacao::CLocalidadeEleitoral secao = appInfo.GetGeral().GetDadoLocal().GetSecaoCarga();
    const comum::CLocal& local = comum::CLocal::GetInst();
    builder.AddTextField(configuracao.GetNome(), api::SPoint(320, 45), FONTE_TITULO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField(configuracao.GetPleito().GetNome(), api::SPoint(320, 80), FONTE_TITULO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField(local.GetNomeMunicipio() + "/" + local.GetUF(), api::SPoint(320, 120),
                         FONTE_INSTRUCAO_TESTE_TECLADO, api::ALINHAMENTO_CENTRO, static_cast<api::TColor>(2),
                         static_cast<api::TColor>(1));
    std::string texto = std::format("{}: {:04} {}: {:04}", comum::md::CTradutorFrase::Traduz("<ZCSA>"), secao.GetZona(),
                                    comum::md::CTradutorFrase::Traduz("<SCSA>"), secao.GetSecao());
    if (local.GetQtdAgregadas() > 0) {
        texto += std::format(" ({})", comum::FormataAgregadasResumidas("{}"));
    }
    builder.AddTextField(texto, api::SPoint(320, 155), FONTE_INSTRUCAO_TESTE_TECLADO, api::ALINHAMENTO_CENTRO,
                         static_cast<api::TColor>(2), static_cast<api::TColor>(1));
}

} // namespace vota
