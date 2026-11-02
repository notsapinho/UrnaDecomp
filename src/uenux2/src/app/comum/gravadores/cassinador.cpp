#include "app/comum/gravadores/cassinador.h"

#include "api/gui/capplication.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/csystem.h"
#include "app/comum/carquivossavd.h"

namespace comum {

CAssinador::CAssinador(ESavdAplic aplic, ESavdPacote pacote)
    : m_aplic(aplic)
    , m_pacote(pacote)
{
    const std::string caminho = CArquivosSavd::GetInst()[pacote];
    m_diretorio = api::GetDirName(caminho) + "/";
    m_caminho = api::GetFileName(caminho);
}

CAssinador::~CAssinador() {}

// (original lines 21-111: content not recovered)
#line 112
void CAssinador::Assina(const ESavdArquivoUE arquivo) const
{
    auto& iSavd = api::CPolySingleton<IInterfaceSavd>::instance();
    const api::CApplicationContextGuard guarda = api::CApplication::CriaContexto(11, "Erro na assinatura", "", "Ocorreu um erro durante a assinatura do arquivo: " + DescricaoArquivo(arquivo));
    AssinarUE(iSavd, m_aplic, 66, arquivo);
}

































} // namespace comum
