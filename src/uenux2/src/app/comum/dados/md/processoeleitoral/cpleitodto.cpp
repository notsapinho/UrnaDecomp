#include "app/comum/dados/md/processoeleitoral/cpleitodto.h"

namespace comum::md {

CPleitoDTO::CPleitoDTO(TPleitoID id, const std::string& nome, const api::CDate& data) : m_id(id), m_nome(nome), m_data(data)
{
}

} // namespace comum::md
