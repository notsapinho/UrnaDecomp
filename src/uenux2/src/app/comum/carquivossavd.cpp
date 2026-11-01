// comum::CArquivosSavd (/home/rubio/tse/uenux2/src/app/comum/carquivossavd.cpp). Its two throws are records of the target:
//   275  operator[](ESavdPacote) const     record at line 49, column 15
//   680  operator[](ESavdArquivoUE) const  record at line 73, column 15
//   5905 DescricaoArquivo(ESavdArquivoUE)  no record: after them, on chosen lines (src/units/95-uenux2-app-comum.mk)

#include "app/comum/carquivossavd.h"

#include <format>

#include "app/comum/euecomumerror.h"

namespace comum {

// (original lines 14-44: content not recovered)
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

std::string DescricaoArquivo(ESavdArquivoUE arquivo)
{
    switch (arquivo) {
    case 25:
        return "EG Geral MI";
    case 26:
        return "EG Geral ME";
    case 27:
        return "EG GAP 1 MI";
    case 28:
        return "EG GAP 2 MI";
    case 29:
        return "EG GAP 1 ME";
    case 30:
        return "EG GAP 2 ME";
    case 31:
        return "EG VOTA MI";
    case 32:
        return "EG VOTA ME";
    case 33:
        return "EG SA MI";
    case 34:
        return "Tabela de correspondência";
    case 35:
        return "BU do VOTA MI (res)";
    case 36:
        return "BU do SA MI (res)";
    case 37:
        return "RDV MI (res)";
    case 38:
        return "Res. RDV SA";
    case 39:
        return "Justif. de Seção MI (res)";
    case 40:
        return "Justif. SA (res)";
    case 41:
        return "Justif. de MRJ MI (res)";
    case 42:
        return "Justif. de MRJ ME (res)";
    case 43:
        return "BU imp. do VOTA MI (res)";
    case 44:
        return "ZE imp. do VOTA MI (res)";
    case 45:
        return "BU imp. do SA MI (res)";
    case 46:
        return "Hashes MI (res)";
    case 47:
        return "Hashes do SA MI (res)";
    case 48:
        return "Habilitados MI (res)";
    case 49:
        return "Não Habilitados MI (res)";
    case 50:
        return "Mesario MI (res)";
    case 51:
        return "Habilitados ME (res)";
    case 52:
        return "Não Habilitados ME (res)";
    case 53:
        return "Mesario ME (res)";
    case 54:
        return "Habilitados MI (res)";
    case 55:
        return "Não Habilitados MI (res)";
    case 56:
        return "Mesario MI (res)";
    case 57:
        return "Habilitados ME (res)";
    case 58:
        return "Não Habilitados ME (res)";
    case 59:
        return "Mesario ME (res)";
    case 60:
        return "Log MI (res)";
    case 61:
        return "Log do SA MI (res)";
    case 62:
        return "Log da MR do SA MI (res)";
    case 63:
        return "BU do VOTA ME (res)";
    case 64:
        return "Justif. de Seção ME (res)";
    case 65:
        return "RDV ME (res)";
    case 66:
        return "BU imp. do VOTA ME (res)";
    case 67:
        return "ZE imp. do VOTA ME (res)";
    case 68:
        return "Hashes ME (res)";
    case 69:
        return "Log ME (res)";
    case 70:
        return "Arquivo de versões na MI";
    case 71:
        return "Arquivo de versões na ME";
    case 72:
        return "Arquivo de versões do SA";
    case 73:
        return "Justif. de Seção MI (rec. Para SA)";
    case 74:
        return "RDV MI (rec. Para SA)";
    case 75:
        return "BU imp. MI (rec. Para SA)";
    case 76:
        return "ZE imp. MI (rec. Para SA)";
    case 77:
        return "Log MI (rec. Para SA)";
    case 78:
        return "Justif. de Seção ME (rec. Para SA)";
    case 79:
        return "RDV ME (rec. Para SA)";
    case 80:
        return "BU imp. ME (rec. Para SA)";
    case 81:
        return "ZE imp. ME (rec. Para SA)";
    case 82:
        return "Log ME (rec. Para SA)";
    case 83:
        return "RDV MI";
    case 84:
        return "BU imp. de Justif. Seção MI";
    case 85:
        return "BU imp. de Justif. Seção ME";
    case 86:
        return "BU imp. do VOTA MI";
    case 87:
        return "BU imp. do VOTA ME";
    case 88:
        return "Zerésima MI";
    case 89:
        return "Resumo da Zerésima MI";
    case 90:
        return "BU imp. do RED. MI";
    case 91:
        return "BUJ imp. do RED MI";
    case 92:
        return "BIM imp. do RED MI";
    case 93:
        return "BEHB imp. do RED MI";
    case 94:
        return "BU imp. do RED ME";
    case 95:
        return "BUJ imp. do RED. ME";
    case 96:
        return "BIM imp. do RED. ME";
    case 97:
        return "BEHB imp. do RED. ME";
    case 98:
        return "RDV SA INT";
    case 99:
        return "ZE SA INT";
    case 100:
        return "BU SEÇÃO SA INT";
    case 101:
        return "SARAIZ SA INT";
    case 102:
        return "SASECAO SA INT";
    case 103:
        return "BU DIGITADO SA INT";
    case 104:
        return "REG CERTIFICAÇÕES SIECO";
    case 105:
        return "REG AUTENTICAÇÕES SIECO";
    case 106:
        return "BIM da MI";
    case 107:
        return "BIM da ME";
    case 108:
        return "BEHB da MI";
    case 109:
        return "BEHB da ME";
    case 110:
        return "UENUXDB INT";
    case 111:
        return "UENUXDB EXT";
    case 112:
        return "Arquivo de local";
    case 113:
        return "Dados disp. carga";
    case 114:
        return "UENUX CFG";
    case 115:
        return "EG RED MI";
    case 116:
        return "ZE imp. SA (res)";
    case 117:
        return "Habilitados da MR do SA MI (res)";
    case 118:
        return "Não habilitados da MR do SA MI (res)";
    case 119:
        return "Mesário da MR do SA MI (res)";
    case 120:
        return "";
    default:
        return "Arquivo não identificado";
    }
}

} // namespace comum
