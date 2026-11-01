#include "app/comum/dados/clocal.h"

#include <format>
#include <mutex>

#include "app/comum/dados/euecomumdadoserror.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum {

using ecourna::api::util::CStringUtils;

CLocal& CLocal::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst = std::make_unique<CLocal>();
    }
    return *s_inst;
}

std::unique_ptr<CLocal> CLocal::s_inst;
std::mutex CLocal::s_mutex;

CLocal::CLocal() = default;

CLocal::~CLocal() = default;

uedword CLocal::GetMunicipio() const
{
    VerificaLido("GetMunicipio");
    return m_local->GetMunicipio().GetCodigo();
}

const std::string& CLocal::GetUF() const
{
    VerificaLido("GetUF");
    return m_local->GetSiglaUF();
}

std::string CLocal::GetUFMinuscula() const
{
    VerificaLido("GetUF");
    return CStringUtils::ToLower(m_local->GetSiglaUF());
}

const md::CLocal& CLocal::GetLocalData() const
{
    VerificaLido("GetLocalData");
    return *m_local;
}

// (original lines 53-76: content not recovered)
#line 77
TZonaID CLocal::GetZonaID() const
{
    VerificaLido("GetZona");
    if (m_local->TemSecao()) {
        return m_local->GetSecao().GetIdentificacao().GetZona();
    }
    if (m_local->TemContingencia()) {
        return m_local->GetContingencia().GetZona();
    }
    throw CUeComumDadosError(EUE_COMUM_DADOS_7872, "Tipo de local inválido");
}

// (original lines 89-100: content not recovered)
#line 101
TSecaoID CLocal::GetSecaoID() const
{
    VerificaLido("GetSecaoID");
    if (m_local->TemSecao()) {
        return m_local->GetSecao().GetIdentificacao().GetSecao();
    }
    if (m_local->TemContingencia()) {
        return 0;
    }
    throw CUeComumDadosError(EUE_COMUM_DADOS_7873, "Tipo de local inválido");
}

const std::string& CLocal::GetNomeMunicipio() const
{
    VerificaLido("GetNomeMunicipio");
    return m_local->GetMunicipio().GetNome();
}

bool CLocal::UrnaBiometrica() const
{
    if (EhSecao("UrnaBiometrica")) {
        return m_local->GetMunicipio().EhUrnaBiometrica();
    }
    return false;
}

TLocalID CLocal::GetLocalID() const
{
    VerificaEhSecao("GetLocalID");
    return m_local->GetSecao().GetIdentificacao().GetLocal();
}

// (original lines 133-341: content not recovered)
#line 342
void CLocal::VerificaLido(const std::string& funcao) const
{
    if (!m_local) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7874, std::format("{}: o arquivo de locais ainda não foi carregado", funcao));
    }
}


void CLocal::VerificaEhSecao(const std::string& funcao) const
{
    VerificaLido(funcao);
    if (!m_local->TemSecao()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7875, std::format("{}: o local não era de seção", funcao));
    }
}

} // namespace comum
