#include "app/comum/dados/crespostas.h"

#include "ecourna/api/pattern/singleton.hpp"

namespace comum {

// (original lines 7-27: content not recovered)
#line 28
SINGLETON_IMPL_GET_INST(CRespostas, s_mutex, s_instancia)






std::unique_ptr<CRespostas> CRespostas::s_instancia;
std::mutex CRespostas::s_mutex;

CRespostas::~CRespostas() = default;

} // namespace comum
