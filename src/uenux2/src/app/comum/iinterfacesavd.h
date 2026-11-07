#pragma once

#include <cstddef>
#include <format>
#include <string>
#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace comum {

// Recovered: only the type of the application a SAVD request is made for, which comum::ValidarUE, AssinarUE,
// AssinarEcourna and EnviarAcaoHSM take (their records in iinterfacesavd.cpp spell it ESavdAplic) and
// comum::CSigVerifier keeps. It is 4 bytes wide (CSigVerifier stores it with an i32.store), and the request builders
// check that it fits in a byte before storing it at the request's +1: the target compares it unsigned, or-ed with the
// other argument it checks (fns 4625, 5889 and 5892: `(a | b) >= 256` with i32.ge_u or i32.gt_u). That rules out a
// plain enum as the compared type: an enum without a fixed type whose values fit in an int promotes to int and compares
// signed (measured: a scratch build of fn 5892 that compared the plain ESavdChaveValidar below with 0xFF gave i32.gt_s
// where the target has the unsigned compare). Two readings give the target's code: a fixed unsigned type, or unsigned
// parameters of the members that compare it (ValidarPacote, EnviarAcaoHSM and AssinarArquivo, whose types no record
// gives). `: unsigned int`, the plainest unsigned type, is the reading chosen. The other SAVD types are not recovered;
// the header's path follows iinterfacesavd.cpp. One value is named: 1, which vota's requests carry (the CAssinador
// that vota::CAssinadorVota's constructor, fn 1501, builds stores it at +4; vota::VerificaAssinaturaMI and MV, fns 3290
// and 3288, pass it to ValidarUE, whose wasm type has lost the parameter: every caller passes 1). Its name is chosen
// from those callers; no evidence names an enumerator.
enum ESavdAplic : unsigned int {
    SAVD_APLIC_VOTA = 1,
};

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

// Recovered: the type of the HSM action comum::EnviarAcaoHSM takes (its record in iinterfacesavd.cpp spells it
// ESavdCmdHSM): fn 5889 compares it unsigned with the ESavdAplic, as above, then refuses any value above 1, so the
// action is 0 or 1. `: unsigned int` is the same reading as ESavdAplic's (an unsigned parameter of the member that
// compares it gives that compare too). The two values are the ones CAssinador::AssinaArquivosResultado (fn 12098 holds
// it inlined) passes 5889 around the files it signs: 0 before CLogComum's "Inicia uma sessão no MSE/MSD" logs, 1 before
// "Finaliza a sessão no MSE/MSD". The enumerators' names are chosen from those texts: no evidence names them.
enum ESavdCmdHSM : unsigned int {
    SAVD_CMD_HSM_INICIA_SESSAO = 0,
    SAVD_CMD_HSM_FINALIZA_SESSAO = 1,
};

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

