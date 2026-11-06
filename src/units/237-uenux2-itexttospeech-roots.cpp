// Roots: a stand-in for the target caller of api::ITextToSpeech::Cache (fn 921) that is not in our link.
// src/units/237-uenux2-itexttospeech.mk has the evidence and the measurements. Cache is an inline member of
// api/audio/itexttospeech.h that no object of ours calls, so this object emits it, at the flags of
// cinstrucaovotacaoacessibilidade.cpp, whose TU's copy the target keeps (a reading: the fragment says why).
// - fn 921 has one direct caller in the target, fn 7787 (awk -F'\t' '$2==921' ledger/callgraph.tsv), which calls it 14
//   times and is not written. w237_cache calls it twice, so that binaryen keeps it out of line as the target does,
//   each time with the default kind, eCacheKept, so that binaryen folds that one value into Cache's body, where the
//   target's 921 passes Store a constant 1.
#include <string>

#include "api/audio/itexttospeech.h"

namespace {

// stands for fn 7787
__attribute__((noinline)) void w237_cache(api::ITextToSpeech& fala, const std::string& tecla,
                                          const std::string& mensagem)
{
    fala.Cache(tecla);
    fala.Cache(mensagem);
}

void (*volatile w237_sink_cache)(api::ITextToSpeech&, const std::string&, const std::string&);

struct STextToSpeechRoots {
    STextToSpeechRoots()
    {
        w237_sink_cache = w237_cache;
    }
} texttospeech_roots;

} // namespace
