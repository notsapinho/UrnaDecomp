#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include "api/gui/primitives.h"
#include "ecourna/api/uetypes.hpp"

namespace api {

/**
 * Um quadro de um filme: a imagem e por quanto tempo ela fica na tela.
 */
// 24 bytes, as the target's callers copy it (fn 1593, api::getResourceMovie: a std::vector<CMovieFrame> copied
// element by element, the bytes with memcpy and an 8-byte field at +16; fn 8605, simulador::CWasmResource slot 4:
// one frame built from a resource's bytes and the integer 80)
struct CMovieFrame {
    std::vector<uebyte> imagem;
    uint64_t duracao;
};

/**
 * Um filme: quadros do mesmo tamanho, exibidos um após o outro.
 */
// 20 bytes: std::make_shared<CMovie> allocates 32, 12 of them the control block (fn 1593); the SPoint is the image's
// width and height (fn 8605 reads them from a GIF or JPEG header)
class CMovie {
public:
    CMovie(std::vector<CMovieFrame> frames, const SPoint& tamanho);

    // back to the first frame: CMovieField::Show (fn 11061) stores 0 in m_frameAtual. The name is chosen, and so is
    // that a member of CMovie does it: the store is all the target shows
    void Rewind() { m_frameAtual = 0; }

    // the frame on show and the size: simulador::CWasmScreen's slot 26 (fn 9038) reads them, the frame through at() (its
    // `call 234`, the vector's out_of_range). The names are chosen
    const CMovieFrame& FrameAtual() const { return m_frames.at(m_frameAtual); }

    const SPoint& Tamanho() const { return m_tamanho; }

private:
    std::vector<CMovieFrame> m_frames;
    size_t m_frameAtual;
    SPoint m_tamanho;
};

} // namespace api
