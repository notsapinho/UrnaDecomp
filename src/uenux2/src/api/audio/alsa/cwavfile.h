#pragma once

#include "ecourna/api/uetypes.hpp"

namespace api {

// The 44-byte RIFF/WAVE header of a PCM stream. CWavFile keeps a copy at +4 and simulador::CWasmWebSound hands it
// to the browser with sizeof 44 (fns 9559, 9565); the TTS slot that builds one (fn 10841) stores the field values
// commented here. No record names this type's header.
struct CWavAudio {
    char riff[4];              // "RIFF"
    uedword tamanhoRiff;       // 36 + tamanhoDados
    char wave[4];              // "WAVE"
    char fmt[4];               // "fmt "
    uedword tamanhoFmt;        // 16
    ueword formato;            // 1, PCM
    ueword canais;             // 1
    uedword taxaAmostragem;
    uedword taxaBytes;         // taxaAmostragem * 2
    ueword alinhamentoBloco;   // 2
    ueword bitsPorAmostra;     // 16
    char data[4];              // "data"
    uedword tamanhoDados;
};

// The three accessors are what simulador::CWasmWebSound reads to hand the WAV to the browser (fns 9559, 9565): the
// header at +4, the samples at +48 and their size at +60. Their names and their being inline accessors are chosen:
// no record or symbol names them, and no target function holds one (they are inlined wherever they are used).
class CWavFile {
public:
    CWavFile(const CWavAudio& audio, const void* dados);
    virtual ~CWavFile();

    const CWavAudio& GetAudio() const { return m_audio; }
    const uebyte* GetDados() const { return m_dados; }
    uedword GetTamanhoDados() const { return m_tamanhoDados; }

private:
    CWavAudio m_audio;
    uebyte* m_dados = nullptr;
    uebyte* m_buffer = nullptr;
    uedword m_tamanhoBuffer = 0;
    uedword m_tamanhoDados = 0;
    uedword m_posicao = 0;
};

} // namespace api
