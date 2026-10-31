#include "app/comum/dados/cpe.h"

#include "ecourna/api/pattern/singleton.hpp"

namespace comum {

// (original lines 7-20: content not recovered)
#line 21
SINGLETON_IMPL_GET_INST(CPE, s_mutex, s_instancia)

// <stubs>
// f2787 · 537 B · unmatched · name unknown
// void f2787(i32) { ... }
// </stubs>

std::unique_ptr<CPE> CPE::s_instancia;
std::mutex CPE::s_mutex;

CPE::~CPE() = default;

} // namespace comum
