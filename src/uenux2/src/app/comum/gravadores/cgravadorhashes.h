#pragma once

#include <memory>
#include <string>

#include "api/util/cdatetime.h"
#include "app/comum/eurnafase.h"
#include "app/comum/gravadores/igravador.h"

namespace comum {

namespace md {
class CIdentificacaoSecao;
class CIdentificacaoUrnaContingencia;
} // namespace md

// RTTI: an si_class of comum::IGravador. vota::CGravaResultado::StartState (fn 12098) builds it as a
// std::shared_ptr<IGravador>(new CGravadorHashes), whose control block's __on_zero_shared is the shared call through
// the vtable (fn 172), so the class is not final. Recovered: the layout, 96 bytes (12098 allocates it with f137(96)),
// and the virtual members. The constructor, which 12098 holds inlined twice, copies the api::CDateTime 12098 builds to
// +40, stores ConverteFase(fase) at +52, copies a string to +56, leaves one std::shared_ptr of +68 and +76 empty and
// fills the other with a CIdentificacaoSecao or a CIdentificacaoUrnaContingencia (the control blocks @1554668 and
// @1554708 name the two types), and copies a string to +84; the base-object destructor (fn 5853, slot 0) destroys those
// four members in reverse. The destructor is not declared (implicit, a choice: `~CGravadorHashes() override = default;`
// in the class gives the same object): the deleting one (fn 11619, slot 1) calls the base-object one and frees what it
// returns, the shape of a destructor that is not out of line and too costly to inline there. GravaResultado (slot 7, fn
// 11620, record cgravadorhashes.cpp:112) is out of line, so it is the key function, in cgravadorhashes.cpp: it passes
// +40 to the entity's header, +52 as its phase, +56 as its UF (CEntidadeHashes's ValidaCriacao tests that string's
// length against 2, so +56's role is evidence) and +84 as the UENUX version, and tests +68, then +76. The constructor
// is not declared; every member name and +84's role are chosen.
class CGravadorHashes : public IGravador {
public:
    virtual void GravaResultado(api::CFile& arquivo) const override;

private:
    api::CDateTime m_dataHora;
    EUrnaFase m_faseUrna;
    std::string m_siglaUF;
    std::shared_ptr<md::CIdentificacaoSecao> m_identificacaoSecao;
    std::shared_ptr<md::CIdentificacaoUrnaContingencia> m_identificacaoContingencia;
    std::string m_versao;
};

} // namespace comum
