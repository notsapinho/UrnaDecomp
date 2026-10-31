#pragma once

#include "ecourna/api/uetypes.hpp"

namespace comum {

// The record of api::CDataMap<CNumeroInscricaoEleitoral, CJustificadorDetalhe>::Add names the class. Recovered: the pair's
// second member is 2 bytes, the ueword CJustificador::Justifica takes (fn 10590, record cjustificador.cpp:55), and fns
// 5725, 6734 and 10590 copy it through a function of its own, fn 3743, where each builds the map's pair. That 3743 is this
// class's copy constructor is a reading: the bytes show an out-of-line 2-byte copy, not whose. A member of a 2-byte class
// with such a constructor reads the same. An implicit copy constructor leaves no such call; a defined one stays a call, in its callers file too.
// That file, this header's path and the names m_ano and ano are chosen.
class CJustificadorDetalhe {
public:
    explicit CJustificadorDetalhe(ueword ano) : m_ano(ano) {}
    CJustificadorDetalhe(const CJustificadorDetalhe& outro);

private:
    ueword m_ano;
};

} // namespace comum
