#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <vector>

#include "api/io/cdatamap.h"
#include "app/comum/dados/celeitordetalhe.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"

namespace comum {

// RTTI: comum::CEleitores has two bases, api::CDataMap<CEleitorIdentidade, CEleitorDetalhe> at +4 and
// comum::IDataSourceAptos at +0, listed in that order, and its vtable has one slot, fn 2824. Slot 0's name is chosen.
class IDataSourceAptos {
public:
    virtual void Slot0() const = 0;
};

// Recovered: the layout, from the destructor (fn 5773), which is out of line and frees, in this order, a tree of strings
// at +112 (fn 2265), three vectors of strings at +88, +76 and +64, a tree at +52 (fn 1594, the tree CConfiguracaoEleicao
// holds at +604), strings at +32 and +20 and the tree at +4. No vptr store opens it, so the class is final. The base's
// 28 bytes end at +32, so what lies above them is this class's own. The map's mapped type at +112 and the members' names
// are chosen; the words between them have no reader here.
class CEleitores final : public api::CDataMap<md::CEleitorIdentidade, CEleitorDetalhe>, public IDataSourceAptos {
public:
    ~CEleitores();

    static CEleitores& GetInst();

    void Slot0() const override;

private:
    std::string m_arquivoDinamico;
    int m_naoRecuperado2[2];
    std::set<ecourna::app::dados::ETipoIdentificadorEleitor> m_tipos;
    std::vector<std::string> m_lista1;
    std::vector<std::string> m_lista2;
    std::vector<std::string> m_lista3;
    int m_naoRecuperado3[3];
    std::map<std::string, std::pair<int, std::string>> m_impedidos;

    static std::unique_ptr<CEleitores> s_instance;
    static std::mutex s_mutex;
};

} // namespace comum
