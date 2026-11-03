#pragma once

#include <string>

#include "app/comum/eurnafase.h"
#include "ecourna/api/uetypes.hpp"

namespace comum {

namespace md {
class CPleito;
} // namespace md

// The phase's letter, a 5-digit number, "-" and the type, "." and the extension, with no UF: fn 3771 (comum's
// processo eleitoral load) holds it behind a stack frame of its own, calling FormataFase (fn 2828) and FormataNumero
// (fn 1161) directly, so it is this file's code, which binaryen inlined into its one caller (reading.md R8, R10). It
// has no target index. Its name and its being a free function of comum are chosen: no record, slot or RTTI names it.
std::string NomeArquivoPE(EUrnaFase fase, uedword idPE, const std::string& tipo, const std::string& extensao);

// Recovered: two of the file's name builders, target fns 1705 and 3772. Each calls the anonymous-namespace helpers of
// cnomearquivo.cpp (records :38, :48 and :73) in its own stack frame, so its code is that file's
// (docs/reference/facts/reading.md R8); the file's records name only its anonymous-namespace functions. No record, slot
// or RTTI names a class or these members: the class name is chosen from the file's name, and that the builders are its
// static members, their names and their parameter types are chosen. The bodies give the parts in order and each
// number's width: the phase's letter, a 5-digit number and the UF, for NomeArquivoSecao a 5-digit and two 4-digit
// numbers more, then "-" and the type, "." and the extension. Fns 3744, 3771 and 5740 call those helpers inside a second
// stack frame, which reads as three more builders of this file that binaryen inlined into their only caller
// (reading.md R10); 3771's is NomeArquivoPE above, and 3744's and 5740's are not reconstructed, so not declared. That the class has no other member is not known.
class CNomeArquivo {
public:
    static std::string NomeArquivoUF(EUrnaFase fase, uedword pleito, const std::string& uf, const std::string& tipo,
        const std::string& extensao);
    static std::string NomeArquivoSecao(EUrnaFase fase, uedword pleito, const std::string& uf, uedword municipio,
        uedword zona, uedword secao, const std::string& tipo, const std::string& extensao);
};

// The election's part of a section's file name: the phase, the processo eleitoral's id and the state, at +0, +4 and +8,
// which fns 3745 and 5727 pass on to NomeArquivoSecao. Both callers of each (comum::CEleitorDetalhe::GetBiometria, fn
// 1937, and fn 7787) pass comum::CConfiguracaoEleicao's +620 as the address, the municipality at +644 and the zone at
// +648 beside it. The object is 24 bytes, built by its constructor, target fn 5726, out of line in
// sidentificacaoarquivo.cpp: the phase at +0, the id at +4, CStringUtils::ToLower of the UF (fn 1879) at +8 and the
// pleito of the load's turn at +20, returning this. 7787 builds it at CConfiguracaoEleicao+620, and
// comum::CPE::CreateInst (fn 2787) at CPE+180 (app/comum/dados/cpe.h). +4 is the id each caller passes: 7787 the
// general state's idPE (md::estadoaplicacao::CEstadoGeral's +4, the ASN.1 field's name), 2787 the processo eleitoral's
// GetID(); that, the constructor and the reference at +20 are the evidence. The struct, its name, its members' names
// and its place here are chosen, and so is the constructor's file. app/comum/dados/cconfiguracaoeleicao.h holds it at
// +620 as m_identificacaoArquivo, the municipality and the zone right after it, which 1937 reads through accessors.
struct SIdentificacaoArquivo {
    SIdentificacaoArquivo(const EUrnaFase fase, const uedword idPE, const std::string& uf, const md::CPleito& pleito);

    EUrnaFase fase;
    uedword idPE;
    std::string uf;
    const md::CPleito& pleito;
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
