#pragma once
#include "api/io/cdatamap.h"
#include "app/comum/justificativa/cjustificadordetalhe.h"
#include "app/comum/justificativa/servico/cjustificadorservico.h"
#include "ecourna/app/dados/cnumeroinscricaoeleitoral.hpp"

namespace comum {

// The justified voters, by their titulo. The name is the records' (cjustificador.cpp lines 55 and 83). At +0 is the
// api::CDataMap<ecourna::app::dados::CNumeroInscricaoEleitoral, CJustificadorDetalhe> whose Add and Next records name it,
// which fn 3742, the constructor, builds with the name "CJustificador". Recovered: the layout, 40 bytes (fn 1391
// allocates 40 before it calls 3742), with a comum::servico::CJustificadorServico at +28, whose vptr 3742 stores and
// whose destructor (fn 3740) the destructor (fn 2810) calls on +28. The map as a base and not a member at +0 is a choice,
// as for CRegistradorMesario (src/units/113-uenux2-cdatamap.mk). The path of this header and the member's name are
// chosen. The other members (Justifica, SaveCurrentInternal, the functions that build the singleton) are not written.
class CJustificador
    : public api::CDataMap<ecourna::app::dados::CNumeroInscricaoEleitoral, CJustificadorDetalhe> {
public:
    CJustificador();

private:
    servico::CJustificadorServico m_servico;
};

} // namespace comum
