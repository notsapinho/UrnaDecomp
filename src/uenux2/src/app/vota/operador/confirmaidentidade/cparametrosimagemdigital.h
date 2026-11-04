#pragma once

#include <memory>
#include <mutex>

namespace vota {

// Target fn 1903: the GetInst of a 16-byte singleton with no vtable, record or RTTI. It creates the object on first use
// under a static std::mutex (@1908640, destroyed at exit by fn 10519) and keeps it in a static std::unique_ptr
// (@1908664, by fn 10520); the object holds the words 8 at +0 and 500 at +4 and, at +8, the double 500 / 2.54
// (4641130074062041959, 196.8503937007874). Its five target callers (fns 1256, 3614, 5372, 10316 and 10465) drop its
// result, and no target function reads the object. A reading of the values: a fingerprint image's 8 bits per pixel and
// its resolution, 500 dots per inch and per centimetre. Chosen, as no evidence names them: the class's name, namespace,
// header and file, its members' names, their types (two ints and a double, the widths the stores give) and their being
// default member initializers, GetInst's being a static member in the tree's singleton form. The constructor is
// declared here and defaulted in the .cpp after the statics, comum::CLogComum's form, measured: with it defaulted in
// the class, clang folds away GetInst's reload of the pointer after operator new, which the target keeps (the old
// value read again, tested and freed); out of line, clang keeps the call and binaryen inlines it into GetInst, its
// one caller. src/units/307-uenux2-cparametrosimagemdigital.mk says where the evidence places the object.
class CParametrosImagemDigital {
public:
    static CParametrosImagemDigital& GetInst();

private:
    CParametrosImagemDigital();

    static std::unique_ptr<CParametrosImagemDigital> s_inst;
    static std::mutex s_mutex;

    int m_bitsPorPixel = 8;
    int m_resolucaoDpi = 500;
    double m_resolucaoPorCentimetro = m_resolucaoDpi / 2.54;
};

} // namespace vota
