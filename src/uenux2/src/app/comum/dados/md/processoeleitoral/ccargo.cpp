// Reconstruction notes: comum::md::CCargo. Lines 81, 89, 112 and 212 to 240 are records' and fix their throws; no record
// names the name getters, so their place around GetOrdinalEscolha, above Valida, is a choice, as their names are (read
// from which field each copies; the fragment lists them). GetDetalheConsulta's own body is target fn 1923, a thunk of
// binaryen's merge 6029, so it stays out of our link: every call of it here is inlined by clang.
#include "app/comum/dados/md/processoeleitoral/ccargo.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

namespace {

// The two sexes the name getters tell apart: CSexo::ESexo's enumerators are not recovered. The names are chosen; the
// values are the ones fns 2796 and 3715 branch on.
constexpr CSexo::ESexo SEXO_MASCULINO = static_cast<CSexo::ESexo>(1);
constexpr CSexo::ESexo SEXO_FEMININO = static_cast<CSexo::ESexo>(2);

} // namespace

// (original lines 22-77: content not recovered)
#line 78
const CDetalheCandidato& CCargo::GetDetalheCandidato() const
{
    if (!m_detalheCandidato) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8134, "Não é cargo de candidato.");
    }
    return *m_detalheCandidato;
}

const CDetalheConsulta& CCargo::GetDetalheConsulta() const
{
    if (!m_detalheConsulta) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8135, "Não é cargo de consulta.");
    }
    return *m_detalheConsulta;
}

std::string CCargo::GetNomeNeutro() const
{
    if (m_detalheCandidato) {
        return m_detalheCandidato->GetNomes().GetNomeNeutro();
    }
    return GetDetalheConsulta().GetNome();
}


std::string CCargo::GetOrdinalEscolha(TQtdEscolha escolha) const
{
    if (m_qtdeEscolhas == 1) {
        return "";
    }

    if (escolha <= m_qtdeEscolhas) {
        return std::format("{}ª vaga", escolha);
    } else {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8137,
                                 std::format("Cargo {} com escolha invalida {}", GetNomeMasculino(), escolha));
    }
}

std::string CCargo::GetNomeMasculino() const
{
    if (m_detalheCandidato) {
        return m_detalheCandidato->GetNomes().GetNomeMasculino();
    }
    return GetDetalheConsulta().GetNome();
}

std::string CCargo::GetNomeFeminino() const
{
    if (m_detalheCandidato) {
        return m_detalheCandidato->GetNomes().GetNomeFeminino();
    }
    return GetDetalheConsulta().GetNome();
}

std::string CCargo::GetNomeAbreviado() const
{
    if (m_detalheCandidato) {
        return m_detalheCandidato->GetNomes().GetNomeAbreviado();
    }
    return GetDetalheConsulta().GetNome();
}

std::string CCargo::GetNome(CSexo::ESexo sexo) const
{
    switch (sexo) {
    case SEXO_MASCULINO:
        return GetNomeMasculino();
    case SEXO_FEMININO:
        return GetNomeFeminino();
    default:
        return GetNomeNeutro();
    }
}

std::string CCargo::GetNomeSuplente(size_t suplente, CSexo::ESexo sexo) const
{
    const CNomesCargo nomes = GetDetalheCandidato().GetSuplente(suplente).GetNomes();
    switch (sexo) {
    case SEXO_MASCULINO:
        return nomes.GetNomeMasculino();
    case SEXO_FEMININO:
        return nomes.GetNomeFeminino();
    default:
        return nomes.GetNomeNeutro();
    }
}

// (original lines 166-208: content not recovered)
#line 209
void CCargo::Valida() const
{
    if (m_abrangencia > ABRANGENCIA_FEDERAL) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8138, "Abrangência inválida.");
    }
    if (m_numeroDigitos < 1 || m_numeroDigitos > 5) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8139, "Número de dígitos inválido.");
    }
    if (m_qtdeEscolhas == 0) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8140, "Quantidade de escolhas inválida.");
    }
    if (m_paginaImpressaoVoto < 1 || m_paginaImpressaoVoto > 5) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8141, "Página de impressão do voto inválida.");
    }
    switch (m_tipo) {
        case CONSULTA:
            if (!m_detalheConsulta) {
                throw CUeComumDadosError(EUE_COMUM_DADOS_8142, "Tipo de cargo de consulta sem informações de consulta.");
            }
            break;


        case MAJORITARIO:
        case PROPORCIONAL:
            if (!m_detalheCandidato) {
                throw CUeComumDadosError(EUE_COMUM_DADOS_8143, "Tipo de cargo de candidato sem informações de candidato.");
            }
            break;


        default:
            throw CUeComumDadosError(EUE_COMUM_DADOS_8144, "Tipo de cargo inválido.");
    }
}

} // namespace comum::md
