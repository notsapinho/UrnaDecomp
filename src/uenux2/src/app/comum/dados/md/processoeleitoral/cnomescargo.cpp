// Reconstruction notes: comum::md::CNomesCargo's constructor, on its records' lines 28 to 37. It is out of line, and
// wasm-opt inlines it into its one caller, comum::asn::CConversorNomesCargo::DoDesconverte (target fn 11369): 11369
// holds its second stack prologue.
#include "app/comum/dados/md/processoeleitoral/cnomescargo.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 10-19: content not recovered)
#line 20
CNomesCargo::CNomesCargo(const std::string& nomeNeutro, const std::string& nomeMasculino, const std::string& nomeFeminino,
                         const std::string& nomeAbreviado)
    : m_nomeNeutro(nomeNeutro),
      m_nomeMasculino(nomeMasculino),
      m_nomeFeminino(nomeFeminino),
      m_nomeAbreviado(nomeAbreviado)
{
    if (m_nomeNeutro.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8155, "Nome neutro inválido.");
    }
    if (m_nomeMasculino.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8156, "Nome masculino inválido.");
    }
    if (m_nomeFeminino.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8157, "Nome feminino inválido.");
    }
    if (m_nomeAbreviado.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8158, "Nome abreviado inválido.");
    }
}

} // namespace comum::md
