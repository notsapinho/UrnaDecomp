#pragma once

#include <string>

#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// A voter's temporary transfer. The records name the class, its nested enum, its constructor from the enum
// (ctransferenciatemporaria.cpp:25) and ValidaConstrucao (:35). Recovered: the layout, 20 bytes, as CEleitor's
// constructors copy it (target fns 5666 and 5668, to +48 of CEleitor): the kind at +0, a string at +4 and a word at
// +16; and the two constructors, which comum::asn::CConversorEntidadeEleitores's slot 2 (fn 11411) holds inlined, each
// behind a 16-byte frame of its own. The one from the kind clears the three members; the test of its argument whose
// throw the record :25 places is gone from the target (no function loads that record, nor the message the .cpp gives
// it, the string at 374643, which no target piece's constant addresses), a reading: its one call passes the kind 0,
// which binaryen folds into the body. The other stores the kind, copies the domicile's state, stores its municipality
// and then throws 8070 for the kind 0 (ValidaConstrucao's record; one frame holds both, so clang inlines
// ValidaConstrucao there, a reading). The string and the word are the destination's state and municipality: the
// converter passes the voter's DomicilioEleitoral uf and codigoMunicipio, and md::CEleitorDecorator::GetAbrangencia (fn
// 3721) compares them with the urn's. The enumerators' values are the converter's (0 for no transfer, which both
// constructors' messages name, 1 to 6 for the ASN.1 kinds it maps: cconversorentidadeeleitores.cpp lists them); their
// names are chosen. The enum's `int`, the type of the word at +16, every member and parameter name, ValidaConstrucao's
// being private, and the three accessors, which the decorator reads, are chosen too.
class CTransferenciaTemporaria {
public:
    enum ETransferenciaTemporaria : int {
        SEM_TRANSFERENCIA,
        TRANSFERENCIA_VOTO_EM_TRANSITO,
        TRANSFERENCIA_PRESO_PROVISORIO,
        TRANSFERENCIA_ACESSIBILIDADE,
        TRANSFERENCIA_OFICIO,
        TRANSFERENCIA_INDIGENA_QUILOMBOLA,
        TRANSFERENCIA_SITUACAO_RUA,
    };

    explicit CTransferenciaTemporaria(ETransferenciaTemporaria tipo);
    CTransferenciaTemporaria(ETransferenciaTemporaria tipo, const std::string& uf, uedword municipio);

    ETransferenciaTemporaria GetTipo() const { return m_tipo; }
    const std::string& GetUF() const { return m_uf; }
    uedword GetMunicipio() const { return m_municipio; }

private:
    void ValidaConstrucao(ETransferenciaTemporaria tipo);

    ETransferenciaTemporaria m_tipo;
    std::string m_uf;
    uedword m_municipio;
};

} // namespace comum::md
