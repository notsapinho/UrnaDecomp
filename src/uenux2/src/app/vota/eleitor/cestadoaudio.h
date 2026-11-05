#pragma once

// Reconstruction's note, not TSE's text: the singleton of fn 509, 12 bytes with no vtable, so no RTTI names it. The target
// shows these of the object, and more than audio:
// - +0 is a byte: 7787 tests it with load8_u and sets it with store8 around the block that loads the urn's data.
// - +1 is a byte: 6734 tests it first and sets it last, and that body holds comum::CEleitores::CompleteLoad's records.
// - +4 is the mode. Not 2 is audio on (10539 returns "AUDIO ATIVADO" for it and 13424 "Audio ativado"), 215 tests 0 and
//   3078 tests 1, and vota::CThreadEleitor's fn 4349 sets 0, 1 and 2 through fns 6745, 6743 and 4195, for the messages
//   8, 9 and 10. Each of the three is a function of its own that stores its constant at +4 and that 4349 calls twice:
//   out of line here, where no caller of this TU inlines them. Their names are chosen.
// - +8 is a byte: 7787 tests it and sets it around the block that starts with the literal "uenux.db".
// - +9 and +10 are bytes: the key the keyboard test expected and the key pressed. vota::testeteclado::CTesteTeclado::
//   ProcessInput (fn 11804) stores the key read at +10 and the expected one (the screen map's char) at +9 when they
//   differ, and the lambda of the failure screen (fn 12903) copies both into its frame and formats "Falha: Esperada {},
//   pressionada {}" of their KeyName, +9 first.
// The object's next members take it as `this`, and neither is written: 6734, which 7787 and 11865 call on it, and 6737,
// which 11865 calls on it and votaInit reaches through table slot 41, and which reads nothing of it. None of them names
// the class. Chosen: the class's name, this path, every member's name, the enumerators, and bool for +0, +1 and +8, which
// hold one-shot flags: char gives the same object.

#include <memory>
#include <mutex>
#include <utility>

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

    void SelecionaModo0();
    void SelecionaModo1();
    void Desativa();

    // The tests of modes 0 and 1: fns 215 (8 bytes that SQLite's pragmaVtabEof, a twin, shares) and 3078, which
    // vota::CMostraEleitorVotando::SalvaHabilitacaoEleitor (inlined into fn 10425) calls four times each on
    // GetInst()'s result for the audio word of comum::CEleitorDadosHabilitacao: 0 in mode 0, else 1 in mode 1, else 2.
    // Out of line here, where no caller of this TU inlines them, as the setters; their names are chosen.
    bool Modo0Selecionado() const;
    bool Modo1Selecionado() const;

    // Out of line in cestadoaudio.cpp, one caller each (fns 11804 and 12903), which hold them inlined by binaryen: the
    // getter's std::pair, returned through the caller's frame, is the copy of +9 and +10 into fn 12903's frame (two
    // store8 at +30 and +31, then two signed loads), a reading of that shape; inline forms were not measured. The
    // setter's two stores come out +10 first in fn 11804, as written here (whole-link score: operand rows only). The
    // names, the pair, the parameters and the members' names are chosen.
    void SetTeclasTesteTeclado(char esperada, char pressionada);
    std::pair<char, char> GetTeclasTesteTeclado() const;

private:
    CEstadoAudio();

    bool m_dadosCarregados;
    bool m_eleitoresCarregados;
    EModo m_modo;
    bool m_bancoCarregado;
    char m_teclaEsperada;
    char m_teclaPressionada;

    static std::unique_ptr<CEstadoAudio> s_inst;
    static std::mutex s_mutex;
};

} // namespace vota
