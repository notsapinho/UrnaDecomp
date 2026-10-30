#pragma once

namespace comum {

// The urna's phase, 4 bytes wide: comum::CGravadorWSQ's constructor stores CGravadorUtil::ConverteFase's result (record
// cgravadorutil.cpp:97, fn 2274) at +52 with an i32.store. The values are evidence: comum::asn::Utils::ConverteFase and
// DesconverteFase compile to tables (@497848, @497860) that map 49, 50 and 51 to ModuloTiposEleitorais::Fase's oficial
// (2), simulado (1) and treinamento (3). So is an unsigned underlying type: their throws format it through fn 536,
// formatter<unsigned int>. A plain enum of these values has one, and `: unsigned int` gives the same; the plain form,
// the character spelling of the values, the names and this path are chosen.
enum EUrnaFase {
    FASE_OFICIAL = '1',
    FASE_SIMULADO = '2',
    FASE_TREINAMENTO = '3',
};

} // namespace comum
