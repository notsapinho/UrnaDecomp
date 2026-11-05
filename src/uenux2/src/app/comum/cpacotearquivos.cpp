// comum::CPacoteArquivos (/home/rubio/tse/uenux2/src/app/comum/cpacotearquivos.cpp). The reconstruction's own note: the
// records of the target fix the lines of the throws of ValidarChaveEAplicacaoValida (85 and 91), of RetornaNomeChave
// (162), TrataErroPacote (169) and TrataErroPacoteArquivo (190), and of the default location of Validar's
// CPolySingleton<IInterfaceSavd>::instance() (116, column 29); every other line, the constructor's place included, is a
// choice (src/units/95-uenux2-app-comum.mk).

#include "app/comum/cpacotearquivos.h"

#include <format>

#include "api/pattern/cpolysingleton.h"
#include "app/comum/euecomumerror.h"
#include "app/comum/iinterfacemensagem.h"

namespace comum {

// (original lines 17-59: content not recovered)
#line 60
CPacoteArquivos::CPacoteArquivos(const std::string& nome, const std::string& arquivo, ESavdChaveValidar chave, ESavdAplic aplic)
    : m_nome(nome), m_chave(chave), m_comando(0x1001), m_aplic(aplic)
{
    ValidarChaveEAplicacaoValida();
    if (!arquivo.empty()) {
        m_arquivos.push_back(arquivo);
    }
    m_comando = m_arquivos.empty() ? 0x2021 : 0x1001;
}

// (original lines 70-81: content not recovered)
#line 82
void CPacoteArquivos::ValidarChaveEAplicacaoValida()
{
    if (m_chave < SAVD_CHAVE_TSE || m_chave > SAVD_CHAVE_SEINT) {
        throw CUeComumError(EUE_COMUM_CHAVE_INVALIDA, std::format("A chave informada não é válida: {}", m_chave));
    }

    // (original lines 88-89: content not recovered)
#line 90
    if (m_aplic < 1 || m_aplic > 9) {
        throw CUeComumError(EUE_COMUM_APLICACAO_INVALIDA, std::format("A aplicação informada não é válida: {}", m_aplic));
    }
}

// (original lines 95-113: content not recovered)
#line 114
void CPacoteArquivos::Validar(IInterfaceMensagem& mensagem) const
{
    IInterfaceSavd& iSavd = api::CPolySingleton<IInterfaceSavd>::instance();
    if (m_comando == 0x2021 || m_comando == 0x1011) {
        mensagem.ValidandoPacote(*this);
        if (!iSavd.ValidarPacote(m_aplic, m_chave, m_comando, m_nome)) {
            TrataErroPacote(iSavd);
        }
        return;
    }
    for (auto it = m_arquivos.begin(); it != m_arquivos.end(); ++it) {
        mensagem.ValidandoArquivo(*this, *it);
        if (!iSavd.VerificarArquivo(m_aplic, m_chave, m_nome, *it)) {
            TrataErroPacoteArquivo(iSavd, *it);
        }
    }
}

// (original lines 132-135: content not recovered)
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

// (original lines 173-184: content not recovered)
#line 185
void CPacoteArquivos::TrataErroPacoteArquivo(const IInterfaceSavd& savd, const std::string& arquivo) const
{
    if (savd.GetCodigo() >= 1 && savd.GetCodigo() <= 3) {
        TrataErroPacote(savd);
    } else {
        throw CUeComumError(EUE_COMUM_VALIDAR_ASSINATURA_ARQUIVO, std::format("Falha ao validar assinatura {}\npacote: ({})\narquivo: ({})\nErro SAVD: ({} - {})",
                                                                          RetornaNomeChave(m_chave), m_nome, arquivo, savd.GetCodigo(), savd.GetMensagem()));
    }
}

} // namespace comum
