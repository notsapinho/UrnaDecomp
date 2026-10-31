#pragma once

#include <string>

#include "api/util/cdate.h"
#include "app/comum/dados/md/processoeleitoral/cpleito.h"

namespace comum::md {

// The layout, 24 bytes, from comum::asn::CConversorPleito::DoDesconverte (target fn 11365), which builds the class in
// place: the id at +0, the name at +4, the date at +16. ModuloProcessoEleitoral::Pleito's fields give the three names.
// No record names the file; the class's name is the RTTI of the converter's base. The path is chosen, beside
// cprocessoeleitoraldto.cpp, which has records. The constructor is what 11365 holds after the arguments: the id, a copy
// of the name and the date's 8 bytes, stored in that order. It is out of line in another TU (cpleitodto.cpp, a path
// chosen), and binaryen inlined it into its one caller: 11365 reads the date with the 2-byte alignment of a
// const api::CDate& (i64.load align=1), and with the constructor in the class it is 8-byte aligned.
class CPleitoDTO {
public:
    CPleitoDTO(TPleitoID id, const std::string& nome, const api::CDate& data);

private:
    TPleitoID m_id;
    std::string m_nome;
    api::CDate m_data;
};

} // namespace comum::md
