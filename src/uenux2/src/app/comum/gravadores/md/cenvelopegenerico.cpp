// Reconstruction: comum::md::CEnvelopeGenerico's constructors (target fns 3821, 5860 and 5861), ValidaCriacao (fn 3822),
// which the three call, and the getters GetUrna, GetLocal and GetSeguranca, which binaryen inlines into
// comum::asn::CConversorEnvelopeGenerico::DoConverte (fn 10271, their one caller). The throws are records of the target
// (lines 96 to 156, column 15); the constructors have none, so their lines are a choice, above the getters.

#include "app/comum/gravadores/md/cenvelopegenerico.h"

#include "app/comum/gravadores/euecomumgravadoreserror.h"

namespace comum::md {

CEnvelopeGenerico::CEnvelopeGenerico(const CCabecalhoEntidade& cabecalho, EUrnaFase fase, TMunicipioID municipio,
    TZonaID zona, const std::optional<TLocalID>& local, TSecaoID secao, Tipo tipo, const CSeguranca& seguranca,
    const std::vector<uebyte>& conteudo, EUrnaTipo tipoUrna)
    : m_cabecalho(cabecalho), m_fase(fase), m_municipio(municipio), m_zona(zona), m_local(local), m_secao(secao),
      m_tipo(tipo), m_seguranca(seguranca), m_conteudo(conteudo), m_tipoUrna(tipoUrna)
{
    ValidaCriacao();
    if (m_tipoUrna != eUrnaVota && m_tipoUrna != eUrnaContingenciaVota && m_tipoUrna != eUrnaContingenciaVotaRecupera) {
        m_local.reset();
    }
}

CEnvelopeGenerico::CEnvelopeGenerico(const CCabecalhoEntidade& cabecalho, EUrnaFase fase, const CUrna& urna,
    TMunicipioID municipio, TZonaID zona, const std::optional<TLocalID>& local, TSecaoID secao, Tipo tipo,
    const std::vector<uebyte>& conteudo)
    : m_cabecalho(cabecalho), m_fase(fase), m_urna(urna), m_municipio(municipio), m_zona(zona), m_local(local),
      m_secao(secao), m_tipo(tipo), m_conteudo(conteudo), m_tipoUrna(urna.GetTipoUrna())
{
    ValidaCriacao();
    if (m_tipoUrna != eUrnaVota && m_tipoUrna != eUrnaContingenciaVota && m_tipoUrna != eUrnaContingenciaVotaRecupera) {
        m_local.reset();
    }
}

CEnvelopeGenerico::CEnvelopeGenerico(const CCabecalhoEntidade& cabecalho, EUrnaFase fase, TMunicipioID municipio,
    TZonaID zona, const std::optional<TLocalID>& local, TSecaoID secao, Tipo tipo, const std::vector<uebyte>& conteudo,
    EUrnaTipo tipoUrna)
    : m_cabecalho(cabecalho), m_fase(fase), m_municipio(municipio), m_zona(zona), m_local(local), m_secao(secao),
      m_tipo(tipo), m_conteudo(conteudo), m_tipoUrna(tipoUrna)
{
    ValidaCriacao();
    if (m_tipoUrna != eUrnaVota && m_tipoUrna != eUrnaContingenciaVota && m_tipoUrna != eUrnaContingenciaVotaRecupera) {
        m_local.reset();
    }
}

// (original lines 48-92: content not recovered)
#line 93
const CUrna& CEnvelopeGenerico::GetUrna() const
{
    if (!m_urna.has_value()) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8675, "Não há informação de urna");
    }
    return *m_urna;
}

// (original lines 101-102: content not recovered)
#line 103
TLocalID CEnvelopeGenerico::GetLocal() const
{
    if (!m_local.has_value()) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8676, "Não há informação de local");
    }
    return *m_local;
}

// (original lines 111-113: content not recovered)
#line 114
const CSeguranca& CEnvelopeGenerico::GetSeguranca() const
{
    if (!m_seguranca.has_value()) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8677, "Não há informação de criptografia");
    }
    return *m_seguranca;
}

// (original lines 122-123: content not recovered)
#line 124
void CEnvelopeGenerico::ValidaCriacao() const
{
    if (m_fase == '0' || m_fase > FASE_TREINAMENTO) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8678, "Fase inválida");
    }
    if (m_municipio >= 100000) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8679, "Código de município inválido");
    }


    if (m_zona >= 10000) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8680, "Número de zona inválido");
    }


    if (m_local.has_value() && *m_local >= 10000) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8681, "Número de local inválido");
    }


    if (m_tipoUrna < eUrnaVota || m_tipoUrna > eUrnaContingenciaVotaRecupera) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8682, "Tipo de urna inválido");
    }

    // (original lines 148-149: content not recovered)
#line 150
    if (m_secao >= 10000) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8683, "Número de seção inválido");
    }


    if (m_tipo > ENVELOPE_ZERESIMA_IMPRESSA) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8684, "Tipo de envelope inválido");
    }
}

} // namespace comum::md
