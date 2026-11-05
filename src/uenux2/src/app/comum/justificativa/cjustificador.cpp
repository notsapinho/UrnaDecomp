#include "app/comum/justificativa/cjustificador.h"
#include "app/comum/justificativa/cjustificadordetalhe.h"
#include "app/comum/justificativa/euecomumjustificativaerror.h"

namespace comum {

CJustificadorDetalhe::CJustificadorDetalhe(const CJustificadorDetalhe& outro) = default;

CJustificador::CJustificador() : CDataMap("CJustificador")
{
}

CJustificador::~CJustificador() = default;

CJustificador& CJustificador::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CJustificador());
    }
    return *s_inst;
}

std::unique_ptr<CJustificador> CJustificador::s_inst;
std::mutex CJustificador::s_mutex;

// (original lines 27-51: content not recovered)
#line 52
void CJustificador::Justifica(const ecourna::app::dados::CNumeroInscricaoEleitoral& titulo, ueword ano)
{
    if (Find(titulo) != nullptr) {
        throw CUeComumJustificativaError(EUE_COMUM_JUSTIFICATIVA_JA_JUSTIFICADO,
                                         "Já havia justificativa para o título");
    }
    Add(titulo, CJustificadorDetalhe(ano));
}

void CJustificador::Justifica(const std::string& titulo, ueword ano)
{
    Justifica(ecourna::app::dados::CNumeroInscricaoEleitoral(titulo), ano);
}

bool servico::CJustificadorServico::Existe(const std::string& titulo) const
{
    return m_dao->RecuperarID(titulo) != nullptr;
}

void servico::CJustificadorServico::Salva(const ecourna::app::dados::CIdentificacaoJustificativa& justificativa) const
{
    if (!Existe(justificativa.GetIdentificacaoEleitor().GetIdentificadorHabilitacao()->GetNumero())) {
        m_dao->Inserir(justificativa);
    }
}

// (original lines 78-79: content not recovered)
#line 80
void CJustificador::SaveCurrentInternal()
{
    if (m_registros.empty()) {
        throw CUeComumJustificativaError(EUE_COMUM_JUSTIFICATIVA_SEM_DADOS, "Não há dados a serem salvos na MI");
    }
    const Container::value_type& corrente = *m_corrente;
    const ecourna::app::dados::CIdentificacaoJustificativa justificativa(
        ecourna::app::dados::CRegistroIdentificacaoEleitor(
            std::make_shared<ecourna::app::dados::CNumeroInscricaoEleitoral>(corrente.first)),
        ecourna::app::dados::TAno(corrente.second.GetAno()));
    m_servico.Salva(justificativa);
}

// (original lines 93-99: content not recovered)
#line 100
std::string CJustificadorDadoTitulo::Text()
{
    const CJustificador& justificador = CJustificador::GetInst();
    if (justificador.IsFim()) {
        throw CUeComumJustificativaError(EUE_COMUM_JUSTIFICATIVA_INVALIDA, "Justificativa inválida");
    }
    return justificador.GetTituloCorrente().GetNumero();
}

std::string CJustificadorDadoQuantidade::Text(const std::string& formato)
{
    const CJustificador& justificador = CJustificador::GetInst();
    std::string texto = formato;
    if (justificador.QuantidadeJustificados() == 1) {
        texto.pop_back();
    }
    const std::size_t quantidade = justificador.QuantidadeJustificados();
    return std::vformat(texto, std::make_format_args(quantidade));
}

} // namespace comum
