#pragma once

#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "app/comum/dados/cqrcodeds.h"
#include "app/vota/eleitor/comum/ctelascargo.h"

namespace api {
class CInputMenuField;
class CProgressBar;
class CFormBuilder;
class CTextBox;
class IScreen;
template <typename MEDIA>
class IForm;
struct SFont;
struct SPoint;
} // namespace api

namespace comum {
class CAppState;
} // namespace comum

namespace comum::md {
class CCandidatura;
} // namespace comum::md

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

    // The QR-code BU's screen ("telaQRCodeBU"), which vota::CMostraQRCodeBU::StartState (fn 12055) holds behind a
    // second stack-pointer prologue (a 208-byte frame), built on each call over three std::functions StartState
    // passes by value: the help text, the QR code's content and the page "i/n" (table slots 1505, 1506 and 1507, fns
    // 12054, 12053 and 12052, in the order of its frame's three temporaries). Evidence: the fields, their texts,
    // names, fonts, colours, positions and order are 12055's code. Readings: that it is CTelasVota's (12055 calls
    // CTelasVota::GetInst(), fn 407, right before it and drops the result, which the object expression of a member
    // call whose body reads no state gives), and that it is defined in ctelasvota.cpp (the vtables of what it builds
    // with std::make_shared, CQRCodeImage's control block @1539236, CDataText<std::function<std::string()>> @1539316
    // and its block @1539276, CTextFieldMultiLine's block @1539352, lie in the target's data in the run of this
    // file's, between CTextFieldUpdate's block @1539196 and CriaTelaVisualizacaoCandidato's lambda @1539548, as
    // cformbuilder.h reads 3058's; and it passes the fonts @474888 and @474896, which FONTE_TITULO and
    // FONTE_INSTRUCAO_TESTE_TECLADO stand for). In ctelasvota.cpp it calls two external free functions, each held by
    // 12055 behind a 48-byte frame of its own (so out of line in the object, inlined by binaryen):
    // AdicionaTextoMultiLinha, a CTextFieldMultiLine over a CDataText of the std::function (alignment 0, colours 2 over
    // 1), and AdicionaTexto, a CTextField over one (alignment 1); the target's bodies hold the font and the alignment
    // as constants, which binaryen's dead-argument elimination of the one caller's arguments gives (a reading). It
    // reads the screen's area through the file-local AreaTela,
    // which returns CApplication::s_areaTela by value: 12055 copies the area's 8 bytes with one i64.load, which
    // that by-value copy gives (and so does a default-constructed SRect assigned from it), where a copy-initialized
    // local, an explicitly copied temporary and a structured binding give three i16 loads (each compiled on a scratch
    // TU at this file's flags). Its layout values are locals declared after the status header: the target computes them ahead of
    // their statements (before std::function copies and releases), which those locals give and expressions at the
    // call do not (measured in the whole link: 756 over 2418 rows with the expressions, 281 over 2368 with the
    // locals). The fonts {15, 0} and {20, 1} (@475008, @475032) are file constants beside them, as the others are.
    // Chosen: every name here and in ctelasvota.cpp (after the class's CriaTela* records), the member's being
    // non-static and const (a static one called through GetInst() is the same reading), the helpers' being free
    // functions of vota and their parameters, AreaTela, the locals, their types and their lines.
    // src/units/37-uenux2-iqrcodebuds.mk has what 12055 still differs in.
    CFormInterativoTelaVota CriaTelaQRCodeBU(std::function<std::string()> ajuda, std::function<std::string()> qrcode,
                                             std::function<std::string()> pagina) const;

    // The candidate's screen vota::CVisualizarCandidatos::StartState (fn 11876) shows for each candidature it pages
    // through (fn 6569): the record of the lambda at ctelasvota.cpp:3366 (fn 12272) names it and its parameters, the
    // lambda at :3323 is its $_0 (CDataImage<__bind<...$_0&, const comum::md::CDadosCandidato&>>'s RTTI), and 11876 calls
    // it with no CTelasVota::GetInst() before it, so it is static. src/units/150-uenux2-eleitor-estados.mk has what each
    // part of its body rests on; the parameters' names are chosen.
    static CFormInterativoTelaVota CriaTelaVisualizacaoCandidato(const comum::md::CCandidatura& candidatura, size_t pagina,
                                                                 size_t total);

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
    void IncrementaBarraSincronismo();
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
    // fns 6580 and 6581: the keyboard test's screens that vota::testeteclado::CRetomada's and CPreZeresima's GetTela (fns
    // 11831, 11862) show, built on each call by TelaTextoConfirmaCorrige (below) over "Por favor, teste o teclado" and
    // the key CONFIRMA alone, and over "Quer testar o teclado?" with CORRIGE too. Their callers call GetInst and drop
    // its result, which a static member called through it gives; as non-static members the result stayed in a local
    // (11831 11 over 43 rows, 11862 11 over 53, measured in the link). That they are CTelasVota's and their names are
    // chosen. Defined in ctelasvota.cpp before TelaTesteTeclado, 6581 first: use band 2 of the object puts them after
    // TelaPreparandoDadosEncerramento (fn 6583) and before the map instance 6579 and the destructor (6548)
    static CFormInterativoTelaVota GetTelaTesteTecladoObrigatorio();
    static CFormInterativoTelaVota GetTelaTesteTecladoOpcional();
    // The screen vota::CImprimirBUOutrasObrigatorias::StartState (fn 12065) shows before each mandatory copy of the BU:
    // the status header (5), "Imprimindo vias obrigatórias" and "do Boletim de Urna" at (320, 60) and (320, 110) in the
    // 30-point font, the copy's number at (320, 170) through a function slot (fn 13023, std::format("Via nº {}") of
    // the vote's BU count plus 1, an unsigned) and "Por favor, aguarde..." at (320, 200) in the 25-point one, a line in
    // colour 3 from (0, 250) to (639, 250), and each non-empty line of comum::CConfiguracaoEleicao's parameters' text
    // at +260 split at '\n' at x 10 from y 275, 25 apart, left-aligned in the 20-point one (@474896), named
    // "telaDestinoBUs" through GetFormulario. Fn 12065 holds it behind a second stack-pointer prologue right after
    // CTelasVota::GetInst() (fn 407), whose result it drops: a static member called through the instance (as fns 6580
    // and 6581). Its name, its being static and its place in ctelasvota.cpp after the file's last record are chosen
    static std::shared_ptr<api::IForm<api::IScreen>> GetTelaDestinoBUs();
    // Fn 6557: TelaNeutra("CONTINUAÇÃO DA VOTAÇÃO&IDENTIFIQUE O ELEITOR", 40, 1), the screen
    // vota::CMostraTelaContinuaVotacao shows and vota::CUrnaInspecionada keeps at +20. Its two callers, those classes'
    // constructors (inlined with their GetInst into fns 7481 and 11797), call CTelasVota::GetInst() (fn 407) right
    // before it and drop the result, the reading made for fns 6580 and 6581: a static member called through the
    // instance. Use band 2 of ctelasvota.cpp.o puts it after the map instance 6579 and before the destructor 6548, so it
    // is defined between SorteiaTeclasTesteTeclado and ~CTelasVota (ld_index 2813, between 2800 and 2814). Its name and
    // its being CTelasVota's are chosen.
    static std::shared_ptr<api::IForm<api::IScreen>> GetTelaContinuaVotacao();
    // The screens of vota::CInspecionaUrna and vota::CUrnaInspecionada (+12 of each): TelaTextoConfirmaCorrige("Por
    // favor, inspecione cabina e urna.", "Continuar", std::nullopt) and TelaNeutra("Inspeção terminada.&Siga as
    // instruções&no terminal do mesário.", 35, 0). Each has one caller, its class's constructor, inlined with GetInst
    // into fn 7481 and fn 11797, which hold them behind a second stack-pointer prologue right after a call of
    // CTelasVota::GetInst() whose result they drop: static members called through the instance, out of line in the
    // object and inlined by binaryen (as GetTelaDestinoBUs). Their names, their being CTelasVota's, and their place
    // after the file's last record are chosen.
    static CFormInterativoTelaVota GetTelaInspecionaUrna();
    static std::shared_ptr<api::IForm<api::IScreen>> GetTelaInspecaoTerminada();
    // Fn 6599, the "Mais informações" screen vota::CMaisInformacoes::StartState (fn 11897) shows, called right after
    // CTelasVota::GetInst() (fn 407), whose result 11897 drops: a static member called through the instance, the
    // reading made for fns 6580 and 6581 (as a const member, 11897 scored 6 over 83 rows against 2 over 83 as a static,
    // pnpm wasm score in the whole link). Evidence, the body: the status header (5), "Mais informações" at (320, 100) in
    // the 30-point font (@474888, FONTE_TITULO), comum::CMenuBase::MontaMenu (fn 5913) on a vota::CMenuMaisInformacoesVota
    // over the builder, destroyed right after it (citensmenuvota.h), "Processo eleitoral: {:05}" and "Pleito: {:05}"
    // (argument type 6: CConfiguracaoEleicao's words at +0 and +28, the process and the pleito's id) and "Local com
    // biometria: " with "Sim" or "Não" (comum::CLocal::UrnaBiometrica, fn 820), at (25, 360), (25, 380) and (25, 400),
    // left-aligned in the 15-point font (@475008, FONTE_VERSAO), colours 2 over 1, the labels of CONFIRMA ('C',
    // "Selecionar") and CORRIGE ('D', "Retornar") through fn 653, and "telaMaisInformacoes" through
    // GetFormularioInterativo (fn 576). Its other target caller is 7787. The name, after the class's recorded CriaTela*
    // statics, and its place in ctelasvota.cpp are chosen; src/units/110-uenux2-singletons.mk has what it differs in.
    static CFormInterativoTelaVota CriaTelaMaisInformacoes();
    // Fn 6595, the screen vota::CVerificaHorarioZeresima::ProcessInput (fn 11869) shows on CONFIRMA, called right after
    // CTelasVota::GetInst() (fn 407), whose result 11869 drops: a static member called through the instance, the
    // reading made for fns 6580, 6581 and 6599. Evidence, the body: a copy of comum::CConfiguracaoEleicao's zerésima
    // time (+544, GetDataHoraZeresima), its hour ("h"), minutes ("mm") and date ("DD/MM/YYYY") through api::CTime's and
    // api::CDate's Format (fns 779, 706), AdicionaTelaQRCode (fn 3059, below) with "ATENÇÃO", "Esta urna eletrônica só
    // funcionará a partir de", <hour>h<minutes> do dia <date>. and the origin 0; then the label of 'C' ("Emissão do
    // estado da urna") when comum::CInformacaoEleicao's count of state reports is above the vote state's count printed
    // (+73 of comum::CAppInfo::GetVota's result), and the label of 'B' ("Mais informações"), through fn 653, and
    // "telaAntesHorarioZeresima" through GetFormularioInterativo (fn 576). The labels' vector is zeroed after the
    // counts are read and its first emplace_back calls the slow path directly (fn 6594, one body for its two
    // instances): the test is a local computed before the vector is declared, a form measured (declared before the if,
    // the vector's words were reloaded after the calls and the first emplace_back kept its fast path). Its other target
    // caller is 7787. The name, from the screen's, its place in ctelasvota.cpp and the bool's name are chosen.
    static CFormInterativoTelaVota CriaTelaAntesHorarioZeresima();

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
// The keyboard test's failure screens, one caller each: the constructors of vota::testeteclado::CTesteFalhou,
// CEnviarManutencao and CErroTesteTecladoFim, inlined with their GetInst into fns 11804, 11809 and 11812, which hold
// the screen behind a second stack-pointer prologue (a 64-byte frame) and with no call of CTelasVota::GetInst() before
// it, so free functions, out of line in the object and inlined by binaryen. Evidence, the bodies: the texts, positions,
// fonts (@474888 and @474992, FONTE_TITULO and FONTE_AGUARDE) and order.
// - TelaTeclaErradaTesteTeclado: AdicionaCabecalhoTesteTeclado (fn 3054), "Teste Falhou" at (320, 140), a field over a
//   function (fn 1191) at (320, 210) whose callback is table slot 1106, fn 12903, a captureless lambda:
//   std::format("Falha: Esperada {}, pressionada {}") of api::KeyName of the two keys
//   vota::CEstadoAudio::GetTeclasTesteTeclado returns (its bytes +9 and +10), then the labels of CONFIRMA ('C', "Repetir
//   teste") and CORRIGE ('D', "Prosseguir") through fn 653, AddInputControl (fn 901) after them, its result dropped,
//   and "telaTeclaErradaTesteTeclado" through GetFormularioInterativo (fn 576).
// - TelaEnviarManutencaoTesteTeclado: the header, "Deseja enviar a urna para manutenção?" at (320, 230), the labels
//   "Repetir teste" and "Enviar para manutenção", AddInputControl and "telaEnviarManutencaoTesteTeclado".
// - TelaErroTesteTeclado: an api::CFormBuilder, the status header (5), "Erro no teste do teclado" at (320, 140) in the
//   30-point font, "Por favor, solicite ajuda dos técnicos do TRE" and "para as devidas providências." at (320, 220)
//   and (320, 260) in the 25-point one, and "telaErroTesteTeclado" through GetFormulario (fn 886). Its three texts are
//   named char arrays: the target loads them with i64.load align=3, at @475072, @475104 and @475152 (16-byte aligned,
//   in the run of this file's fonts), which a named array of 16 bytes or more gives (wasm32's large-array alignment,
//   measured: a 46-byte named const char[] is p2align=4 and loaded align=3, a 15-byte one and a 25-byte literal stay
//   p2align=0) and a string literal does not (align=0: fn 11812 scored 59 over 464 rows with the literals, every row an
//   operand, those loads' alignments among them, and 48 over 464 with the arrays). The arrays' names, and their being
//   file-scope constants of an anonymous namespace (a function-local static array gives the same alignment), are
//   chosen.
// The names, their being free functions of vota, the lambda's spelling (a structured binding of the pair) and their
// place after the file's last record are chosen.
CFormInterativoTelaVota TelaTeclaErradaTesteTeclado();
CFormInterativoTelaVota TelaEnviarManutencaoTesteTeclado();
std::shared_ptr<api::IForm<api::IScreen>> TelaErroTesteTeclado();

