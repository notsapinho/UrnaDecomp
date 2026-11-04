#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "app/comum/cappstate.h"
#include "app/comum/dados/md/eleitor/cdedo.h"

namespace api {
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CControlaReconhecimento (RTTI: si_class of comum::CAppState; vtable @1590984 [244, 387, 10512, 7480, 1661, 218,
// 425, 10511, 425]): it overrides StartState (slot 2, fn 10512, written, not matched: unit 161's fragment says why)
// and ProcessInput (slot 7, fn 10511), and
// keeps the counters of the voter's biometric recognition in statics that other states' slots test and advance through
// its static members. The records of ccontrolareconhecimento.cpp name three of those: AvancaTentativa (line 167, fn
// 5406), AvancaVerificacao (line 176, held inlined by fn 10447) and AvancaProximoDedo1x4 (line 187, held inlined by fn
// 10465). The destructor is out of line, the body 49 final states share (fns 244 and 387): a std::shared_ptr at +12 is
// all it releases. GetInst (fn 1256) is the tree's singleton form: it allocates the 20-byte object when its static
// std::unique_ptr (@1908756, destroyed at exit by fn 10515) is null, the constructor inlined there (binaryen's: our
// object calls it), deletes the old object through fn 244 and, before it returns, calls fn 150 (one body with
// std::mutex::unlock) on its static std::mutex (@1908732, by fn 10514). The constructor passes
// comum::CAppState::EVENTO_ENTRADA (2) to the base's, fills +12 from MontaTelaEleitorPodeVotar (fn 5410) and calls
// vota::CParametrosImagemDigital::GetInst (fn 1903), dropping its result; that it is a statement of the constructor's
// body is chosen.
//
// The statics are what the slots and the static members read and write: in .data, three 32-bit words that hold 1, set
// again by StartState, second first (@1590924, @1590928, @1590932: first to third below); in .bss, a byte (@1908668).
// AvancaTentativa compares the first with the byte CConfiguracaoEleicao holds at +136 (its CParametrosUrna's
// numTentativasHabilitacao), AvancaVerificacao the second with the one at +140 (numTentativasVerificacao); fn 10465
// copies the first into the third, and fn 10425 reads the third's low byte. The .bss byte is the index of the finger
// being captured: StartState and AvancaTentativa set it to 0; AvancaProximoDedo1x4, inlined into fn 10465 under
// record 187, adds 1 to it while it is not 4 and otherwise throws EUeVotaError 9399 ("Fim da verificação 1x4
// atingido."); fn 10465 also tests it against 4 at +0xe62, a `br_if` out of a loop, and fns 10465 and 10425 read the
// word at @1590944 + 4 * byte, a table whose words are 1, 6, 2, 7, 3, 4, 5, 8, 9, 10. So it is an unsigned byte
// counter (each read is i32.load8_u), not a flag; uebyte, the tree's spelling of that type, is a choice. The table is
// s_dedosVerificacao, the fingers in the order of the verification: it lies in .data after the three words and before
// the vtable (@1590984), which reads as this object's data; 10465 passes its words as the comum::md::CDedo::TipoDedo of
// CBiometriaEleitor::TemDedo and GetDedo. Its being one array, a static member, not const (a reading: a const one would
// be read-only data, apart from the words), its element type and its name are chosen.
// StartState also clears two std::vector<uebyte> in .bss (@1908672 and @1908684, its end set to its begin; fns 10425,
// 10451, 10465 and 3614 copy them byte for byte, 10465 assigns the first through
// vector<unsigned char>::__assign_with_size, fn 1681) and, in the training of the mesarios, fills five words from
// @1908712: the number of voters, then a sixth of it four times; fn 10465 adds the four up, one more each round.
// Between them lie a std::string (@1908696, which fns 3614 and 10425 copy) and a 16-bit word (@1908708, stored by 10465
// with i32.store16 and read by 10425: the score 10425 passes CEleitorDadosHabilitacaoBiometrica's constructor). Their
// exit destructors, 10518, 10517 and 10516, sit in use band 1 before s_inst's and s_mutex's (10515, 10514), so the file
// defines them in that order, before GetInst's statics. Five statics give the target's store order, measured on 10512
// (which does not match): StartState stores the four sixths in increasing address order (+4, +8, +12, +16 of the
// first), where one array or one struct of five ints gives the reverse, +16 down to +4 (wasm-objdump -d of the object
// each way). Their being five objects is a reading: nothing in the bodies marks where one ends, and 10465 reads the
// four either way (10512 alone the first). Their being static members, private, their types where the bodies give only
// a width, and their names are chosen: s_indiceDedo from the byte's role, s_tentativaRegistrada from 10465's copy,
// s_qualidadeCapturada from 10425's use, s_eleitoresTreinamento and s_faixaTentativa1 to 4 from StartState's division
// and 10465's test of each sum with the attempt number 1 to 4; the others' names are not read from their readers'
// roles.
// src/units/161-uenux2-app-vota-operador-identidade.mk says which of this is evidence and which is chosen.
class CControlaReconhecimento final : public comum::CAppState {
public:
    virtual ~CControlaReconhecimento() override;

    static CControlaReconhecimento& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

    static void AvancaTentativa();
    static void AvancaVerificacao();
    static bool AtingiuLimiteTentativas();
    static bool AtingiuLimiteVerificacoes();
    static bool PrimeiraTentativa();
    // The attempt number, read by vota::CPedeDigital::StartState (fn 10468) for its log: the low byte of the first
    // static (`i32.load8_u[1590924]`). vota::CDigitalNaoReconhecidaPorTempo::StartState (fn 10486) formats it as an
    // unsigned (argument code 6), so the result is a byte. Its name, its type's spelling and its being an inline member
    // here are chosen.
    static uebyte GetTentativa() { return s_tentativa; }
    // The urna's limit of attempts, CConfiguracaoEleicao's byte at +136 (its CParametrosUrna's
    // numTentativasHabilitacao), which fns 10474 and 10486 read in place right after a call of GetInst whose result they
    // drop, for the second argument of "Tentativa {} de {}". Out of line in ccontrolareconhecimento.cpp, which includes
    // the configuration's header, and called through GetInst()'s result: binaryen inlines its two-instruction body into
    // every caller (measured: no function of its own in the link). Its name, its being a static member and its place are
    // chosen.
    static uebyte GetLimiteTentativas();
    // The members vota::CPedeDigital::ProcessTick (fn 10465) reaches the statics through, each held inlined there.
    // AvancaProximoDedo1x4 is the record's (line 187, column 15: the throw's), behind the 16-byte frame of its
    // message's std::string: out of line here, binaryen inlined it into its one caller. GetMinuciasDedoCorrente is the
    // 64-byte frame of 10465's loop over the fingers: CEleitores::GetCurrentBiometriaEleitor's object asked TemDedo,
    // then, when the finger is there, a second one's GetDedo, whose CDedo's minutiae vector is copied into the result
    // (the copy constructor's code, the result's zeroing before the source's loads) before either temporary is
    // destroyed, the empty result otherwise; the frame says out of line in another TU than its caller, binaryen's
    // inlining (a reading). DigitalReconhecidaTreinamento is 10465's test, in the training of the mesarios, of the
    // voter's sequential number (its low 16 bits, i32.load16_u) against the running sums of the four sixths, each with
    // its attempt number; it calls nothing but CEleitores::GetInst and GetCurrent, and its place in this TU is chosen
    // like its being out of line. RegistraDigitalCapturada is 10465's assignment of the digital into s_digitalCapturada
    // (the vector's operator=, its self-assignment test and __assign_with_size, fn 1681) and of the attempt into
    // s_tentativaRegistrada. GetIndiceDedo and SetQualidadeCapturada read and write the byte and the 16-bit word,
    // inline here. The names, their being static members, the result and parameter types where the bodies give a width,
    // the inline ones' being inline and the out-of-line ones' lines at the end of ccontrolareconhecimento.cpp are
    // chosen.
    static void AvancaProximoDedo1x4();
    static uebyte GetIndiceDedo() { return s_indiceDedo; }
    static std::vector<api::SXYT> GetMinuciasDedoCorrente();
    static bool DigitalReconhecidaTreinamento();
    static void RegistraDigitalCapturada(const std::vector<uebyte>& digital);
    static void SetQualidadeCapturada(ueword qualidade) { s_qualidadeCapturada = qualidade; }

private:
    CControlaReconhecimento();

    static std::unique_ptr<CControlaReconhecimento> s_inst;
    static std::mutex s_mutex;

    static int s_tentativa;
    static int s_verificacao;
    static int s_tentativaRegistrada;
    static comum::md::CDedo::TipoDedo s_dedosVerificacao[10];
    static uebyte s_indiceDedo;
    static std::vector<uebyte> s_digitalCapturada;
    static std::vector<uebyte> s_digitalRegistrada;
    static std::string s_dedoRegistrado;
    static ueword s_qualidadeCapturada;
    static int s_eleitoresTreinamento;
    static int s_faixaTentativa1;
    static int s_faixaTentativa2;
    static int s_faixaTentativa3;
    static int s_faixaTentativa4;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

// The form "ELEITOR(A) PODE VOTAR" (fn 5410), which fn 1256 (this class's GetInst) and fn 5399
// (vota::CInformaEleitorPodeVotar's) call to fill +12: a function of its own, out of line in both callers. It reads no
// state; its being a free function, its name and its place in ccontrolareconhecimento.cpp, ahead of AvancaTentativa as
// the uses-2 band links fn 5410 before fn 5406, are chosen.
std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTelaEleitorPodeVotar();

} // namespace vota
