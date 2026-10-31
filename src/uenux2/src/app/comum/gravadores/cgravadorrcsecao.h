#pragma once

#include "api/util/cdatetime.h"
#include "app/comum/eurnafase.h"
#include "app/comum/gravadores/igravador.h"
#include "ecourna/app/dados/iidentificadoreleitor.hpp"

namespace comum {

namespace md {
class CEleitorIdentidade;
}

// RTTI: an si_class of comum::IGravador. vota::CGravaResultado::StartState (fn 12098) builds it as a
// std::shared_ptr<IGravador>(new CGravadorRCSecao), whose control block's __on_zero_shared is the shared call through the
// vtable (fn 172), so the class is not final. Recovered: the layout, 60 bytes (12098 allocates it with f137(60)), the
// virtual members, and CriaIdentidadeEleitor (target fn 5845), declared as its record (cgravadorrcsecao.cpp:230) prints
// it; it reads no member, and its one caller is GravaResultado (fn 11616), so that it is private is a choice. The
// constructor, which 12098 holds inlined, copies the api::CDateTime 12098 builds to +40, stores ConverteFase(fase) at
// +52 and 0 at +56. No member's destruction emits code: slot 0 holds IResultado's base-object destructor (fn 12090),
// and the deleting one (fn 11615, slot 1) holds that body and frees `this`, so the destructor is not declared
// (implicit). GravaResultado (slot 7, fn 11616, record cgravadorrcsecao.cpp:110) is out of line, so it is the key
// function; it is not reconstructed. The constructor is not declared; +56 as an int and every member name are chosen.
class CGravadorRCSecao : public IGravador {
public:
    virtual void GravaResultado(api::CFile& arquivo) const override;

private:
    ecourna::app::dados::TSharedIdentificadorEleitor CriaIdentidadeEleitor(
        const comum::md::CEleitorIdentidade& identidade) const;

    api::CDateTime m_dataHora;
    EUrnaFase m_faseUrna;
    int m_quantidade;
};

} // namespace comum
