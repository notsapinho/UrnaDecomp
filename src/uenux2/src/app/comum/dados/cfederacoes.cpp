// Reconstruction notes, not TSE's text: comum::CFederacoes's singleton (target fns 2832, 11553, 11552), its constructor
// (which 2832 holds inlined), its destructor (5800) and GetFederacao (5799). Load's records are lines 141 and 149, which
// stay blank past the end of this file; the lines of everything written here are a choice.
// src/units/162-uenux2-cfederacoes.mk says what the bytes decide.
#include "app/comum/dados/cfederacoes.h"

#include <algorithm>
#include <memory>
#include <mutex>

namespace comum {

CFederacoes& CFederacoes::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst = std::make_unique<CFederacoes>();
    }
    return *s_inst;
}

std::unique_ptr<CFederacoes> CFederacoes::s_inst;
std::mutex CFederacoes::s_mutex;

CFederacoes::CFederacoes() : CFederacoes("CFederacoes") {}

CFederacoes::~CFederacoes() = default;

const ecourna::app::dados::CFederacao* CFederacoes::GetFederacao(ueword partido) const
{
    if (m_federacoes.empty()) {
        return nullptr;
    }
    const auto federacao = std::find_if(m_federacoes.begin(), m_federacoes.end(),
                                        [partido](const ecourna::app::dados::CFederacao& candidata) {
                                            const ecourna::app::dados::TVectorNumeroPartido partidos =
                                                candidata.GetPartidos();
                                            return std::find(partidos.begin(), partidos.end(), partido) != partidos.end();
                                        });
    return federacao != m_federacoes.end() ? &*federacao : nullptr;
}

} // namespace comum
