#pragma once

// The reconstruction's notes, not TSE's text: an ASN.1 file read and converted with CONVERSOR (api::CFileASN::
// ReadFromFile, then IConversorASN::Desconverte), out of line in carregaarquivo.cpp, which instantiates it for each
// converter its callers use. The target holds the package header's instance as a function of its own, fn 5706
// (callers 5778 and 7787), and the others inside fns 3771 and 5778, each behind a 64-byte stack frame of its own that
// holds the converter (binaryen's inlining of a function with one caller; clang would inline them into callers in their
// own TU, a reading). The name, this path, the template's form and its file are chosen: no record names them.
#include <string>

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

} // namespace comum
