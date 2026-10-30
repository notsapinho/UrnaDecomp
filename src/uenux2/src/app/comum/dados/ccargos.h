#pragma once

#include <cstddef>
#include <utility>
#include <vector>

#include "app/comum/dados/md/processoeleitoral/ccargo.h"
#include "app/comum/dados/md/rdv/cvotoscargos.h"

namespace comum {

// TCargoID, TEleicaoID: the records of CCargos::GetCurrentCargoID and GetCurrentEleicaoID spell them comum::. The
// project declares them in comum::md (md/rdv/cvotoscargos.h), so these aliases give the records' spelling.
using TCargoID = md::TCargoID;
using TEleicaoID = md::TEleicaoID;

// Recovered: the layout, 28 bytes: CreateInst (inlined into fn 7787) allocates 28, zeroes +0 and builds the two vectors
// at +4 and +16 with one function (fn 3774); fn 7377, which holds FiltraPorAbrangencia, reads +4 and sorts +16. Their
// elements are 8 bytes, the election id at +0 and the cargo id at +4 (fns 1938 and 2835). That the element is a std::pair
// and the members' names are chosen.
class CCargos {
public:
    using TCargoEleicao = std::pair<TEleicaoID, TCargoID>;

    void Next();
    comum::TCargoID GetCurrentCargoID() const;
    comum::TEleicaoID GetCurrentEleicaoID() const;

private:
    size_t m_atual;
    std::vector<TCargoEleicao> m_todos;
    std::vector<TCargoEleicao> m_cargos;
};

} // namespace comum
