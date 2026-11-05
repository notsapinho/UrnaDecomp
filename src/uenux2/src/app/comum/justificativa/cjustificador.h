#pragma once
#include <memory>
#include <mutex>
#include <string>

#include "api/io/cdatamap.h"
#include "app/comum/justificativa/cjustificadordetalhe.h"
#include "app/comum/justificativa/servico/cjustificadorservico.h"
#include "ecourna/app/dados/cnumeroinscricaoeleitoral.hpp"

namespace comum {

// The justified voters, by their titulo. The name is the records' (cjustificador.cpp lines 55 and 83). At +0 is the
// api::CDataMap<ecourna::app::dados::CNumeroInscricaoEleitoral, CJustificadorDetalhe> whose Add and Next records name it,
// which fn 3742, the constructor, builds with the name "CJustificador". Recovered: the layout, 40 bytes (fn 1391
// allocates 40 before it calls 3742), with a comum::servico::CJustificadorServico at +28, whose vptr 3742 stores and
// whose destructor (fn 3740) the destructor (fn 2810) calls on +28. The map as a base and not a member at +0 is a choice,
// as for CRegistradorMesario (src/units/113-uenux2-cdatamap.mk). The path of this header and the member's name are
// chosen. Fn 11474 is not written.
//
// The singleton (fn 1391, GetInst, a chosen name) is the shape of comum::CFotos's (fn 2819): under the mutex at
// 1838988, when the pointer at 1839012 is empty, it allocates 40 bytes, calls 3742 and stores the new object there. The
// destructor (fn 2810) is out of line: 1391 and the pointer's exit destructor (fn 11477, 37 B) keep a call of it, the
// shape src/units/110-uenux2-singletons.mk measures for an out-of-line destructor. s_inst and s_mutex are chosen names.
class CJustificador
    : public api::CDataMap<ecourna::app::dados::CNumeroInscricaoEleitoral, CJustificadorDetalhe> {
public:
    CJustificador();
    ~CJustificador();

    static CJustificador& GetInst();

    // The título of the current record, the map's key: CJustificadorDadoTitulo::Text (fn 11475) reads the cursor at +12
    // and calls GetNumero (fn 1139, a twin) on the node's key. The name is chosen.
    const ecourna::app::dados::CNumeroInscricaoEleitoral& GetTituloCorrente() const { return m_corrente->first; }
    // How many voters are justified, the map's size (+8): vota::CReinicioVotacao::StartState (fn 11835) tests it for 0
    // in place. The name, and that it is an inline accessor, are chosen.
    std::size_t QuantidadeJustificados() const { return m_registros.size(); }

    // The records' members (cjustificador.cpp:55 and :83), each held by fn 10590 behind a stack frame of its own.
    // Justifica throws 8800 when Find, which moves the cursor, finds the título, and adds the record otherwise; the
    // overload over a std::string, a function of its own (a 32-byte frame that builds the key), is a reading, and its
    // name and signature are chosen. SaveCurrentInternal throws 8801 on an empty map and hands the servico the
    // cursor's record. src/units/283-uenux2-app-vota-operador-justificativa.mk has the forms.
    void Justifica(const ecourna::app::dados::CNumeroInscricaoEleitoral& titulo, ueword ano);
    void Justifica(const std::string& titulo, ueword ano);
    void SaveCurrentInternal();

private:
    servico::CJustificadorServico m_servico;

    static std::unique_ptr<CJustificador> s_inst;
    static std::mutex s_mutex;
};

// The current justified voter's título, a screen's text (fn 11475, reached only by table slot 2949). The class's name
// and Text's signature are the record's (cjustificador.cpp:104); that the class holds nothing else and is declared here
// are chosen.
class CJustificadorDadoTitulo {
public:
    static std::string Text();
};

} // namespace comum
