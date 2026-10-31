#pragma once

#include "app/comum/gravadores/igravador.h"
#include "ecourna/app/dados/iidentificadoreleitor.hpp"

namespace comum {

namespace md {
class CEleitorIdentidade;
}

// RTTI: an si_class of comum::IGravador. vota::CGravaResultado::StartState (fn 12098) builds it as a
// std::shared_ptr<IGravador>(new CGravadorRCSecao), whose control block's __on_zero_shared is the shared call through the
// vtable (fn 172), so the class is not final. Recovered: the head, which is all that block needs, and
// CriaIdentidadeEleitor (target fn 5845), declared as its record (cgravadorrcsecao.cpp:230) prints it; it reads no
// member, and its one caller is GravaResultado (fn 11616), so that it is private is a choice. The constructor, the data
// members and the slots are not reconstructed (the file is the header of cgravadorrcsecao.cpp, which its records name).
class CGravadorRCSecao : public IGravador {
private:
    ecourna::app::dados::TSharedIdentificadorEleitor CriaIdentidadeEleitor(
        const comum::md::CEleitorIdentidade& identidade) const;
};

} // namespace comum
