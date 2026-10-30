// Roots: keep the members src/units/95-uenux2-app-comum.mk lists in the skeleton link. The target calls each directly
// from several functions (ledger/callgraph.tsv: 275 from 1501 1836 3333 4682 4687 6737 7174 12098, 680 from 1836 4657
// 7174, 347 from 1164 3798 5876 6045, 5900 from 4625 5901, 3830 from 4625 5890 5892), none of them reconstructed yet and
// none through the table.
// Two noinline callers with different bodies give each two call sites, so binaryen keeps its body out of line, and they
// pass every argument through, so its dead-argument elimination folds none in. `this` of CArquivosResultado::operator[]
// is passed too: the member does not read it, and binaryen drops the parameter as the target's (i32 i32)->() shows.
// Address-taken from a static constructor. Declared through asm labels with the object's signatures (a result by value
// is a hidden first parameter); compiled with APP_CXXFLAGS.
extern "C" {
void w275_root_0(int, int, int) __asm__("_ZNK5comum13CArquivosSavdixENS_11ESavdPacoteE");
void w680_root_0(int, int, int) __asm__("_ZNK5comum13CArquivosSavdixENS_14ESavdArquivoUEE");
void w347_root_0(int, int, int) __asm__("_ZNK5comum18CArquivosResultadoixENS_25EExtensaoArquivoResultadoE");
void w5900_root_0(int, int) __asm__("_ZN5comum15CPacoteArquivos16RetornaNomeChaveENS_17ESavdChaveValidarE");
int w3830_root_0(int, int, int, int) __asm__("_ZN5comum14IInterfaceSavd16EnviarRequisicaoERiRNS_16ueRequisicaoSavdERKNSt3__212basic_stringIcNS4_11char_traitsIcEENS4_9allocatorIcEEEE");
}

namespace {

__attribute__((noinline)) void NomesDoPacote(int nome, int nomeAssinado, int arquivos, int pacote, int arquivo)
{
    w275_root_0(nome, arquivos, pacote);
    w680_root_0(nomeAssinado, arquivos, arquivo);
}

__attribute__((noinline)) void NomesDePacotes(int nome, int outro, int arquivos, int pacote, int arquivo)
{
    w680_root_0(nome, arquivos, arquivo);
    w275_root_0(outro, arquivos, pacote + 1);
    w275_root_0(nome + 12, arquivos, pacote);
    w680_root_0(outro + 12, arquivos, arquivo + 1);
}

__attribute__((noinline)) void NomeResultado(int nome, int arquivos, int extensao)
{
    w347_root_0(nome, arquivos, extensao);
}

__attribute__((noinline)) void NomesResultado(int nome, int arquivos, int extensao, int assinatura)
{
    w347_root_0(nome + 12, arquivos, assinatura);
    w347_root_0(nome, arquivos, extensao);
}

__attribute__((noinline)) void NomeChave(int nome, int chave)
{
    w5900_root_0(nome, chave);
}

__attribute__((noinline)) void NomesChaves(int nome, int chave, int outra)
{
    w5900_root_0(nome + 12, outra);
    w5900_root_0(nome, chave);
}

__attribute__((noinline)) int EnviaUma(int savd, int codigo, int requisicao, int dados)
{
    return w3830_root_0(savd, codigo, requisicao, dados);
}

__attribute__((noinline)) int EnviaDuas(int savd, int codigo, int requisicao, int dados)
{
    return w3830_root_0(savd, codigo, requisicao, dados) + w3830_root_0(savd, codigo + 8, requisicao + 8, dados + 12);
}

void* volatile w95_sink;

struct SW95Roots {
    SW95Roots()
    {
        w95_sink = reinterpret_cast<void*>(&NomesDoPacote);
        w95_sink = reinterpret_cast<void*>(&NomesDePacotes);
        w95_sink = reinterpret_cast<void*>(&NomeResultado);
        w95_sink = reinterpret_cast<void*>(&NomesResultado);
        w95_sink = reinterpret_cast<void*>(&NomeChave);
        w95_sink = reinterpret_cast<void*>(&NomesChaves);
        w95_sink = reinterpret_cast<void*>(&EnviaUma);
        w95_sink = reinterpret_cast<void*>(&EnviaDuas);
    }
} w95_roots;

} // namespace