// The three screens of vota::CRetirarMR, which its constructor builds into +12, +20 and +28 (inlined with GetInst into fn
// 2291, each behind a second stack-pointer prologue: one caller each, inlined by binaryen, so out of line in the object,
// docs/how-to-decompile.md step 3). Each is the status header (5) and centred lines in colours 2 over 1: TelaRetireMR
// three in the 30-point font (@474888) named "telaRetireMR" through GetFormulario (fn 886); TelaLacreTampa three in that
// font and TelaMRModoDemo five in the 25-point one (@474992), each with the label of CONFIRMA ('C', "Continuar" and
// "Prosseguir", fn 653), named "telaLacreTampa" and "telaMRModoDemo" through GetFormularioInterativo (fn 576). Why
// ctelasvota.cpp: both fonts are the ones AdicionaTelaAguarde passes, file constants of ctelasvota.cpp (the reading
// above). No record names them: the names (from the forms' names), their being free functions of vota and their place
// after the file's last record are chosen.
std::shared_ptr<api::IForm<api::IScreen>> TelaRetireMR();
CFormInterativoTelaVota TelaLacreTampa();
CFormInterativoTelaVota TelaMRModoDemo();

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

// Fn 2376 (callers 6580, 6581, 7481 and 7787): a status header, the text centred at (320, 200) in a 35-point font,
// the form's control field and, through api::CInteractiveFormBuilder::AddLabeledInputControl (fn 653), the labels of
// CONFIRMA ('C') and CORRIGE ('D') for each label given, named "telaTextoConfirmaCorrige" by GetFormularioInterativo.
// Its arguments are the text and two std::optional<std::string> its callers build (an engaged flag at +12). It passes
// api::CApplication::s_areaTela itself: through GetAreaTela 653 kept the area as a parameter (213 over 654 rows,
// measured), a call binaryen inlines only after it folds constant parameters (a reading of its passes' order). Defined after GetTelaCargo in
// ctelasvota.cpp with its SFont {35, 0} (@475016; 3059, 3074 and 7787 load it too), places chosen (no record); the
// names, the references and its being a free function of vota are chosen (the file's recorded builders, records
// 1536640-1536768, are static CTelasVota members)
CFormInterativoTelaVota TelaTextoConfirmaCorrige(const std::string& texto, const std::optional<std::string>& confirma,
                                                 const std::optional<std::string>& corrige);

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
//   12040 and 12055 read too: ctelasvota.cpp's FONTE_VERSAO, which CriaTelaQRCodeBU reads as well (a reading, as for
//   FONTE_TITULO). Callers: fns 2380, 6601 and 7787.
// - TelaNeutra (fn 2380): the message's lines (CStringUtils::Split on '&'), each centred at x 320 in the font of the size
//   it is given, the first at 240 + size / 2 - lines * size - size / 4 and the next ones a size and a half apart, over
//   the status header (5), then the location line when bit 0 of its last parameter is set, named "telaNeutra"
//   (GetFormulario, fn 886). The target tests that bit with `i32.const 1; i32.and`, which a bool parameter does not
//   give (it is tested bare: a probe compiled at the tree's flags), so the parameter is an integer; its callers pass 0
//   (6587, 11797) and 1 (6557). The positions' 16-bit values and the step held in an int are the forms that give the
//   target's arithmetic (variants compared in the object; src/units/110-uenux2-singletons.mk). Callers: 6557, 6587, 7787
//   and 11797.
// - TelaPorFavorAguarde (fn 6587): TelaNeutra("Por favor, aguarde...", 35, 0). Callers: 11855 and 11991, the zerésima
//   printing states. The candidates' menu, which vota::CMenuVisualizarCandidatos::StartState (fn 11881) holds behind a
//   second stack-pointer prologue (a 144-byte frame), with no call of CTelasVota::GetInst() before it: a free function,
//   out of line in the object and inlined by binaryen. Evidence, the body: the status header (5), "Visualização de
//   candidatos" at (320, 40) in the 30-point font (@474888, FONTE_TITULO), a menu at (40, 85) in the 25-point one
//   (@474992, FONTE_AGUARDE) through api::AddInputMenuField (fn 3675) with "Selecione um filtro: " and 32767, its items
//   "Por cargo", "Por partido" and "Candidato específico" (api::CInputMenuField::AddItem, fn 1693, with the default
//   callback), each given a std::pair<comum::CAppState*, comum::CAppState*> in its std::any (the typeinfo @1539540
//   11881's std::any_cast names; 11881 copies each pair from a local of its own frame before the screen's prologue,
//   which by-value parameters give, a reading), the labels of CONFIRMA ('C', "Executar opção") and CORRIGE ('D',
//   "Retornar") through fn 653, and "telaMenuVisualizacaoCandidatos" through GetFormularioInterativo (fn 576); it
//   returns the form and the menu. The names, the alias, its being a free function of vota and its place after the
//   file's last record are chosen.
using TOpcaoMenuCandidatos = std::pair<comum::CAppState*, comum::CAppState*>;
std::pair<CFormInterativoTelaVota, std::shared_ptr<api::CInputMenuField>> TelaMenuVisualizacaoCandidatos(
    TOpcaoMenuCandidatos porCargo, TOpcaoMenuCandidatos porPartido, TOpcaoMenuCandidatos candidato);

