// The reconstruction's notes, not TSE's text: CarregaArquivo and its instances (carregaarquivo.h). The order of the
// explicit instantiations is chosen.
#include "app/comum/dados/carregaarquivo.h"

#include "api/io/asn/cfileasn.h"
#include "app/comum/dados/asn/correspondencia/cconversorcabecalhopacote.h"
#include "app/comum/dados/asn/processoeleitoral/cconversoreleicaope.h"
#include "app/comum/dados/asn/processoeleitoral/cconversorprocessoeleitoral.h"
#include "app/comum/dados/asn/processoeleitoral/cconversorsituacoeseleicoes.h"

namespace comum {

template <typename CONVERSOR>
typename CONVERSOR::TDado CarregaArquivo(const std::string& arquivo)
{
    CONVERSOR conversor;
    return conversor.Desconverte(api::CFileASN::ReadFromFile<typename CONVERSOR::TEntidade>(arquivo));
}

template md::CProcessoEleitoralDTO CarregaArquivo<asn::CConversorProcessoEleitoral>(const std::string& arquivo);
template std::vector<md::CSituacoesEleicoes> CarregaArquivo<asn::CConversorSituacoesEleicoes>(const std::string& arquivo);
template md::CEleicaoPE CarregaArquivo<asn::CConversorEleicaoPE>(const std::string& arquivo);
template md::CCabecalhoPacote CarregaArquivo<asn::CConversorCabecalhoPacote>(const std::string& arquivo);

} // namespace comum
