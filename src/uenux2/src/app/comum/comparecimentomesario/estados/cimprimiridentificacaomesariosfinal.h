#pragma once

#include <string>

#include "api/gui/cpaperformbuilder.h"
#include "api/gui/ipaperrelatorios.h"
#include "api/pattern/cpolysingleton.h"

namespace comum {

// comum::CImprimirIdentificacaoMesariosFinal: the report of the poll workers registered at the opening and at the
// closing (the BIM) that vota::CGeraRelatorios::StartState (target fn 12105) writes to bim.dat. Its records name two
// members: GetNomeMesario (fn 5385, record cimprimiridentificacaomesariosfinal.cpp 229:84, a non-static, non-const
// member: the record text has neither `static` nor `const`) and GetPrinter (an inline const member at this header's
// line 41, column 47, the default argument of api::CPolySingleton<api::IPaperRelatorios>::instance, which 12105 holds).
// No vtable, typeinfo or allocation of the class is in the target's data. Recovered from 12105, which builds the object
// in its own frame (16 bytes: the builder's vector, then bytes at +12, +13 and +14) and holds the constructor, Imprime
// and the members Imprime calls inlined by binaryen (frames of 16, 16, 384, 48, 32, 32 and 416 bytes of their own):
// the three bytes' uses (+12 picks the header's kind and gates the opening and closing times, +13 titles the report for
// the data recovery system, +14 prints the emission's date and time). The constructor stores 1 at +12 with a byte store
// and 0 at +13 and +14 with one 16-bit store, through its `this` held in a local: an out-of-line constructor whose +12 is
// a parameter its one caller passes as 1 (folded by binaryen's dead-argument elimination) and the other two constants
// clang merges (a reading; an inline constructor of three parameters gave a 16-bit store at +12 and a byte at +14,
// measured in a whole link). Chosen: the members' names but the records', the parameter, the access, GetTitulo's const,
// the order of the declarations.
class CImprimirIdentificacaoMesariosFinal {
public:
    explicit CImprimirIdentificacaoMesariosFinal(bool secao);

    void Imprime(const std::string& arquivo);
    std::string GetNomeMesario(const std::string& titulo);

private:
    std::string GetTitulo() const;
    void ImprimeCabecalho();
    void ImprimeDadosUrna();
    void ImprimeMesariosAbertura();
    void ImprimeMesariosFechamento();
    void ImprimeRodape();

    api::IPaper& GetPrinter() const  { return api::CPolySingleton<api::IPaperRelatorios>::instance(); }

    api::CPaperFormBuilder m_builder;
    bool m_secao;
    bool m_recuperador;
    bool m_dataHoraEmissao;
};

} // namespace comum
