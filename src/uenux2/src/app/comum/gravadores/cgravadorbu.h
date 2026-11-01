#pragma once

#include <map>
#include <string>
#include <vector>

#include "api/util/cdatetime.h"
#include "app/comum/asn/util.h"
#include "app/comum/dados/md/estadoaplicacao/cdadocorrespondencia.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "app/comum/eurnafase.h"
#include "app/comum/gravadores/igravador.h"
#include "app/comum/relatorios/cgeradorbuqrcode.h"
#include "ecourna/api/uetypes.hpp"

namespace comum {

// RTTI: an si_class of comum::IGravador. vota::CGravaResultado::StartState (fn 12098) builds it as a
// std::shared_ptr<IGravador>(new CGravadorBU), whose control block's __on_zero_shared is the shared call through the
// vtable (fn 172), so the class is not final. Recovered: the layout, 304 bytes (12098 allocates it with f137(304)), and
// the virtual members. The constructor is not written: 12098 holds it inlined, after IGravador's constructor (fn 1396,
// with the extension 4 and the SAVD file 35): it stores this vptr (@1554132 + 8), copies the api::CDateTime it also
// passes CGravadorEnvelopeArquivo's constructor to +40 and 12 more bytes to +52, stores ConverteFase(fase) at +64 and
// 49 at +68, copies a md::estadoaplicacao::CDadoCorrespondencia to +72 (fn 1249), moves a vector to +168 and a map to
// +180, stores a byte at +192, a 16-bit word at +194 and a word at +196, builds the string "bu.pk1" at +200, stores 1
// at +212, copies 68 bytes to +216, fills the map at +284 in a loop over comum::CCargos (a node of 16 bytes: the post's
// byte at +13 and a counter's byte at +14; that the counter is the post's order is a reading) and copies 8 bytes to
// +296. The destructor is not declared (implicit; one defined in the class was not measured): the base-object one (fn
// 5857, slot 0) stores this vptr, then destroys the map at +284 (fn 3814), the string at +200, the map at +180 (fn
// 1405, the destroy of std::map<md::ETipoAbrangencia, SQtdeAptos>'s tree, the one cgeradorbuqrcode.h's map has), the
// strings of the vector at +168 and the vector, the correspondencia (fn 857), and holds IResultado's (its vptr, the
// string at +20); the deleting one (fn 11628, slot 1) frees what that one returns, the shape of a destructor whose
// base-object body is too large to inline (docs/how-to-decompile.md step 5). GravaResultado (slot 7, fn 11629, records
// cgravadorbu.cpp:484 and :485) is out of line, so it is the key function; it is not reconstructed, and neither is
// AcrescentaVotoVotavel (fn 3820, record cgravadorbu.cpp:221), which waits for a lookup of comum::CPartidos as an
// api::CDataMap (src/units/200-uenux2-cgravadorbu.mk has the measurement). Evidence for the types: +72's copy
// constructor call, +180's tree destroy, +168's 12-byte elements whose destruction frees a std::string, +284's node and
// its unsigned compare of the post (md::TCargoID is a byte); +40 is the same object fn 12098 passes
// CGravadorEnvelopeArquivo's constructor as its api::CDateTime. Chosen: +68 as comum::EUrnaTipo (49 is eUrnaVota), as
// igravadorenvelope.h does, +192, +194, +196 and +212 as the plainest types of their widths, the byte value of +284's
// map, and every member name; the bytes at +52, +216 and +296 have no reader here and are not recovered.
class CGravadorBU : public IGravador {
public:
    virtual void GravaResultado(api::CFile& arquivo) const override;

private:
    api::CDateTime m_dataHora;
    uedword m_naoRecuperado1[3];
    EUrnaFase m_faseUrna;
    EUrnaTipo m_tipoUrna;
    md::estadoaplicacao::CDadoCorrespondencia m_correspondencia;
    std::vector<std::string> m_lista;
    std::map<md::ETipoAbrangencia, SQtdeAptos> m_qtdAptos;
    uebyte m_byte;
    ueword m_word;
    uedword m_dword;
    std::string m_arquivoChave;
    uebyte m_marca;
    uedword m_naoRecuperado2[17];
    std::map<md::TCargoID, uebyte> m_ordemCargos;
    uebyte m_naoRecuperado3[8];
};

} // namespace comum
