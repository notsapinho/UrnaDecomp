// comum::md::CEntidadeBU (/home/rubio/tse/uenux2/src/app/comum/gravadores/md/centidadebu.cpp, the file its records
// name): the four constructors, ValidaCriacao, which each of them calls, and the three getters that throw when their part
// of the BU is missing. The throws are records of the target, so their lines are fixed:
//   ValidaCriacao                   records at lines 159, 162, 167, 172 and 177, column 15
//   GetDadosVota                    record at line 186, column 15
//   GetDadosSA                      record at line 196, column 15
//   GetDetalhamentoComparecimento   record at line 206, column 15
// None of these functions has a target index of its own. The constructors and ValidaCriacao are held by target fn 11629
// (comum::CGravadorBU::GravaResultado), inside the frame of CGravadorBU::MontaEntidadeBU (record cgravadorbu.cpp:636),
// which builds the entity in four branches, one per constructor: ValidaCriacao's 640-byte frame opens once, after the
// four branches meet. Defined in the class instead of here, the constructors give the same fn 11629 (pnpm wasm score
// in the whole link, 423 over 7089 rows both ways, every one operand-only); out of line is the form this directory's
// classes with a ValidaCriacao have (cenvelopegenerico.cpp), a choice. The getters are held by
// CConversorEntidadeBU::DoConverte (fn 10273), each behind a frame of its own. The constructors have no record: their
// lines, above ValidaCriacao's, are a choice, and so is where ValidaCriacao and each getter start. ValidaCriacao's
// test of the phase (48 rejected, and every value above 51) is cenvelopegenerico.cpp's spelling of the same test.

#include "app/comum/gravadores/md/centidadebu.h"

#include <format>

#include "app/comum/gravadores/euecomumgravadoreserror.h"

