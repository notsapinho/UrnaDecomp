// The reconstruction's notes, not TSE's text: comum::CPE's GetInst (line 21, the macro of unit 110), Existe (fn 2788, no
// record: its line is chosen) and CreateInst (fn 2787, its throw's record at line 26, column 15), with the constructor
// CreateInst holds inlined and the statics below them, as in unit 110's other +47 files.
#include "app/comum/dados/cpe.h"

#include "app/comum/dados/carregaprocessoeleitoral.h"
#include "app/comum/dados/euecomumdadoserror.h"
#include "ecourna/api/pattern/singleton.hpp"

namespace comum {

bool CPE::Existe()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    return s_instancia != nullptr;
}

// (original lines 18-20: content not recovered)
#line 21
SINGLETON_IMPL_GET_INST(CPE, s_mutex, s_instancia)

void CPE::CreateInst(const md::estadoaplicacao::CEstadoGeral& estadoGeral, const EFlashOrigem origem)
{
    if (s_instancia) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7876, "Instância já criada");
    }
    const md::CProcessoEleitoral processo = CarregaProcessoEleitoral(estadoGeral, origem);
    s_instancia.reset(new CPE(processo, estadoGeral.GetDadoCarga().GetTurno(), estadoGeral.GetDadoCarga().GetFase(),
        estadoGeral.GetDadoLocal().GetUF()));
}

std::unique_ptr<CPE> CPE::s_instancia;
std::mutex CPE::s_mutex;

CPE::CPE(const md::CProcessoEleitoral& processo, const EUrnaTurno turno, const EUrnaFase fase, const std::string& uf)
    : m_processo(processo), m_turno(turno),
      m_identificacao(fase, m_processo.GetID(), uf, turno == TURNO_1 ? m_processo.GetPleito1() : m_processo.GetPleito2())
{
}

CPE::~CPE() = default;

} // namespace comum
