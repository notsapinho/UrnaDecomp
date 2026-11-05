// The reconstruction's note, not TSE's text: CriaComum (fn 2799, records at lines 25 and 31), GetDedo (fn 3720, record
// at line 93), TemDedo (fn 3719, no record, its line a choice) and GetFoto (record at line 115, no target index:
// binaryen inlines it into fn 3616, its one caller; its lines but the throw's are chosen). The three constructors (no
// record; binaryen inlines them into fn 11422, fragment 335) and their lines, 37 to 50, are chosen.
#include "app/comum/dados/md/eleitor/cbiometriaeleitor.h"

#include <format>
#include <utility>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 14-21: content not recovered)
#line 22
void CBiometriaEleitor::CriaComum(std::vector<CDedo> dedos)
{
    if (dedos.size() > 10) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8056, std::format("Mais de dez dedos na biometria do eleitor: {}", dedos.size()));
    }

    for (size_t i = 0; i < dedos.size(); ++i) {
        const CDedo& dedo = dedos[i];
        if (!m_dedos->insert(std::make_pair(dedo.GetTipo(), dedo)).second) {
            throw CUeComumDadosError(EUE_COMUM_DADOS_8057, "Dedo já existente ou duplicado");
        }
    }
}


CBiometriaEleitor::CBiometriaEleitor(const ecourna::app::dados::CFoto& foto, const std::vector<CDedo>& dedos)
    : m_foto(foto), m_dedos(std::map<CDedo::TipoDedo, CDedo>()), m_erroDecifracao()
{
    CriaComum(dedos);
}

CBiometriaEleitor::CBiometriaEleitor(const ecourna::app::dados::CFoto& foto) : m_foto(foto), m_dedos(), m_erroDecifracao()
{
}

CBiometriaEleitor::CBiometriaEleitor(const std::vector<CDedo>& dedos)
    : m_foto(), m_dedos(std::map<CDedo::TipoDedo, CDedo>()), m_erroDecifracao()
{
    CriaComum(dedos);
}

// (original lines 53-88: content not recovered)
#line 89
CDedo CBiometriaEleitor::GetDedo(CDedo::TipoDedo tipo) const
{
    const auto dedo = m_dedos->find(tipo);
    if (dedo == m_dedos->end()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8058, "Dedo não encontrado.");
    }
    return dedo->second;
}

bool CBiometriaEleitor::TemDedo(CDedo::TipoDedo tipo) const
{
    return m_dedos.has_value() && m_dedos->contains(tipo);
}

// (original lines 103-111: content not recovered)
#line 112
const ecourna::app::dados::CFoto& CBiometriaEleitor::GetFoto() const
{
    if (!m_foto) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8059, "Não há informação de foto.");
    }
    return *m_foto;
}

} // namespace comum::md
