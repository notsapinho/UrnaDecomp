// comum::CSubstituidorTitulo (/home/rubio/tse/uenux2/src/app/comum/relatorios/csubstituidortitulo.cpp). Notes
// of the reconstruction, not TSE's text, with no blank-line gap in the file. The file's two records are GetInst's (line
// 21, column 66: the closing parenthesis of SINGLETON_IMPL_GET_INST, as for the singletons of
// src/units/110-uenux2-singletons.mk, whose column formula gives 47 plus the class name's 19 characters) and
// CreateInst's throw (line 26, column 15). The other members have no record: their lines are chosen. The statics follow
// GetInst, which gives the target's .bss order (the mutex 24 bytes below the pointer), as unit 110 measured.
// The destructor is out of line: fn 3689 (CreateInst's reset) and fn 11175 (the pointer's exit destructor) call it
// as fn 5576, a reading: at -fPIC a D1 call stays a call in its own TU (docs/reference/facts/codegen.md C6).
#include "app/comum/relatorios/csubstituidortitulo.h"

#include <utility>

#include "app/comum/relatorios/euecomumrelatorioserror.h"
#include "ecourna/api/pattern/singleton.hpp"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum {

using ecourna::api::util::CStringUtils;

SINGLETON_IMPL_GET_INST(CSubstituidorTitulo, s_mutex, s_instancia)

void CSubstituidorTitulo::CreateInst(const std::map<std::string, std::string>& substituicoes)
{
    if (s_instancia) {
        throw CUeComumRelatoriosError(EUE_COMUM_RELATORIOS_9088, "Instância já criada");
    }
    s_instancia.reset(new CSubstituidorTitulo(substituicoes));
}

std::unique_ptr<CSubstituidorTitulo> CSubstituidorTitulo::s_instancia;
std::mutex CSubstituidorTitulo::s_mutex;

CSubstituidorTitulo::CSubstituidorTitulo(const std::map<std::string, std::string>& substituicoes)
    : m_substituicoes(substituicoes)
{
}

CSubstituidorTitulo::~CSubstituidorTitulo() = default;

bool CSubstituidorTitulo::Existe()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    return s_instancia != nullptr;
}

std::string CSubstituidorTitulo::Substitui(const std::string& texto) const
{
    std::string resultado = texto;
    for (const auto& substituicao : m_substituicoes) {
        resultado = CStringUtils::Replace(std::as_const(resultado), substituicao.first, substituicao.second);
    }
    return resultado;
}

} // namespace comum
