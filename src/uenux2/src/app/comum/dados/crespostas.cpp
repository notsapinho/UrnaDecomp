#include "app/comum/dados/crespostas.h"

#include <format>

#include "app/comum/dados/crespostasds.h"
#include "ecourna/api/pattern/singleton.hpp"

namespace comum {

// (original lines 10-27: content not recovered)
#line 28
SINGLETON_IMPL_GET_INST(CRespostas, s_mutex, s_instancia)






std::unique_ptr<CRespostas> CRespostas::s_instancia;
std::mutex CRespostas::s_mutex;

CRespostas::~CRespostas() = default;

std::string CRespostasDSNumero::operator()() const
{
    return std::format("{:0{}}", CRespostas::GetInst().GetCurrent()->GetNumero(), m_digitos);
}

std::string RespostaCorrente()
{
    return CRespostas::GetInst().GetCurrent()->GetResposta();
}

} // namespace comum
