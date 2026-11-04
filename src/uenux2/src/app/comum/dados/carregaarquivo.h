#pragma once

// The reconstruction's notes, not TSE's text: an ASN.1 file read and converted with CONVERSOR (api::CFileASN::
// ReadFromFile, then IConversorASN::Desconverte), out of line in carregaarquivo.cpp, which instantiates it for each
// converter its callers use. The target holds the package header's instance as a function of its own, fn 5706
// (callers 5778 and 7787), and the others inside fns 3771 and 5778, each behind a 64-byte stack frame of its own that
// holds the converter (binaryen's inlining of a function with one caller; clang would inline them into callers in their
// own TU, a reading). The name, this path, the template's form and its file are chosen: no record names them.
#include <string>
#include <vector>

#include "api/io/cfile.h"

namespace comum::md {
class CEleitor;
} // namespace comum::md

namespace comum {

template <typename CONVERSOR>
typename CONVERSOR::TDado CarregaArquivo(const std::string& arquivo);

// The reconstruction's note, not TSE's text: the same read for an ecourna converter
// (ecourna::api::asn::IConversorASN, whose member is Deconverte), out of line in carregaarquivo.cpp. The target holds
// its one instance, for ecourna::app::dados::asn::CConversorInformacaoMidia, as fn 3735 (callers 11587, 11626 and
// 11629, the recorders, in other objects): its records are cfileasn.h's readers' for
// ModuloInformacaoMidia::InformacaoMidia and iconversorasn.hpp:66 (Deconverte), and it stores the converter's vptr
// in a 64-byte frame of its own before the read. The name, its being a second template beside CarregaArquivo and its
// file are chosen: no record names them.
template <typename CONVERSOR>
typename CONVERSOR::TDado CarregaArquivoEcourna(const std::string& arquivo);

// The reconstruction's note, not TSE's text: the voters read from a file already open, with the partial reader
// (comum::asn::CConversorEntidadeEleitores over a new comum::asn::CVisitanteEleitor, IConversorParcialASN::Desconverte),
// out of line in carregaarquivo.cpp. Target fn 11523, the call operator of CEleitores::GetEleitoresEstaticos's lambda
// (celeitores.cpp), holds it behind an 80-byte frame of its own (the entity at +8, the visitor's shared_ptr at +68, the
// converter at +76) after its own frame's open of the file: binaryen's inlining of a function with one caller. The
// visitor's control block's vtable and the records of the partial reader's instances lie in the entity readers' run of
// the target's data, between the Candidatos reader's records and LeBiometriaEleitor's, so this file's object (unit 280's
// evidence) makes that code. It returns a copy of the entity's voters (fn 946 per voter, inside that frame) and releases
// the visitor before the copy: the read itself is carregaarquivo.cpp's CarregaArquivoParcial pair, which clang inlines
// (src/units/310-uenux2-cconversorentidadeeleitores.mk measures the forms). The names, the parameter and their being
// free functions of comum are chosen: no record names them.
std::vector<md::CEleitor> LeEleitores(const api::CFile& arquivo);

} // namespace comum
