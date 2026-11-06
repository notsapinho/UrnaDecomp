#pragma once

#include <map>
#include <string>
#include <vector>

#include "api/io/cinikey.h"
#include "api/io/cinisection.h"

namespace api {

// Reconstruction: the object an INI file is read into, 24 bytes: a std::map from a section's name to its CIniSection at
// +0 and a std::map from a key's name to its CIniKey at +12. Carrega is target fn 5480, the loader: it reads the file's
// lines (ecourna's CFile::ReadLine, inlined) and returns Interpreta's object, which binaryen inlined behind a stack
// frame of its own (the stores of the two maps' end nodes, then the parse), holding SetSection and SetKey the same way.
// comum::CGeracaoVersoesContratos's destructor (fn 5866) destroys two such objects, at +0 and +24, each by its two
// trees (fns 1397 and 2859, the map at +12 and the map at +0). FindKey (fn 10877) and EndKey are the find and the end
// of the map at +12 that comum::md::CVersoesContratos::GetValor and CDependenciasContratos::GetValor call out of line
// (their merged body, fn 6044, calls both, the end as fn 5481, a body the target keeps once for boost's
// sp_counted_impl_pd's get_untyped_deleter too). No record, slot or RTTI names the class or a member: the class, its
// members' names, which map holds what beyond the bodies' layout, FindKey's and EndKey's iterator type and that they
// are not const, Carrega's and Interpreta's being static members that return the object, the private members and this
// header's and cinifile.cpp's paths are chosen (src/units/379-uenux2-cinifile.mk).
class CIniFile {
public:
    using TMapSecoes = std::map<std::string, CIniSection>;
    using TMapChaves = std::map<std::string, CIniKey>;

    static CIniFile Carrega(const std::string& arquivo);

    TMapChaves::iterator FindKey(const std::string& nome);
    TMapChaves::iterator EndKey();

private:
    CIniFile() = default;
    static CIniFile Interpreta(const std::vector<std::string>& linhas);

    TMapSecoes::iterator SetSection(const CIniSection& secao);
    void SetKey(const CIniKey& chave);

    TMapSecoes m_secoes;
    TMapChaves m_chaves;
};

} // namespace api
