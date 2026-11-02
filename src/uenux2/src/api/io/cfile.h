#pragma once

#include "ecourna/api/io/cfile.hpp"

namespace api {

// The type the records spell api::CFile: comum::CGravadorBU::GravaResultado(api::CFile &) and its overriders
// (cgravadorbu.cpp 484 and 485, cgravadorhashes.cpp 112, cgravadorrcsecao.cpp 110) and
// comum::asn::IConversorParcialASN::Desconverte(const api::CFile &, ...) (iconversorparcialasn.h 52); inside namespace
// api, api::CFileASN::ReadFromFile (cfileasn.h 48 and 60) and api::CPartialFileASN::ReadFromFile (cpartialfileasn.h
// 182) spell it CFile. Evidence: the object comum::IGravador's slots 4 and 5 (target fns 11634, 11633) pass to slot 7
// as one is ecourna's CFile, built by ecourna::api::io::CFile::CFile (fn 517), closed by fn 336 and destroyed by that
// class's inline destructor. Chosen: that api::CFile is an alias of that class, where the bodies read so far do not
// tell it from a class of uenux2's own derived from it with no member of its own, and this header's path, which no
// record names. No TU includes it yet: app/comum/gravadores/igravador.h and app/comum/asn/iconversorparcialasn.h
// forward-declare a class api::CFile, which an alias cannot meet in one TU, so each includes this header in place of
// its forward declaration once a TU of its needs the type.
using CFile = ecourna::api::io::CFile;

} // namespace api
