// Reconstruction: comum::md::CEleitor's two constructors (target fns 5668 and 5666) and ValidaCriacao (fn 5667), which
// both call; ValidaCriacao's records (lines 103 and 107, column 15, and 113, column 19) place its throws. The
// constructors have no record, so their lines are a choice, above the member they call, in the order the target's
// indices give (docs/how-to-decompile.md step 3, "The order of two members"). GetOffsetBiometria (record line 79) is not
// written: binaryen inlines it into its one caller, fn 1937.
#include "app/comum/dados/md/eleitor/celeitor.h"

#include "app/comum/dados/euecomumdadoserror.h"
#include "ecourna/api/util/cstringutils.hpp"

using ecourna::api::util::CStringUtils;

namespace comum::md {

CEleitor::CEleitor(int sequencial, ueword secao, const std::vector<CEleitorIdentidade>& identidades,
    ENecessidadeEspecial necessidadeEspecial, const std::string& nome, const std::string& nomeSocial,
    const CTransferenciaTemporaria& transferencia, const std::string& nomeMae, const std::vector<uebyte>& biometria,
    const CIndexer& offsetBiometria)
    : m_sequencial(sequencial), m_secao(secao), m_identidades(identidades), m_necessidadeEspecial(necessidadeEspecial),
      m_nome(nome), m_nomeSocial(nomeSocial), m_transferencia(transferencia), m_nomeMae(nomeMae),
      m_biometria(biometria), m_offsetBiometria(offsetBiometria)
{
    ValidaCriacao();
}

CEleitor::CEleitor(int sequencial, ueword secao, const std::vector<CEleitorIdentidade>& identidades,
    ENecessidadeEspecial necessidadeEspecial, const std::string& nome, const std::string& nomeSocial,
    const CTransferenciaTemporaria& transferencia, const std::string& nomeMae)
    : m_sequencial(sequencial), m_secao(secao), m_identidades(identidades), m_necessidadeEspecial(necessidadeEspecial),
      m_nome(nome), m_nomeSocial(nomeSocial), m_transferencia(transferencia), m_nomeMae(nomeMae)
{
    ValidaCriacao();
}

// (original lines 35-98: content not recovered)
#line 99
void CEleitor::ValidaCriacao() const
{
    const std::string nome = CStringUtils::Trim(m_nome);
    if (nome.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8064, "Nome vazio");
    }

    if (m_necessidadeEspecial < 0 || m_necessidadeEspecial > 1) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8065, "Necessidade especial inválida");
    }

    if (!m_nomeSocial.empty()) {
        const std::string nomeSocial = CStringUtils::Trim(m_nomeSocial);
        if (nomeSocial.empty()) {
            throw CUeComumDadosError(EUE_COMUM_DADOS_8066, "Nome social vazio");
        }
    }
}

} // namespace comum::md