// The candidate-number filter, which vota::CMenuFiltrarCandidatosPorNumero::StartState (fn 11892) holds behind a
// second stack-pointer prologue (a 240-byte frame), after the call of CVisualizarCandidatos::GetInst().GetCargo()
// (fns 1279, 5951) whose result it takes, and with no call of CTelasVota::GetInst() before it: a free function, out of
// line in its object and inlined by binaryen. Evidence, the body: a copy of comum::CConfiguracaoEleicao::GetCargo's
// md::CCargo (fn 861; the 140 bytes and the two optionals' copies, fns 365 and 374) at +96, the frame's highest offset,
// which the first object a function creates takes (docs/reference/facts/codegen.md C5), the status header (5),
// "Visualização de candidatos" at (320, 40) in the 30-point font (@474888, FONTE_TITULO), "Filtragem por número do
// candidato" at (320, 75) and "Número do " with the cargo's GetNome(SEXO_MASCULINO) (fn 2796, its argument 1) and ": "
// (the tail of " : " @445416) at (320, 215) in the 25-point one (@474992, FONTE_AGUARDE), AdicionaCampoNumerico (fn
// 2383) with the cargo's number of digits (its byte +12) and the flags 1, 0, 0, 1, 0 at (320, 265) in the 30-point
// font, all centred, the labels of CONFIRMA ('C', "Confirmar seleção") and CORRIGE ('D', "Retornar") through fn 653,
// and "telaFiltragemCandidatosPorNumero" through GetFormularioInterativo (fn 576). Why ctelasvota.cpp: it passes the
// two fonts the file's other screens pass, a reading that rests on the fonts being file constants (above).
// AdicionaCampoNumerico is defined in ctelasvota.cpp and not declared here; src/units/110-uenux2-singletons.mk has its
// evidence and the measurements of both. Chosen: the names, the parameter's, the copy's being a named local, its being
// a free function of vota and its place in ctelasvota.cpp (after TelaErroTesteTeclado, past the file's last record).
CFormInterativoTelaVota TelaFiltragemCandidatosPorNumero(const comum::TCargoID idCargo);

