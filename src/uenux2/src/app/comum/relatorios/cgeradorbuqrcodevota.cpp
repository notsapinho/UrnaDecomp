// comum::CGeradorBUQRCodeVota (cgeradorbuqrcodevota.h says why this path). This comment is the reconstruction's. No record
// names this file or gives one of its lines, so every line is a choice. Written here: the constructor, fn 5603, the
// destructor, fns 11244 (D2) and 11243 (D0), the key function, Slot2, fn 11242, and Slot3, fn 11241.
#include "app/comum/relatorios/cgeradorbuqrcodevota.h"

#include <utility>

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/clocal.h"
#include "app/comum/dados/crdvvota.h"

namespace comum {

CGeradorBUQRCodeVota::CGeradorBUQRCodeVota(const CCabecalhoQRCodeBuilder& cabecalho, ueword comparecimento,
                                           bool origemRED, bool comEmissao, const api::CDateTime& dataHoraEmissao)
    : CGeradorBUQRCode(cabecalho, CRdvVota::GetInst(), CEleitores::GetInst().QuantidadeAptosPorAbrangencia()),
      m_comparecimento(comparecimento),
      m_origemRED(origemRED),
      m_comEmissao(comEmissao),
      m_dataHoraEmissao(dataHoraEmissao)
{
}

CGeradorBUQRCodeVota::~CGeradorBUQRCodeVota() = default;

void CGeradorBUQRCodeVota::Slot2(CCabecalhoQRCodeBuilder& cabecalho) const
{
    const bool temVota =
        CAppInfo::GetInst().TemVota(std::as_const(CAppInfo::GetInst()).GetGeral().GetDadoCarga().GetTurno());
    const CLocal& local = CLocal::GetInst();
    const CEleitores& eleitores = CEleitores::GetInst();
    const SQtdeAptos aptos = eleitores.QuantidadeAptos();
    if (m_origemRED) {
        cabecalho.DefineOrigemRED();
    } else {
        cabecalho.DefineOrigemVOTA();
    }
    if (!local.GetIdentificacoesAgregadas().empty()) {
        cabecalho.DefineAgregadas(local.GetAgregadas());
    }
    cabecalho.DefineLocal(local.GetLocalID());
    cabecalho.DefineQtdeAptos(aptos.m_qtdeAptosDaSecao + aptos.m_qtdeAptosTTE);
    cabecalho.DefineQtdeAptosDaSecao(aptos.m_qtdeAptosDaSecao);
    cabecalho.DefineQtdeAptosTTE(aptos.m_qtdeAptosTTE);
    cabecalho.DefineQtdeCompareceram(m_comparecimento);
    cabecalho.DefineMunicipio(CAppInfo::GetInst().GetGeral().GetDadoLocal().GetSecaoCarga().GetMunicipio());
    if (local.UrnaBiometrica()) {
        cabecalho.DefineQtdeHabilitacaoBiometrica(eleitores.QuantidadeHabilitacaoBiometrica());
        cabecalho.DefineQtdeHabilitacaoBiografica(eleitores.QuantidadeHabilitacaoBiografica());
        cabecalho.DefineQtdeHabilitacaoSemBiometria(eleitores.QuantidadeHabilitacaoSemBiometria());
    }
    cabecalho.DefineQtdeFaltosos(aptos.m_qtdeAptosDaSecao + aptos.m_qtdeAptosTTE - m_comparecimento);
    if (temVota) {
        const md::estadoaplicacao::CEstadoGeralVota& vota = CAppInfo::GetInst().GetVota();
        const api::CDateTime inicio = vota.GetDtHrInicioAquisicao();
        const api::CDateTime fim = vota.GetDtHrFimAquisicao();
        cabecalho.DefineAbertura(inicio);
        cabecalho.DefineFechamento(fim);
    }
    if (m_comEmissao) {
        cabecalho.DefineEmissao(m_dataHoraEmissao);
    }
}

std::string CGeradorBUQRCodeVota::Slot3(TEleicaoID) const
{
    return "";
}

} // namespace comum
