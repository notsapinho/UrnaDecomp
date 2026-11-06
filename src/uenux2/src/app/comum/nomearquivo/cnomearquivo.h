#pragma once

#include <map>
#include <string>

#include "app/comum/dados/md/processoeleitoral/cpleito.h"
#include "app/comum/eurnafase.h"
#include "ecourna/api/uetypes.hpp"

namespace comum {

// The municipality's identifier as ajustaAbrangenciaUFMunicipio's record (cnomearquivo.cpp:208) spells it, unqualified
// in comum: app/comum/md/cidentificacaourna.h says what shows it. Repeating the alias here is a choice.
using TMunicipioID = uedword;

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
// (reading.md R10); 3771's is NomeArquivoPE above, 5740's NomeArquivoLocal (a 112-byte frame: a 5-digit and two 4-digit
// numbers, "-" and the type, "." and the extension, the parts NomeArquivoSecao ends with), and 3744's
// NomeArquivoAbrangencia (a 528-byte frame, below). NomeArquivoLocal's and NomeArquivoAbrangencia's names, their being
// static members and their parameters' types are chosen, as the others'. That the class has no other member is not
// known.
class CNomeArquivo {
public:
    static std::string NomeArquivoUF(EUrnaFase fase, uedword pleito, const std::string& uf, const std::string& tipo,
        const std::string& extensao);
    static std::string NomeArquivoSecao(EUrnaFase fase, uedword pleito, const std::string& uf, uedword municipio,
        uedword zona, uedword secao, const std::string& tipo, const std::string& extensao);
    static std::string NomeArquivoLocal(uedword municipio, uedword zona, uedword secao, const std::string& tipo,
        const std::string& extensao);
    // The builder fn 3744 holds behind a 528-byte frame of its own (binaryen's inlining of a function with one caller):
    // a copy of the UF, ajustaAbrangenciaUFMunicipio's switch (record :208) inlined, then the phase's letter, the
    // election's 5-digit number, the UF, the municipality's 5-digit number, "-" and the type, "." and the extension. It
    // calls the anonymous-namespace helpers, so it is this file's code; its one caller, 3744, is another TU's, so the
    // object keeps it out of line and binaryen inlines it (reading.md R10). No record names it: its name, its being a
    // static member and the parameters' types are chosen.
    static std::string NomeArquivoAbrangencia(EUrnaFase fase, uedword idEleicao, const std::string& uf,
        TMunicipioID municipio, md::ETipoAbrangencia abrangencia, const std::string& tipo, const std::string& extensao);
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

// Target fn 3744, in cnomearquivoeleitores.cpp beside 3745 (src/units/388-uenux2-nomesarquivos.mk says what places it):
// for one election of the pleito, when it holds a candidate's post (md::CEleicaoPE::PossuiCargoCandidato, fn 5653), the
// name NomeArquivoAbrangencia builds, keyed by the election's abrangencia. Its callers, fns 2811 and 7787, pass the
// identification at +0 and +8, the pleito and the municipality apart, and fn 7787 "ca" and "dat". No record names it:
// its name, its being a free function of comum declared here and the parameters' types are chosen.
std::map<md::ETipoAbrangencia, std::string> NomesArquivosEleicao(const SIdentificacaoArquivo& identificacao,
    const md::CPleito& pleito, TMunicipioID municipio, md::TEleicaoID idEleicao, const std::string& tipo,
    const std::string& extensao);

} // namespace comum
