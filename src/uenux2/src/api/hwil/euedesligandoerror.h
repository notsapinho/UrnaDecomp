#pragma once

// api::EUeDesligandoError and api::CUeDesligandoError. RTTI names the class, an si_class of
// CBaseError<api::EUeDesligandoError, SErrorLimits{4200, 4250}> (typeinfo 1532348), and so the enumeration, its
// namespace and its limits. No record names this file or a member: the header's name is chosen, after the tree's other
// error headers (eueprintererror.h beside it).
//
// The class adds no member: fn 1685, its constructor, builds the 40 bytes of CError at the address the throw allocated
// (40 B, `__cxa_allocate_exception(40)`) and stores the class's vptr (vtable @1599932: the shared CError slots 4636, 454
// and 11562). It builds the message "Urna desligando" itself and passes the code 4201 and the location of
// vota::CSincronizaVota::VerificaUrnaDesligando (csincronizavota.cpp 47:15) to CError's constructor; its wasm type,
// (i32)->(i32), has lost the location: every caller passes the same one, which binaryen's dead-argument elimination
// folds. So the location is a parameter, a default argument the throw takes, and the message and the code are the
// constructor's own; that the code is not a parameter too, folded the same way, is a choice. The constructor is out of
// line, in a TU other than its callers', a reading of the data: the vtable lies in api/'s run of the data (after
// api/hash/cmontadorhash.cpp's records, before api/ipc/cthread.cpp's), where the typeinfo is a copy in
// csincronizavota.cpp's run, so the throwing TU emits the typeinfo and not the vtable. euedesligandoerror.cpp is a chosen
// path for it. The enumerator's name is chosen from the message.

#include <source_location>

#include "ecourna/api/exception/cbaseerror.hpp"

namespace api {

enum EUeDesligandoError {
    EUE_DESLIGANDO_URNA_DESLIGANDO = 4201,
};

class CUeDesligandoError
    : public ecourna::api::exception::CBaseError<EUeDesligandoError, ecourna::api::exception::SErrorLimits{4200, 4250}> {
public:
    explicit CUeDesligandoError(std::source_location local = std::source_location::current());
};

} // namespace api
