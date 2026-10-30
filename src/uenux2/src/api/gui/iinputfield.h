#pragma once

// api::IInputField<MEDIA>: RTTI gives IInputField<IScreen> and IInputField<IScreenMT>, each an si_class of the
// IFormField of its media (ledger/classes.json), and the __func of the constructor's lambda gives the constructor's
// parameters (std::shared_ptr<IInputValidation> const&, unsigned long, five bools). The path (the class name in lower
// case, beside the recorded cinputfield.h) is chosen.
//
// The vtables (IScreen @1538844, 13 slots; IScreenMT @1580576, 11) hold, after the media's IFormField slots: Show and
// Hide (slots 3 and 4, fns 6327 and 6324, one body for both media), Refresh and SetForm inherited, then three slots of
// this class. The first is `virtual EInputResult Read(IInput &)`: fn 10894, CInputMenuField's override in that slot,
// has the record (cinputmenufield.cpp 419:21). The last is SetLength(size_t): fn 12387, CInputField<CFramedText>'s
// override, has the record (cinputfield.h 148:13). The middle one, fn 6317, has no record, and Clear is chosen from its
// body.
//
// The layout comes from the constructor (fn 2024 for IScreen, fn 3673 for IScreenMT) and the destructor:
//   +24      the text, a std::string; the constructor reserves the length argument there
//   +36/+40  the validation, a copy of the constructor's shared_ptr
//   +44      the length argument, which the mangled name gives as an unsigned long
//   +48, +49 bytes the constructor sets to 0 and 1 (`i32.store16 256`). Hide stores 0 in +48, and Show tests it. The
//            timer's lambda (fn 6306) flips +49 unless the text is full, and CInputField's Draw (fn 12438) reads both
//            to draw the cursor. Only that use and their size are evidence: the bools are chosen
//   +50..+54 the five bool parameters, in order
//   +55      the last key read, a byte Read stores and compares; the constructor zeroes it
//   +56/+60  a std::shared_ptr of api::ITimer: the constructor gets it from slot 0 of ITimerScheduler::GetInst() (fn
//            1259), with 600 ms and the lambda, and the body calls slots 2, 3 and 4 (Start, Stop, IsRunning)
//
// Names: every data member, the five parameters, Clear and the enumerators of EInputResult are chosen. The records
// print EInputResult unqualified, so its scope is chosen too (docs/reference/facts/reading.md §R11), and its values are
// the ones Read returns. The bools' names say what Read does with each; keys 66, 67 and 68 are the ones fn 653 maps to
// the bits of CInputFieldControl's constructor. A reading of Read's body, not a recovered text.
//
// The destructor (D2 fn 4021 for IScreen, fn 5517 for IScreenMT, thunks of binaryen's fn 6061) stops the timer if it is
// running and has a D0 only in derived classes, which call it (fn 6328, f136(f4021(p0))). It is written in the class.
// `inline` there gives the same functions, and so does an early return; the body is what the bytes settle.
// Forms that give the same functions, each compiled and compared by function with the object-local numbers masked:
// Show as nested ifs, an early return or `m_length > 0`; Clear with `size() != 0` or an early return; SetLength with an
// early return; Read as `for (;;)` with the test first, `!(a && b)` for the test of a full text and `+=` for push_back;
// the lambda with `^= true`. Written as below by choice. Forms that do not: Read with the `C` test's operands swapped,
// with the `B` test's order changed, and with the two branches of the `D` case the other way round; so those orders are
// evidence.
//
// The constructor is written and no function of this tree's link holds it: it calls ITimerScheduler::GetInst, which has
// no body here, so only functions the link drops reach it. Nothing has compared it with fns 2024 and 3673. Read
// (fns 6319, 11024) stays `unresolved` although its bytes are the target's: see src/units/92-uenux2-iinputfield.mk.

#include <chrono>
#include <cstddef>
#include <memory>
#include <string>

