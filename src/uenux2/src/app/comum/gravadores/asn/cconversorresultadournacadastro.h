#pragma once

#include <vector>

#include "api/io/cfile.h"
#include "ecourna/api/uetypes.hpp"
#include "ecourna/app/dados/resultadournacadastro/cdadoscomparecimento.hpp"
#include "ecourna/app/dados/resultadournacadastro/cresultadournacadastro.hpp"

namespace comum::asn {

// Writes the voter-register result into an open file (target fn 5366): an
// ecourna::app::dados::asn::CConversorResultadoUrnaCadastro on the stack (5366 stores its vptr), IConversorASN::Converte
// (record iconversorasn.hpp:49 under the conan package's path, uenux2's copy of ecourna's header) and
// api::CFileASN::WriteToFile with its CodeObjectFunction (records cfileasn.h:161 and :171), which clang inlines. Its one
// caller, comum::CGravadorRCSecao::GravaResultado (fn 11616), calls it twice, with the result that holds the ciphered
// attendance and with the one that holds it plain. That this file is the function's is a reading of the data: its
// records (@1599476 to @1599508) follow those of unit 145's GravaArquivo, which fn 11582 holds inlined (@1599428 to
// @1599460, cconversorversoesarquivos.cpp), and come before the attendance's (below), as 5367's follow its converter's
// vtable (cconversorentidadehashes.h). Its name, its being a free function of comum::asn, the file and its path, and
// the `const api::CFile&` are chosen.
void GravaArquivo(const api::CFile& arquivo, const ecourna::app::dados::CResultadoUrnaCadastro& resultado);

// The attendance data coded as BER: an ecourna::app::dados::asn::CConversorDadosComparecimento on the stack, its
// Converte (fn 5365, out of line) and api::CFileASN::CodeObject over the entity, whose vector<char> is copied into the
// bytes the result returns. No target function of its own: 11616 holds it behind an 80-byte stack frame, followed by
// a 32-byte one and a 656-byte one, which hold the records cfileasn.h:161 and :171 for
// ModuloResultadoUrnaCadastro::DadosComparecimento (@1599540 and @1599556): the shape of three functions binaryen
// inlined, each into its one caller, read as this function, CodeObject and CodeObjectFunction. The record of a Converte over the attendance under the conan path (@1599524), which no
// target function loads, lies between 5366's records and those, a reading that this object instantiated that Converte
// too. Its name, its signature and its being a free function of comum::asn are chosen.
std::vector<uebyte> CodificaDadosComparecimento(const ecourna::app::dados::CDadosComparecimento& dados);

} // namespace comum::asn
