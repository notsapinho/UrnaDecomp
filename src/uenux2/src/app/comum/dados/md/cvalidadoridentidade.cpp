#include "app/comum/dados/md/cvalidadoridentidade.h"

#include "ecourna/api/pattern/singleton.hpp"

namespace comum::md {

// (original lines 7-22: content not recovered)
#line 23
std::unique_ptr<CValidadorIdentidade> CValidadorIdentidade::s_instance;
std::mutex CValidadorIdentidade::s_mutex;

SINGLETON_IMPL_GET_INST(CValidadorIdentidade, s_mutex, s_instance)

CValidadorIdentidade::~CValidadorIdentidade() = default;

} // namespace comum::md

// <stubs>
// f566 · 997 B · unmatched · name unknown
// ? f566(i32, i32, i32) { ... }
// </stubs>
