#pragma once

#include <optional>

#include "api/util/cdatetime.h"
#include "app/comum/dados/md/estadoaplicacao/cdadocorrespondencia.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "app/comum/gravadores/igravador.h"
#include "app/comum/gravadores/md/ctipoapuracaosa.h"

namespace comum {

// RTTI: an si_class of comum::IGravador. vota::CGravaResultado::StartState (fn 12098) builds it as a
// std::shared_ptr<IGravador>(new CGravadorRDV), whose control block's __on_zero_shared is the shared call through the
// vtable (fn 172), so the class is not final. Recovered: the layout, 168 bytes (12098 allocates it with f137(168)), and
// the virtual members. The constructor, which 12098 holds inlined, copies the api::CDateTime 12098 builds to +40,
// stores 49 at +52, copies a md::estadoaplicacao::CDadoCorrespondencia to +56 (its copy constructor, fn 1249), leaves a
// std::optional of 8 bytes at +152 empty (engaged at +160) and stores a word at +164. The base-object destructor
// (fn 11586, slot 0) destroys the correspondencia (fn 857) only; binaryen merged it with IGravadorEnvelope's, which
// holds one at +76 (fn 6043 over both, the offset and the vptr its arguments). The destructor is not declared
// (implicit): the deleting one (fn 11585, slot 1) holds the base-object body and frees `this`. GravaResultado (slot 7,
// fn 11587) is out of line, so it is the key function; it is not reconstructed, and no record names this class's file
// (the path follows igravador.h). The constructor is not declared. Chosen: +52 as comum::EUrnaTipo (49 is eUrnaVota),
// +152 as a std::optional<md::CTipoApuracaoSA> (CUrna holds one), +164 as an int, and every member name.
class CGravadorRDV : public IGravador {
public:
    virtual void GravaResultado(api::CFile& arquivo) const override;

private:
    api::CDateTime m_dataHora;
    EUrnaTipo m_tipoUrna;
    md::estadoaplicacao::CDadoCorrespondencia m_correspondencia;
    std::optional<md::CTipoApuracaoSA> m_tipoApuracao;
    int m_quantidade;
};

} // namespace comum
