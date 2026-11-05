// Roots: keep the CEPESC/CKeyLoader units' functions in the skeleton link the way the target keeps them
// (their callers — comum::CControlaArmazenamentoDeImagens, CCepescCipher, … — are not reconstructed yet).
// Target call shapes (ledger/callgraph.tsv + the elem segment): CInfoSalt::CInfoSalt(vec, vec) = 2 direct callers
// (fns 11419, 11616; 11419, fragment 335's, and 11616, unit 122's, are in the link, so the stand-in that stood for
// them went); every other body is reached only through invoke_* (a table slot, uses 0): the copy ctor (slot 6323),
// both CCipheredOut ctors (6317/6318), CPlainText's 9-argument ctor (6328), DecipherKeyIfNeeded<EntidadeChave> (6313).
// Address-taken from a static constructor like tools/round/gen_try_roots.py does: bodies intact, no export, no inlining.
// Declared through asm labels with the wasm-level signatures so no header (and no ASN.1 type) is needed here.
extern "C" {
int cepesc_infosalt_copy(int, int) __asm__("_ZN7ecourna3api6cepesc9CInfoSaltC2ERKS2_");
int cepesc_cipheredout_ctor2(int, int, int) __asm__("_ZN7ecourna3api6cepesc12CCipheredOutC2ERKNSt3__26vectorIhNS3_9allocatorIhEEEES9_");
int cepesc_cipheredout_ctor3(int, int, int, int) __asm__("_ZN7ecourna3api6cepesc12CCipheredOutC2ERKNSt3__26vectorIhNS3_9allocatorIhEEEES9_RKNS1_9CInfoSaltE");
int cepesc_plaintext_ctor(int, int, int, int, int, int, int, int, int, int) __asm__("_ZN7ecourna3api6cepesc10CPlainTextC2EhhttNSt3__26vectorIhNS3_9allocatorIhEEEES7_S7_S7_NS3_10shared_ptrINS1_9CInfoSaltEEE");
int cepesc_plaintext_ctor_salt(int, int, int, int, int, int, int, int, int, int) __asm__("_ZN7ecourna3api6cepesc10CPlainTextC2EhhttNSt3__26vectorIhNS3_9allocatorIhEEEES7_S7_S7_RKNS1_9CInfoSaltE");
void keyloader_decipher(int, int, int) __asm__("_ZN7ecourna3api8security10CKeyLoader19DecipherKeyIfNeededIN19ModuloEnvelopeChave13EntidadeChaveEEENSt3__26vectorIhNS6_9allocatorIhEEEERKT_");
}

namespace {

void* volatile cepesc_sink;

struct SCepescRoots {
    SCepescRoots()
    {
        cepesc_sink = reinterpret_cast<void*>(&cepesc_infosalt_copy);
        cepesc_sink = reinterpret_cast<void*>(&cepesc_cipheredout_ctor2);
        cepesc_sink = reinterpret_cast<void*>(&cepesc_cipheredout_ctor3);
        cepesc_sink = reinterpret_cast<void*>(&cepesc_plaintext_ctor);
        cepesc_sink = reinterpret_cast<void*>(&cepesc_plaintext_ctor_salt);
        cepesc_sink = reinterpret_cast<void*>(&keyloader_decipher);
    }
} cepesc_roots;

} // namespace
