#pragma once

#include <cstddef>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "app/comum/dados/md/processoeleitoral/ccargo.h"
#include "app/comum/dados/md/rdv/cvotoscargos.h"

namespace comum {

namespace md {
class CEleicaoPE;
}

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

    ~CCargos();

    static CCargos& GetInst();

    void Reset();
    bool IsFim() const;
    // Whether the current position is the first: vota::CEleitorVotando::ProcessTick (fn 7349) tests the word at +0
    // against 0. The member and its name are chosen.
    bool IsPrimeiro() const { return m_atual == 0; }
    void Next();
    const md::CCargo& GetCurrent() const;
    comum::TCargoID GetCurrentCargoID() const;
    const md::CEleicaoPE& GetCurrentEleicao() const;
    comum::TEleicaoID GetCurrentEleicaoID() const;
    comum::TEleicaoID GetUltimaEleicaoID() const { return m_cargos.back().first; }

    // fn 3784: copies the vector at +4 over the one at +16, through std::vector's range assign (fn 3783, which fn 7377,
    // FiltraPorAbrangencia, calls too). Its callers, fns 12098 and 12110 (vota::CGravaResultado's and vota::CGeraBU's slot
    // 2), call it on GetInst()'s result, so it is a member, out of line since they keep the call. No record names it:
    // the name, that it is the undoing of FiltraPorAbrangencia, and its place in ccargos.cpp are chosen.
    void RemoveFiltro();

private:
    size_t m_atual;
    std::vector<TCargoEleicao> m_todos;
    std::vector<TCargoEleicao> m_cargos;

    static std::mutex s_mutex;
    static std::unique_ptr<CCargos> s_instancia;
};

// The name of the current position's election, a report's text: fn 5580 passes it to
// api::CPaperFormBuilder::AddTextField (fn 604) by table slot 3049, and no direct call reaches it. Its body, fn 11556,
// holds GetInst's code (record ccargos.cpp:24), which only ccargos.cpp can inline, so it is defined there. Its name, its
// being a free function and this header are chosen.
std::string NomeEleicaoCorrente();

} // namespace comum
