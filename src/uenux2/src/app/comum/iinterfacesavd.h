#pragma once

#include <cstddef>
#include <format>
#include <string>
#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace comum {

// Recovered: only the type of the application a SAVD request is made for, which comum::ValidarUE, AssinarUE,
// AssinarEcourna and EnviarAcaoHSM take (their records in iinterfacesavd.cpp spell it ESavdAplic) and
// comum::CSigVerifier keeps. It is 4 bytes wide (CSigVerifier stores it with an i32.store), and EnviarAcaoHSM checks
// that it fits in a byte before sending it. Its enumerators and the other SAVD types are not recovered; the header's
// path follows iinterfacesavd.cpp.
enum ESavdAplic : int;

// Recovered: only the type of the SAVD package that comum::CArquivosSavd::operator[] takes (its record in
// carquivossavd.cpp spells it ESavdPacote, fn 275) and comum::CAssinador keeps: vota::CAssinadorVota's constructor
// (fn 1501) stores its argument in the inlined CAssinador's +8 member with an i32.store and passes it to that
// operator. Its enumerators are not recovered, and that it is declared beside ESavdAplic is a choice.
enum ESavdPacote : int;

// Recovered: only the type of the SAVD file of the urna that CArquivosSavd::operator[] (its record in
// carquivossavd.cpp spells it ESavdArquivoUE), CAssinador::Assina and comum::IResultado's constructor take: 4 bytes
// wide (that constructor, inlined into fn 1396, stores it at +36 with an i32.store). Its enumerators are not
// recovered, and that it is declared beside ESavdAplic is a choice.
enum ESavdArquivoUE : int;

// Recovered: the values of the key comum::CPacoteArquivos::RetornaNomeChave names (its record in cpacotearquivos.cpp
// spells the type ESavdChaveValidar, fn 5900; the cases are 49 to 59). Each name is chosen from the text its case
// returns: no evidence names an enumerator. That it is declared beside ESavdAplic is a choice.
enum ESavdChaveValidar {
    SAVD_CHAVE_TSE = 49,
    SAVD_CHAVE_SECAD = 50,
    SAVD_CHAVE_SECINP = 51,
    SAVD_CHAVE_SEVIN = 52,
    SAVD_CHAVE_UE = 53,
    SAVD_CHAVE_SCUE = 54,
    SAVD_CHAVE_CLOGI = 55,
    SAVD_CHAVE_CLOGI_CERT = 56,
    SAVD_CHAVE_CLOGI_UPDATE = 57,
    SAVD_CHAVE_PU = 58,
    SAVD_CHAVE_SEINT = 59,
};

// Recovered: the request header fn 3830 sends, 8 bytes: it writes the mark at +0 and the data's size at +4, and its
// callers fill +1 to +3 (fn 5890 stores 1, 0x21, 0x20). Every name, the two bytes after the first and the type's place
// are chosen: no record names it.
struct ueRequisicaoSavd {
    uebyte marca;
    uebyte comando;
    uebyte parametro1;
    uebyte parametro2;
    uedword tamanho;
};

// Recovered: the response header DesconverteHeader returns (its record spells the type ueRespostaSavd): 12 bytes, the
// size that function checks, with the mark at +0 and, as fn 3830 reads them, a byte that says the request failed at +1,
// the code at +4 and the message's size at +8. The members' names are chosen.
struct ueRespostaSavd {
    uebyte marca;
    uebyte erro;
    ueint32 codigo;
    uedword tamanho;
};

