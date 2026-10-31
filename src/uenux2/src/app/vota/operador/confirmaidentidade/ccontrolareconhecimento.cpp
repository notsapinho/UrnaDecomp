// vota::CControlaReconhecimento (the records' file). The reconstruction's notes are in ccontrolareconhecimento.h and
// src/units/161-uenux2-app-vota-operador-identidade.mk.
#include "app/vota/operador/confirmaidentidade/ccontrolareconhecimento.h"

#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/vota/euevotaerror.h"

namespace vota {

int CControlaReconhecimento::s_tentativa = 1;
int CControlaReconhecimento::s_verificacao = 1;
int CControlaReconhecimento::s_tentativaRegistrada = 1;
uebyte CControlaReconhecimento::s_indiceDedo = 0;

CControlaReconhecimento::~CControlaReconhecimento() = default;

// (original lines 17-160: content not recovered)
#line 161
void CControlaReconhecimento::AvancaTentativa()
{
    if (!AtingiuLimiteTentativas()) {
        s_indiceDedo = 0;
        ++s_tentativa;
    } else {
        throw CUeVotaError(EUE_VOTA_LIMITE_TENTATIVAS_ATINGIDO, "Limite de tentativas atingido.");
    }
}



















bool CControlaReconhecimento::AtingiuLimiteTentativas()
{
    const uebyte limite = comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetNumTentativasHabilitacao();
    return limite == s_tentativa;
}

bool CControlaReconhecimento::AtingiuLimiteVerificacoes()
{
    const uebyte limite = comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetNumTentativasVerificacao();
    return limite == s_verificacao;
}

bool CControlaReconhecimento::PrimeiraTentativa()
{
    return s_tentativa == 1;
}

} // namespace vota

// <stubs>
// f1256 · 109 B · unmatched · placement: link order · name unknown
// ? f1256() { ... }
// </stubs>
