#include "app/comum/dados/crdvvota.h"

#include <algorithm>
#include <string>

#include "ecourna/api/pattern/singleton.hpp"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum {

using ecourna::api::util::CStringUtils;

size_t CRdvPosicionadorVota::Posicao(const std::vector<md::CVoto>& votos, const md::CVoto& voto) const
{
    return std::upper_bound(votos.begin(), votos.end(), voto) - votos.begin();
}

md::TQtdVoto CRdvVota::Candidato(md::TCargoID cargo, uedword numero, uebyte digitos) const
{
    const std::string numeroCandidato = CStringUtils::PreencheAEsquerda(std::to_string(numero), '0', digitos);
    return m_votos.Candidato(cargo, numeroCandidato);
}

// (original lines 24-86: content not recovered)
#line 87
SINGLETON_IMPL_GET_INST(CRdvVota, s_mutex, s_instancia)

// (original lines 89-93: content not recovered)
#line 94
std::unique_ptr<CRdvVota> CRdvVota::s_instancia;
std::mutex CRdvVota::s_mutex;

CRdvVota::~CRdvVota() = default;

} // namespace comum

// <stubs>
// f11487 · 707 B · unmatched · name unknown
// void f11487(i32, i32) { ... }
// </stubs>
