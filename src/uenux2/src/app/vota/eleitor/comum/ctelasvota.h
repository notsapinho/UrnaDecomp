#pragma once

#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "app/vota/eleitor/comum/ctelascargo.h"

namespace api {
class CProgressBar;
class CFormBuilder;
class CTextBox;
class IScreen;
template <typename MEDIA>
class IForm;
struct SFont;
struct SPoint;
} // namespace api

namespace vota::testeteclado::impl {
class IGeradorTeclas;
} // namespace vota::testeteclado::impl

namespace vota {

// Recovered: the layout, from the destructor (fn 6548): a map at +0 whose nodes hold a CTelasCargo at +20, and so
// another map at +24 (fn 4137), and over it a map whose nodes hold a shared_ptr at +20 (fn 1314); then 30 shared_ptrs
// from +12 to +251, released last to first. Record 1536832, CFormInterativoTelaVota
// vota::CTelasVota::GetTelaCargo(const comum::TCargoID, const ETelaVotacao), held by fn 4135, gives the map's types:
// 4135 walks the map at +0 comparing a one-byte key at node+16 with its first argument, and it holds record 1536624
// too, CTelasCargo::GetTela, with its `this` at node+20, so that is the element. The members' names are chosen, and so
// is the type of 29 of the 30 (+180's is evidence, below): only their destruction shows, which any std::shared_ptr
// gives. Five constructors copy one member each, through a getter: vota::CImprimindoBU's (inlined into fn 5986) the one
// at +100, vota::CReinicioVotacao's (inlined into fn 5938) the one at +148, and the zeresima states' (fns 5965, 11945
// and 5957) those at +212, +220 and +228. Four GetInst copy one more each, right after CTelasVota::GetInst() (fn 407):
// vota::CAplicacaoEncerrada's (fn 3877) the one at +36, vota::CExibeAlertaDesligamento's (fn 5979) +44,
// vota::CConfirmaImpressaoZeresima's (fn 5959) +52 and vota::CInstrucaoVotacaoAcessibilidade's (fn 4420) +124.
// vota::CLimiteCopiasBUAtingido's constructor (its GetInst inlined into fn 12023) copies the one at +108. The getters'
// names, and that they are getters, are chosen. GetTelaCargo is the record's (1536832, ctelasvota.cpp:3534), defined in
// ctelasvota.cpp. Seven more members are read the same way: the constructors of vota::CVerificaHorarioZeresima (inlined
// into fn 5947) +20, vota::CInicioVotacao (fn 2880) +116, vota::CQuerImprimirBU (inlined into fn 12062) +236 and
// vota::CQuerReimprimirZeresima (fn 5940) +244 copy one each; vota::CVerificaEleicaoPassou::StartState (fn 11914)
// copies +76 into a temporary and calls its slot 2 before the temporary is released: GetTelaEleicaoPassou returns the
// std::shared_ptr by value, a choice, which gives that copy (fn 11914 matches with it; a copy the caller makes is not
// measured); and vota::CSincronismoEleitor::StartState (fn 7178) calls slot 2 of +172 and api::CProgressBar::SetValor
// (fn 3667) on +180 with that bar's +28, with no copy of either. So +180's pointee is an api::CProgressBar, and its
// member's type says so; the other 29 stay the forms' type (ctelasvota.cpp.o compiles to the same object either way,
// cmp). vota::CEmitirMaisBU::StartState (fn 12082) copies +196 into a temporary and calls its slot 2 before the
// temporary is released, as fn 11914 does with +76: GetTelaEmitirMaisBU returns it by value, the same choice.
class CTelasVota {
public:
    ~CTelasVota();

    static CTelasVota& GetInst();

    CFormInterativoTelaVota GetTelaCargo(const comum::TCargoID cargo, const ETelaVotacao tela) const;

