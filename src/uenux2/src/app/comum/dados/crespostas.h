#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "app/comum/dados/ccargos.h"
#include "app/comum/dados/md/processoeleitoral/crespostaconsulta.h"

namespace comum {

// Recovered: the layout, 28 bytes: CreateInst (inlined into fn 7787) allocates 28; the destructor (fn 5730) frees a
// string at +16 and destroys a tree at +0, whose nodes (48 bytes, fn 1929) hold a word at +16 and a CRespostaConsulta at
// +20. +12 takes the map's begin in CreateInst, so it is read as an iterator. The map's key type and the members' names
// are chosen.
class CRespostas {
public:
    using TMapaRespostas = std::map<TCargoID, md::CRespostaConsulta>;

    ~CRespostas();

    static CRespostas& GetInst();

private:
    TMapaRespostas m_respostas;
    TMapaRespostas::const_iterator m_atual;
    std::string m_titulo;

    static std::mutex s_mutex;
    static std::unique_ptr<CRespostas> s_instancia;
};

} // namespace comum
