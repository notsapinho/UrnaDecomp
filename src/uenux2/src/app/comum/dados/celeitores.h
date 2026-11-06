#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <vector>

#include "api/io/cdatamap.h"
#include "app/comum/dados/celeitordetalhe.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"

namespace comum {

class CEleitorDadosHabilitacao;
struct SQtdeAptos;

namespace md {
class CImpedido;
} // namespace md

// RTTI: comum::CEleitores has two bases, api::CDataMap<CEleitorIdentidade, CEleitorDetalhe> at +4 and
// comum::IDataSourceAptos at +0, listed in that order, and its vtable has one slot, fn 2824. That slot returns the map
// CGeradorBUQRCodeVota's constructor (fn 5603) moves into comum::CGeradorBUQRCode's +404 (cgeradorbuqrcode.h has its
// types). The slot's name, from what the body counts, and its const are chosen; the class has no other member.
class IDataSourceAptos {
public:
    virtual std::map<md::ETipoAbrangencia, SQtdeAptos> QuantidadeAptosPorAbrangencia() const = 0;
};

// Recovered: the layout, from the destructor (fn 5773), which is out of line and frees, in this order, a tree of
// strings at +112 (fn 2265), three vectors of strings at +88, +76 and +64, a tree at +52 (fn 1594, the tree
// CConfiguracaoEleicao holds at +604), strings at +32 and +20 and the tree at +4. No vptr store opens it, so the class
// is final. The base's 28 bytes end at +32, so what lies above them is this class's own. ValidaIdentidadesEleitor (fn
// 5765) compares the word at +100 with the voter's identities' type, so it has that type. The map at +112 is keyed by
// CEleitorIdentidade and holds one: fns 2264 and 2225 find in it with that key (fn 1703, the find of every map so
// keyed) and pass the value at +32 of the node found, a CEleitorIdentidade, as the key of the base's find; its destroy
// (fn 2265) frees the strings at +16 and +32 of each node. The members' names are chosen; the other words between them
// have no reader here. LocalizaEleitor (names chosen), both overloads out of line in celeitores.cpp: the string one is
// fn 2264 (five callers, no record), and the CEleitorIdentidade one has no target function of its own. 2264 holds it as
// clang inlines it, and fn 2225 (cinformacaothreadoperador.cpp) as binaryen inlines its one call, a reading (how-to
// step 3's sign: the record's address tested after it); defined here, clang inlines it into 2225 too and folds that
// test (src/units/50-uenux2-cinformacaothreadoperador.mk has the measurement). Its record lookup is CDataMap::Find (the
// cursor at +16 set, the record's address returned). 2264 builds the identity as a named local: the target frees the
// copy of the string before the two finds, which a temporary in the call gives after them (measured on the object of
// each form).
class CEleitores final : public api::CDataMap<md::CEleitorIdentidade, CEleitorDetalhe>, public IDataSourceAptos {
public:
    ~CEleitores();

    static CEleitores& GetInst();

    // fn 2824, slot 0: the map's three keys (every md::ETipoAbrangencia) start at zero, and each record with no
    // impediment counts once at its voter's coverage and at each wider one, in the first count without a temporary
    // transfer and in the second with one (the IsTTE word, as QuantidadeAptos reads it).
    std::map<md::ETipoAbrangencia, SQtdeAptos> QuantidadeAptosPorAbrangencia() const override;

    CEleitorDetalhe* LocalizaEleitor(const md::CEleitorIdentidade& identidade);
    CEleitorDetalhe* LocalizaEleitor(const std::string& identificador, ecourna::app::dados::ETipoIdentificadorEleitor tipo);

    // fn 5761, records celeitores.cpp:301, :305 and :358, which give the signature and its const: with records and no
    // dynamic data yet, one md::CEleitorDinamico per record (state 0 when the set at +52 holds the voter's coverage or
    // a wider one, else 1), then the table of the database file named: written when it is empty, else both lists sorted
    // by voter and compared (code 7839 when they differ). Its one target caller is fn 6737, twice, with two database
    // files' paths; src/units/383-uenux2-celeitores-dinamicos.mk has the evidence and the forms measured.
    void DynamicCreate(const std::string& banco) const;

    // CompleteLoad: the records celeitores.cpp:205, :219 and :238 give the signature (codes 7834 to 7836). It has no
    // target index: fn 6734 (vota::CEstadoAudio::CarregaEleitores, cestadoaudio.h) holds it behind an 864-byte prologue
    // inside the 48-byte frame of the overload with no parameter, which passes GetPathEstatico(FLASH_INTERNA)'s string
    // and GetArquivoBancoDadosInterno() (both inlined by binaryen). The overload's existence is that frame; its being a
    // member overload and its name are chosen. src/units/386-uenux2-carregaeleitores.mk has the evidence and the forms
    // measured.
    void CompleteLoad(const std::string& diretorio, const std::string& banco);
    void CompleteLoad();

