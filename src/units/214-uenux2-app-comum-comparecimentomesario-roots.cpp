// Roots: reach unit 214's functions the way the target's callers do, until they land. Each has direct callers in the
// target that are not all written, so each gets the call sites it lacks here, two in all, and stays out of line; each
// stand-in has a body no target function has (the calls, then a constant, the results' last bytes or a word read from
// the result), and none is called:
// - comum::ListaArquivosNaoRegistrados (fn 5374): fns 1149 and 10451, one call each; 1149 is in the link (it holds the
//   constructor that calls it), so one call here stands for 10451;
// - comum::CControladorReconhecimentoMesario::GetInst (fn 1149): fns 3614, 5382, 10316, 10337 and 10451; 10337 is in
//   the link (unit 135's IGestorDadoMesario::StartState), so one call here stands for the other four;
// - comum::CImprimirIdentificacaoMesariosFinal::GetNomeMesario (fn 5385): fn 12105, which calls it twice.
// The first and the third return a class by value through a hidden result pointer, so they are declared through asm
// labels with that pointer first and called into buffers the stand-ins never destroy: nothing of libc++ is
// instantiated here. The member's `this` is a parameter of ours that its body never reads, as the target's wasm type
// has none. GetInst returns a reference, the object's address.
extern "C" {
void w214_lista(void* resultado) __asm__("_ZN5comum27ListaArquivosNaoRegistradosEv");
const void* w214_controlador() __asm__("_ZN5comum33CControladorReconhecimentoMesario7GetInstEv");
void w214_nome(void* resultado, void* objeto, const void* titulo) __asm__(
    "_ZN5comum35CImprimirIdentificacaoMesariosFinal14GetNomeMesarioERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
}

namespace {

// stands for fn 10451
__attribute__((noinline)) int w214_arquivos(void* resultado)
{
    w214_lista(resultado);
    return 23;
}

// stands for fns 3614, 5382, 10316 and 10451
__attribute__((noinline)) int w214_controlador_limiar()
{
    return static_cast<const int*>(w214_controlador())[1] + 31;
}

// stands for fn 12105
__attribute__((noinline)) int w214_nomes(void* objeto, const void* primeiro, const void* segundo)
{
    alignas(4) unsigned char a[12];
    alignas(4) unsigned char b[12];
    w214_nome(a, objeto, primeiro);
    w214_nome(b, objeto, segundo);
    return a[11] + b[11];
}

int (*volatile w214_sink_arquivos)(void*);
int (*volatile w214_sink_controlador)();
int (*volatile w214_sink_nomes)(void*, const void*, const void*);

struct SW214Roots {
    SW214Roots()
    {
        w214_sink_arquivos = w214_arquivos;
        w214_sink_controlador = w214_controlador_limiar;
        w214_sink_nomes = w214_nomes;
    }
} w214_roots;

} // namespace
