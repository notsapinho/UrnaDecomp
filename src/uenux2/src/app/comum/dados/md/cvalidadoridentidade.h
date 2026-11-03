#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "app/comum/dados/md/iregraidentidade.h"

namespace comum::md {

// Recovered: the layout, 12 bytes: CreateInst (inlined into fn 7787) allocates 12; the destructor (fn 5671) walks one
// vector of pointers backwards, nulls each and deletes it through slot 1, so its elements are unique_ptrs to a class
// with a virtual destructor. That the class is IRegraIdentidade comes from Valida's body (inlined in fn 566), which
// holds the loop over them. The member's name is chosen.
// Valida (record cvalidadoridentidade.cpp:61) is inlined into fn 566, CEleitorIdentidade's constructor. EhValida (fn
// 2803) is the same search with a bool result instead of the throw (callers 2225, 10313, 10420, 10721); its name is
// chosen.
// TiposValidos is held inlined by binaryen in vota::CValidaIdentidade::StartState (fn 10627), its one caller, behind a
// 16-byte frame of its own after the caller's call of GetInst (fn 1926): the types of the rules whose EhValida (fn
// 3723) accepts the number, in the rules' order, pushed through std::vector::push_back(&&) (fn 543). It reads the
// rules, so it is a member; its name, its result type and its being const are chosen.
class CValidadorIdentidade {
public:
    ~CValidadorIdentidade();

    static CValidadorIdentidade& GetInst();

    void Valida(ecourna::app::dados::ETipoIdentificadorEleitor tipo, const std::string& numero) const;
    bool EhValida(ecourna::app::dados::ETipoIdentificadorEleitor tipo, const std::string& numero) const;
    std::vector<ecourna::app::dados::ETipoIdentificadorEleitor> TiposValidos(const std::string& numero) const;

private:
    std::vector<std::unique_ptr<IRegraIdentidade>> m_regras;

    static std::unique_ptr<CValidadorIdentidade> s_instance;
    static std::mutex s_mutex;
};

} // namespace comum::md