// comum::IInterfaceSavd: the channel to the SAVD. Its vtable (@1526728, 5 slots) holds the destructor (slot 0, fn 5503;
// slot 1 is fn 325, the trap an abstract class's deleting destructor gets) and three pure members, and
// (anonymous namespace)::CWasmSavd, of the executable TU, overrides them (fns 425, 10949, 10930). No record names a
// slot, so `Escreve`, `RecebeMensagem` and `Slot4` are chosen: the first from what fn 3830 does with it, the second from
// the text fn 10949 throws ("CWasmSavd::RecebeMensagem - mensagem de tamanho invalido"); their parameter types are
// read from those calls and CWasmSavd's overriders. The members: +4 the std::string fns 3830, 5889 and 5890 store the
// failure's text in, +16 the code fn 3830 writes through its first parameter (fn 5890 passes this + 16). Their names and
// the header's path are chosen. CPacoteArquivos::TrataErroPacote (fn 5901) formats both, the code as an int (argument
// type 3), through the two getters, whose names and form are chosen. EnviarRequisicao (fn 3830) is named from what it
// does, ConverteHeader (no target function: binaryen inlines it into 3830, its one caller, and 3829 holds the same
// loop, so re-read this form when 3829 lands) likewise; the two Desconverte members are the records'. ConverteHeader
// fills in the request's mark and size from the data before it copies the request out: the form clang keeps out of
// line at the tree's -O3 (unit 95's fragment has the costs).
// The destructor is `= default` in the class, a choice among the inline forms: the target's copy, 5503, is the executable
// TU's, compiled -Oz (docs/reference/facts/levels.md V1, the call of the string's destructor), and nothing of ours
// emits it, so fn 5503 is not reconstructed.
class IInterfaceSavd {
public:
    virtual ~IInterfaceSavd() = default;

    virtual void Escreve(const std::vector<uebyte>& dados) = 0;
    virtual void RecebeMensagem(ueint32& estado, std::vector<uebyte>& dados, size_t tamanho) = 0;
    virtual ueint32 Slot4() = 0;

    bool EnviarRequisicao(ueint32& codigo, ueRequisicaoSavd& requisicao, const std::string& dados);

    const std::string& GetMensagem() const { return m_mensagem; }
    ueint32 GetCodigo() const { return m_codigo; }

private:
    static std::vector<uebyte> ConverteHeader(ueRequisicaoSavd& requisicao, const std::string& dados);
    static const ueRespostaSavd* DesconverteHeader(const std::vector<uebyte>& resposta);
    static std::string DesconverteMensagem(const ueRespostaSavd* header, const std::vector<uebyte>& mensagem);

    std::string m_mensagem;
    ueint32 m_codigo;
};

} // namespace comum

// These enums format as their unsigned value: the target's std::format calls pass them as a handle (argument type 15,
// fns 275, 680 and 5900), and the handle's body, fn 536, tests `>= 128` unsigned for the char presentation, as
// formatter<unsigned int> does. That reads as a plain enum, whose underlying type is unsigned, and ESavdChaveValidar is
// one here. ESavdPacote and ESavdArquivoUE keep their opaque `: int` declarations, which a plain enum has no form for
// while its enumerators are not recovered, so these specializations state the unsigned value themselves. Their form is
// chosen, the one app/dados/tiposbasicos.hpp has: binaryen keeps one body for every such enum.
template <>
struct std::formatter<comum::ESavdPacote> : std::formatter<unsigned int> {
    template <typename FormatContext>
    auto format(comum::ESavdPacote valor, FormatContext& contexto) const
    {
        return std::formatter<unsigned int>::format(static_cast<unsigned int>(valor), contexto);
    }
};

template <>
struct std::formatter<comum::ESavdArquivoUE> : std::formatter<unsigned int> {
    template <typename FormatContext>
    auto format(comum::ESavdArquivoUE valor, FormatContext& contexto) const
    {
        return std::formatter<unsigned int>::format(static_cast<unsigned int>(valor), contexto);
    }
};

template <>
struct std::formatter<comum::ESavdChaveValidar> : std::formatter<unsigned int> {
    template <typename FormatContext>
    auto format(comum::ESavdChaveValidar valor, FormatContext& contexto) const
    {
        return std::formatter<unsigned int>::format(static_cast<unsigned int>(valor), contexto);
    }
};
