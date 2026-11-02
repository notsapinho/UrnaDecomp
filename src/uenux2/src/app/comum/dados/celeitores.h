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

// RTTI: comum::CEleitores has two bases, api::CDataMap<CEleitorIdentidade, CEleitorDetalhe> at +4 and
// comum::IDataSourceAptos at +0, listed in that order, and its vtable has one slot, fn 2824. Slot 0's name is chosen.
class IDataSourceAptos {
public:
    virtual void Slot0() const = 0;
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

    void Slot0() const override;

    CEleitorDetalhe* LocalizaEleitor(const md::CEleitorIdentidade& identidade);
    CEleitorDetalhe* LocalizaEleitor(const std::string& identificador, ecourna::app::dados::ETipoIdentificadorEleitor tipo);

    void MarcaEleitorFoiHabilitado(const CEleitorDadosHabilitacao& dados);
    // MarcaVotou: the records celeitores.cpp:456 and 460 (vota::CSincronismoOperador::StartState, target fn 10210, holds
    // it inlined by binaryen, one call). It counts the voter at +104 (an increment of that word). The counter's name is
    // chosen; its type is the one GetComparecimento's readers give (below).
    void MarcaVotou();
    // fn 2822: the records with dynamic data whose comparecimento state is 3 (the state MarcaEleitorFoiHabilitado
    // refuses as "Eleitor já votou") and whose kind of enabling is 0 (the kind md::CEleitorDinamico::HabilitaSemBiometria
    // stores). One caller, fn 10699, formats the count into "Habilitação sem biometria: {}", which the name is chosen
    // from; the result's 16 bits are the body's mask.
    ueword QuantidadeHabilitacaoSemBiometria() const;
    void ValidaIdentidadesEleitor(const md::CEleitorDecorator& eleitor) const;
    // The unsigned word at +104, a count of the voters who voted (a reading of its readers): fn 12098
    // (vota::CGravaResultado's slot 2) compares it with comum::CRdvVota::Comparecimento() (fn 1269),
    // vota::CSincronismoOperador's slot 2 (fn 10210) adds one to it, and vota::impl::CInformacaoThreadOperador's
    // slots 16 and 19 (fns 10569, 10566) read it in place; 10569 formats it as an unsigned (argument type 6) where it
    // stands for 1269's result. The member's and the accessor's names and the accessor's being inline in the class are
    // chosen.
    unsigned int GetComparecimento() const { return m_qtdVotaram; }

private:
    std::string m_arquivoDinamico;
    int m_naoRecuperado2[2];
    std::set<ecourna::app::dados::ETipoIdentificadorEleitor> m_tipos;
    std::vector<std::string> m_lista1;
    std::vector<std::string> m_lista2;
    std::vector<std::string> m_lista3;
    ecourna::app::dados::ETipoIdentificadorEleitor m_tipoIdentificadorPrincipal;
    unsigned int m_qtdVotaram;
    int m_naoRecuperado3;
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

} // namespace comum
