// Reconstruction: comum::md::CDataJE's constructor, which comum::asn::CConversorEntidadeEleitores's slot 2 (target fn
// 11411) holds inlined (cdataje.h). Its record, line 26, column 15, places the throw; the other lines and the test's
// form are chosen (cdataje.h says what the target's test is).
#include "app/comum/dados/md/cdataje.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 12-21: content not recovered)
#line 22
CDataJE::CDataJE(const std::string& data) : m_data(data)
{
    if (m_data.size() != 8 || m_data.find_first_not_of("0123456789") != std::string::npos) {

        throw CUeComumDadosError(EUE_COMUM_DADOS_8002, std::format("DataJE com formato inválido: {}", data));
    }
}

} // namespace comum::md
