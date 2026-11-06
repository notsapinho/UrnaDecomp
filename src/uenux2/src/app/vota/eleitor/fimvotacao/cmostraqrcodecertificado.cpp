#include "app/vota/eleitor/fimvotacao/cmostraqrcodecertificado.h"

#include "api/gui/cinteractiveform.h"
#include "api/util/cstringutils.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/fimvotacao/cmostraqrcodebu.h"

namespace vota {
namespace {
std::string ConteudoQRCodeCertificado();
} // namespace

CMostraQRCodeCertificado::CMostraQRCodeCertificado()
    : CEstadoComDesligamentoAutomatico(EVENTO_ENTRADA)
{
}
CMostraQRCodeCertificado::~CMostraQRCodeCertificado() = default;
CMostraQRCodeCertificado& CMostraQRCodeCertificado::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CMostraQRCodeCertificado());
    }
    return *s_inst;
}
std::unique_ptr<CMostraQRCodeCertificado> CMostraQRCodeCertificado::s_inst;
std::mutex CMostraQRCodeCertificado::s_mutex;
void CMostraQRCodeCertificado::StartState()
{
    m_form = CTelasVota::GetInst().CriaTelaQRCodeCertificado(ConteudoQRCodeCertificado);
    m_form->Slot2();
    m_pNextState = this;
}
void CMostraQRCodeCertificado::ProcessInput()
{
    if (m_form->GetEntradas().size() != 1) {
        throw CUeVotaError(EUE_VOTA_QRCODE_CERTIFICADO_NUMERO_INPUTS_INVALIDO, "Número de inputs inválido");
    }
    if (m_form->Read() == api::INPUT_CORRIGE) {
        m_pNextState = &CMostraQRCodeBU::GetInst();
    }
}

namespace {

std::vector<std::pair<std::string, std::string>> DadosCertificado()
{
    return comum::CAppInfo::GetInst().GetGeral().GetDadosQRCodeCertificado(false).front();
}

std::string ConteudoQRCodeCertificado()
{
    return api::CStringUtils::JuntaTags(DadosCertificado());
}

} // namespace

} // namespace vota
