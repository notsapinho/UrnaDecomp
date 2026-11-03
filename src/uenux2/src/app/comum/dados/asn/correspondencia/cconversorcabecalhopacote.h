#pragma once

#include <vector>

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/md/ccabecalhopacote.h"
#include "asn1/modules/ModuloDadosDisponiveisCarga.h"
#include "asn1/modules/ModuloTiposEleitorais.h"

namespace comum::asn {

// Recovered: the class head. RTTI names the class and its base (typeinfo 1562760, vtable @1562736, whose slots 2 and 3
// are target fns 11438 and 11437, DoConverte and DoDesconverte, defined in cconversorcabecalhopacote.cpp). No record
// names the class's file. In the use band its two members lie right after the candidatura converters' and right
// before CConversorDadosDisponiveisCarga's; in the data its vtable follows CConversorFotoCandidato's and the records
// of md/ccabecalhopacote.cpp (1562656 to 1562688). This header's path, beside the other converter's, is chosen.
class CConversorCabecalhoPacote
    : public IConversorASN<ModuloTiposEleitorais::CabecalhoPacote, md::CCabecalhoPacote> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

// The imported packages' list each way, used by CConversorDadosDisponiveisCarga (cconversorcabecalhopacote.cpp says
// what shows them and what is chosen).
ASN1::SEQUENCE_OF<ModuloTiposEleitorais::CabecalhoPacote> ConvertePacotes(const std::vector<md::CCabecalhoPacote>& pacotes);
std::vector<md::CCabecalhoPacote> DesconvertePacotes(
    const ModuloDadosDisponiveisCarga::DadosDisponiveisCarga::pacotesImportados::value_type& pacotesImportados);

} // namespace comum::asn
