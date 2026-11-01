#pragma once

#include <string>
#include <vector>

#include "app/comum/asn/iconversorasn.h"
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
// class's. The member names and the words' types (by width) are chosen. DoDesconverte (fn 11482) is defined below;
// DoConverte (fn 11483) is not written: 140-uenux2-app-comum-converters-pending.cpp traps it for the instance.
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

} // namespace comum::asn
