#pragma once

#include <string>

#include "api/util/cdatetime.h"
#include "ecourna/api/uetypes.hpp"
#include "ecourna/app/dados/cidentificadorgeradormidia.hpp"

namespace comum::md {

// Recovered: the layout only, 76 bytes, from its implicit copy constructor (target fn 1557, which
// CCorrespondenciaResultado's constructor, fn 2801, and CUrna's, fns 2854 and 2855, call): a word at +0, strings at +4
// and +28, 12 trivially copied bytes at +16, and three strings at +40, +52 and +64, which the copy constructor copies
// inline (our copy, with ecourna::app::dados::CIdentificadorGeradorMidia's copy constructor inlined there, matches; that
// class's own is fn 9872). The fields follow
// ModuloTiposEcoUrna::Carga's, whose types fit those widths: numeroInternoUrna, numeroSerieFC, dataHoraCarga (12 bytes,
// an api::CDateTime), codigoCarga and identificadorGeradorMidia. ValidaCriacao (fn 5670, records ccarga.cpp:36 to :51)
// tests the string at +4 as the MC's serial and the one at +28 as the load's code (its messages say so); the rest of
// the placing among the strings, the types and the member names are chosen. The constructor (target fn 2802, no
// record) copies its five arguments into the members in that order and calls ValidaCriacao; its parameters' order is
// the fields', and their types (a reference for each class) are chosen. The getters are what
// comum::asn::CConversorCarga::DoConverte (fn 10291) reads, by reference for the classes; their names are chosen.
class CCarga {
public:
    CCarga(uedword numeroInternoUrna, const std::string& numeroSerieFC, const api::CDateTime& dataHoraCarga,
           const std::string& codigoCarga, const ecourna::app::dados::CIdentificadorGeradorMidia& identificadorGeradorMidia);

    uedword GetNumeroInternoUrna() const { return m_numeroInternoUrna; }
    const std::string& GetNumeroSerieFC() const { return m_numeroSerieFC; }
    const api::CDateTime& GetDataHoraCarga() const { return m_dataHoraCarga; }
    const std::string& GetCodigoCarga() const { return m_codigoCarga; }
    const ecourna::app::dados::CIdentificadorGeradorMidia& GetIdentificadorGeradorMidia() const
    {
        return m_identificadorGeradorMidia;
    }

private:
    void ValidaCriacao() const;

    uedword m_numeroInternoUrna;
    std::string m_numeroSerieFC;
    api::CDateTime m_dataHoraCarga;
    std::string m_codigoCarga;
    ecourna::app::dados::CIdentificadorGeradorMidia m_identificadorGeradorMidia;
};

} // namespace comum::md
