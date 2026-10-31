// api::CMovie (/home/rubio/tse/uenux2/src/api/gui/cmovie.cpp): the constructor's throw is a record of the target, so
// its position in this file is fixed:
//   5526  CMovie(std::vector<CMovieFrame>, const SPoint&)   record at line 29, column 15

#include "api/gui/cmovie.h"

#include <utility>

#include "api/gui/eueguierror.h"

namespace api {

// (original lines 13-16: content not recovered)
#line 17
/**
 * Cria um filme com os quadros @p frames, exibidos a partir do primeiro.
 *
 * @param frames quadros do filme, na ordem em que são exibidos
 * @param tamanho largura (x) e altura (y) dos quadros
 *
 * @throw CUeGuiError se não houver quadros
 */
CMovie::CMovie(std::vector<CMovieFrame> frames, const SPoint& tamanho)
    : m_frames(std::move(frames)), m_frameAtual(0), m_tamanho(tamanho)
{
    if (m_frames.empty()) {
        throw CUeGuiError(EUE_GUI_MOVIE_SEM_FRAMES, "Não havia frames");
    }
}

CMovieFrame::CMovieFrame(std::vector<uebyte> imagem, uint64_t duracao) : imagem(std::move(imagem)), duracao(duracao)
{
}

} // namespace api
