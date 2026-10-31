#pragma once

#include <optional>

#include "api/util/cdatetime.h"
#include "app/comum/dados/md/estadoaplicacao/cdadocorrespondencia.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "app/comum/eurnafase.h"
#include "app/comum/gravadores/igravador.h"
#include "app/comum/gravadores/md/cenvelopegenerico.h"
#include "app/comum/gravadores/md/ctipoapuracaosa.h"

namespace comum {

// RTTI: an si_class of comum::IGravador, vtable @1554448 [11625, 325, ...], an abstract class with one pure slot more
// (slot 8). Recovered: the layout, 172 bytes, and the virtual members. CGravadorEnvelopeArquivo's constructor (fn
// 5856) holds this one inlined: after IGravador's it stores this vptr, copies the api::CDateTime it is given to +40,
// stores ConverteFase(fase) at +52 and 49 at +56, leaves a std::optional of 8 bytes at +60 empty (engaged at +68),
// stores its ninth argument at +72 (2 and 4 in fn 12098's two calls) and copies a
// md::estadoaplicacao::CDadoCorrespondencia to +76 (fn 1249). The base-object destructor (fn 11625, slot 0) destroys
// the correspondencia (fn 857) only: binaryen merged it with CGravadorRDV's (fn 6043). The destructor is not declared
// (implicit); slot 1 holds the abstract class's trap (fn 325). GravaResultado (slot 7, fn 11626) is out of line, so it
// is the key function; it is not reconstructed. Slot 8 is pure; no evidence names it, so it is named after its slot.
// The path is chosen, beside igravador.h: no record names it. Chosen: +56 as comum::EUrnaTipo (49 is eUrnaVota), +60
// as a std::optional<md::CTipoApuracaoSA>, +72 as md::CEnvelopeGenerico::Tipo (2 and 4 are its BU impresso and
// zeresima impressa), and every member name; the constructor is not declared.
class IGravadorEnvelope : public IGravador {
public:
    virtual void GravaResultado(api::CFile& arquivo) const override;
    virtual void Slot8() = 0;

protected:
    api::CDateTime m_dataHora;
    EUrnaFase m_faseUrna;
    EUrnaTipo m_tipoUrna;
    std::optional<md::CTipoApuracaoSA> m_tipoApuracao;
    md::CEnvelopeGenerico::Tipo m_tipoEnvelope;
    md::estadoaplicacao::CDadoCorrespondencia m_correspondencia;
};

} // namespace comum
