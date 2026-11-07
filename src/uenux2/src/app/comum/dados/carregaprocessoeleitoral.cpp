// The reconstruction's notes, not TSE's text. comum's load of the processo eleitoral from its files: target fn 3771
// (CarregaProcessoEleitoral of the general state, with LeProcessoEleitoral inlined behind a stack frame of its own) and
// fn 5778 (CarregaPleito, which 3771 calls once per pleito), over CarregaArquivo's instances (carregaarquivo.h). No
// record names the file or these functions: every name, the path, the lines and their being free functions are chosen.
// Two forms are measured, not read from any record: LeProcessoEleitoral defined below CarregaProcessoEleitoral, which
// declares it, and its upper-casing written with std::transform. src/units/280-uenux2-processoeleitoral.mk has the
// evidence for each form and the forms that give the same object.
#include "app/comum/dados/carregaprocessoeleitoral.h"

#include <algorithm>
#include <cctype>
#include <iterator>
#include <utility>
#include <vector>

#include "api/util/csystem.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/carregaarquivo.h"
#include "app/comum/dados/asn/correspondencia/cconversorcabecalhopacote.h"
#include "app/comum/dados/asn/processoeleitoral/cconversoreleicaope.h"
#include "app/comum/dados/asn/processoeleitoral/cconversorprocessoeleitoral.h"
#include "app/comum/dados/asn/processoeleitoral/cconversorsituacoeseleicoes.h"
#include "app/comum/dados/md/processoeleitoral/cprocessoeleitoraldto.h"
#include "app/comum/nomearquivo/cnomearquivo.h"

namespace comum {

md::CPleito CarregaPleito(const EUrnaFase fase, const std::string& uf, const std::filesystem::path& diretorio,
    const md::CPleitoDTO& dto)
{
    const std::string nomeSituacoes = CNomeArquivo::NomeArquivoUF(fase, dto.GetID(), uf, "ste", "dat");
    md::TVectorEleicaoPE eleicoes;
    md::TMapVersaoPacoteEleicao versoes;
    std::vector<md::CSituacoesEleicoes> situacoes;
    if (api::CSystem::ExistFile((diretorio / nomeSituacoes).string())) {
        situacoes = CarregaArquivo<asn::CConversorSituacoesEleicoes>((diretorio / nomeSituacoes).string());
        for (const md::CSituacoesEleicoes& situacao : situacoes) {
            const std::string nomeEleicao =
                CNomeArquivo::NomeArquivoUF(fase, situacao.GetIdEleicao(), uf, "ce", "dat");
            const md::CEleicaoPE eleicao = CarregaArquivo<asn::CConversorEleicaoPE>((diretorio / nomeEleicao).string());
            eleicoes.push_back(eleicao);
            const std::string nomeCabecalho = api::TrocaExtensao(nomeEleicao, "pid");
            const md::CCabecalhoPacote cabecalho =
                CarregaArquivo<asn::CConversorCabecalhoPacote>((diretorio / nomeCabecalho).string());
            versoes.insert(std::make_pair(eleicao.GetID(), cabecalho.GetVersao()));
        }
    }
    return md::CPleito(dto.GetID(), dto.GetNome(), dto.GetData(), eleicoes, versoes, situacoes);
}

md::CProcessoEleitoral LeProcessoEleitoral(const EUrnaFase fase, const uedword idPE, const std::string& uf,
    const std::filesystem::path& diretorio);

md::CProcessoEleitoral CarregaProcessoEleitoral(const md::estadoaplicacao::CEstadoGeral& estadoGeral,
    const EFlashOrigem origem)
{
    const std::filesystem::path diretorio = CPath::GetPathEstatico(origem);
    return LeProcessoEleitoral(estadoGeral.GetDadoCarga().GetFase(), estadoGeral.GetIdPE(),
        estadoGeral.GetDadoLocal().GetUF(), diretorio);
}

md::CProcessoEleitoral LeProcessoEleitoral(const EUrnaFase fase, const uedword idPE, const std::string& uf,
    const std::filesystem::path& diretorio)
{
    const std::string nomeProcesso = NomeArquivoPE(fase, idPE, "cp", "dat");
    const md::CProcessoEleitoralDTO dto =
        CarregaArquivo<asn::CConversorProcessoEleitoral>((diretorio / nomeProcesso).string());
    const md::CPleito pleito1 = CarregaPleito(fase, uf, diretorio, dto.GetPleito1());
    std::string ufMaiuscula;
    std::transform(uf.begin(), uf.end(), std::back_inserter(ufMaiuscula), ::toupper);
    if (dto.TemPleito2()) {
        const md::CPleito pleito2 = CarregaPleito(fase, uf, diretorio, dto.GetPleito2());
        return md::CProcessoEleitoral(dto.GetID(), ufMaiuscula, dto.GetNome(), dto.GetUtilizaBiometria(),
            dto.GetOrigem(), pleito1, pleito2, dto.GetIdentificadorPrincipal(), dto.GetIdentificadores());
    }
    return md::CProcessoEleitoral(dto.GetID(), ufMaiuscula, dto.GetNome(), dto.GetUtilizaBiometria(), dto.GetOrigem(),
        pleito1, dto.GetIdentificadorPrincipal(), dto.GetIdentificadores());
}

} // namespace comum
