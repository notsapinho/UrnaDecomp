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

// The election's part of a section's file name: the phase, the pleito and the state, at +0, +4 and +8, which fns 3745
// and 5727 pass on to NomeArquivoSecao. Both callers of each (comum::CEleitorDetalhe::GetBiometria, fn 1937, and fn
// 7787) pass comum::CConfiguracaoEleicao's +620 as the address, the municipality at +644 and the zone at +648 beside
// it. The struct, its name, its members' names and its place here are chosen. app/comum/dados/cconfiguracaoeleicao.h
// reads the same bytes as the end of m_naoRecuperado3 (+616) and m_descricao (+628): both are readings, and whoever
// writes 1937 or 7787 reconciles them, CConfiguracaoEleicao then holding one.
struct SIdentificacaoArquivo {
    EUrnaFase fase;
    uedword pleito;
    std::string uf;
};

// The names of the files of a section's voters, "el", and of the voters temporarily transferred to it, "tte", both
// ".dat" (target fns 3745 and 5727): each builds its two strings and calls NomeArquivoSecao. No record names them: their
// names, their being free functions of comum declared here and defined in cnomearquivoeleitores.cpp, and the
// parameters' names and types (the bodies pass the three numbers on as words; the callers load the zone and the section
// as 16 bits) are chosen.
std::string NomeArquivoEleitores(const SIdentificacaoArquivo& identificacao, uedword municipio, ueword zona,
    ueword secao);
std::string NomeArquivoEleitoresTTE(const SIdentificacaoArquivo& identificacao, uedword municipio, ueword zona,
    ueword secao);

} // namespace comum
