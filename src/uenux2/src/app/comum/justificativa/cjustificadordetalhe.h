#pragma once

#include "ecourna/api/uetypes.hpp"

namespace comum {

// The record of api::CDataMap<CNumeroInscricaoEleitoral, CJustificadorDetalhe>::Add names the class. Recovered: 2 bytes,
// the ueword CJustificador::Justifica takes (fn 10590, record cjustificador.cpp:55), and a copy constructor of its own,
// fn 3743, which fns 5725, 6734 and 10590 call where each builds the map's pair: clang would inline an implicit one, so
// it is defined in another object. That constructor's file, this header's path and the names m_ano and ano are chosen.
class CJustificadorDetalhe {
public:
    explicit CJustificadorDetalhe(ueword ano) : m_ano(ano) {}
    CJustificadorDetalhe(const CJustificadorDetalhe& outro);

private:
    ueword m_ano;
};

} // namespace comum
