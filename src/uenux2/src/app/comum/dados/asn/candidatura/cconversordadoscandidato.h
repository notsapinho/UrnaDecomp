#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/candidatura/cdadoscandidato.h"
#include "asn1/modules/ModuloCandidatos.h"

namespace comum::asn {

// Reads a candidate's data; the conversion the other way is the base's default DoConverte (the vtable's slot 2 is
// IConversorASN's, target fn 11449). RTTI names the class and its base (vtable @1562224). comum::asn::
// CConversorCandidatura::DoDesconverte (fn 11448) builds one on its stack with the constructor inlined: the vptr and, at
// +4, a byte of its own object; DoDesconverte (fn 11450) passes that byte, inverted, as the candidate's ESituacao. The
// member's name and the constructor's form are chosen.
class CConversorDadosCandidato : public IConversorASN<ModuloCandidatos::DadosCandidato, md::CDadosCandidato> {
public:
    explicit CConversorDadosCandidato(bool sinalizador) : m_sinalizador(sinalizador) {}

protected:
    TDado DoDesconverte(const TEntidade& entidade) const override;

private:
    bool m_sinalizador;
};

} // namespace comum::asn
