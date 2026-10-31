#pragma once

#include <string>

#include "app/comum/eurnafase.h"
#include "ecourna/api/uetypes.hpp"

namespace comum {

// Recovered: two of the file's name builders, target fns 1705 and 3772. Each calls the anonymous-namespace helpers of
// cnomearquivo.cpp (records :38, :48 and :73) in its own stack frame, so its code is that file's
// (docs/reference/facts/reading.md R8); the file's records name only its anonymous-namespace functions. No record, slot
// or RTTI names a class or these members: the class name is chosen from the file's name, and that the builders are its
// static members, their names and their parameter types are chosen. The bodies give the parts in order and each
// number's width: the phase's letter, a 5-digit number and the UF, for NomeArquivoSecao a 5-digit and two 4-digit
// numbers more, then "-" and the type, "." and the extension. Fns 3744, 3771 and 5740 call those helpers inside a second
// stack frame, which reads as three more builders of this file that binaryen inlined into their only caller
// (reading.md R10); they are not reconstructed, so not declared. That the class has no other member is not known.
class CNomeArquivo {
public:
    static std::string NomeArquivoUF(EUrnaFase fase, uedword pleito, const std::string& uf, const std::string& tipo,
        const std::string& extensao);
    static std::string NomeArquivoSecao(EUrnaFase fase, uedword pleito, const std::string& uf, uedword municipio,
        uedword zona, uedword secao, const std::string& tipo, const std::string& extensao);
};

} // namespace comum