    void MarcaEleitorFoiHabilitado(const CEleitorDadosHabilitacao& dados);
    // MarcaVotou: the records celeitores.cpp:456 and 460 (vota::CSincronismoOperador::StartState, target fn 10210, holds
    // it inlined by binaryen, one call). It counts the voter at +104 (an increment of that word). The counter's name is
    // chosen; its type is the one GetComparecimento's readers give (below).
    void MarcaVotou();
    // fn 2822: the records with dynamic data whose comparecimento state is 3 (the state MarcaEleitorFoiHabilitado
    // refuses as "Eleitor já votou") and whose kind of enabling is 0 (the kind md::CEleitorDinamico::HabilitaSemBiometria
    // stores). One of its four callers, fn 10699, formats the count into "Habilitação sem biometria: {}", which
    // the name is chosen from; the result's 16 bits are the body's mask; its const is chosen, as no record gives it.
    ueword QuantidadeHabilitacaoSemBiometria() const;
    // fns 2821 and 1935: the same count for the kinds of enabling 1 and 2 (the kinds md::CEleitorDinamico's
    // HabilitaPorBiometria and HabilitaPorMesario store). The target holds each as a 9-byte thunk of one body binaryen
    // merged, fn 6034, which takes the kind as its second parameter: 2821 passes 1, 1935 passes 2. Of their callers,
    // fns 10701 and 10700 format the counts into "Habilitação biométrica: {}" and "Habilitação biográfica: {}", which
    // the names are chosen from; the rest is as for QuantidadeHabilitacaoSemBiometria. Their place after it in
    // celeitores.cpp is chosen, within what their bands allow (2821 after 2822 in band 4, 1935 after MontaCaminhos, fn
    // 1936, in band 6).
    ueword QuantidadeHabilitacaoBiometrica() const;
    ueword QuantidadeHabilitacaoBiografica() const;
    // fn 2823: the records with no impediment (CEleitorDetalhe::SemImpedimento, fn 2266), counted apart by whether the
    // voter is on a temporary transfer (md::CEleitorDecorator's word at +48, which IsTTE tests): two 16-bit counts the
    // body returns through the result's address, the first for the voters with no transfer. It returns a SQtdeAptos
    // (cgeradorbuqrcode.h): RTTI types four std::function<comum::SQtdeAptos()> whose call operator is fn 2881, and 2881
    // passes its own result's address straight to 2823 (`f2823(p0, f326())`), where a result of another type would take
    // a temporary and a copy (a reading). Its callers are fns 652 (whose vota::MontaTelaVotacao, inlined by binaryen,
    // adds the two), 2881, 11242 and 12110.
    // Band 4 puts it between slot 0 (fn 2824) and QuantidadeHabilitacaoSemBiometria (fn 2822). The function's name and
    // its const are chosen.
    SQtdeAptos QuantidadeAptos() const;
    void ValidaIdentidadesEleitor(const md::CEleitorDecorator& eleitor) const;
    // The unsigned word at +104, a count of the voters who voted (a reading of its readers): fn 12098
    // (vota::CGravaResultado's slot 2) compares it with comum::CRdvVota::Comparecimento() (fn 1269),
    // vota::CSincronismoOperador's slot 2 (fn 10210) adds one to it, and vota::impl::CInformacaoThreadOperador's
    // slots 16 and 19 (fns 10569, 10566) read it in place; 10569 formats it as an unsigned (argument type 6) where it
    // stands for 1269's result. The member's and the accessor's names and the accessor's being inline in the class are
    // chosen.
    unsigned int GetComparecimento() const { return m_qtdVotaram; }
    // Record celeitores.cpp:497 (7847); slot 2 of vota::CEleitorVotando (fn 7377) holds it behind a 32-byte prologue.
    md::ETipoAbrangencia GetCurrentAbrangenciaEleitor() const;
    // The current record, read through the cursor (+16) with no test of the map's end: the report of
    // comum::CGeradorRelEleitoresHabBiograf (held by target fn 12105) walks the records with Reset and Next (fn 5601)
    // and reads each in place, with no call of GetCurrent (fn 656). The accessor, its name and its being inline here
    // are chosen, as CJustificador's GetTituloCorrente is.
    const CEleitorDetalhe& GetDetalheCorrente() const { return m_corrente->second; }
    // fn 1393: the current record's CEleitorDetalhe::GetBiometria (fn 1937), returned through the result's address. Its
    // six callers (fns 10425, 10465, 10474, 10478, 10500, 10512, vota's identification states) call it on
    // CEleitores::GetInst()'s result (10500: `f1393(frame, f326())`), so it takes the singleton as `this`: a member, a
    // reading. No record, slot or RTTI names it: its name, after GetCurrentAbrangenciaEleitor's, and its const are
    // chosen; its file is a reading (src/units/291-uenux2-biometria-eleitor.mk).
    md::CBiometriaEleitor GetCurrentBiometriaEleitor() const;

private:
    // fn 5767: the impediments read from each file of a list, through a std::function over a lambda (RTTI of its
    // __func, vtable @1559564, names this member and its parameter), appended in the files' order. No `this`: the
    // target passes the list alone. Its being private is chosen.
    static std::vector<md::CImpedido> GetEleitoresImpedidos(const std::vector<std::string>& arquivos);

