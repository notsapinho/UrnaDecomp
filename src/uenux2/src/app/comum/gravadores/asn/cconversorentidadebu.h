#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/processoeleitoral/ccargo.h"
#include "app/comum/dados/md/rdv/cvoto.h"
#include "app/comum/gravadores/md/centidadebu.h"
#include "asn1/modules/ModuloBoletimUrna.h"

namespace comum::asn {

// Writes the BU's entity; the conversion the other way is the base's default DoDesconverte (the vtable's slot 3 is
// IConversorASN's, target fn 10272). RTTI names the class and its base (vtable @1597528); fn 11629 stores its vptr.
// DoConverte (slot 2, fn 10273, record cconversorentidadebu.cpp:232) is the class's only override and so its key
// function. ConverteTipoVoto and ConverteTipoCargo are static members, as their records print them
// (cconversorentidadebu.cpp:284 and :299), and public, since the file's anonymous helpers call them; binaryen inlines
// both into fn 10273, each with a frame of its own. ConverteDadosVota and ConverteDadosSA have no record: they build
// ModuloBoletimUrna's DadosSecao and DadosSA, the first out of line (its frame opens inside fn 10273's) and the second
// in DoConverte's frame. That clang kept the first out of line says it is no internal function, which with its one
// call in the TU clang would inline (docs/how-to-decompile.md step 3, linkage): a reading. Their names, their being
// static members and their access are chosen. The header's path, beside the .cpp its records name, is chosen.
class CConversorEntidadeBU : public IConversorASN<ModuloBoletimUrna::EntidadeBoletimUrna, md::CEntidadeBU> {
public:
    static ModuloBoletimUrna::TipoVoto::NamedNumber ConverteTipoVoto(md::CVoto::ETipo tipo);
    static ModuloTiposEleitorais::TipoCargoConsulta::NamedNumber ConverteTipoCargo(md::CCargo::ETipo tipo);
    static ModuloBoletimUrna::DadosSecao ConverteDadosVota(const md::CDadosBUVota& dados);
    static ModuloBoletimUrna::DadosSA ConverteDadosSA(const md::CDadosBUSA& dados);

protected:
    TEntidade DoConverte(const TDado& dado) const override;
};

} // namespace comum::asn
