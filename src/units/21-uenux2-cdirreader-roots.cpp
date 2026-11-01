// Roots: keep api::CDirReader's members in the skeleton link. The target calls each directly and never through the
// table (ledger/callgraph.tsv), and none of their callers outside the class is reconstructed yet:
//   NextEntry (1260)    from 2762 5360 5458 5572 7160 11167
//   the constructor (1914) and the destructor (1913)    from 2762 5360 5458 5572 7160 11167
//   Close (2232), IsDir (1912) and IsFile (2231)        from 2762 5360 5458 5572 11167
//   Open (5470)         from 1914 (the constructor, reconstructed) and 5360
//   IsLink (5469)       from 5360 and 5458
// The noinline callers below give each two call sites or more (Open one more beside the constructor's), so binaryen
// keeps every body out of line as the target does. Their bodies differ from each other and from every target function.
// AbreDois and FechaDois read the constructor's and the destructor's results, which the target keeps (fns 1914 and 1913
// return this). They are address-taken from a static constructor. Declared through asm labels with the wasm-level
// signatures, the constructor and destructor with the object's int result; compiled as uenux2 code.
extern "C" {
int w1260_root_0(int) __asm__("_ZN3api10CDirReader9NextEntryEv");
int w1914_root_0(int, int) __asm__("_ZN3api10CDirReaderC1ERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
int w1913_root_0(int) __asm__("_ZN3api10CDirReaderD1Ev");
int w5470_root_0(int, int) __asm__("_ZN3api10CDirReader4OpenERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void w2232_root_0(int) __asm__("_ZN3api10CDirReader5CloseEv");
int w1912_root_0(int) __asm__("_ZNK3api10CDirReader5IsDirEv");
int w2231_root_0(int) __asm__("_ZNK3api10CDirReader6IsFileEv");
int w5469_root_0(int) __asm__("_ZNK3api10CDirReader6IsLinkEv");
}

namespace {

__attribute__((noinline)) int ContaEntradas(int leitor)
{
    int n = 0;
    while (w1260_root_0(leitor)) {
        ++n;
    }
    return n;
}

__attribute__((noinline)) int TemEntrada(int leitor)
{
    return w1260_root_0(leitor);
}

__attribute__((noinline)) int AbreDois(int leitorA, int leitorB, int diretorio)
{
    const int primeiro = w1914_root_0(leitorA, diretorio);
    return w1914_root_0(leitorB, diretorio + 12) + w5470_root_0(primeiro, diretorio + 24);
}

__attribute__((noinline)) int FechaDois(int leitorA, int leitorB)
{
    w2232_root_0(leitorA);
    w2232_root_0(leitorB);
    return w1913_root_0(leitorA) - w1913_root_0(leitorB);
}

__attribute__((noinline)) int TiposDaEntrada(int leitor)
{
    return w1912_root_0(leitor) + 2 * w2231_root_0(leitor) + 4 * w5469_root_0(leitor);
}

__attribute__((noinline)) int AlgumTipo(int leitorA, int leitorB)
{
    return w1912_root_0(leitorA) | w2231_root_0(leitorB) | w5469_root_0(leitorA + leitorB);
}

void* volatile w1260_sink;

struct SW1260Roots {
    SW1260Roots()
    {
        w1260_sink = reinterpret_cast<void*>(&ContaEntradas);
        w1260_sink = reinterpret_cast<void*>(&TemEntrada);
        w1260_sink = reinterpret_cast<void*>(&AbreDois);
        w1260_sink = reinterpret_cast<void*>(&FechaDois);
        w1260_sink = reinterpret_cast<void*>(&TiposDaEntrada);
        w1260_sink = reinterpret_cast<void*>(&AlgumTipo);
    }
} w1260_roots;

} // namespace
