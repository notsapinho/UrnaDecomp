#pragma once

#include <optional>
#include <string>
#include <vector>

#include "api/util/cdate.h"
#include "app/comum/dados/md/processoeleitoral/cpleito.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Recovered: the layout, 176 bytes, from its destructor (fn 2830) and the copy CPE::CreateInst makes of it (fn 2787): a
// word at +0, strings at +4 and +16, 8 bytes at +28, a CPleito at +36, a std::optional<CPleito> at +96 with its flag at
// +156, a word at +160 and a vector of a trivial element at +164. That the 8 bytes are a CDate, the element's type and the
// members' names are chosen; the first pleito's reading comes from the name GetPleito2. GetPleito2 (fn 1267) reads the
// optional. Nothing may construct this class yet: its constructors are not recovered.
class CProcessoEleitoral {
public:
    const CPleito& GetPleito2() const;

private:
    uedword m_codigo;
    std::string m_nome;
    std::string m_descricao;
    api::CDate m_data;
    CPleito m_pleito1;
    std::optional<CPleito> m_pleito2;
    uedword m_quantidade;
    std::vector<unsigned char> m_dados;
};

} // namespace comum::md
