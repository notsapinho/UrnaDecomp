#pragma once

#include <memory>
#include <mutex>

#include "api/io/cdatamap.h"
#include "app/comum/dados/md/processoeleitoral/crespostaconsulta.h"

namespace comum {

// Recovered: the layout, 28 bytes: CreateInst (inlined into fn 7787) allocates 28; the destructor (fn 5730) frees a
// string at +16 and destroys a tree at +0, whose nodes (48 bytes, fn 1929) hold the key at +16 and a CRespostaConsulta at
// +20. Record 1536124, api::CDataMap<unsigned int, comum::md::CRespostaConsulta>::GetCurrent, held by fn 3125, gives the
// key and the element, and fn 11478 applies 3125 to this class's pointer: the class is a CDataMap and adds no member.
class CRespostas : public api::CDataMap<unsigned int, md::CRespostaConsulta> {
public:
    ~CRespostas();

    static CRespostas& GetInst();

private:
    static std::mutex s_mutex;
    static std::unique_ptr<CRespostas> s_instancia;
};

} // namespace comum
