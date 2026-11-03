// The reconstruction's notes, not TSE's text: CarregaArquivo and its instances (carregaarquivo.h), and
// CLeitorASN::LeBiometriaEleitor (app/comum/asn/cleitorasn.h). No record names this file: the target's data put the
// records of these instances' templates and of LeBiometriaEleitor's in one object, a run of entity readers
// (src/units/280-uenux2-processoeleitoral.mk). The order of the explicit instantiations is chosen; LeBiometriaEleitor's
// place among them follows that run's order (its records lie between the EleicaoPE instance's and the
// CabecalhoPacote instance's); at the head or at the end of the file the object's code is the same
// (src/units/98-uenux2-app-comum-dados.mk).
#include "app/comum/dados/carregaarquivo.h"

#include "api/io/asn/cfileasn.h"
#include "app/comum/asn/cleitorasn.h"
#include "app/comum/asn/legravaentidade.h"
#include "app/comum/dados/asn/correspondencia/cconversorcabecalhopacote.h"
#include "app/comum/dados/asn/eleitor/cconversorbiometriaeleitorcifrada.h"
#include "app/comum/dados/asn/processoeleitoral/cconversoreleicaope.h"
#include "app/comum/dados/asn/processoeleitoral/cconversorprocessoeleitoral.h"
#include "app/comum/dados/asn/processoeleitoral/cconversorsituacoeseleicoes.h"
#include "app/comum/dados/md/eleitor/cparametro.h"

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

md::CBiometriaEleitor CLeitorASN::LeBiometriaEleitor(const std::string& arquivo, const md::CParametro& parametro)
{
    return LeEntidadeBiometria<asn::CConversorBiometriaEleitorCifrada>(
        arquivo, parametro, parametro.GetOffset(), "LeBiometriaEleitor(" + parametro.GetIdentidade().GetIdentificador() + ")");
}

template md::CCabecalhoPacote CarregaArquivo<asn::CConversorCabecalhoPacote>(const std::string& arquivo);

} // namespace comum
