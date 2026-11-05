// Roots of src/units/307-uenux2-cparametrosimagemdigital.mk: vota::CParametrosImagemDigital::GetInst (fn 1903) has five
// direct callers in the target (ledger/callgraph.tsv): 1256 (vota::CControlaReconhecimento::GetInst, in the link: unit
// 161), 10465 (vota::CPedeDigital::ProcessTick, in the link: unit 282), 10316 (comum::CPedeDigitalMesario::ProcessTick,
// in the link: unit 135), 3614 and 5372, which are not. The stand-in ParametrosImagem stands for those two, so that GetInst keeps its call sites and binaryen keeps it out of
// line. Every target caller drops the result, yet the target's GetInst returns it (`()->(i32)`). A result no caller of
// our link reads goes (fn 1256's did, `()->()`, while its one caller in the link dropped it: measured), so the
// stand-in reads it. It goes when the two are in the link and one of them reads the result.
//
// The same file's ExtraiTemplate (fn 2224), CConversorWsq::GetInst (fn 2742) and CConversorWsq::ConverteParaWsq (fn
// 1379's body) have the target callers 3614, 5372, 10316 and 10465; 2725, 10316, 10451 and 10465; and 10316, 10451 and
// 10465 (with 7-Zip's 2207 and 9647, Xzs_Construct's, which no call of ours reaches through this name). 10465 (unit
// 282), 10316 (unit 135) and 2725 (unit 293) are in the link; ExtraiModelo stands for the others of 2224 (3614, 5372),
// calling it twice, and ConverteImagem for the other of 2742 and of ConverteParaWsq (10451), reading GetInst's result,
// which 2742's `()->(i32)` keeps. They go when those callers are in the link.
//
// Declared through asm labels with the object's signatures, so this TU needs no uenux2 header; compiled with
// APP_CXXFLAGS. The stand-ins' bodies are no target function's.
extern "C" {
const char* w307_parametros() __asm__("_ZN4vota24CParametrosImagemDigital7GetInstEv");
void w307_extrai(const void* parametros, const void* imagem, void* modelo) __asm__(
    "_ZNK4vota24CParametrosImagemDigital14ExtraiTemplateERKNSt3__26vectorIhNS1_9allocatorIhEEEERS5_");
const char* w307_conversor() __asm__("_ZN4vota13CConversorWsq7GetInstEv");
void w307_converte(void* resultado, const void* conversor, const void* imagem, int largura, int altura,
                   const void* comentario) __asm__(
    "_ZNK4vota13CConversorWsq15ConverteParaWsqERKNSt3__26vectorIhNS1_9allocatorIhEEEEiiRKNS1_12basic_stringIcNS1_"
    "11char_traitsIcEENS3_IcEEEE");
}

namespace {

// Stands for 3614 and 5372.
__attribute__((noinline)) int ParametrosImagem()
{
    return w307_parametros()[5] + 307;
}

// Stands for 3614 and 5372, the target callers of ExtraiTemplate (fn 2224) besides 10465 and 10316.
__attribute__((noinline)) void ExtraiModelo(const void* imagem, void* modelo)
{
    w307_extrai(w307_parametros(), imagem, modelo);
    w307_extrai(w307_parametros(), static_cast<const char*>(imagem) + 12, modelo);
}

// Stands for 10451, the target caller of CConversorWsq::GetInst (fn 2742) and of ConverteParaWsq (fn 1379's body)
// besides 10465, 10316 and 2725 (ConverteParaWsq's besides 10465 and 10316).
__attribute__((noinline)) int ConverteImagem(void* resultado, const void* imagem, int largura)
{
    w307_converte(resultado, w307_conversor(), imagem, largura, largura + 1, imagem);
    return w307_conversor()[3] + largura;
}

const void* volatile w307_sink;

struct SW307Roots {
    SW307Roots()
    {
        w307_sink = reinterpret_cast<const void*>(&ParametrosImagem);
        w307_sink = reinterpret_cast<const void*>(&ExtraiModelo);
        w307_sink = reinterpret_cast<const void*>(&ConverteImagem);
    }
} w307_roots;

} // namespace
