// comum::CGeradorRelVersaoPacoteDados's members but slots 3 and 5. The reconstruction's own note: no record names this
// file or its lines; cgeradorrelversaopacotedados.h and src/units/287-uenux2-cgeradorrelversaopacotedados.mk say what
// is evidence and what is chosen.
#include "app/comum/relatorios/cgeradorrelversaopacotedados.h"

#include <format>

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "app/comum/relatorios/adicionaparametro.h"

namespace comum {

CGeradorRelVersaoPacoteDados::CGeradorRelVersaoPacoteDados(const std::vector<md::CCabecalhoPacote>& pacotes)
    : m_pacotes(pacotes)
{
}

CGeradorRelVersaoPacoteDados::~CGeradorRelVersaoPacoteDados()
{
}

void CGeradorRelVersaoPacoteDados::Imprime(const std::string& titulo, const std::string& subtitulo)
{
    ImprimeTituloJE();
    ImprimeVersoesPacotes();
    ImprimeRodape();
    m_builder.Show(titulo, subtitulo, true);
}

void CGeradorRelVersaoPacoteDados::ImprimeVersoesPacotes()
{
    m_builder.AddNewLine(1);
    const md::estadoaplicacao::CEstadoGeral& geral = CAppInfo::GetInst().GetGeral();
    for (const md::CCabecalhoPacote& pacote : m_pacotes) {
        const std::string espacos(38 - (pacote.GetNome().size() + pacote.GetVersao().size()), ' ');
        m_builder.AddTextField(std::format("{}{}{}", pacote.GetNome(), espacos, pacote.GetVersao()),
                               static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    }
    const std::string hash = geral.GetResumoHashVersoesPacotes();
    AdicionaParametro(m_builder, "Dados:", hash);
    m_builder.AddNewLine(1);
}

} // namespace comum
