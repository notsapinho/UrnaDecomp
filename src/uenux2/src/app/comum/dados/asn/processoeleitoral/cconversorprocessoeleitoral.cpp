#include "app/comum/dados/asn/processoeleitoral/cconversorprocessoeleitoral.h"

#include <algorithm>
#include <iterator>
#include <format>

#include "app/comum/dados/asn/processoeleitoral/cconversororigemconfiguracao.h"
#include "app/comum/dados/asn/processoeleitoral/cconversorpleito.h"
#include "app/comum/dados/asn/processoeleitoral/cconversortipoidentificadoreleitor.h"
#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::asn {

// (original lines 14-26: content not recovered)
#line 27
md::CProcessoEleitoralDTO CConversorProcessoEleitoral::DoDesconverte(const TEntidade& entidade) const
{
    const CConversorOrigemConfiguracao conversorOrigem;
    const CConversorTipoIdentificadorEleitor conversorTipoIdentificador;

    const uedword id = entidade.get_cabecalho().get_idEleitoral().get_idProcessoEleitoral().getValue();
    const std::string nome = entidade.get_nome();
    const bool utilizaBiometria = entidade.get_utilizaBiometria();
    const md::EOrigemConfiguracao origem = conversorOrigem.Desconverte(entidade.get_origemConfiguracao());

    const CConversorPleito conversorPleito;
    const md::CPleitoDTO pleito1 = conversorPleito.Desconverte(entidade.get_pleito1());

    const ecourna::app::dados::ETipoIdentificadorEleitor identificadorPrincipal =
        conversorTipoIdentificador.Desconverte(entidade.get_tipoIdentificadorPrincipalEleitor());
    std::vector<ecourna::app::dados::ETipoIdentificadorEleitor> identificadores;
    std::transform(entidade.get_tiposIdentificadoresPermitidos().begin(),
                   entidade.get_tiposIdentificadoresPermitidos().end(), std::back_inserter(identificadores),
                   [&conversorTipoIdentificador](const auto& tipo) {
                       return conversorTipoIdentificador.Desconverte(tipo);
                   });

    if (std::find(identificadores.begin(), identificadores.end(), identificadorPrincipal) == identificadores.end()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8185,
            std::format("Identidade principal ({}) ausente na lista de identidades", static_cast<int>(identificadorPrincipal)));
    }

    if (entidade.pleito2_isPresent()) {
        return TDado(id, nome, utilizaBiometria, origem, pleito1, conversorPleito.Desconverte(entidade.get_pleito2()),
            identificadorPrincipal, identificadores);
    }
    return TDado(id, nome, utilizaBiometria, origem, pleito1, identificadorPrincipal, identificadores);
}

} // namespace comum::asn