// Recovered: the request header fns 3830 and 3829 send, 8 bytes: they write the mark at +0 and the data's size at +4,
// and their callers fill +1 with the ESavdAplic (fn 5892 stores its argument there, which fn 11179 passes from
// CSigVerifier's +4) and +2 with a 16-bit command (an i32.store16: 0x2021 or 0x1011 in fn 4625, 0x1001 in fn 5892,
// 0x1604 in fn 5889). Every name and the type's place are chosen: no record names it.
struct ueRequisicaoSavd {
    uebyte marca;
    uebyte aplicacao;
    ueword comando;
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
// slot 1 is fn 325, the trap an abstract class's deleting destructor gets) and three pure members, and (anonymous
// namespace)::CWasmSavd, of the executable TU, overrides them (fns 425, 10949, 10930). No record names a slot, so
// `Escreve`, `RecebeMensagem` and `Slot4` are chosen: the first from what fn 3830 does with it, the second from the
// text fn 10949 throws ("CWasmSavd::RecebeMensagem - mensagem de tamanho invalido"); their parameter types are read
// from those calls and CWasmSavd's overriders. The members: +4 the std::string fns 3830, 5889, 5890 and 5891 store the
// failure's text in, +16 the code fn 3830 writes through its first parameter (fn 5890 passes this + 16). Their names
// and the header's path are chosen. CPacoteArquivos::TrataErroPacote (fn 5901) formats both, the code as an int
// (argument type 3), through the two getters, whose names and form are chosen. EnviarRequisicao (fn 3830) is named from
// what it does, ConverteHeader (no target function: binaryen inlines it into 3830, its one caller) likewise; the two
// Desconverte members are the records'. ConverteHeader fills in the request's mark and size from the data before it
// copies the request out: the form clang keeps out of line at the tree's -O3 (unit 95's fragment has the costs). The
// second EnviarRequisicao (fn 3829, an overload by choice) sends a byte vector and returns the failure's text, empty
// when the SAVD accepts, where fn 3830 throws; it builds the header in place (unit 95's fragment says why).
// AssinarArquivo (fn 5891), ValidarPacote and EnviarAcaoHSM (no target functions: clang inlines ValidarPacote into
// comum::ValidarUE, fn 5890, and binaryen into CPacoteArquivos::Validar, which fn 4625 holds; binaryen inlines
// EnviarAcaoHSM into comum::EnviarAcaoHSM, fn 5889) check their arguments, build a request and store the failure's text
// at +4. ValidarPacote takes the command in 32 bits (4625 loads CPacoteArquivos's +28 whole and stores its low half)
// and assigns the request's application before its command (4625 stores the command first), both measured; that the
// command is a signed ueint32 is a choice, and so is the key's uedword, as VerificarArquivo's (the enum with an
// unsigned type gives the same objects: unit 95's
// fragment). VerificarArquivo (fn 5892) does the same for a package and a file, over the request TLV of both, with the
// command 0x1001; its name is chosen from the text it stores ("Argumento inválido assinar verificar arquivo."), and its
// key is a uedword: fn 5892 or-s it with the ESavdAplic and compares unsigned, and of the two readings ESavdAplic's
// comment gives, the unsigned parameter is the one chosen (the other is not measured in the landed order). They are
// members because they write +4 and +16. AssinarArquivo's, ValidarPacote's and VerificarArquivo's names are chosen;
// EnviarAcaoHSM's is the one its log string gives ("IInterfaceSavd::EnviarAcaoHSM - Tentativa de envio..."), the
// IInterfaceSavd:: qualifier included. The destructor is `= default` in the class, a choice among the inline forms: the
// target's copy, 5503, is the executable TU's, compiled -Oz (docs/reference/facts/levels.md V1, the call of the
// string's destructor), and it matches from that TU's object (unit 170), whose CWasmSavd derives from this class.
class IInterfaceSavd {
public:
    virtual ~IInterfaceSavd() = default;

    virtual void Escreve(const std::vector<uebyte>& dados) = 0;
    virtual void RecebeMensagem(ueint32& estado, std::vector<uebyte>& dados, size_t tamanho) = 0;
    virtual ueint32 Slot4() = 0;

    bool EnviarRequisicao(ueint32& codigo, ueRequisicaoSavd& requisicao, const std::string& dados);
    std::string EnviarRequisicao(ueint32& codigo, ueRequisicaoSavd& requisicao, const std::vector<uebyte>& dados);

    bool AssinarArquivo(ESavdAplic aplic, ueint32 comando, uebyte operacao, ueint32 arquivo);
    bool VerificarArquivo(ESavdAplic aplic, uedword chave, const std::string& pacote, const std::string& arquivo);
    bool ValidarPacote(ESavdAplic aplic, uedword chave, ueint32 comando, const std::string& pacote);
    bool EnviarAcaoHSM(ESavdAplic aplic, ESavdCmdHSM acao);
    // No target index: CAssinador::AssinaArquivosResultado (fn 12098 holds it inlined) holds it behind a 32-byte stack
    // frame of its own (binaryen's inlining of a function with one caller), between the HSM session's start and the
    // loop over the files. It refuses an ESavdAplic above 255 ("Argumento inválido para local.") and, after the bytes'
    // allocation, a local of another size than 15 ("Argumento inválido, tamanho do local."), sends {254, the local's 15
    // characters} with the command 0x404 through 3829 and keeps the returned text at +4, as EnviarAcaoHSM does; its
    // caller drops the result (the target keeps the two loads of m_mensagem.empty() and reads neither). A member, as it
    // writes +4 and +16; its name is chosen from the texts it stores, and the local's type from what it reads of it
    // (the std::string CAssinador keeps at +36).
    bool EnviarLocal(ESavdAplic aplic, const std::string& local);

