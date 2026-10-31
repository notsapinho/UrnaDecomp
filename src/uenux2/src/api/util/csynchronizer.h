#pragma once

#include <memory>

namespace api {

// Reconstruction's note, not TSE's text. api::CSynchronizer's only record is CreateInst's throw (csynchronizer.cpp:37,
// fn 600 holds it inlined into GetInst). What the target shows: fn 600 creates the instance with `new` of one byte and
// a call of fn 5729, which stores its bool argument (1) at +0 and returns this, so the class is that one byte, set by an
// out-of-line constructor; the instance is held in a static std::unique_ptr (fn 10867 destroys the word at 1839324 at
// exit through fn 349, which unit 03's fragment reads as a static unique_ptr's destructor). The names GetInst,
// m_habilitado and s_instancia, GetInst's reference result, the bool's meaning and the constructor's being public are
// chosen, after ecourna::api::util::CSynchronizer (src/ecourna/api/util/csynchronizer.hpp), whose CreateInst throws the
// same message.
class CSynchronizer {
public:
    static void CreateInst(bool habilitado);
    static CSynchronizer& GetInst();

    explicit CSynchronizer(bool habilitado);

private:
    bool m_habilitado;

    static std::unique_ptr<CSynchronizer> s_instancia;
};

} // namespace api
