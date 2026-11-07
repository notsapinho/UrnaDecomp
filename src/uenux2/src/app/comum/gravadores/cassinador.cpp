// comum::CAssinador (/home/rubio/tse/uenux2/src/app/comum/gravadores/cassinador.cpp). The records of the target fix
// the lines of Assina's CPolySingleton<IInterfaceSavd>::instance() (114, fn 1277) and of AssinaArquivosResultado's
// throw and its two instance() calls (141, 146 and 149; fn 12098 holds it inlined). Every other line is a choice;
// unit 34's fragment has the evidence.

#include "app/comum/gravadores/cassinador.h"

#include <format>

#include "api/gui/capplication.h"
#include "api/hwil/iurna.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/csystem.h"
#include "app/comum/carquivossavd.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/clocal.h"
#include "app/comum/gravadores/euecomumgravadoreserror.h"
#include "app/comum/log/clogcomum.h"

namespace comum {

CAssinador::CAssinador(ESavdAplic aplic, ESavdPacote pacote)
    : m_aplic(aplic)
    , m_pacote(pacote)
{
    const std::string caminho = CArquivosSavd::GetInst()[pacote];
    m_diretorio = api::GetDirName(caminho) + "/";
    m_caminho = api::GetFileName(caminho);
}

CAssinador::CAssinador(ESavdAplic aplic, ESavdPacote pacote, TMunicipioID municipio, TZonaID zona, TSecaoID secao,
    char fase)
    : m_aplic(aplic)
    , m_pacote(pacote)
    , m_local(std::format("{}{:05}{:04}{:04}", CLocal::GetInst().GetUFMinuscula(), municipio, zona, secao))
{
    const auto pleito = CConfiguracaoEleicao::GetInst().GetPleito().GetID();
    const std::string formato = CArquivosSavd::GetInst()[pacote];
    const std::string uf = CLocal::GetInst().GetUFMinuscula();
    const std::string caminho = std::vformat(formato, std::make_format_args(fase, pleito, uf, municipio, zona, secao));
    m_diretorio = api::GetDirName(caminho) + "/";
    m_caminho = api::GetFileName(caminho);
}

CAssinador::~CAssinador() {}

// (original lines 47-111: content not recovered)
#line 112
void CAssinador::Assina(const ESavdArquivoUE arquivo) const
{
    auto& iSavd = api::CPolySingleton<IInterfaceSavd>::instance();
    const api::CApplicationContextGuard guarda = api::CApplication::CriaContexto(11, "Erro na assinatura", "", "Ocorreu um erro durante a assinatura do arquivo: " + DescricaoArquivo(arquivo));
    AssinarUE(iSavd, m_aplic, 66, arquivo);
}

// (original lines 119-137: content not recovered)
#line 138
void CAssinador::AssinaArquivosResultado(const std::vector<ESavdArquivoUE>& arquivos) const
{
    if (arquivos.empty()) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8636, "Não foi passado nenhum arquivo de resultado");
    }

    // (original lines 144-145: content not recovered)
#line 146
    auto& iSavd = api::CPolySingleton<IInterfaceSavd>::instance();
    EnviarAcaoHSM(iSavd, m_aplic, SAVD_CMD_HSM_INICIA_SESSAO);

    api::IUrna& iUrna = api::CPolySingleton<api::IUrna>::instance();
    if (iUrna.Modelo() >= 2020) {
        CLogComum::GetInst().LogaIniciaSessaoMSE();
    } else {
        CLogComum::GetInst().LogaIniciaSessaoMSD();
    }

    iSavd.EnviarLocal(m_aplic, m_local);
    for (const ESavdArquivoUE arquivo : arquivos) {
        const api::CApplicationContextGuard guarda = api::CApplication::CriaContexto(11, "Erro na assinatura dos arquivos de resultado", "", "Ocorreu um erro durante a assinatura dos arquivos: " + DescricaoArquivo(arquivo));
        AssinarEcourna(iSavd, m_aplic, 128, arquivo);
    }

    EnviarAcaoHSM(iSavd, m_aplic, SAVD_CMD_HSM_FINALIZA_SESSAO);
    if (iUrna.Modelo() >= 2020) {
        CLogComum::GetInst().LogaFinalizaSessaoMSE();
    } else {
        CLogComum::GetInst().LogaFinalizaSessaoMSD();
    }
}

} // namespace comum
