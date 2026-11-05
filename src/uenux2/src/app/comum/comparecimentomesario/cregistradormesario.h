#pragma once

#include <map>
#include <memory>
#include <mutex>

#include "api/io/cdatamap.h"
#include "app/comum/comparecimentomesario/md/ccomparecimentomesario.h"
#include "app/comum/comparecimentomesario/servico/ccomparecimentomesarioservico.h"

namespace comum {

// The record of SaveCurrentInternal (cregistradormesario.cpp:85, held by fn 10337) names the class and the file, and
// the literal fn 815 gives the map as its name is the class's. Recovered: the object fn 815 builds, 52 bytes: the map
// of comparecimentos at +0, the section's mesarios by identity at +28, a servico::CComparecimentoMesarioServico at +40
// (vptr 1595676); and the singleton's std::mutex (1909908) and std::unique_ptr (1909932), which fns 815 and 2221 read
// and the exit destructors 10309 and 10310 destroy. The constructor is in the class, since fn 815 holds it inlined (an
// out-of-line one in the .cpp would stay a call at -fPIC, docs/reference/facts/codegen.md C6: a reading, not tried
// here). The destructor is out of line in the .cpp: 815 and 10310 call fn 5380 and then free this, the shape of a
// destructor their TU defines (docs/reference/facts/reading.md R5); an implicit one is not tried.
// QuantidadeMesariosInicio and QuantidadeMesariosFim (fns 3606 and 2727) count the comparecimentos of period 1 and of
// period 2; their caller 10795 compares the count unsigned, and 5387 formats it as an unsigned argument. Chosen: the
// names Registra, AtualizaMesarioSecao, GetInst, HasInst, the two Quantidade*, m_mesariosSecao, m_servico, s_inst and
// s_mutex; std::size_t among the unsigned types of that width; GetInst's reference for a pointer; the private
// constructor; this header's path. CDataMap as a base is a choice: as a member at +0 the bytes are the same.
class CRegistradorMesario : public api::CDataMap<md::CComparecimentoMesarioPK, md::CComparecimentoMesario> {
public:
    static CRegistradorMesario& GetInst();
    static bool HasInst();

    ~CRegistradorMesario();

    void Registra(const md::CComparecimentoMesario& comparecimento);
    std::size_t QuantidadeMesariosInicio() const;
    std::size_t QuantidadeMesariosFim() const;

    // Hands the current record to the servico, after a test that the map holds one: its record (cregistradormesario.cpp:85,
    // the throw's) names it, and fn 10337 (IGestorDadoMesario::StartState) holds it inlined by binaryen, a 16-byte frame of
    // its own. Its being public, called with no wrapper, is chosen.
    void SaveCurrentInternal();

    // The three maps vota::CRegistraDigitalOperador's searches walk (fn 10451 holds each behind a frame of its own,
    // binaryen's inlining): the section's mesarios with a finger of habilitation (m_mesariosSecao's records whose
    // dedo_habilitacao is not 0), those without one, and the comparecimentos of mesarios not of the section, keyed by
    // their identity. Each copies what it keeps into a new map through a std::insert_iterator, whose hint is the node
    // after the last one inserted (the target's emplace calls, fn 5376 for the first two, take it so), and visits the
    // records as a filter_view does: the first kept one, then the next kept one after each insertion. Their names,
    // their being const members and the ranges' spelling are chosen; std::ranges::copy over the views gives those
    // loops.
    std::map<md::CEleitorIdentidade, md::CComparecimentoMesario> GetMesariosSecaoComBiometria() const;
    std::map<md::CEleitorIdentidade, md::CComparecimentoMesario> GetMesariosSecaoSemBiometria() const;
    std::map<md::CEleitorIdentidade, md::CComparecimentoMesario> GetMesariosForaSecao() const;

private:
    CRegistradorMesario() : CDataMap("CRegistradorMesario") {}

    void AtualizaMesarioSecao(const md::CComparecimentoMesario& comparecimento);

    std::map<md::CEleitorIdentidade, md::CComparecimentoMesario> m_mesariosSecao;
    servico::CComparecimentoMesarioServico m_servico;

    static std::unique_ptr<CRegistradorMesario> s_inst;
    static std::mutex s_mutex;
};

} // namespace comum
