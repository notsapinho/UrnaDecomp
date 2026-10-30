// comum::IInterfaceSavd (/home/rubio/tse/uenux2/src/app/comum/iinterfacesavd.cpp). The records of the target fix the lines
// of DesconverteHeader's and DesconverteMensagem's throws; iinterfacesavd.h has the class, and the unit's fragment which
// members are reconstructed.

#include "app/comum/iinterfacesavd.h"

#include <algorithm>
#include <format>
#include <iterator>

#include "app/comum/euecomumerror.h"

namespace comum {

namespace {

// the mark of a request, of a response header and of a message: fns 3829, 3830 and 5889 store and compare 254
constexpr uebyte MARCA_SAVD = 254;

// a message holds its mark and at least one byte of text: DesconverteMensagem's size check
constexpr size_t TAMANHO_MINIMO_MENSAGEM = 2;

} // namespace

// (original lines 25-479: content not recovered)
#line 480
bool IInterfaceSavd::EnviarRequisicao(ueint32& codigo, ueRequisicaoSavd& requisicao, const std::string& dados)
{
    m_mensagem = "";

    requisicao.marca = MARCA_SAVD;
    requisicao.tamanho = dados.size();

    std::vector<uebyte> resposta = ConverteHeader(requisicao);
    Escreve(resposta);
    if (!dados.empty()) {
        Escreve(std::vector<uebyte>(dados.begin(), dados.end()));
    }

    resposta.clear();
    ueint32 estado;
    Le(estado, resposta, sizeof(ueRespostaSavd));
    const ueRespostaSavd* header = DesconverteHeader(resposta);

    const uebyte erro = header->erro;
    if (erro) {
        codigo = header->codigo;

        std::string motivo;
        if (header->tamanho) {
            std::vector<uebyte> mensagem;
            Le(estado, mensagem, header->tamanho);
            motivo = DesconverteMensagem(header, mensagem);
        } else {
            motivo = "Motivo não informado pelo serviço.";
        }
        m_mensagem = motivo;
    }
    return !erro;
}

std::vector<uebyte> IInterfaceSavd::ConverteHeader(const ueRequisicaoSavd& requisicao)
{
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

} // namespace comum

// <stubs>
// f5890 · 717 B · unmatched · name unknown
// void f5890(i32, i32) { ... }

// f5889 · 761 B · unmatched · name unknown
// void f5889(i32, i32, i32) { ... }
// </stubs>
