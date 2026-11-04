#pragma once

#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// The SA application's part of the BU (ModuloBoletimUrna::DadosSA). The class name is the one the record of
// CEntidadeBU::GetDadosSA (centidadebu.cpp:196, held by target fn 10273) prints. Recovered: the layout, 8 bytes, from
// comum::asn::CConversorEntidadeBU::DoConverte (fn 10273), which stores the 16-bit words at +0 and +2 into DadosSA's
// juntaApuradora and turmaApuradora and the 32-bit word at +4 into numeroInternoUrnaOrigem when it is not 0, omitting
// that optional field otherwise. The member and getter names, their types beyond their widths and the header's path,
// beside centidadebu.h (no record names a file of this class), are chosen. The constructor is not recovered, so nothing
// may construct the class.
class CDadosBUSA {
public:
    ueword GetJuntaApuradora() const { return m_juntaApuradora; }
    ueword GetTurmaApuradora() const { return m_turmaApuradora; }
    uedword GetNumeroInternoUrnaOrigem() const { return m_numeroInternoUrnaOrigem; }

private:
    ueword m_juntaApuradora;
    ueword m_turmaApuradora;
    uedword m_numeroInternoUrnaOrigem;
};

} // namespace comum::md
