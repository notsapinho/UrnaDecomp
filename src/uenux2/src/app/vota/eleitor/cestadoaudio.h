#pragma once

// Reconstruction's note, not TSE's text: the singleton of fn 509, 12 bytes with no vtable, so no RTTI names it. Its
// callers test +4: below 2 the audio is on (10539 returns "AUDIO ATIVADO" for it and 13424 "Audio ativado"), and
// CThreadEleitor::ProcessarEntrada (4349) sets 0, 1 and 2 through fns 6745, 6743 and 4195. Everything here is chosen from
// that: the class's name, this path, every member's name, the enumerators, and the widths of +0 and +8 (16-bit stores
// of 0 that could be two bytes each). +9 and +10 are bytes: 11804 stores them and 12903 loads them.

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

    short m_campo0;
    EModo m_modo;
    bool m_campo8;
    char m_campo9;
    char m_campo10;

    static std::unique_ptr<CEstadoAudio> s_inst;
    static std::mutex s_mutex;
};

} // namespace vota
