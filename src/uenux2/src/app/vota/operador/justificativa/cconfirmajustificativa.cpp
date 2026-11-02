// vota::CConfirmaJustificativa. This comment is the reconstruction's: no record names this file or its functions, and
// its name and lines are chosen (cconfirmajustificativa.h, src/units/243-uenux2-app-vota-justificativa.mk).
#include "app/vota/operador/justificativa/cconfirmajustificativa.h"

#include "app/comum/dados/md/parametrizacaourna/ctradutorfrase.h"

namespace vota {

namespace {

std::string FraseNaoPertence()
{
    return comum::md::CTradutorFrase::Traduz("não pertence <S|a|ao|à> <SCSN>");
}

} // namespace

CConfirmaJustificativa& CConfirmaJustificativa::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CConfirmaJustificativa());
    }
    return *s_inst;
}

CConfirmaJustificativa::CConfirmaJustificativa()
    : IConfirmaJustificativa(FraseNaoPertence())
{
}

CConfirmaJustificativa::~CConfirmaJustificativa() = default;

std::unique_ptr<CConfirmaJustificativa> CConfirmaJustificativa::s_inst;
std::mutex CConfirmaJustificativa::s_mutex;

} // namespace vota
