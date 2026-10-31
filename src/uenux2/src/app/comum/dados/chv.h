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

private:
    void VerificaEntraEmHorarioVerao(const std::string& funcao) const;

    md::CHorarioVeraoMunicipio m_horarioVerao;

    static std::mutex s_mutex;
    static std::unique_ptr<CHV> s_instancia;
};

} // namespace comum
