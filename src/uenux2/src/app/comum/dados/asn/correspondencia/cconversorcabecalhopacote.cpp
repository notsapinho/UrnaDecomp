// Reconstruction: comum::asn::CConversorCabecalhoPacote's DoConverte and DoDesconverte (target fns 11438 and 11437), and
// two free functions over the class that convert the imported packages' list each way. The two members hold the
// Utils conversions (util.cpp's records) and the md members (records of md/cideleitoral.cpp, cidpacote.cpp and
// ccabecalhopacote.cpp) inlined by binaryen; DoConverte comes first, as the use band orders the two (11438 links ahead
// of 11437), and its key-function place makes this object emit the vtable. DoDesconverte reads the entity into named
// locals before the header's constructor, in the target's order of the frame (the identifier at +40, the name at +24,
// the version at +8). Units 96 and 273 have the rest; the names of the locals are chosen.
// The free functions: CConversorDadosDisponiveisCarga's DoConverte (target fn 11424) and DoDesconverte (fn 11423) hold
// one each behind a stack-pointer prologue of its own (64 and 80 bytes), the sign of a function binaryen inlined
// (docs/how-to-decompile.md step 3). Measured: written in DoConverte's TU, ConvertePacotes is inlined there by clang and
// 11424 differs; here, 11424 matches. DesconvertePacotes in either TU leaves 11423 at the same score (145 operand-only
// rows over 2696, its names), so its file is chosen.
// No record names them; names and free functions chosen. The file (the class's own) is a reading for ConvertePacotes
// (Converte<CabecalhoPacote>'s record, 1562828, after this class's vtable) and chosen for DesconvertePacotes.
#include "app/comum/dados/asn/correspondencia/cconversorcabecalhopacote.h"

#include <string>

#include "app/comum/asn/util.h"

namespace comum::asn {

ModuloTiposEleitorais::CabecalhoPacote CConversorCabecalhoPacote::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_tipoPacote(Utils::ConverteTipoPacote(dado.GetTipo()));
    entidade.set_idPacote(Utils::ConverteIdPacote(dado.GetIdPacote()));
    entidade.set_nomepacote(dado.GetNome());
    entidade.set_versao(dado.GetVersao());
    entidade.set_origem(Utils::ConverteIdSistema(dado.GetSistema()));
    return entidade;
}

md::CCabecalhoPacote CConversorCabecalhoPacote::DoDesconverte(const TEntidade& entidade) const
{
    const md::ETipoPacote tipo = Utils::DesconverteTipoPacote(entidade.get_tipoPacote());
    const md::CIDPacote id = Utils::DesconverteIdPacote(entidade.get_idPacote());
    const std::string nome = entidade.get_nomepacote();
    const std::string versao = entidade.get_versao();
    const ESistemaJE sistema = Utils::DesconverteIdSistema(entidade.get_origem());
    return md::CCabecalhoPacote(tipo, id, nome, versao, sistema);
}

ASN1::SEQUENCE_OF<ModuloTiposEleitorais::CabecalhoPacote> ConvertePacotes(const std::vector<md::CCabecalhoPacote>& pacotes)
{
    ASN1::SEQUENCE_OF<ModuloTiposEleitorais::CabecalhoPacote> entidades;
    CConversorCabecalhoPacote conversor;
    for (size_t i = 0; i < pacotes.size(); ++i) {
        entidades.push_back(conversor.Converte(pacotes[i]));
    }
    return entidades;
}

std::vector<md::CCabecalhoPacote> DesconvertePacotes(
    const ModuloDadosDisponiveisCarga::DadosDisponiveisCarga::pacotesImportados::value_type& pacotesImportados)
{
    std::vector<md::CCabecalhoPacote> pacotes;
    CConversorCabecalhoPacote conversor;
    for (size_t i = 0; i < pacotesImportados.size(); ++i) {
        const md::CCabecalhoPacote pacote = conversor.Desconverte(pacotesImportados[i]);
        pacotes.push_back(pacote);
    }
    return pacotes;
}

} // namespace comum::asn