void AdicionaLocal(api::CFormBuilder& builder);
std::shared_ptr<api::IForm<api::IScreen>> TelaNeutra(const std::string& mensagem, const int16_t tamanho,
    const int opcoes);
std::shared_ptr<api::IForm<api::IScreen>> TelaPorFavorAguarde();

// The body of the screens that show the urn's QR code (fn 3059) and the location's header it adds (fn 4160), in
// ctelasvota.cpp: use band 4 puts 3059 among this object's functions (3064, record 1585, above it, 3054 below it) and
// band 3 puts 4160 below AdicionaLocal (fn 4161); src/units/110-uenux2-singletons.mk has their places' measurement.
// - AdicionaTelaQRCode (fn 3059; callers 6592, 6595 and 7787, the screens "telaConfirmaImpressaoZeresima" and
//   "telaAntesHorarioZeresima" and CTelasVota's constructor): the status header (5), AdicionaCabecalhoLocal, "RESUMO DA
//   CORRESPONDÊNCIA: " and comum::FormataCodigoCargaResumido (fn 2792) of the general state's correspondence (through
//   the const comum::CAppInfo::GetGeral, fn 457, read before the header) at (320, 200), centred; an
//   api::CImageFieldUpdate at (626, 250), ANCHOR_TOP_RIGHT, refreshed every 15000 ms, over an api::CQRCodeImage of 148
//   (fn 3662, SharedIImage(new X), the __shared_ptr_pointer block @1538404) of a comum::CQRCodeDS of the general
//   state's GetDadosQRCode (fn 5636) with the origin given; the title at (25, 260) in the 35-point font (@475016), the
//   two other texts at (25, 310) and (25, 340) in the 20-point one (@474896) when they are not empty, and "Versão: {}"
//   of api::CApplication::s_versao at (25, 400), left-aligned, and "Dados: {}" of
//   CEstadoGeral::GetResumoHashVersoesPacotes (fn 3703) at (620, 400), right-aligned, in the 15-point one (@475008),
//   colours 2 over 1. Written and not matched: src/units/110-uenux2-singletons.mk has the measurement.
// - AdicionaCabecalhoLocal (fn 4160; callers 3059 and 7787): comum::CConfiguracaoEleicao's name (+8) and its pleito's
//   (+32) at (320, 45) and (320, 80) in the 30-point font (@474888), comum::CLocal's municipality name, "/" and its UF
//   at (320, 120), and "{}: {:04} {}: {:04}" of the translated <ZCSA>, the zone, <SCSA> and the section of the general
//   state's section (CDadoLocal's +12, read as one i64 right after the const GetGeral, before CLocal::GetInst),
//   followed by " ({})" of comum::FormataAgregadasResumidas("{}") (clocal.h) when the location has aggregated sections,
//   at (320, 155), all centred in the 20-point font, colours 2 over 1. CAppInfo::GetInst is called before
//   CConfiguracaoEleicao::GetInst, as the target calls them. No record names them; their names, their parameters'
//   names, the origin's type (comum::CQRCodeDS::EOrigem, whose 2 fn 6592 passes has no enumerator) and their being free
//   functions of vota with external linkage are chosen.
void AdicionaTelaQRCode(api::CFormBuilder& builder, const std::string& titulo, const std::string& mensagem,
                        const std::string& detalhe, comum::CQRCodeDS::EOrigem origem);
void AdicionaCabecalhoLocal(api::CFormBuilder& builder);

} // namespace vota
