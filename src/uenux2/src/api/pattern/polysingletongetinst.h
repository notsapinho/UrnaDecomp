#pragma once

// Reconstruction notes, not TSE's text: the definition of a poly singleton's GetInst that creates its default instance
// on first use. The path, the macro's name and its parameters' names are chosen; src/units/50-uenux2-cinformacaothreadoperador.mk
// has the evidence for a macro and what it does not settle.
#include <memory>
#include <mutex>

#include "api/pattern/cpolysingleton.h"
#include "api/pattern/cpolysingletonlist.h"

#define POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO(INTERFACE, CLASSE)                                            \
    static std::mutex s_mutexGetInst;                                                                                  \
    INTERFACE& INTERFACE::GetInst()                                                                                    \
    {                                                                                                                  \
        std::lock_guard<std::mutex> trava(s_mutexGetInst);                                                             \
        if (!api::CPolySingletonList::has<INTERFACE>()) {                                                              \
            api::CPolySingletonList::push<INTERFACE>(std::make_unique<CLASSE>(), api::g_polySingletonsInfo());         \
        }                                                                                                              \
        return api::CPolySingleton<INTERFACE>::instance();                                                             \
    }
