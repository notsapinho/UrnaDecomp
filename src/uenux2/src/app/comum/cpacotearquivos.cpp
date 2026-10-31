// comum::CPacoteArquivos (/home/rubio/tse/uenux2/src/app/comum/cpacotearquivos.cpp). RetornaNomeChave's throw is a record
// of the target:
//   5900  RetornaNomeChave(ESavdChaveValidar)  record at line 162, column 11

#include "app/comum/cpacotearquivos.h"

#include <format>

#include "app/comum/euecomumerror.h"

namespace comum {

// (original lines 13-81: content not recovered)
#line 82
// <stubs>
// f4625 · 3584 B · unmatched · name unknown
// void f4625(i32) { ... }
// </stubs>

// (original lines 87-135: content not recovered)
#line 136
std::string CPacoteArquivos::RetornaNomeChave(ESavdChaveValidar chave)
{
    switch (chave) {
    case SAVD_CHAVE_TSE:
        return "TSE";
    case SAVD_CHAVE_SECAD:
        return "SECAD";
    case SAVD_CHAVE_SECINP:
        return "SECINP";
    case SAVD_CHAVE_SEINT:
        return "SEINT";
    case SAVD_CHAVE_SEVIN:
        return "SEVIN";
    case SAVD_CHAVE_UE:
        return "UE";
    case SAVD_CHAVE_SCUE:
        return "SCUE";
    case SAVD_CHAVE_CLOGI:
        return "CLOGI";
    case SAVD_CHAVE_CLOGI_CERT:
        return "CLOGI_CERT";
    case SAVD_CHAVE_CLOGI_UPDATE:
        return "CLOGI_UPDATE";
    case SAVD_CHAVE_PU:
        return "PU";
    }
    throw CUeComumError(EUE_COMUM_CHAVE_DESCONHECIDA, std::format("Chave desconhecida: {}", chave));
}

// (original lines 165-166: content not recovered)
#line 167
void CPacoteArquivos::TrataErroPacote(const IInterfaceSavd& savd) const
{
    throw CUeComumError(EUE_COMUM_VALIDAR_ASSINATURA_PACOTE, std::format("Falha ao validar assinatura {}\npacote: ({})\nErro SAVD: ({} - {})",
                                                                         RetornaNomeChave(m_chave), m_nome, savd.GetCodigo(), savd.GetMensagem()));
}

} // namespace comum