namespace comum::md {

CEntidadeBU::CEntidadeBU(const CCabecalhoEntidade& cabecalho, EUrnaFase fase, const CUrna& urna, TMunicipioID municipio,
    TZonaID zona, TLocalID local, TSecaoID secao, ueword qtdEleitoresCompareceram,
    const std::vector<CResultadoVotacaoPorEleicao>& resultadosVotacaoPorEleicao,
    const std::vector<std::string>& historicoCodigosCarga, const CDadosBUVota& dadosVota,
    const api::CDateTime& dataHoraEmissao, const std::vector<CHistoricoVotoImpresso>& historicoVotoImpresso)
    : m_cabecalho(cabecalho),
      m_fase(fase),
      m_urna(urna),
      m_municipio(municipio),
      m_zona(zona),
      m_local(local),
      m_secao(secao),
      m_qtdEleitoresCompareceram(qtdEleitoresCompareceram),
      m_resultadosVotacaoPorEleicao(resultadosVotacaoPorEleicao),
      m_historicoCodigosCarga(historicoCodigosCarga),
      m_dadosVota(dadosVota),
      m_dataHoraEmissao(dataHoraEmissao),
      m_historicoVotoImpresso(historicoVotoImpresso)
{
    ValidaCriacao();
}

CEntidadeBU::CEntidadeBU(const CCabecalhoEntidade& cabecalho, EUrnaFase fase, const CUrna& urna, TMunicipioID municipio,
    TZonaID zona, TLocalID local, TSecaoID secao, ueword qtdEleitoresCompareceram,
    const std::vector<CResultadoVotacaoPorEleicao>& resultadosVotacaoPorEleicao,
    const std::vector<std::string>& historicoCodigosCarga, const CDadosBUVota& dadosVota,
    const api::CDateTime& dataHoraEmissao, const std::vector<CHistoricoVotoImpresso>& historicoVotoImpresso,
    const ecourna::app::dados::CDetalhamentoComparecimento& detalhamentoComparecimento)
    : m_cabecalho(cabecalho),
      m_fase(fase),
      m_urna(urna),
      m_municipio(municipio),
      m_zona(zona),
      m_local(local),
      m_secao(secao),
      m_qtdEleitoresCompareceram(qtdEleitoresCompareceram),
      m_resultadosVotacaoPorEleicao(resultadosVotacaoPorEleicao),
      m_historicoCodigosCarga(historicoCodigosCarga),
      m_dadosVota(dadosVota),
      m_dataHoraEmissao(dataHoraEmissao),
      m_historicoVotoImpresso(historicoVotoImpresso),
      m_detalhamentoComparecimento(detalhamentoComparecimento)
{
    ValidaCriacao();
}

CEntidadeBU::CEntidadeBU(const CCabecalhoEntidade& cabecalho, EUrnaFase fase, const CUrna& urna, TMunicipioID municipio,
    TZonaID zona, TLocalID local, TSecaoID secao, ueword qtdEleitoresCompareceram,
    const std::vector<CResultadoVotacaoPorEleicao>& resultadosVotacaoPorEleicao,
    const std::vector<std::string>& historicoCodigosCarga, const CDadosBUSA& dadosSA,
    const api::CDateTime& dataHoraEmissao, const std::vector<CHistoricoVotoImpresso>& historicoVotoImpresso)
    : m_cabecalho(cabecalho),
      m_fase(fase),
      m_urna(urna),
      m_municipio(municipio),
      m_zona(zona),
      m_local(local),
      m_secao(secao),
      m_qtdEleitoresCompareceram(qtdEleitoresCompareceram),
      m_resultadosVotacaoPorEleicao(resultadosVotacaoPorEleicao),
      m_historicoCodigosCarga(historicoCodigosCarga),
      m_dadosSA(dadosSA),
      m_dataHoraEmissao(dataHoraEmissao),
      m_historicoVotoImpresso(historicoVotoImpresso)
{
    ValidaCriacao();
}

CEntidadeBU::CEntidadeBU(const CCabecalhoEntidade& cabecalho, EUrnaFase fase, const CUrna& urna, TMunicipioID municipio,
    TZonaID zona, TLocalID local, TSecaoID secao, ueword qtdEleitoresCompareceram,
    const std::vector<CResultadoVotacaoPorEleicao>& resultadosVotacaoPorEleicao,
    const std::vector<std::string>& historicoCodigosCarga, const CDadosBUSA& dadosSA,
    const api::CDateTime& dataHoraEmissao, const std::vector<CHistoricoVotoImpresso>& historicoVotoImpresso,
    const ecourna::app::dados::CDetalhamentoComparecimento& detalhamentoComparecimento)
    : m_cabecalho(cabecalho),
      m_fase(fase),
      m_urna(urna),
      m_municipio(municipio),
      m_zona(zona),
      m_local(local),
      m_secao(secao),
      m_qtdEleitoresCompareceram(qtdEleitoresCompareceram),
      m_resultadosVotacaoPorEleicao(resultadosVotacaoPorEleicao),
      m_historicoCodigosCarga(historicoCodigosCarga),
      m_dadosSA(dadosSA),
      m_dataHoraEmissao(dataHoraEmissao),
      m_historicoVotoImpresso(historicoVotoImpresso),
      m_detalhamentoComparecimento(detalhamentoComparecimento)
{
    ValidaCriacao();
}

// (original lines 118-155: content not recovered)
#line 156
void CEntidadeBU::ValidaCriacao() const
{
    if (m_fase == FASE_INDEFINIDA || m_fase > FASE_TREINAMENTO) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8665, "Fase inválida");
    }
    if (m_municipio >= 100000) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8666,
                                      std::format("Código de município inválido: {}", m_municipio));
    }

    if (m_zona >= 10000) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8667,
                                      std::format("Número de zona inválido: {}", m_zona));
    }

    if (m_local >= 10000) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8668,
                                      std::format("Número de local inválido: {}", m_local));
    }

    if (m_secao >= 10000) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8669,
                                      std::format("Número de seção inválido: {}", m_secao));
    }
}


const CDadosBUVota& CEntidadeBU::GetDadosVota() const
{
    if (!m_dadosVota.has_value()) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8670, "Dados específicos de BU do Vota não definidos");
    }
    return *m_dadosVota;
}

// (original lines 191-192: content not recovered)
#line 193
const CDadosBUSA& CEntidadeBU::GetDadosSA() const
{
    if (!m_dadosSA.has_value()) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8671, "Dados específicos de BU do SA não definidos");
    }
    return *m_dadosSA;
}

// (original lines 201-202: content not recovered)
#line 203
const ecourna::app::dados::CDetalhamentoComparecimento& CEntidadeBU::GetDetalhamentoComparecimento() const
{
    if (!m_detalhamentoComparecimento.has_value()) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8664, "Dados específicos de BU do SA não definidos");
    }
    return *m_detalhamentoComparecimento;
}

} // namespace comum::md