    const std::string& GetMensagem() const { return m_mensagem; }
    ueint32 GetCodigo() const { return m_codigo; }

private:
    static std::vector<uebyte> ConverteHeader(ueRequisicaoSavd& requisicao, const std::string& dados);
    static const ueRespostaSavd* DesconverteHeader(const std::vector<uebyte>& resposta);
    static std::string DesconverteMensagem(const ueRespostaSavd* header, const std::vector<uebyte>& mensagem);

    std::string m_mensagem;
    ueint32 m_codigo;
};

// The tags of a request's TLV (api::CGenericTags), defined in iinterfacesavd.cpp: the target holds them as constant
// std::strings of three characters, "sup", "pkg", "key" and "fil" at 494896 to 494932, in the read-only data after
// iinterfaceinit.cpp's. Their names are chosen; their linkage is a reading of that order (unit 95's fragment).
extern const std::string TAG_SUP;
extern const std::string TAG_PKG;
extern const std::string TAG_KEY;
extern const std::string TAG_FIL;

// The request TLV of a package (fn 3831) and its content (no target function: binaryen inlines it into 3831, its one
// caller), and the request TLV of a package and a file, which decodes the "sup" of 3831's TLV, appends the file's TLV
// to its content and encodes "sup" again (no target function: binaryen inlines it into fn 5892, its one caller, behind a
// frame of its own). Names chosen; MontaRequisicaoTLV over a package is
// called by fns 4625, 5890 and 5892.
std::string MontaRequisicaoTLV(const std::string& pacote, ueint32 chave);
std::string MontaConteudoTLV(const std::string& pacote, ueint32 chave);
std::string MontaRequisicaoTLV(const std::string& pacote, ueint32 chave, const std::string& arquivo);

void ValidarUE(IInterfaceSavd& savd, ESavdAplic aplic, const std::string& pacote);
void ValidarUE(IInterfaceSavd& savd, ESavdAplic aplic, const std::string& pacote, const std::string& arquivo);
void AssinarUE(IInterfaceSavd& savd, ESavdAplic aplic, ueint32 comando, ueint32 arquivo);
// Record iinterfacesavd.cpp:1022 (code 7338); no target index: binaryen inlined it, behind a 496-byte stack frame of
// its own, into CAssinador::AssinaArquivosResultado, which fn 12098 holds inlined.
void AssinarEcourna(IInterfaceSavd& savd, ESavdAplic aplic, ueint32 comando, ueint32 arquivo);
void EnviarAcaoHSM(IInterfaceSavd& savd, ESavdAplic aplic, ESavdCmdHSM acao);

} // namespace comum

// These enums format as their unsigned value: the target's std::format calls pass them as a handle (argument type 15,
// fns 275, 680 and 5900, and ESavdAplic's in CPacoteArquivos::ValidarChaveEAplicacaoValida, which fn 4625 holds), and
// the handle's body, fn 536, tests `>= 128` unsigned for the char presentation, as formatter<unsigned int> does: an
// unsigned value. ESavdPacote and ESavdArquivoUE keep their opaque `: int` declarations while their enumerators are not
// recovered, ESavdChaveValidar is a plain enum and ESavdAplic has no formatter of its own, so these specializations
// state the unsigned value themselves. Their form is chosen, the one app/dados/tiposbasicos.hpp has: binaryen keeps one
// body for every such enum.
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

template <>
struct std::formatter<comum::ESavdAplic> : std::formatter<unsigned int> {
    template <typename FormatContext>
    auto format(comum::ESavdAplic valor, FormatContext& contexto) const
    {
        return std::formatter<unsigned int>::format(static_cast<unsigned int>(valor), contexto);
    }
};
