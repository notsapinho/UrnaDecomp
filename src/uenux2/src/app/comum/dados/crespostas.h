#pragma once

#include <memory>
#include <mutex>
#include <vector>

#include "api/io/cdatamap.h"
#include "app/comum/dados/md/processoeleitoral/crespostaconsulta.h"
#include "app/comum/dados/md/rdv/cvotoscargos.h"

namespace comum {

// Recovered: the layout, 28 bytes: CreateInst (inlined into fn 7787) allocates 28; the destructor (fn 5730) frees a
// string at +16 and destroys a tree at +0, whose nodes (48 bytes, fn 1929) hold the key at +16 and a CRespostaConsulta at
// +20. Record 1536124, api::CDataMap<unsigned int, comum::md::CRespostaConsulta>::GetCurrent, held by fn 3125, gives the
// key and the element, and fn 11478 applies 3125 to this class's pointer: the class is a CDataMap and adds no member.
class CRespostas : public api::CDataMap<unsigned int, md::CRespostaConsulta> {
public:
    ~CRespostas();

    static CRespostas& GetInst();

    // The numbers of one post's answers, in key order: target fn 11212 holds it inlined by binaryen (a frame of its
    // own). Busca finds an answer by the base's key, the post times 1000000 plus the number, and moves the cursor to it,
    // as CCandidaturas::Busca does: the target calls one body, fn 1273, on both singletons (11212 passes this one). No
    // record names either; their names and their being members are chosen (they read the base's map).
    std::vector<TCandidatoID> GetNumeros(md::TCargoID cargo) const;
    md::CRespostaConsulta* Busca(md::TCargoID cargo, TCandidatoID numero);

private:
    static std::mutex s_mutex;
    static std::unique_ptr<CRespostas> s_instancia;
};

} // namespace comum
