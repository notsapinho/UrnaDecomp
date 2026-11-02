#pragma once

namespace comum {

// The urna's phase, 4 bytes wide: comum::CGravadorWSQ's constructor stores CGravadorUtil::ConverteFase's result (record
// cgravadorutil.cpp:97, fn 2274) at +52 with an i32.store. The values are evidence: comum::asn::Utils::ConverteFase and
// DesconverteFase compile to tables (@497848, @497860) that map 49, 50 and 51 to ModuloTiposEleitorais::Fase's oficial
// (2), simulado (1) and treinamento (3). Their throws format it through fn 536, formatter<unsigned int>, which a plain
// enum of these values gives; `: unsigned int`, and `: int` with an explicit formatter<unsigned int>, give the same. The
// plain form, the character spelling of the values, the enumerators' names, the comum:: scope and this path are chosen.
// The value 48, '0', is evidence too: comum::md::CDadosDisponiveisCarga's constructor (held inlined by target fn 11423)
// rejects that one phase, with code 8040 (record cdadosdisponiveiscarga.cpp:41); FASE_INDEFINIDA's name is chosen.
enum EUrnaFase {
    FASE_INDEFINIDA = '0',
    FASE_OFICIAL = '1',
    FASE_SIMULADO = '2',
    FASE_TREINAMENTO = '3',
};

} // namespace comum
