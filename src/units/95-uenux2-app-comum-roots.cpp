// Roots: keep the members src/units/95-uenux2-app-comum.mk lists in the skeleton link. The target calls each directly
// from several functions (ledger/callgraph.tsv: 275 from 1501 1836 3333 4682 4687 6737 7174 12098, 680 from 1836 4657
// 7174, 347 from 1164 3798 5876 6045, 5900 from 4625 5901, 3830 from 4625 5890 5892), none of them reconstructed yet but
// 5901 (CPacoteArquivos::TrataErroPacote, written in cpacotearquivos.cpp: the stand-ins for 5900 stay for 4625) and
// 5890 (comum::ValidarUE, written in iinterfacesavd.cpp: the stand-ins for 3830 stay for 4625 and 5892), and none
// through the table. TrataErroPacote (fn 5901) itself has one caller in the target, 4625, which calls it twice.
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
void w5901_root_0(int, int) __asm__("_ZNK5comum15CPacoteArquivos15TrataErroPacoteERKNS_14IInterfaceSavdE");
int w3830_root_0(int, int, int, int) __asm__("_ZN5comum14IInterfaceSavd16EnviarRequisicaoERiRNS_16ueRequisicaoSavdERKNSt3__212basic_stringIcNS4_11char_traitsIcEENS4_9allocatorIcEEEE");
void w5890_root_0(int, int, int) __asm__("_ZN5comum9ValidarUEERNS_14IInterfaceSavdENS_10ESavdAplicERKNSt3__212basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEE");
void w3831_root_0(int, int, int) __asm__("_ZN5comum18MontaRequisicaoTLVERKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEEi");
int w5891_root_0(int, int, int, int, int) __asm__("_ZN5comum14IInterfaceSavd14AssinarArquivoENS_10ESavdAplicEihi");
void w5889_root_0(int, int, int) __asm__("_ZN5comum13EnviarAcaoHSMERNS_14IInterfaceSavdENS_10ESavdAplicENS_11ESavdCmdHSME");
void w5905_root_0(int, int) __asm__("_ZN5comum16DescricaoArquivoENS_14ESavdArquivoUEE");
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

// stands for fn 4625, which calls TrataErroPacote twice
__attribute__((noinline)) void ErrosPacote(int pacote, int savd, int outro)
{
    w5901_root_0(pacote, savd);
    w5901_root_0(pacote + 28, outro);
}

__attribute__((noinline)) int EnviaUma(int savd, int codigo, int requisicao, int dados)
{
    return w3830_root_0(savd, codigo, requisicao, dados);
}

__attribute__((noinline)) int EnviaDuas(int savd, int codigo, int requisicao, int dados)
{
    return w3830_root_0(savd, codigo, requisicao, dados) + w3830_root_0(savd, codigo + 8, requisicao + 8, dados + 12);
}

// stand for fns 3288 and 3290 (vota::VerificaAssinaturaMV and VerificaAssinaturaMI), each of which passes the ESavdAplic
// 1 to ValidarUE once
__attribute__((noinline)) void ValidaUE(int savd, int pacote)
{
    w5890_root_0(savd, 1, pacote);
}

__attribute__((noinline)) void ValidaDuasUE(int savd, int pacote, int outro)
{
    w5890_root_0(savd, 1, pacote);
    w5890_root_0(savd, 1, outro);
}

// stands for fns 4625 and 5892, which pass MontaRequisicaoTLV a key of their own
__attribute__((noinline)) void MontaRequisicoes(int saida, int pacote, int chave)
{
    w3831_root_0(saida, pacote, chave);
    w3831_root_0(saida + 12, pacote, chave + 1);
}

// stand for fns 1277 and 12098 (the inlined AssinarUE and AssinarEcourna), which pass AssinarArquivo the command and
// the file they sign, and both the operation byte 61
__attribute__((noinline)) int AssinaArquivo(int savd, int aplic, int comando, int arquivo)
{
    return w5891_root_0(savd, aplic, comando, 61, arquivo);
}

__attribute__((noinline)) int AssinaDoisArquivos(int savd, int aplic, int comando, int arquivo)
{
    return w5891_root_0(savd, aplic, comando, 61, arquivo) + w5891_root_0(savd, aplic, comando + 1, 61, arquivo + 1);
}

// stands for fn 12098 (vota::CGravaResultado::StartState), the one target caller of EnviarAcaoHSM, which keeps it out
// of line: two call sites, every argument passed through
__attribute__((noinline)) void EnviaAcoesHSM(int savd, int aplic, int acao)
{
    w5889_root_0(savd, aplic, acao);
    w5889_root_0(savd, aplic, acao + 1);
}

// stand for fns 1277 and 12098 (the inlined AssinarUE and AssinarEcourna), which name the file they sign
__attribute__((noinline)) void DescreveArquivo(int descricao, int arquivo)
{
    w5905_root_0(descricao, arquivo);
}

__attribute__((noinline)) void DescreveDoisArquivos(int descricao, int arquivo, int outro)
{
    w5905_root_0(descricao, arquivo);
    w5905_root_0(descricao + 12, outro);
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
        w95_sink = reinterpret_cast<void*>(&ErrosPacote);
        w95_sink = reinterpret_cast<void*>(&ValidaUE);
        w95_sink = reinterpret_cast<void*>(&ValidaDuasUE);
        w95_sink = reinterpret_cast<void*>(&MontaRequisicoes);
        w95_sink = reinterpret_cast<void*>(&AssinaArquivo);
        w95_sink = reinterpret_cast<void*>(&AssinaDoisArquivos);
        w95_sink = reinterpret_cast<void*>(&EnviaAcoesHSM);
        w95_sink = reinterpret_cast<void*>(&DescreveArquivo);
        w95_sink = reinterpret_cast<void*>(&DescreveDoisArquivos);
    }
} w95_roots;

} // namespace
