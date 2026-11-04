// Reconstruction: comum::asn::CConversorBiometriaEleitor's slot 3 (target fn 11422, fragment 335). Its record places
// the throw, line 26, column 15; every other line of this file is chosen. The dedos::value_type it builds and never
// reads is the target's (fragment 335 has the evidence); its being a named local is a reading.
#include "app/comum/dados/asn/eleitor/cconversorbiometriaeleitor.h"

#include "app/comum/dados/asn/eleitor/cconversordedo.h"
#include "app/comum/dados/euecomumdadoserror.h"
#include "ecourna/app/dados/asn/cconversorfoto.hpp"

namespace comum::asn {

// (original lines 12-22: content not recovered)
#line 23
md::CBiometriaEleitor CConversorBiometriaEleitor::DoDesconverte(const TEntidade& entidade) const
{
    if (!entidade.foto_isPresent() && !entidade.dedos_isPresent()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7893, "Não tem nem foto nem dedos, mas falou que tem biometria.");
    }

    std::vector<md::CDedo> dedos;
    if (entidade.dedos_isPresent()) {
        CConversorDedo conversorDedo;
        ModuloEleitores::BiometriaEleitor::dedos::value_type listaDedos;
        for (size_t i = 0; i < entidade.get_dedos().size(); ++i) {
            dedos.push_back(conversorDedo.Desconverte(entidade.get_dedos()[i]));
        }
    }

    if (entidade.foto_isPresent()) {
        ecourna::app::dados::asn::CConversorFoto conversorFoto;
        const ecourna::app::dados::CFoto foto = conversorFoto.Deconverte(entidade.get_foto());
        if (entidade.dedos_isPresent()) {
            return md::CBiometriaEleitor(foto, dedos);
        }
        return md::CBiometriaEleitor(foto);
    }
    return md::CBiometriaEleitor(dedos);
}

} // namespace comum::asn
