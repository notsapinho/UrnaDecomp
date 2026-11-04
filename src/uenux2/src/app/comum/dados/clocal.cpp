#include "app/comum/dados/clocal.h"

#include <format>
#include <mutex>

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/asn/cconversorlocal.h"
#include "app/comum/dados/carregaarquivo.h"
#include "app/comum/dados/euecomumdadoserror.h"
#include "app/comum/nomearquivo/cnomearquivo.h"
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

bool CLocal::EhExterior() const
{
    VerificaLido("EhExterior");
    return GetUF() == "ZZ";
}

// (original lines 64-76: content not recovered)
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

uebyte CLocal::GetQtdAgregadas() const
{
    if (EhSecao("GetQtdAgregadas")) {
        return m_local->GetSecao().GetAgregadas().size();
    }
    return 0;
}

std::vector<ueword> CLocal::GetAgregadas() const
{
    const bool ehSecao = EhSecao("GetAgregadas");
    std::vector<ueword> numeros;
    if (ehSecao) {
        const md::CSecaoEleitoral& secao = m_local->GetSecao();
        const md::TVectorIdentificacaoAgregada& agregadas = m_local->GetSecao().GetAgregadas();
        for (const md::CIdentificacaoAgregada& agregada : m_local->GetSecao().GetAgregadas()) {
            numeros.insert(numeros.end(), 1, agregada.GetNumero());
        }
    }
    return numeros;
}

ETipoLocalVotacao CLocal::GetTipoLocalVotacao() const
{
    VerificaEhSecao("GetTipoLocalVotacao");
    return m_local->GetSecao().GetTipo();
}

// (original lines 161-341: content not recovered)
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

md::TVectorIdentificacaoAgregada CLocal::GetTodasSecoes() const
{
    const bool ehSecao = EhSecao("GetTodasSecoes");
    md::TVectorIdentificacaoAgregada secoes;
    if (ehSecao) {
        const md::CSecaoEleitoral secao = m_local->GetSecao();
        secoes.push_back(md::CIdentificacaoAgregada(secao.GetIdentificacao().GetSecao(), secao.GetTipo()));
        const md::TVectorIdentificacaoAgregada agregadas = secao.GetAgregadas();
        secoes.insert(secoes.end(), agregadas.begin(), agregadas.end());
    }
    return secoes;
}

void CLocal::Carrega()
{
    const std::string arquivo = GetPathArquivoLocal();
    m_local.reset(new md::CLocal(CarregaArquivo<asn::CConversorLocal>(arquivo)));
}

std::string GetPathArquivoLocal()
{
    return (CPath::GetPathEstatico(FLASH_INTERNA) / GetNomeArquivoLocal()).string();
}

static std::string NomeArquivoLocal(uedword municipio, ueword zona, ueword secao)
{
    return CNomeArquivo::NomeArquivoLocal(municipio, zona, secao, "lo", "dat");
}

std::string GetNomeArquivoLocal()
{
    const md::estadoaplicacao::CEstadoGeral geral = CAppInfo::GetGeralInterno();
    const md::estadoaplicacao::CLocalidadeEleitoral& secao = geral.GetDadoLocal().GetSecaoCarga();
    return NomeArquivoLocal(secao.GetMunicipio(), secao.GetZona(), secao.GetSecao());
}

bool CLocal::TemSecao() const
{
    return m_local->TemSecao();
}

bool CLocal::TemContingencia() const
{
    return m_local->TemContingencia();
}

std::string FormataAgregadas(const std::string& formato)
{
    const CLocal& local = CLocal::GetInst();
    const uebyte quantidade = local.GetQtdAgregadas();
    std::string agregadas;
    if (quantidade > 0) {
        const std::vector<ueword> numeros = local.GetAgregadas();
        const char* separador = "";
        for (size_t i = 0; i < quantidade; ++i) {
            agregadas += std::format("{}{:04}", separador, numeros[i]);
            separador = " ";
        }
    }
    return std::vformat(formato, std::make_format_args(agregadas));
}

std::string FormataQtdAgregadas(const std::string& formato)
{
    const uebyte quantidade = CLocal::GetInst().GetQtdAgregadas();
    return std::vformat(formato, std::make_format_args(quantidade));
}

} // namespace comum