    const CFormInterativoTelaVota& GetTelaAplicacaoEncerrada() const { return m_tela4; }
    const CFormInterativoTelaVota& GetTelaAlertaDesligamento() const { return m_tela5; }
    const CFormInterativoTelaVota& GetTelaConfirmaImpressaoZeresima() const { return m_tela6; }
    const CFormInterativoTelaVota& GetTelaImprimindoBU() const { return m_tela12; }
    const CFormInterativoTelaVota& GetTelaInstrucaoVotacaoAcessibilidade() const { return m_tela15; }
    const CFormInterativoTelaVota& GetTelaReinicioVotacao() const { return m_tela18; }
    const CFormInterativoTelaVota& GetTelaGeraZeresima() const { return m_tela26; }
    const CFormInterativoTelaVota& GetTelaGeraResumoZeresima() const { return m_tela27; }
    const CFormInterativoTelaVota& GetTelaQuerImprimirZeresima() const { return m_tela28; }
    const CFormInterativoTelaVota& GetTelaLimiteCopiasBUAtingido() const { return m_tela13; }
    const CFormInterativoTelaVota& GetTelaVerificaHorarioZeresima() const { return m_tela2; }
    CFormInterativoTelaVota GetTelaEleicaoPassou() const { return m_tela9; }
    const CFormInterativoTelaVota& GetTelaInicioVotacao() const { return m_tela14; }
    const CFormInterativoTelaVota& GetTelaSincronismo() const { return m_tela21; }
    const std::shared_ptr<api::CProgressBar>& GetBarraSincronismo() const { return m_barraSincronismo; }
    const CFormInterativoTelaVota& GetTelaQuerImprimirBU() const { return m_tela29; }
    const CFormInterativoTelaVota& GetTelaQuerReimprimirZeresima() const { return m_tela30; }
    // +84, which vota::CConfirmaRegerarZeresima's constructor copies (its GetInst inlined into fn 11835); the getter's
    // name, and that it is one, are chosen, as for the others
    const CFormInterativoTelaVota& GetTelaConfirmaRegerarZeresima() const { return m_tela10; }
    CFormInterativoTelaVota GetTelaEmitirMaisBU() const { return m_tela24; }
    // +156, whose slot 2 vota::CFimVotoEleitor::StartState (fn 7198) calls with no copy; the getter's name, and that it
    // is one, are chosen, as for the others
    const CFormInterativoTelaVota& GetTelaFimVoto() const { return m_tela19; }
    // +164, whose slot 2 vota::CEleitorVotando::DescartaVotos (fn 4449) calls with no copy; the getter's name, and that
    // it is one, are chosen, as for the others
    const CFormInterativoTelaVota& GetTelaDescartaVotos() const { return m_tela20; }
    // +60 and +68, which the constructors of vota::CImpressaoZeresimaTardia and vota::CInformacaoZeresimaTardia copy
    // (inlined with their GetInst into fns 11927 and 11931); the getters' names, and that they are getters, are chosen,
    // as for the others
    const CFormInterativoTelaVota& GetTelaImpressaoZeresimaTardia() const { return m_tela7; }
    const CFormInterativoTelaVota& GetTelaInformacaoZeresimaTardia() const { return m_tela8; }
    // +204, which vota::CEmitirMaisBU::ProcessInput (fn 12081) copies into a temporary and calls slot 2 of before the
    // temporary is released, as fn 11914 does with +76: returned by value, the same choice; the name chosen
    CFormInterativoTelaVota GetTelaLimiteViasAdicionais() const { return m_tela25; }
    // +132 and +140, whose slot 2 fn 5972 (the function both of vota::CInicioVotacao's slots call) calls with no copy,
    // the first when no voter has voted yet, the second otherwise; the names chosen, as for the others
    const CFormInterativoTelaVota& GetTelaAguardaEleitor() const { return m_tela16; }
    const CFormInterativoTelaVota& GetTelaAguardaProximoEleitor() const { return m_tela17; }

private:
    std::map<comum::TCargoID, CTelasCargo> m_mapaTelas;
    CFormInterativoTelaVota m_tela1, m_tela2, m_tela3, m_tela4, m_tela5, m_tela6, m_tela7, m_tela8, m_tela9, m_tela10;
    CFormInterativoTelaVota m_tela11, m_tela12, m_tela13, m_tela14, m_tela15, m_tela16, m_tela17, m_tela18, m_tela19, m_tela20;
    CFormInterativoTelaVota m_tela21;
    std::shared_ptr<api::CProgressBar> m_barraSincronismo;
    CFormInterativoTelaVota m_tela23, m_tela24, m_tela25, m_tela26, m_tela27, m_tela28, m_tela29, m_tela30;