#include "api/gui/iform.h"
#include "api/gui/iformfield.h"
#include "api/gui/iinputvalidation.h"
#include "api/hwil/iinput.h"
#include "api/util/itimer.h"
#include "api/util/itimerscheduler.h"

namespace api {

enum EInputResult {
    INPUT_BRANCO = 3,
    INPUT_CORRIGE = 5,
    INPUT_CONFIRMA = 9,
    INPUT_SEM_TECLA = 13,
};

/**
 * Campo de entrada de um formulário: guarda o texto digitado.
 */
template <typename MEDIA>
class IInputField : public IFormField<MEDIA> {
public:
    IInputField(const std::shared_ptr<IInputValidation>& validation, size_t length, bool confirmaAoCompletar,
                bool corrigeLimpa, bool aceitaConfirma, bool aceitaBranco, bool corrigeSai)
        : m_validation(validation),
          m_length(length),
          m_confirmaAoCompletar(confirmaAoCompletar),
          m_corrigeLimpa(corrigeLimpa),
          m_aceitaConfirma(aceitaConfirma),
          m_aceitaBranco(aceitaBranco),
          m_corrigeSai(corrigeSai),
          m_timer(ITimerScheduler::GetInst().CreateTimer(std::chrono::milliseconds(600), [this] {
              if (m_texto.size() != m_length) {
                  m_cursor = !m_cursor;
                  this->Invalidate();
              }
          }))
    {
        m_texto.reserve(length);
    }

    ~IInputField() override
    {
        if (m_timer->IsRunning()) {
            m_timer->Stop();
        }
    }

    void Show() override
    {
        if (m_ativo && m_length != 0) {
            m_timer->Start();
        }
    }

    void Hide() override
    {
        m_timer->Stop();
        m_ativo = false;
    }

    virtual EInputResult Read(IInput& input);

    virtual void Clear()
    {
        if (!m_texto.empty()) {
            m_texto.clear();
            this->Invalidate();
        }
    }

    virtual void SetLength(size_t length)
    {
        if (length != m_length) {
            m_texto.clear();
            m_length = length;
            this->Invalidate();
        }
    }

    const std::string& GetTexto() const { return m_texto; }

protected:
    std::string m_texto;
    std::shared_ptr<IInputValidation> m_validation;
    size_t m_length;
    bool m_ativo = false;
    bool m_cursor = true;
    bool m_confirmaAoCompletar;
    bool m_corrigeLimpa;
    bool m_aceitaConfirma;
    bool m_aceitaBranco;
    bool m_corrigeSai;
    char m_ultimaTecla = 0;
    std::shared_ptr<ITimer> m_timer;
};

template <typename MEDIA>
EInputResult IInputField<MEDIA>::Read(IInput& input)
{
    while (input.HasKey()) {
        m_ultimaTecla = input.GetKey();

        if (m_texto.size() != m_length && m_validation->isValidChar(m_ultimaTecla)) {
            m_texto.push_back(m_ultimaTecla);
            this->Invalidate();
        }

        if (m_aceitaConfirma && m_ultimaTecla == 'C') {
            if (m_validation->isValid(m_texto)) {
                return INPUT_CONFIRMA;
            }
            Clear();
        }

        if (m_ultimaTecla == 'D') {
            if (m_texto.empty()) {
                return INPUT_CORRIGE;
            }

            if (m_corrigeLimpa) {
                Clear();
                if (m_corrigeSai) {
                    return INPUT_CORRIGE;
                }
            } else {
                m_texto.pop_back();
                this->Invalidate();
            }
        }

        if (m_texto.size() == m_length && (!m_confirmaAoCompletar || m_ultimaTecla == 'C')) {
            if (m_validation->isValid(m_texto)) {
                return INPUT_CONFIRMA;
            }
            Clear();
        }

        if (m_texto.empty() && m_aceitaBranco && m_ultimaTecla == 'B') {
            return INPUT_BRANCO;
        }
    }

    return INPUT_SEM_TECLA;
}

} // namespace api
