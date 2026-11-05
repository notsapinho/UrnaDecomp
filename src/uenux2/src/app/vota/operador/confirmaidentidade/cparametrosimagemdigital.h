#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace api {
struct SXYT;
} // namespace api

namespace vota {

// Target fn 2742: the GetInst of a singleton with no vtable, record or RTTI, `f2900(1908612, 1908636)`, a thunk into
// binaryen's shared body 2900 of the tree's singleton form for a 1-byte object (comum::CLogComum::GetInst's, 948, and
// comum::CArquivosResultado's, 348, are thunks into it too): a static std::mutex (@1908612, destroyed at exit by fn
// 10521) and a static std::unique_ptr (@1908636, by fn 10522), which lie in .bss right below
// CParametrosImagemDigital's, their exit destructors right before that class's in use band 1 (10522, 10521, then
// 10520, 10519). Its four target callers (2725, 10316, 10451, 10465) drop its result. In 10465 the call comes after
// api::CBmpConversor::VerticalFlip, then the scanner's slots 2 and 1 (their results dropped), a std::string built from
// "" and destroyed, and fn 1379 on a 12-byte frame slot that 10465 then reads as a vector's begin and end: one body,
// after binaryen's dead-argument elimination, with 7-Zip's Xzs_Construct (three words cleared), which 10316 and 10451
// call too. So a member of this object takes the image, the two ints and a string and returns an empty vector, and
// binaryen dropped every parameter but the result's; that it is the image in WSQ, the format
// comum::CControlaArmazenamentoDeImagens::CifrarWsq ciphers (records ccontrolaarmazenamentodeimagens.cpp:149, :152), is
// a reading. Chosen: the class's name, its being here (it reads like a neighbour of the parameters' class, a reading of
// the .bss order), the member's name, its being const, its parameters' types and names, and GetInst's and the
// constructor's form (comum::CLogComum's: the constructor out of line, defaulted after the statics).
class CConversorWsq {
public:
    static CConversorWsq& GetInst();

    std::vector<uebyte> ConverteParaWsq(const std::vector<uebyte>& imagem, int largura, int altura,
                                        const std::string& comentario) const;
    // comum::CControlaArmazenamentoDeImagens' fn 2725 calls GetInst (fn 2742), drops its result and copies the image
    // it was given in place: a member of this object inlined there, its name, its being inline and its body chosen
    // (src/units/293-uenux2-ccontrolaarmazenamentodeimagens.mk).
    std::vector<uebyte> PreparaWsq(const std::vector<uebyte>& wsq) const { return wsq; }

private:
    CConversorWsq();

    static std::unique_ptr<CConversorWsq> s_inst;
    static std::mutex s_mutex;
};

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

    // Target fn 2224, `p0[4] = p0[0]`: a vector cleared. Its four target callers (3614, 5372, 10316, 10465) each call
    // it right after GetInst (fn 1903), whose result they drop, and 10465 after a load of the image's pointer it drops:
    // a member whose object and image binaryen's dead-argument elimination dropped, its body the output's clear() (a
    // reading). Chosen: its name, its being const, its parameters and that it is this class's.
    void ExtraiTemplate(const std::vector<uebyte>& imagem, std::vector<uebyte>& modelo) const;
    // In 3614 and 5372 the call of fn 2224 comes after GetInst and after the scanner's slots 2 and 1, whose results
    // they drop: a member that takes the image's width and height too, which dead-argument elimination dropped with the
    // object and the image. 5372's second call fills the vector it hands api::IFingerMatcher's slot 2 as its second
    // argument, the minutiae fn 10465 passes there: ExtraiMinucias. Both bodies clear their output, as the first
    // overload does, so after that elimination binaryen keeps one body for the three (measured: names.tsv holds the
    // first overload's symbol alone). Chosen: the overload, ExtraiMinucias's name, their parameters' order and types.
    void ExtraiTemplate(const std::vector<uebyte>& imagem, int largura, int altura, std::vector<uebyte>& modelo) const;
    void ExtraiMinucias(const std::vector<uebyte>& imagem, int largura, int altura,
                        std::vector<api::SXYT>& minucias) const;

private:
    CParametrosImagemDigital();

    static std::unique_ptr<CParametrosImagemDigital> s_inst;
    static std::mutex s_mutex;

    int m_bitsPorPixel = 8;
    int m_resolucaoDpi = 500;
    double m_resolucaoPorCentimetro = m_resolucaoDpi / 2.54;
};

} // namespace vota
