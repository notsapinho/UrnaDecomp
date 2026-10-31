#pragma once

#include <map>

#include "api/io/cdatamap.h"
#include "app/comum/comparecimentomesario/md/ccomparecimentomesario.h"

namespace comum {

// The record of SaveCurrentInternal (cregistradormesario.cpp:85, held by fn 10337) names the class and the file, and the
// literal fn 815 gives the map as its name is the class's. Recovered: the object fn 815 builds, 52 bytes: the map of
// comparecimentos at +0, the section's mesarios by identity at +28, a servico::CComparecimentoMesarioServico at +40
// (vptr 1595676). The last is not declared here, so sizeof is wrong and nothing may construct this class yet. Registra,
// AtualizaMesarioSecao and m_mesariosSecao are chosen names, as is this header's path. CDataMap as a base is a choice: as
// a member at +0 the bytes are the same.
class CRegistradorMesario : public api::CDataMap<md::CComparecimentoMesarioPK, md::CComparecimentoMesario> {
public:
    void Registra(const md::CComparecimentoMesario& comparecimento);

private:
    void AtualizaMesarioSecao(const md::CComparecimentoMesario& comparecimento);

    std::map<md::CEleitorIdentidade, md::CComparecimentoMesario> m_mesariosSecao;
};

} // namespace comum
