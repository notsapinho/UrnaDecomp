#pragma once

#include <memory>
#include <mutex>
#include <string>

#include "app/comum/dados/md/chorarioveraomunicipio.h"

namespace comum {

// Recovered: the layout, 28 bytes, one CHorarioVeraoMunicipio at +0: CreateInst (inlined into fn 7787) allocates 28, and
// fn 11510, the pointer's exit destructor, frees it with no destructor call. The members' names are chosen.
class CHV {
public:
    static CHV& GetInst();

    const md::CHorarioVerao& GetHorarioVerao() const;
    // The name is chosen: comum::CRelatorioTesteImpressora's slot 3 (fn 11202) reads the optional's flag at +24.
    bool TemHorarioVerao() const { return m_horarioVerao.TemHorarioVerao(); }

private:
    // fn 3754: CreateInst (inlined into fn 7787) calls it on each of its three paths with the 28 bytes it allocates and
    // a CHorarioVeraoMunicipio it built, then stores the object at 1838872, s_instancia; it copies that object into the
    // member. Out of line in chv.cpp: at the tree's flags clang keeps a constructor's C1 call in its own file, as the
    // target's calls show (a probe compile, src/units/110-uenux2-singletons.mk says which). explicit, private and the
    // parameter's name are chosen.
    explicit CHV(const md::CHorarioVeraoMunicipio& horarioVerao);

    void VerificaEntraEmHorarioVerao(const std::string& funcao) const;

    md::CHorarioVeraoMunicipio m_horarioVerao;

    static std::mutex s_mutex;
    static std::unique_ptr<CHV> s_instancia;
};

} // namespace comum
