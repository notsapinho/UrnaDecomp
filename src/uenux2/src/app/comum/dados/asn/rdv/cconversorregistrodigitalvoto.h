#pragma once

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/asn/util.h"
#include "app/comum/dados/md/processoeleitoral/cpleito.h"
#include "app/comum/dados/md/rdv/cvotoseleicoesvota.h"
#include "app/comum/eurnafase.h"
#include "asn1/modules/ModuloRegistroDigitalVoto.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::asn {

// Converts an RDV's whole entity; CONVERSOR converts its elections. RTTI names the one instance,
// CConversorRegistroDigitalVoto<CConversorEleicoesVota>, and its base (vtable @1560296). Recovered: the layout, 56
// bytes, from the destructors (fns 11485, 11484, and comum::CRdvVota's, fn 5734, which holds one at +44): the vptr,
// CONVERSOR at +4, then the words DoConverte (fn 11483) puts in the entity's pleito, fase and identificacao (+20, +24,
// and the section's municipio +28, zona +32, local +36 and secao +40, 32- and 16-bit), and at +44 a vector of strings it
// puts in historicoCodigosCarga. The D2 begins with the class's vptr store, so the class is not final. No record names
// the file: the directory mirrors md::CVotosEleicoesVota's (docs/how-to-decompile.md step 3, rule 3), the name is the
// class's. The member names and the words' types (by width) are chosen. Both slots are defined below, and unit 13's
// crdvvota.cpp.o emits them with the vtable.
template <typename CONVERSOR>
class CConversorRegistroDigitalVoto
    : public IConversorASN<ModuloRegistroDigitalVoto::EntidadeRegistroDigitalVoto, md::CVotosEleicoesVota> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;

private:
    CONVERSOR m_conversor;
    md::TPleitoID m_pleito;
    EUrnaFase m_fase;
    uedword m_municipio;
    ueword m_zona;
    uedword m_local;
    ueword m_secao;
    std::vector<std::string> m_historicoCodigosCarga;
};

// Target fn 11482: the elections' field (the entity's fifth, +16 in its field table) through the member converter's
// Desconverte, which binaryen inlines (its frame opens in a frameless caller), then its slot 3 through the vtable.
template <typename CONVERSOR>
typename CConversorRegistroDigitalVoto<CONVERSOR>::TDado
CConversorRegistroDigitalVoto<CONVERSOR>::DoDesconverte(const TEntidade& entidade) const
{
    return m_conversor.Desconverte(entidade.get_eleicoes());
}

// Target fn 11483: the section's identification built first (MunicipioZona, then IdentificacaoSecaoEleitoral, the
// frame's two highest locals), the elections through the member converter's Converte (iconversorasn.h:56, which
// binaryen inlines: its 640-byte frame opens inside this one), then the entity, constructed after them, and its five
// fields in order. pleito goes through a Constrained_INTEGER temporary (the module's setter takes const_reference).
// The code history is std::ranges::transform into a back_inserter with a lambda that returns each string by value:
// the target keeps that loop in a function of its own that binaryen inlined (a 48-byte frame around the loop, and the
// algorithm's {last, out} result stored back into this frame), copies each string, builds the GeneralString from the
// copy, calls AbstractString::do_clone directly and destroys the GeneralString before the copy. What the other forms
// gave is in unit 140's fragment.
template <typename CONVERSOR>
typename CConversorRegistroDigitalVoto<CONVERSOR>::TEntidade
CConversorRegistroDigitalVoto<CONVERSOR>::DoConverte(const TDado& dado) const
{
    ModuloTiposEleitorais::MunicipioZona municipioZona;
    municipioZona.set_municipio(m_municipio);
    municipioZona.set_zona(m_zona);
    ModuloTiposEleitorais::IdentificacaoSecaoEleitoral identificacao;
    identificacao.set_municipioZona() = municipioZona;
    identificacao.set_local(m_local);
    identificacao.set_secao(m_secao);
    const ModuloRegistroDigitalVoto::Eleicoes eleicoes = m_conversor.Converte(dado);
    TEntidade entidade;
    entidade.set_pleito(m_pleito);
    entidade.set_fase() = Utils::ConverteFase(m_fase);
    entidade.set_identificacao() = identificacao;
    ModuloRegistroDigitalVoto::HistoricoCodigosCarga historico;
    std::ranges::transform(m_historicoCodigosCarga, std::back_inserter(historico),
        [](const std::string& codigo) { return codigo; });
    entidade.set_historicoCodigosCarga() = historico;
    entidade.set_eleicoes() = eleicoes;
    return entidade;
}

// An RDV's votes to and from its BER bytes, through the RDV's converter (comum::CRdvVota's m_conversor). Codifica
// converts the votes (IConversorASN::Converte) and codes the entity with api::CFileASN::CodeObject into the bytes it
// returns. Decodifica (target fn 5680, called by CRdvVota's Desconverte and Confere, fns 11487 and 11486) copies the
// bytes into a std::vector<char>, decodes them with api::CFileASN::DecodeObject (fn 5825) and converts the entity back
// (IConversorASN::Desconverte, whose code sits behind a 640-byte frame of its own in 5680). Codifica has no target
// index: binaryen inlines it into its one caller, CRdvVota::Converte (fn 11488), whose code is one outer block holding
// a 64-byte frame (Codifica's: the entity at +12, the coded vector at +0) and inside it the frames of Converte (640
// bytes), CodeObject (32) and CodeObjectFunction (656).
// Where they are defined, evidence then reading. The records those frames hold lie after the run of
// asn/rdv/cconversoreleicoesvota.cpp's (@1571240 to @1571484) and before md/cdataje.cpp's (@1571564):
// iconversorasn.h:56 (@1571500), cfileasn.h:161 and :171 (@1571516, @1571532), then 5680's iconversorasn.h:71
// (@1571548); crdvvota.cpp's, the object of CRdvVota's slots (use band 1: 11490, 11488, 11487, 11486, 11485), run from
// @1560132 to @1560616. In use band 2 the target runs 5682, 5681, 5680, 5679 in link order (ledger/ordinals.tsv), and
// 5681 matches from cconversoreleicoesvota.cpp.o's copy, which that object emits after every function it defines
// (names.tsv's ld_index). Read together: CRdvVota's slots call functions an object after that one defines out of line,
// each holding these instances, which a template or inline function crdvvota.cpp.o emitted would have kept in its own
// run; that they are two external functions of an object of their own, cconversorregistrodigitalvoto.cpp, is chosen.
// Chosen too: their names, their being free functions of comum::asn (they use the converter's public interface only),
// the converter's type (the base the calls go through; the derived class gives the same object) and their order,
// Codifica first (its records come first).
std::vector<uebyte> Codifica(
    const IConversorASN<ModuloRegistroDigitalVoto::EntidadeRegistroDigitalVoto, md::CVotosEleicoesVota>& conversor,
    const md::CVotosEleicoesVota& votos);
md::CVotosEleicoesVota Decodifica(
    const IConversorASN<ModuloRegistroDigitalVoto::EntidadeRegistroDigitalVoto, md::CVotosEleicoesVota>& conversor,
    const std::vector<uebyte>& dados);

} // namespace comum::asn
