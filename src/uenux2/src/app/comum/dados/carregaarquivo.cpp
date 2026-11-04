// The reconstruction's notes, not TSE's text: CarregaArquivo and CarregaArquivoEcourna and their instances
// (carregaarquivo.h), LeEleitores (carregaarquivo.h) and CLeitorASN::LeBiometriaEleitor (app/comum/asn/cleitorasn.h).
// No record names this file: the target's data put the records of these instances' templates, of the partial reader
// LeEleitores instantiates and of LeBiometriaEleitor's in one object, a run of
// entity readers (src/units/280-uenux2-processoeleitoral.mk). The order of the processo eleitoral's three instances is
// chosen; the places of the others follow that run's order: the CConversorLocal instance's records (@1563320 to
// @1563436) lie before the processo eleitoral's (@1563464), LeEleitores's records (its partial reader's) lie after the
// EleicaoPE instance's and the unwritten readers' of fn 7787 and before LeBiometriaEleitor's, LeBiometriaEleitor's
// before the CabecalhoPacote instance's, the CConversorImpedido instance's after LeBiometriaEleitor's, and the
// CConversorInformacaoMidia instance's after CabecalhoPacote's. For LeBiometriaEleitor, at the head or at the end of
// the file the object's code is the same (src/units/98-uenux2-app-comum-dados.mk); the four others were measured only
// at these places.
#include "app/comum/dados/carregaarquivo.h"

#include "api/io/asn/cfileasn.h"
#include "app/comum/asn/cleitorasn.h"
#include "app/comum/asn/legravaentidade.h"
#include "app/comum/dados/asn/cconversorlocal.h"
#include "app/comum/dados/asn/correspondencia/cconversorcabecalhopacote.h"
#include "app/comum/dados/asn/eleitor/cconversorbiometriaeleitorcifrada.h"
#include "app/comum/dados/asn/eleitor/cconversorentidadeeleitores.h"
#include "app/comum/dados/asn/eleitor/cconversorimpedido.h"
#include "app/comum/dados/asn/processoeleitoral/cconversoreleicaope.h"
#include "app/comum/dados/asn/processoeleitoral/cconversorprocessoeleitoral.h"
#include "app/comum/dados/asn/processoeleitoral/cconversorsituacoeseleicoes.h"
#include "app/comum/dados/md/eleitor/celeitor.h"
#include "app/comum/dados/md/eleitor/cimpedido.h"
#include "app/comum/dados/md/eleitor/cparametro.h"
#include "ecourna/app/dados/asn/midias/cconversorinformacaomidia.hpp"

namespace comum {

template <typename CONVERSOR>
typename CONVERSOR::TDado CarregaArquivo(const std::string& arquivo)
{
    CONVERSOR conversor;
    return conversor.Desconverte(api::CFileASN::ReadFromFile<typename CONVERSOR::TEntidade>(arquivo));
}

template md::CLocal CarregaArquivo<asn::CConversorLocal>(const std::string& arquivo);

template md::CProcessoEleitoralDTO CarregaArquivo<asn::CConversorProcessoEleitoral>(const std::string& arquivo);
template std::vector<md::CSituacoesEleicoes> CarregaArquivo<asn::CConversorSituacoesEleicoes>(const std::string& arquivo);
template md::CEleicaoPE CarregaArquivo<asn::CConversorEleicaoPE>(const std::string& arquivo);

template <typename CONVERSOR>
typename CONVERSOR::TDado CarregaArquivoParcial(const api::CFile& arquivo, const std::shared_ptr<typename CONVERSOR::TVisitor>& visitante)
{
    CONVERSOR conversor;
    return conversor.Desconverte(arquivo, visitante);
}

template <typename CONVERSOR>
typename CONVERSOR::TDado CarregaArquivoParcial(const api::CFile& arquivo)
{
    return CarregaArquivoParcial<CONVERSOR>(arquivo, std::shared_ptr<typename CONVERSOR::TVisitor>(new typename CONVERSOR::TVisitor()));
}

std::vector<md::CEleitor> LeEleitores(const api::CFile& arquivo)
{
    const md::CEntidadeEleitores entidade = CarregaArquivoParcial<asn::CConversorEntidadeEleitores>(arquivo);
    return entidade.GetEleitores();
}

md::CBiometriaEleitor CLeitorASN::LeBiometriaEleitor(const std::string& arquivo, const md::CParametro& parametro)
{
    return LeEntidadeBiometria<asn::CConversorBiometriaEleitorCifrada>(
        arquivo, parametro, parametro.GetOffset(), "LeBiometriaEleitor(" + parametro.GetIdentidade().GetIdentificador() + ")");
}

template std::vector<md::CImpedido> CarregaArquivo<asn::CConversorImpedido>(const std::string& arquivo);

template md::CCabecalhoPacote CarregaArquivo<asn::CConversorCabecalhoPacote>(const std::string& arquivo);

template <typename CONVERSOR>
typename CONVERSOR::TDado CarregaArquivoEcourna(const std::string& arquivo)
{
    CONVERSOR conversor;
    return conversor.Deconverte(api::CFileASN::ReadFromFile<typename CONVERSOR::TEntidade>(arquivo));
}

template ecourna::app::dados::CInformacaoMidia
CarregaArquivoEcourna<ecourna::app::dados::asn::CConversorInformacaoMidia>(const std::string& arquivo);

} // namespace comum
