#pragma once

#include <algorithm>
#include <format>
#include <string>
#include <vector>

#include "api/hwil/iurna.h"

namespace api::teste {

// Recovered: RTTI names the class, an si_class of api::IUrna (vtable @1530880). The object is 28 bytes: fn 8302
// (simulador's init) allocates 28 and clang inlined the constructor there: the implicit constructor this class gives
// compiles to the same stores in the same order (+20, +12, +4, the vptr), neighbouring members merged into i64
// constants, so the layout and the initial values below are read from those stores: three ints at +4, +8 and +12, set to
// 2020, 87654321 and 255, and at +16 an empty std::vector of a trivially destructible byte type (slot 4 copies it as
// bytes; a std::vector<char> gives the same bytes). Slots 0, 2 and 3 return the ints and are shared bodies (fns 1661,
// 2587 and 3383, 7-byte getters of other classes). The destructors (slots 7 and 8: fns 8130 and 8129) store this
// class's vptr first, so the class is not final (docs/reference/facts/reading.md R4; `final` differs, measured), and
// the deleting one holds the other's body (R5): implicit here, and a body cheap enough that a destructor defined in
// the class, with or without `inline`, gives the same bytes. The members' names are IUrna's, chosen (api/hwil/iurna.h
// says from what), and so are the data members'. The path is chosen as cpowermock.h's is.
class CUrnaMock : public IUrna {
public:
    virtual int Modelo() const override { return m_modelo; }
    virtual std::string ModeloAbreviado() const override { return std::format("{:02}", m_modelo - 2000); }
    virtual int NumeroSerie() const override { return m_numeroSerie; }
    virtual int Slot3() const override { return m_slot3; }

    // the data, then 1s up to 1024 bytes. The test and the size taken after it are the target's: fn 8144 fills 1024 bytes
    // with a constant size where the path that copies computes its own, and without the test, or with the size taken
    // before it, clang joins the two paths. The count is unsigned: its loop's test is `size != 1024`, as the target's.
    virtual void Slot4(uebyte* destino) const override
    {
        if (m_dados.empty()) {
            std::fill_n(destino, 1024, 1);
            return;
        }
        const std::size_t tamanho = m_dados.size();
        std::copy(m_dados.begin(), m_dados.end(), destino);
        std::fill_n(destino + tamanho, 1024 - tamanho, 1);
    }

    virtual void Slot5(uebyte* destino) const override { std::fill_n(destino, 32, 2); }
    virtual void Semente(uebyte* destino) const override { std::fill_n(destino, 128, 3); }

private:
    int m_modelo = 2020;
    int m_numeroSerie = 87654321;
    int m_slot3 = 255;
    std::vector<uebyte> m_dados;
};

} // namespace api::teste
