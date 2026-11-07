#pragma once

#include <optional>

#include "api/util/cdatetime.h"
#include "app/comum/dados/md/estadoaplicacao/cdadocorrespondencia.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "app/comum/gravadores/igravador.h"
#include "app/comum/gravadores/md/ctipoapuracaosa.h"
#include "app/comum/gravadores/md/curna.h"

namespace comum {

class CRdv;

// RTTI: an si_class of comum::IGravador. vota::CGravaResultado::StartState (fn 12098) builds it as a
// std::shared_ptr<IGravador>(new CGravadorRDV), whose control block's __on_zero_shared is the shared call through the
// vtable (fn 172), so the class is not final. Recovered: the layout, 168 bytes (12098 allocates it with f137(168)), and
// the virtual members. The constructor, which 12098 holds inlined with no frame of its own (no target index; written in
// cgravadorrdv.cpp, unrooted), calls IGravador's constructor (fn 1396) with the extension 6 and the SAVD file 37, copies
// the api::CDateTime 12098 builds to +40,
// stores 49 at +52, copies a md::estadoaplicacao::CDadoCorrespondencia to +56 (its copy constructor, fn 1249), leaves a
// std::optional of 8 bytes at +152 empty (engaged at +160) and stores a word at +164. GravaResultado (fn 11587, in
// cgravadorrdv.cpp) calls slot 11 of the object +164 points at (CRdv's Converte, the RDV's bytes), passes +52 to
// md::CUrna's constructors as their ETipoArquivo (49 is TIPO_ARQUIVO_VOTACAO_UE), and +152 to the one that takes a
// md::CTipoApuracaoSA when +160 is set. The base-object destructor
// (fn 11586, slot 0) destroys the correspondencia (fn 857) only; binaryen merged it with IGravadorEnvelope's, which
// holds one at +76 (fn 6043 over both, the offset and the vptr its arguments). The destructor is not declared
// (implicit): the deleting one (fn 11585, slot 1) holds the base-object body and frees `this`. GravaResultado (slot 7,
// fn 11587) is out of line, so it is the key function; no record names this class's file (the path follows
// igravador.h). Chosen: +152 as a std::optional (CUrna holds one), +164 as a pointer to a const CRdv (a reference
// compiles the same), every member name, and the constructor's parameters (their order and form, and the extension, the
// SAVD file and the ETipoArquivo as its own constants rather than 12098's arguments: one call cannot tell them apart).
class CGravadorRDV : public IGravador {
public:
    CGravadorRDV(const api::CDateTime& dataHora, TMunicipioID municipio, TZonaID zona, TLocalID local, TSecaoID secao,
        char fase, const md::estadoaplicacao::CDadoCorrespondencia& correspondencia, const CRdv* rdv);

    virtual void GravaResultado(api::CFile& arquivo) const override;

private:
    api::CDateTime m_dataHora;
    ETipoArquivo m_tipoArquivo;
    md::estadoaplicacao::CDadoCorrespondencia m_correspondencia;
    std::optional<md::CTipoApuracaoSA> m_tipoApuracao;
    const CRdv* m_rdv;
};

} // namespace comum
