#pragma once

#include "app/comum/asn/iconversorbiometriaasn.h"
#include "app/comum/dados/md/eleitor/cbiometriaeleitor.h"
#include "asn1/modules/ModuloEleitores.h"

namespace comum::asn {

// Reads a voter's ciphered biometry under a parameter; the conversion the other way is the base's default DoConverte
// (the vtable's slot 2 is IConversorBiometriaASN's, target fn 11418). RTTI names the class and its base (vtable
// @1566292); records put DoDesconverte's inlined LeChave (fn 11419) in cconversorbiometriaeleitorcifrada.cpp, and this
// header beside it is a chosen path.
class CConversorBiometriaEleitorCifrada
    : public IConversorBiometriaASN<ModuloEleitores::BiometriaEleitorCifrada, md::CBiometriaEleitor> {
protected:
    TDado DoDesconverte(const TEntidade& entidade, const md::CParametro& parametro) const override;

private:
    // LeChave's records name it, its const and its result (cconversorbiometriaeleitorcifrada.cpp:91, :101, :109); Decifra
    // has none: its name, its parameters and its being a member (it calls LeChave) are chosen, and so is private.
    std::vector<uebyte> Decifra(const TEntidade& entidade, const md::CParametro& parametro,
                                const std::vector<uebyte>& chaveSessao) const;
    std::vector<uebyte> LeChave() const;
};

} // namespace comum::asn
