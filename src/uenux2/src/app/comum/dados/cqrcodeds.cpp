// comum::CQRCodeDS. The reconstruction's own note: no record names this file or a function in it; the path, the
// definitions' order and every line are chosen (src/units/299-uenux2-cqrcodeds-processoeleitoral.mk says what places
// them, and why ExtraiVersao and MontaConteudo are functions of their own).
#include "app/comum/dados/cqrcodeds.h"

#include <regex>

#include "api/gui/capplication.h"
#include "api/util/cdatetime.h"
#include "api/util/cstringutils.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/chv.h"

namespace comum {

const std::string ExtraiVersao(const std::string& versao)
{
    const std::regex expressao("[0-9]+.[0-9]+.[0-9]+.[0-9]+");
    const std::sregex_iterator resultado(versao.begin(), versao.end(), expressao);
    if (resultado != std::sregex_iterator()) {
        return resultado->str().c_str();
    }
    return "0.0.0.0";
}

CQRCodeDS::CQRCodeDS(const TTags& tags) : m_tags(tags)
{
}

void CQRCodeDS::SetOrigem(EOrigem origem)
{
    switch (origem) {
    case eOrigemTela:
        m_tags.push_back(std::make_pair(std::string("ORIG"), std::string("T")));
        break;
    case eOrigemImpressora:
        m_tags.push_back(std::make_pair(std::string("ORIG"), std::string("I")));
        break;
    }
}

std::string CQRCodeDS::operator()() const
{
    return MontaConteudo(CConfiguracaoEleicao::GetInst().GetPleito());
}

std::string CQRCodeDS::MontaConteudo(const md::CPleito& pleito) const
{
    const api::CDateTime agora;
    const std::string dataPleito = pleito.GetData().Format("YYYYMMDD");
    const auto& horarioVerao = CHV::GetInst().TemHorarioVerao() ? "1" : "0";
    TTags tags = m_tags;
    tags.emplace_back("VERS", ExtraiVersao(api::CApplication::s_versao));
    tags.emplace_back("DTAG", agora.GetData().Format("YYYYMMDD"));
    tags.emplace_back("HRAG", agora.GetHora().Format("hhmmss"));
    tags.emplace_back("DTPL", dataPleito);
    tags.emplace_back("HRVR", horarioVerao);
    return api::CStringUtils::JuntaTags(tags);
}

} // namespace comum
