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

// A singleton's CreateInst, the member GetInst's instance comes from: target fn 7787 holds vota::CTelasVota's inlined
// (record ctelasvota.cpp:3435, column 45, the `)` of an invocation on the line after GetInst's), the lock of MUTEX,
// the throw of code 1304 when INSTANCIA is set, and INSTANCIA.reset(new CLASSE()). The macro's name is chosen and
// fitted to the record with the parameters GetInst's macro takes: the record fixes the invocation's length only.
// CCargos's CreateInst record (ccargos.cpp:25:42, its members s_mutex and s_instancia) fits the same invocation;
// CInfoMTLCD's (cinfomtlcd.cpp:33:45) is five columns past one over its members (s_mutex, s_inst): its form is not
// known. Neither is written.
#define CREATE_INST(CLASSE, MUTEX, INSTANCIA)                                                                          \
    void CLASSE::CreateInst()                                                                                          \
    {                                                                                                                  \
        std::lock_guard<std::mutex> trava(MUTEX);                                                                      \
        if (INSTANCIA) {                                                                                               \
            throw ecourna::api::pattern::CPatternError(ecourna::api::pattern::EPE_SINGLETON_JA_CRIADO,                 \
                                                       #CLASSE " - instancia ja criada");                              \
        }                                                                                                              \
        INSTANCIA.reset(new CLASSE());                                                                                 \
    }
