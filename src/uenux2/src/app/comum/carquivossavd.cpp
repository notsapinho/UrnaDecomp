// comum::CArquivosSavd (/home/rubio/tse/uenux2/src/app/comum/carquivossavd.cpp). Its two throws are records of the target:
//   275  operator[](ESavdPacote) const     record at line 49, column 15
//   680  operator[](ESavdArquivoUE) const  record at line 73, column 15

#include "app/comum/carquivossavd.h"

#include <format>

#include "app/comum/euecomumerror.h"

namespace comum {

// (original lines 13-44: content not recovered)
#line 45
std::string CArquivosSavd::operator[](ESavdPacote pacote) const
{
    const auto it = m_assinaturas.find(pacote);
    if (it == m_assinaturas.end()) {
        throw CUeComumError(EUE_COMUM_ARQUIVO_ASSINATURA_NAO_ENCONTRADO, std::format("Arquivo de assinatura associado ao identificador {} não encontrado", pacote));
    }
    return it->second;
}

// (original lines 54-68: content not recovered)
#line 69
std::string CArquivosSavd::operator[](ESavdArquivoUE arquivo) const
{
    const auto it = m_assinados.find(arquivo);
    if (it == m_assinados.end()) {
        throw CUeComumError(EUE_COMUM_ARQUIVO_ASSINADO_NAO_ENCONTRADO, std::format("Arquivo assinado associado ao identificador {} não encontrado", arquivo));
    }
    return it->second;
}

} // namespace comum
