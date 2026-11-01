// comum::IInterfaceSavd and the SAVD requests (/home/rubio/tse/uenux2/src/app/comum/iinterfacesavd.cpp). The records
// of the target fix the lines of DesconverteHeader's and DesconverteMensagem's throws (553 to 578), ValidarUE's (886)
// and EnviarAcaoHSM's (1040); lines 898, 1004 and 1022 stay blank for the records of the ValidarUE over a file,
// AssinarUE and AssinarEcourna, not written (fns 11179, 1277 and 12098 hold them). Every other line is a choice: the
// use bands put fn 3831 ahead of EnviarRequisicao (3830) and 3829 after it, and AssinarArquivo (5891) ahead of
// ValidarUE (5890). iinterfacesavd.h has the class, and the unit's fragment which members are reconstructed.

#include "app/comum/iinterfacesavd.h"

#include <algorithm>
#include <format>
#include <iterator>

#include "api/util/cgenerictags.h"
#include "app/comum/euecomumerror.h"

namespace comum {

const std::string TAG_SUP = "sup";
const std::string TAG_PKG = "pkg";
const std::string TAG_KEY = "key";
const std::string TAG_FIL = "fil";

namespace {

// the mark of a request, of a response header and of a message: fns 3829, 3830 and 5889 store and compare 254
constexpr uebyte MARCA_SAVD = 254;

// a message holds its mark and at least one byte of text: DesconverteMensagem's size check
constexpr size_t TAMANHO_MINIMO_MENSAGEM = 2;
// the tags a request's TLV is encoded with: fns 3831 and 5892 hold these inserts inline
api::CGenericTags CriaTags()
{
    api::CGenericTags tags(3);
    tags.insert(TAG_PKG, 1);
    tags.insert(TAG_KEY, 1);
    tags.insert(TAG_FIL, 1);
    tags.insert(TAG_SUP, 3);
    return tags;
}

} // namespace

std::string MontaRequisicaoTLV(const std::string& pacote, ueint32 chave)
{
    const api::CGenericTags tags = CriaTags();
    return tags.EncodeTLV(TAG_SUP, MontaConteudoTLV(pacote, chave));
}

std::string MontaConteudoTLV(const std::string& pacote, ueint32 chave)
{
    const api::CGenericTags tags = CriaTags();
    std::string conteudo;
    conteudo = tags.EncodeTLV(TAG_PKG, pacote);
    tags.AppendTLV(conteudo, TAG_KEY, std::format("{}", chave));
    return conteudo;
}

// (original lines 59-479: content not recovered)
#line 480
bool IInterfaceSavd::EnviarRequisicao(ueint32& codigo, ueRequisicaoSavd& requisicao, const std::string& dados)
{
    m_mensagem = "";

    std::vector<uebyte> resposta = ConverteHeader(requisicao, dados);
    Escreve(resposta);
    if (!dados.empty()) {
        Escreve(std::vector<uebyte>(dados.begin(), dados.end()));
    }

    resposta.clear();
    ueint32 estado;
    RecebeMensagem(estado, resposta, sizeof(ueRespostaSavd));
    const ueRespostaSavd* header = DesconverteHeader(resposta);

    const uebyte erro = header->erro;
    if (erro) {
        codigo = header->codigo;

        std::string motivo;
        if (header->tamanho) {
            std::vector<uebyte> mensagem;
            RecebeMensagem(estado, mensagem, header->tamanho);
            motivo = DesconverteMensagem(header, mensagem);
        } else {
            motivo = "Motivo não informado pelo serviço.";
        }
        m_mensagem = motivo;
    }
    return !erro;
}

std::vector<uebyte> IInterfaceSavd::ConverteHeader(ueRequisicaoSavd& requisicao, const std::string& dados)
{
    requisicao.marca = MARCA_SAVD;
    requisicao.tamanho = dados.size();

    std::vector<uebyte> buffer;
    buffer.reserve(sizeof(requisicao));
    const uebyte* bytes = reinterpret_cast<const uebyte*>(&requisicao);
    std::copy(bytes, bytes + sizeof(requisicao), std::back_inserter(buffer));
    return buffer;
}

// (original lines 524-549: content not recovered)
#line 550
const ueRespostaSavd* IInterfaceSavd::DesconverteHeader(const std::vector<uebyte>& resposta)
{
    if (resposta.size() != sizeof(ueRespostaSavd)) {
        throw CUeComumError(EUE_COMUM_SAVD_HEADER_TAMANHO_INCORRETO, std::format("Header com tamanho incorreto: {}/{}", resposta.size(), sizeof(ueRespostaSavd)));
    }

    const ueRespostaSavd* header = reinterpret_cast<const ueRespostaSavd*>(resposta.data());

    if (header->marca != MARCA_SAVD) {
        throw CUeComumError(EUE_COMUM_SAVD_HEADER_MARCA_INCORRETA, "Header com marca incorreta");
    }
    return header;
}


std::string IInterfaceSavd::DesconverteMensagem(const ueRespostaSavd* header, const std::vector<uebyte>& mensagem)
{
    if (mensagem.size() < TAMANHO_MINIMO_MENSAGEM) {
        throw CUeComumError(EUE_COMUM_SAVD_MENSAGEM_TAMANHO_INCORRETO, std::format("Mensagem com tamanho incorreto: {}/{}", mensagem.size(), TAMANHO_MINIMO_MENSAGEM));
    }

    // (original lines 571-572: content not recovered)
#line 573
    if (mensagem[0] != MARCA_SAVD) {
        throw CUeComumError(EUE_COMUM_SAVD_MENSAGEM_MARCA_INCORRETA, "Mensagem com marca incorreta");
    }

    if (mensagem.size() < header->tamanho) {
        throw CUeComumError(EUE_COMUM_SAVD_MENSAGEM_BUFFER_INSUFICIENTE, std::format("Buffer com tamanho insuficiente para mensagem: {}/{}", mensagem.size(), header->tamanho));
    }

    std::string texto;
    texto.reserve(header->tamanho - 1);
    std::copy(mensagem.begin() + 1, mensagem.begin() + header->tamanho, std::back_inserter(texto));
    return texto;
}


std::string IInterfaceSavd::EnviarRequisicao(ueint32& codigo, ueRequisicaoSavd& requisicao, const std::vector<uebyte>& dados)
{
    requisicao.marca = MARCA_SAVD;
    requisicao.tamanho = dados.size();

    std::vector<uebyte> resposta;
    resposta.reserve(sizeof(requisicao));
    const uebyte* bytes = reinterpret_cast<const uebyte*>(&requisicao);
    std::copy(bytes, bytes + sizeof(requisicao), std::back_inserter(resposta));
    Escreve(resposta);
    if (!dados.empty()) {
        Escreve(dados);
    }

    resposta.clear();
    ueint32 estado;
    RecebeMensagem(estado, resposta, sizeof(ueRespostaSavd));
    if (resposta.size() != sizeof(ueRespostaSavd)) {
        return "Resposta com tamanho incorreto.";
    }

    const ueRespostaSavd* header = reinterpret_cast<const ueRespostaSavd*>(resposta.data());
    if (header->marca != MARCA_SAVD) {
        return "Resposta com marca incorreta.";
    }
    if (header->erro) {
        codigo = header->codigo;
        if (header->tamanho) {
            std::vector<uebyte> mensagem;
            RecebeMensagem(estado, mensagem, header->tamanho);
            if (mensagem[0] != MARCA_SAVD) {
                return "Mensagem com marca incorreta.";
            }

            const uedword tamanho = header->tamanho;
            std::string texto;
            texto.reserve(tamanho - 1);
            std::copy(mensagem.begin() + 1, mensagem.begin() + tamanho, std::back_inserter(texto));
            return texto;
        }
        return "Motivo não informado pelo serviço.";
    }
    return "";
}

// (original lines 633-849: content not recovered)
#line 850
bool IInterfaceSavd::AssinarArquivo(ESavdAplic aplic, ueint32 comando, uebyte operacao, ueint32 arquivo)
{
    if (aplic > 0xFF || comando > 0xFFFF || arquivo > 0xFF) {
        m_mensagem = "Argumento inválido validar assinar.";
        return false;
    }

    std::vector<uebyte> dados(3);
    dados[0] = MARCA_SAVD;
    dados[1] = operacao;
    dados[2] = arquivo;
    ueRequisicaoSavd requisicao = {};
    requisicao.aplicacao = aplic;
    requisicao.comando = comando;
    m_mensagem = EnviarRequisicao(m_codigo, requisicao, dados);
    return m_mensagem.empty();
}


bool IInterfaceSavd::ValidarPacote(ESavdAplic aplic, ESavdChaveValidar chave, ueword comando, const std::string& pacote)
{
    if (aplic > 0xFF || chave > 0xFF || pacote.empty()) {
        m_mensagem = "Argumento inválido validar assinar o pacote.";
        return false;
    }

    const std::string dados = MontaRequisicaoTLV(pacote, chave);
    ueRequisicaoSavd requisicao = {};
    requisicao.comando = comando;
    requisicao.aplicacao = aplic;
    return EnviarRequisicao(m_codigo, requisicao, dados);
}

void ValidarUE(IInterfaceSavd& savd, ESavdAplic aplic, const std::string& pacote)
{
    if (!savd.ValidarPacote(aplic, SAVD_CHAVE_UE, 0x2021, pacote)) {
        throw CUeComumError(EUE_COMUM_VALIDAR_ASSINATURA_UE, std::format("Falha ao validar assinatura UE\npacote: ({})\nErro SAVD: ({})\n{}", pacote, savd.GetCodigo(), savd.GetMensagem()));
    }
}

// (original lines 890-979: content not recovered)
#line 980
bool IInterfaceSavd::EnviarAcaoHSM(ESavdAplic aplic, ESavdCmdHSM acao)
{
    if (aplic > 0xFF || acao > 0xFF) {
        m_mensagem = "Argumento inválido para ação do hsm.";
        return false;
    }
    if (acao > 1) {
        m_mensagem = "IInterfaceSavd::EnviarAcaoHSM - Tentativa de envio de ação inválido ao serviço.";
        return false;
    }

    std::vector<uebyte> dados(2);
    dados[0] = MARCA_SAVD;
    dados[1] = acao;
    ueRequisicaoSavd requisicao;
    requisicao.aplicacao = aplic;
    requisicao.comando = 0x1604;
    m_mensagem = EnviarRequisicao(m_codigo, requisicao, dados);
    return m_mensagem.empty();
}

// (original lines 1001-1036: content not recovered)
#line 1037
void EnviarAcaoHSM(IInterfaceSavd& savd, ESavdAplic aplic, ESavdCmdHSM acao)
{
    if (!savd.EnviarAcaoHSM(aplic, acao)) {
        throw CUeComumError(EUE_COMUM_ENVIAR_ACAO_HSM, std::format("Falha ao enviar ação ao HSM. {}", savd.GetMensagem()));
    }
}

} // namespace comum
