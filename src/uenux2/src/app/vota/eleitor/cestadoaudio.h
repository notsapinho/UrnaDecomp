#pragma once

// Reconstruction's note, not TSE's text: the singleton of fn 509, 12 bytes with no vtable, so no RTTI names it. The target
// shows these of the object, and more than audio:
// - +0 is a byte: 7787 tests it with load8_u and sets it with store8 around the block that loads the urn's data.
// - +1 is a byte: 6734 tests it first and sets it last, and that body holds comum::CEleitores::CompleteLoad's records.
// - +4 is the mode. Not 2 is audio on (10539 returns "AUDIO ATIVADO" for it and 13424 "Audio ativado"), 215 tests 0 and
//   3078 tests 1, and CThreadEleitor::ProcessarEntrada (4349) sets 0, 1 and 2 through fns 6745, 6743 and 4195.
// - +8 is a byte: 7787 tests it and sets it around the block that starts with the literal "uenux.db".
// - +9 and +10 are bytes: 11804 stores them and 12903 loads them.
// The object's next members take it as `this`, and neither is written: 6734, which 7787 and 11865 call on it, and 6737,
// which 11865 calls on it and votaInit reaches through table slot 41, and which reads nothing of it. None of them names
// the class. Chosen: the class's name, this path, every member's name, the enumerators, and bool for +0, +1 and +8, which
// hold one-shot flags: char gives the same object.

#include <memory>
#include <mutex>

namespace vota {

class CEstadoAudio {
public:
    enum EModo {
        MODO_0 = 0,
        MODO_1 = 1,
        MODO_DESATIVADO = 2,
    };

    static CEstadoAudio& GetInst();

    bool Ativo() const { return m_modo != MODO_DESATIVADO; }

private:
    CEstadoAudio();

    bool m_dadosCarregados;
    bool m_eleitoresCarregados;
    EModo m_modo;
    bool m_bancoCarregado;
    char m_campo9;
    char m_campo10;

    static std::unique_ptr<CEstadoAudio> s_inst;
    static std::mutex s_mutex;
};

} // namespace vota
