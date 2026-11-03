// Reconstruction: comum::md::CIDPacote's members. CIDPacoteValidar (record cidpacote.cpp:21) is the phase test each
// constructor makes, inlined by clang; the four constructors (no record: their lines are chosen) are held by target fn
// 11437 and the three getters (cidpacote.cpp:67, 75, 83) by fn 11438, each behind a stack-pointer prologue of its own
// (binaryen inlined them). CIDEleitoral's constructor is here, out of line (fn 1081's twin): the target's factories call
// it, which clang would not do in cideleitoral.cpp's TU (fragment 273 has the measurement); this file is chosen. That
// CIDPacoteValidar is file-local is chosen. The rest is blank where the original is not recovered.
#include "app/comum/md/cidpacote.h"

#include "app/comum/md/euecomummderror.h"

namespace comum::md {

CIDEleitoral::CIDEleitoral(uedword id, ETipo tipo)
    : m_id(id), m_tipo(tipo)
{
}

static void CIDPacoteValidar(EUrnaFase fase)
{
    if (fase == FASE_INDEFINIDA || fase == FASE_INVALIDA) {
        throw CUeComumMdError(EUE_COMUM_MD_8921, "Fase inválida.");
    }
}

CIDPacote::CIDPacote(const CIDEleitoral& idEleitoral, const EUrnaFase fase)
    : m_idEleitoral(idEleitoral), m_fase(fase)
{
    CIDPacoteValidar(fase);
}

CIDPacote::CIDPacote(const CIDEleitoral& idEleitoral, const EUrnaFase fase, const std::string& uf)
    : m_idEleitoral(idEleitoral), m_fase(fase), m_uf(uf)
{
    CIDPacoteValidar(fase);
}

CIDPacote::CIDPacote(const CIDEleitoral& idEleitoral, const EUrnaFase fase, const std::string& uf,
    const TMunicipioID municipio)
    : m_idEleitoral(idEleitoral), m_fase(fase), m_uf(uf), m_municipio(municipio)
{
    CIDPacoteValidar(fase);
}

CIDPacote::CIDPacote(const CIDEleitoral& idEleitoral, const EUrnaFase fase, const std::string& uf,
    const TMunicipioID municipio, const TZonaID zona)
    : m_idEleitoral(idEleitoral), m_fase(fase), m_uf(uf), m_municipio(municipio), m_zona(zona)
{
    CIDPacoteValidar(fase);
}

// (original lines 51-63: content not recovered)
#line 64
std::string CIDPacote::UF() const
{
    if (!m_uf.has_value()) {
        throw CUeComumMdError(EUE_COMUM_MD_8922, "Valor não disponível.");
    }
    return *m_uf;
}

TMunicipioID CIDPacote::Municipio() const
{
    if (!m_municipio.has_value()) {
        throw CUeComumMdError(EUE_COMUM_MD_8923, "Valor não disponível.");
    }
    return *m_municipio;
}

TZonaID CIDPacote::Zona() const
{
    if (!m_zona.has_value()) {
        throw CUeComumMdError(EUE_COMUM_MD_8924, "Valor não disponível.");
    }
    return *m_zona;
}

} // namespace comum::md