    static std::mutex s_mutex;
    static std::unique_ptr<CTelasVota> s_instancia;
};

// The screens of the end of the vote and of the keyboard test built outside CTelasVota, in ctelasvota.cpp. No record
// names any of them; their names, their being free functions of vota and their parameters' types are chosen.
// - AdicionaTelaAguarde (fn 4152): the status header (5: date and time, battery icon), the message at (320, 160) in a
//   30-point font and "Por favor, aguarde..." at (320, 240) in a 25-point one, centred, colours 2 over 1. Callers:
//   fns 6129, 6174 and 6583.
// - AdicionaCabecalhoTesteTeclado (fn 3054): the status header (5), "Teste de teclado" at (320, 80) in the 30-point
//   font and a line in colour 3 from (0, 429) to (640, 429). Callers: fns 5936, 11804, 11805 and 11809.
// - TelaPreparandoDadosEncerramento (fn 6583), TelaVotacaoEncerrada and TelaCopiaResultadoParaMR: a form of
//   AdicionaTelaAguarde's fields with their message, named, through GetFormulario (fn 886). The first is called by
//   vota::CGeraRelatorios's and vota::CGeraBU's constructors (inlined into fns 6084 and 6129); the other two each have
//   one caller, CGeraBU's and vota::CCopiaResultadoParaMR's constructors, which hold them behind a second
//   stack-pointer prologue (inlined by binaryen, so out of line in the object: docs/how-to-decompile.md step 3).
// - TelaEsperaRepetirTesteTeclado: AdicionaCabecalhoTesteTeclado's fields, an api::CTextFieldUpdate with an interval
//   of 200 ms over a std::function and the format "Por favor, espere {}s para a", and two lines below it, in a
//   25-point font, named
//   through GetFormulario. Its one caller, vota::testeteclado::CEsperaRetestar's constructor (inlined into fn 5936),
//   holds it behind a second stack-pointer prologue, as the two above.
// Why ctelasvota.cpp: fns 4152 and 3054 pass the same SFont {30, 0} by address (@474888); that they share a TU rests on
// the fonts being file constants, a choice (@474888 has 19 target readers). It and 4152's SFont {25, 0} (@474992) lie
// in one read-only run after vota::CPreShowProgressBar's typeinfo name (@474851), a run that functions loading
// ctelasvota.cpp's records read (7787 its strings and fonts; 6624, 6652, 6603, 6605, 6608 its fonts): a reading of
// the data's order. Fn 6583: use band 2, between this TU's 6602 and 6548, a reading; the three with no index, chosen.
void AdicionaTelaAguarde(api::CFormBuilder& builder, const std::string& mensagem);
void AdicionaCabecalhoTesteTeclado(api::CFormBuilder& builder);
std::shared_ptr<api::IForm<api::IScreen>> TelaPreparandoDadosEncerramento();
std::shared_ptr<api::IForm<api::IScreen>> TelaVotacaoEncerrada();
std::shared_ptr<api::IForm<api::IScreen>> TelaCopiaResultadoParaMR();
std::shared_ptr<api::IForm<api::IScreen>> TelaEsperaRepetirTesteTeclado(
    std::function<std::string(const std::string&)> fonte);

// The keyboard test's screen and key sequence, which vota::testeteclado::CTesteTeclado::StartState (fn 11805) holds
// behind second stack-pointer prologues, one caller each: TelaTesteTeclado and SorteiaTeclasTesteTeclado, defined in
// ctelasvota.cpp (TelaTesteTeclado holds GetKeyboardLayout, record ctelasvota.cpp:1301), and AdicionaCaixaTecla, which
// TelaTesteTeclado calls per key, defined in ctesteteclado.cpp. TECLAS_TESTE_TECLADO, the 13 key names, is defined in
// ctelasvota.cpp after CTelasVota's statics and read above them. TTeclasTesteTeclado is the type of CTesteTeclado's
// +36, each key's name mapped to the char its key gives and to its box. src/units/217-uenux2-ctesteteclado.mk has the
// evidence and the choices (all names here are chosen).
using TTeclasTesteTeclado = std::map<std::string, std::pair<char, std::shared_ptr<api::CTextBox>>>;
extern const std::vector<std::string> TECLAS_TESTE_TECLADO;
std::shared_ptr<api::CTextBox> AdicionaCaixaTecla(api::CFormBuilder& builder, const std::string& texto, api::SPoint posicao,
                                                  api::SFont fonte, api::SPoint tamanho);
std::pair<CFormInterativoTelaVota, TTeclasTesteTeclado> TelaTesteTeclado();
std::vector<std::string> SorteiaTeclasTesteTeclado(testeteclado::impl::IGeradorTeclas& gerador);

// The zerésima chain's screens, in ctelasvota.cpp where the object's code and data orders put them, at lines chosen
// inside those bounds (src/units/110-uenux2-singletons.mk has the measurements): TelaNeutra and TelaPorFavorAguarde
// above AdicionaTelaAguarde, since use band 2 puts 6587 ahead of TelaPreparandoDadosEncerramento (6583) and band 3
// puts 4161 ahead of 4152, the place TelaNeutra's call gives AdicionaLocal; AdicionaLocal's body after GetTelaCargo,
// since the target holds its font after FONTE_INSTRUCAO_TESTE_TECLADO's. No record names them; their names, their
// being free functions of vota with external linkage and their parameters' types and names are chosen.
// - AdicionaLocal (fn 4161): the location line at the foot of a screen. It reloads comum::CLocal (Carrega, fn 5740) and
//   formats "{}: {:05} - {}     {}: {:04}     {}: {:04}" of the translated <MCSN>, the municipality and its name, <ZCSN>,
//   the zone, <SCSN> and the section when the data hold a section, else "{}: {:05} - {}     {}: {:04}     {}" with
//   "CONTINGÊNCIA" when they hold a contingency urn (the string literal passed as such: packed argument type 13 with its
//   address and 12), else nothing; then a fill from (0, 458) to (640, 480) in colour 22 and the text at (320, 460),
//   centred, 2 over 22, in the font {15, 0} the target holds at @475008 and passes by address, which 3059, 6599, 7787,
//   12040 and 12055 read too: a file constant of ctelasvota.cpp (a reading, as for FONTE_TITULO). Callers: fns 2380,
//   6601 and 7787.
// - TelaNeutra (fn 2380): the message's lines (CStringUtils::Split on '&'), each centred at x 320 in the font of the size
//   it is given, the first at 240 + size / 2 - lines * size - size / 4 and the next ones a size and a half apart, over
//   the status header (5), then the location line when bit 0 of its last parameter is set, named "telaNeutra"
//   (GetFormulario, fn 886). The target tests that bit with `i32.const 1; i32.and`, which a bool parameter does not
//   give (it is tested bare: a probe compiled at the tree's flags), so the parameter is an integer; its callers pass 0
//   (6587, 11797) and 1 (6557). The positions' 16-bit values and the step held in an int are the forms that give the
//   target's arithmetic (variants compared in the object; src/units/110-uenux2-singletons.mk). Callers: 6557, 6587, 7787
//   and 11797.
// - TelaPorFavorAguarde (fn 6587): TelaNeutra("Por favor, aguarde...", 35, 0). Callers: 11855 and 11991, the zerésima
//   printing states.
void AdicionaLocal(api::CFormBuilder& builder);
std::shared_ptr<api::IForm<api::IScreen>> TelaNeutra(const std::string& mensagem, const int16_t tamanho,
    const int opcoes);
std::shared_ptr<api::IForm<api::IScreen>> TelaPorFavorAguarde();

} // namespace vota
