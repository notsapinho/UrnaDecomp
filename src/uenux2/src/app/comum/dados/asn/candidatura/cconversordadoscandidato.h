#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/candidatura/cdadoscandidato.h"
#include "asn1/modules/ModuloCandidatos.h"

namespace comum::asn {

// Reads a candidate's data; the conversion the other way is the base's default DoConverte (the vtable's slot 2 is
// IConversorASN's, target fn 11449). RTTI names the class and its base (vtable @1562224). comum::asn::
// CConversorCandidatura::DoDesconverte (fn 11448) builds one on its stack with the constructor inlined: the vptr and,
// at +4, a byte of its own object; DoDesconverte (fn 11450) passes that byte, inverted, as the candidate's ESituacao.
// 11448 holds the object's address in a local and stores the byte before the vptr, an out-of-line constructor's order
// (fn 5712's), so the constructor is out of line in the class's .cpp and binaryen inlined it into its one caller (a
// reading: docs/how-to-decompile.md step 3, "Code binaryen inlined from another function"; fragment 159 has the scores
// of both forms). The member's name is chosen.
class CConversorDadosCandidato : public IConversorASN<ModuloCandidatos::DadosCandidato, md::CDadosCandidato> {
public:
    explicit CConversorDadosCandidato(bool sinalizador);

protected:
    TDado DoDesconverte(const TEntidade& entidade) const override;

private:
    bool m_sinalizador;
};

} // namespace comum::asn