    // fn 5772: the voters of the urn's static files, sorted. Its lambda's __func typeinfo (string 500386, a local `$_0` of
    // `ZN5comum10CEleitores21GetEleitoresEstaticosERKNSt3__212basic_string...`, no K: not const) names the member and
    // its parameter, and it reads `this`: the lists at +76 and +64 (each prefixed with the directory by MontaCaminhos,
    // fn 1936, and read through LeArquivos, fn 5771) and the type at +100 it decorates each voter with. Its callers are
    // CompleteLoad (held by fn 6734, src/units/386-uenux2-carregaeleitores.mk) and StaticLoad (held by fn 7787, not
    // written). Its being private is chosen.
    std::vector<md::CEleitorDecorator> GetEleitoresEstaticos(const std::string& diretorio);

    // fn 5764, record celeitores.cpp:719, which gives the signature: the voter's record, with the impediments of the
    // entry of the sorted list at the index when its identity is the voter's (the index then moves on), none when it
    // is beyond the voter's, and code 7851 when the voter's is beyond it; with the voter's dynamic data when given. The
    // wasm has no `this`: binaryen dropped the one it never reads. Its being private is chosen.
    CEleitorDetalhe LoadEleitorDetalhe(const md::CEleitorDecorator& eleitor, const std::vector<md::CImpedido>& impedidos,
        size_t& indice, const md::CEleitorDinamico* dinamico) const;

    // GetCurrentAbrangenciaEleitor passes the string at +32 and the word at +44 to
    // md::CEleitorDecorator::GetAbrangencia (fn 3721), which compares them with the voter's temporary transfer's
    // string and word: the urn's state and
    // municipality by a reading (md::CAbrangencia holds a state and a municipality so). The names and the word's type
    // are chosen; the word at +48 has no reader here.
    std::string m_uf;
    uedword m_municipio;
    int m_naoRecuperado2;
    // The set at +52 holds coverages, a reading: DynamicCreate (fn 5761) looks for 0, 1 and 2 in it and tests the
    // result against GetAbrangencia's 0, 1 and 2, where the identifier types run 1 to 3, and its destroy, fn 1594, is
    // CConfiguracaoEleicao's set's at +604 too (cconfiguracaoeleicao.h). The name is chosen.
    std::set<md::ETipoAbrangencia> m_tipos;
    std::vector<std::string> m_lista1;
    std::vector<std::string> m_lista2;
    std::vector<std::string> m_lista3;
    ecourna::app::dados::ETipoIdentificadorEleitor m_tipoIdentificadorPrincipal;
    unsigned int m_qtdVotaram;
    // The byte at +108: CompleteLoad stores 1 there last (fn 6734's rows); no reader of it is read here. Its name and
    // its type, bool for a byte the body stores, are chosen.
    bool m_completo;
    std::map<md::CEleitorIdentidade, md::CEleitorIdentidade> m_identidades;

    static std::unique_ptr<CEleitores> s_instance;
    static std::mutex s_mutex;
};

// The voter's data a screen formats, each read from CEleitores's current record (target fns 11529, 11528, 11527, 11526,
// reached by table slot only). Their records in celeitores.cpp name the classes and Text's signatures; that the classes
// hold nothing else, that they are declared here and the parameter's name are chosen.
class CEleitorDadoNomeParaUrna {
public:
    static std::string Text(const std::string& formato);
};

class CEleitorDadoSequencial {
public:
    static std::string Text(const std::string& formato);
};

class CEleitorDadoSecao {
public:
    static std::string Text(const std::string& formato);
};

class CEleitorDadoTTE {
public:
    static std::string Text();
};

// The path of "uenux.db" in the work directory of the internal flash (target fn 2826) and of the external one (fn
// 5762), as a string: CPath::GetPathTrab of that flash with the name appended. No record, slot or RTTI names them;
// their names and their being free functions (they read no class state) are chosen. 5762's band puts it in
// celeitores.cpp; 2826 is here by its pair with 5762 and CompleteLoad's call, a reading. Each is a thunk of a body
// binaryen merged with crdv.h's function of the same flash: 2826 and 1551 call 6036, 5762 and 1701 6035.
std::string GetArquivoBancoDadosInterno();
std::string GetArquivoBancoDadosExterno();

} // namespace comum
