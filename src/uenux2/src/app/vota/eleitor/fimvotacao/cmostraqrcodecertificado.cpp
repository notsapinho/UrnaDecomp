#include "app/vota/eleitor/fimvotacao/cmostraqrcodecertificado.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/eleitor/fimvotacao/cmostraqrcodebu.h"

namespace vota {

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

// (original lines 28-35: content not recovered)
#line 36
void CMostraQRCodeCertificado::ProcessInput()
{
    if (m_form->GetEntradas().size() != 1) {
        throw CUeVotaError(EUE_VOTA_QRCODE_CERTIFICADO_NUMERO_INPUTS_INVALIDO, "Número de inputs inválido");
    }
    if (m_form->Read() == api::INPUT_CORRIGE) {
        m_pNextState = &CMostraQRCodeBU::GetInst();
    }
}

} // namespace vota
