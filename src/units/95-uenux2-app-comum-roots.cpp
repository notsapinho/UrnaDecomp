// Roots: keep the members src/units/95-uenux2-app-comum.mk lists in the skeleton link. The target calls each directly
// from several functions (ledger/callgraph.tsv: 275 from 1501 1836 3333 4682 4687 6737 7174 12098, 680 from 1836 4657
// 7174, 347 from 1164 3798 5876 6045), none of them reconstructed yet but 1164 (CArquivosSavd::GetInst: the stand-ins
// for 347 stay for 3798, 5876 and 6045) and 1501, 1836, 4657, 4682 and 4687 (units 165 and 205, and 205's 3333: the
// stand-ins for 275 and 680 stay for 6737, 7174 and 12098), and none through the table. The stand-ins for fn 4625's
// calls of RetornaNomeChave (5900), TrataErroPacote (5901), EnviarRequisicao (3830), MontaRequisicaoTLV (3831) and
// VerificarArquivo (5892) went when 4625 (vota::VerificaAssinaturaArquivos, unit 168) was written: every target caller
// of each is in the link (5900: 4625, 5901; 5901: 4625, which calls it twice; 3830 and 3831: 4625, 5890, 5892; 5892:
// 4625, 11179).
// Two noinline callers with different bodies give each two call sites, so binaryen keeps its body out of line, and they
// pass every argument through, so its dead-argument elimination folds none in. `this` of CArquivosResultado::operator[]
// is passed too: the member does not read it, and binaryen drops the parameter as the target's (i32 i32)->() shows.
// Address-taken from a static constructor. Declared through asm labels with the object's signatures (a result by value
// is a hidden first parameter); compiled with APP_CXXFLAGS.
extern "C" {
void w275_root_0(int, int, int) __asm__("_ZNK5comum13CArquivosSavdixENS_11ESavdPacoteE");
void w680_root_0(int, int, int) __asm__("_ZNK5comum13CArquivosSavdixENS_14ESavdArquivoUEE");
void w347_root_0(int, int, int) __asm__("_ZNK5comum18CArquivosResultadoixENS_25EExtensaoArquivoResultadoE");
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

// stood for fns 1277 and 12098 (the inlined AssinarUE and AssinarEcourna), which pass AssinarArquivo the command and
// the file they sign, and both the operation byte 61; 1277 (comum::CAssinador::Assina) is in the link now, and they
// stay for 12098
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

// stood for fns 1277 and 12098 (the inlined AssinarUE and AssinarEcourna), which name the file they sign; 1277 is in
// the link now, and they stay for 12098
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
        w95_sink = reinterpret_cast<void*>(&AssinaArquivo);
        w95_sink = reinterpret_cast<void*>(&AssinaDoisArquivos);
        w95_sink = reinterpret_cast<void*>(&EnviaAcoesHSM);
        w95_sink = reinterpret_cast<void*>(&DescreveArquivo);
        w95_sink = reinterpret_cast<void*>(&DescreveDoisArquivos);
    }
} w95_roots;

} // namespace
