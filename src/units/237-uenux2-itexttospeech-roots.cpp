// Roots: stand-ins for target callers of api::ITextToSpeech's cache code that are not in our link. The code itself is
// the executable TU's copies, which src/app/roots_texttospeech.cpp emits; src/units/237-uenux2-itexttospeech.mk has the
// evidence. Each stand-in calls through an __asm__ label with the object's signature, so this file includes no header and
// instantiates nothing.
// - fn 5685, the kept map's __emplace_unique_key_args (unordered_map<string, shared_ptr<CWavFile>>), has two direct
//   callers in the target (awk -F'\t' '$2==5685' ledger/callgraph.tsv: 921 and 11447). 11447, the map's operator[]
//   (table slot 210, which Store passes to invoke_iii), is in the link; 921, an ITextToSpeech member that only fn 7787
//   calls, is not: with one caller binaryen inlines 5685 into 11447. w237_guarda stands for 921, and goes when 921 lands.
extern "C" {
void w237_insere(void* resultado, void* tabela, const void* chave, const void* modo, void* argumentos, void* vazio) __asm__(
    "_ZNSt3__212__hash_tableINS_17__hash_value_typeINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEENS_10shared_"
    "ptrIN3api8CWavFileEEEEENS_22__unordered_map_hasherIS7_NS_4pairIKS7_SB_EENS_4hashIS7_EENS_8equal_toIS7_EELb1EEENS_21__"
    "unordered_map_equalIS7_SG_SK_SI_Lb1EEENS5_ISG_EEE25__emplace_unique_key_argsIS7_JRKNS_21piecewise_construct_tENS_5tup"
    "leIJRSF_EEENSU_IJEEEEEENSE_INS_15__hash_iteratorIPNS_11__hash_nodeISC_PvEEEEbEERKT_DpOT0_");
}

namespace {

// stands for fn 921
__attribute__((noinline)) void w237_guarda(void* tabela, const void* chave)
{
    char resultado[8];
    const void* argumentos = chave;
    w237_insere(resultado, tabela, chave, &argumentos, &argumentos, resultado);
}

void (*volatile w237_sink_guarda)(void*, const void*);

struct STextToSpeechRoots {
    STextToSpeechRoots()
    {
        w237_sink_guarda = w237_guarda;
    }
} texttospeech_roots;

} // namespace
