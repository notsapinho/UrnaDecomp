#pragma once

// Reconstruction notes: the definition of a singleton's GetInst. The path, the macro's name and its parameters' names
// are chosen; src/units/110-uenux2-singletons.mk has the evidence for a macro and what it does not settle.
#include <mutex>

#include "ecourna/api/pattern/epatternerror.hpp"

#define SINGLETON_IMPL_GET_INST(CLASSE, MUTEX, INSTANCIA)                                                              \
    CLASSE& CLASSE::GetInst()                                                                                          \
    {                                                                                                                  \
        std::lock_guard<std::mutex> trava(MUTEX);                                                                      \
        if (!INSTANCIA) {                                                                                              \
            throw ecourna::api::pattern::CPatternError(ecourna::api::pattern::EPE_SINGLETON_NAO_CRIADO,                \
                                                       #CLASSE " - instancia nao criada");                             \
        }                                                                                                              \
        return *INSTANCIA;                                                                                             \
    }
