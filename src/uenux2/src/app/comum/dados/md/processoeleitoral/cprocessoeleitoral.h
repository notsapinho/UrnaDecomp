#pragma once

#include <optional>
#include <string>
#include <vector>

#include "app/comum/dados/md/processoeleitoral/cpleito.h"
#include "app/comum/dados/md/processoeleitoral/eorigemconfiguracao.h"
#include "ecourna/api/uetypes.hpp"
#include "ecourna/app/dados/tiposbasicos.hpp"

namespace comum::md {

// Recovered: the layout, 176 bytes, from its destructor (fn 2830), the copy CPE::CreateInst makes of it (fn 2787) and
// the two constructors comum's processo eleitoral load (fn 3771) holds: the DTO's id at +0, a string at +4 (the UF in
// upper case, which 3771 builds), the DTO's name at +16, its biometry flag at +28 and origin at +32, a CPleito at +36,
// a std::optional<CPleito> at +96 with its flag at +156, the DTO's principal identifier at +160 and the vector of
// identifiers at +164. The members' names are chosen; GetPleito2 (fn 1267) reads the optional.
// The constructors are out of line in cprocessoeleitoral.cpp, a reading: 3771 moves the vector it takes by value and
// then tests and frees the moved-from copy, which clang drops where it sees the move, so binaryen inlined each into
// its one caller (docs/how-to-decompile.md step 3). That one of them takes the second pleito and the other not is a
// reading of 3771's two branches, which build the optional engaged and empty.
class CProcessoEleitoral {
public:
    CProcessoEleitoral(uedword id, const std::string& uf, const std::string& nome, bool utilizaBiometria,
        EOrigemConfiguracao origem, const CPleito& pleito1,
        ecourna::app::dados::ETipoIdentificadorEleitor identificadorPrincipal,
        std::vector<ecourna::app::dados::ETipoIdentificadorEleitor> identificadores);
    CProcessoEleitoral(uedword id, const std::string& uf, const std::string& nome, bool utilizaBiometria,
        EOrigemConfiguracao origem, const CPleito& pleito1, const CPleito& pleito2,
        ecourna::app::dados::ETipoIdentificadorEleitor identificadorPrincipal,
        std::vector<ecourna::app::dados::ETipoIdentificadorEleitor> identificadores);

    // The name is chosen: CPE::CreateInst (fn 2787) takes this pleito in the first turn.
    uedword GetID() const { return m_id; }
    const CPleito& GetPleito1() const { return m_pleito1; }
    const CPleito& GetPleito2() const;
    // The name is chosen: comum::CRelatorioTesteImpressora's slot 14 (fn 11191) tests the flag at +156 first.
    bool TemPleito2() const { return m_pleito2.has_value(); }

private:
    uedword m_id;
    std::string m_uf;
    std::string m_nome;
    bool m_utilizaBiometria;
    EOrigemConfiguracao m_origem;
    CPleito m_pleito1;
    std::optional<CPleito> m_pleito2;
    ecourna::app::dados::ETipoIdentificadorEleitor m_identificadorPrincipal;
    std::vector<ecourna::app::dados::ETipoIdentificadorEleitor> m_identificadores;
};

} // namespace comum::md
