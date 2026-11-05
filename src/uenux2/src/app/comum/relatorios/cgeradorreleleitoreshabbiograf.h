#pragma once

#include <filesystem>

namespace comum {

// comum::CGeradorRelEleitoresHabBiograf, the report of the voters enabled by a poll worker (their biographical data)
// that vota::CGeraRelatorios::StartState (target fn 12105) writes to behb.dat. Reconstruction notes, not TSE's text:
// RTTI names the class and its nested enum EGeradorRelatorio, in the typeinfo of the std::function's __func of a lambda
// of comum::(anonymous namespace)::MontaCabecalho(comum::CGeradorRelEleitoresHabBiograf::EGeradorRelatorio) (vtable
// @1576044); no record names this header or its .cpp, whose paths are chosen beside the family's sources (the .cpp's
// object lies before cgeradorrellistaeleitores.cpp's in the target's data). 12105 holds Gera inlined by binaryen (a
// 560-byte frame of its own) and calls the constructor, fn 2262, the body binaryen shares with comum::CLocal's (0
// stored at +0, `this` returned): so the constructor stores the constant itself. Written with the enum as a parameter
// its one caller passes as 0, our 12105 called comum::CInformacaoEleicao's constructor (fn 603, the parameter stored at
// +0) there and never 2262 (measured in a whole link): binaryen merged the two bodies before dead-argument elimination
// could fold the constant (a reading).
// Gera reads the enum at +0 twice: 1 titles the report "Sistema Recuperador de Dados\n..." and 0 signs it as the
// section's poll workers do, any other value as an electoral board does. Chosen: the enumerators' names, the member's
// name, Gera's name and parameter, its const, the default constructor's being the only one.
class CGeradorRelEleitoresHabBiograf {
public:
    enum EGeradorRelatorio {
        eGeradorUrna,
        eGeradorRecuperador,
    };

    CGeradorRelEleitoresHabBiograf();

    void Gera(const std::filesystem::path& arquivo) const;

private:
    EGeradorRelatorio m_tipo;
};

} // namespace comum
