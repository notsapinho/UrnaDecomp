// The reconstruction's notes, not TSE's text: comum::CPleitoAtual's constructor, target fn 5726 (cpleitoatual.h). No
// record names the file or the function: the path and the line are chosen.
#include "app/comum/dados/cpleitoatual.h"

#include "ecourna/api/util/cstringutils.hpp"

namespace comum {

CPleitoAtual::CPleitoAtual(const EUrnaFase fase, const uedword idPE, const std::string& uf, const md::CPleito& pleito)
    : m_fase(fase), m_idPE(idPE), m_uf(ecourna::api::util::CStringUtils::ToLower(uf)), m_pleito(pleito)
{
}

} // namespace comum
