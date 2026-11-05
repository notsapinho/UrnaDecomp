// Roots of src/units/325-uenux2-geradores-zeresima.mk: caller stand-ins for the functions this unit writes whose
// target callers are not all in our link. binaryen inlines a function with one call site, so each gets two here; the
// stand-in's comment names the target callers it stands for, and it goes when they are all in the link. Its body
// differs from every target function's. Declared through asm labels with the object's signatures, so this TU needs no
// header and instantiates nothing.
extern "C" void w1047(int, int, int) __asm__("_ZN4vota8CLogVota20LogaGerandoRelatorioEN5comum13ERelatoriosUEEb");
extern "C" void w5977(int, int) __asm__(
    "_ZN4vota12CRelVotaUtil13CriaCabecalhoERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
extern "C" void w3873(int) __asm__("_ZN4vota22CriaCabecalhoDetalheZEEv");
extern "C" void w3872(int, int) __asm__("_ZN4vota20CriaDetalheCandidatoEb");
extern "C" void w5971(int, int) __asm__(
    "_ZN4vota20CriaPartesExtratoRDVERKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");
extern "C" void w3699(int, int) __asm__(
    "_ZN5comum15CriaTituloCargoERKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");
extern "C" void w5580(int) __asm__("_ZN5comum8CRelUtil20FormCabecalhoEleicaoEv");
extern "C" int w2875(int, int, int, int, int) __asm__(
    "_ZNSt3__26vectorINS_10shared_ptrIN3api11IReportPartEEENS_9allocatorIS4_EEE18__insert_with_sizeB8ne210108INS_11__"
    "wrap_iterIPKS4_EESC_EENS9_IPS4_EESC_T_T0_l");
extern "C" void w5579(int, int, int, int) __asm__(
    "_ZN5comum8CRelUtil18FormRodapeZeresimaERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEERKNS1_"
    "6vectorIN7ecourna3app5dados16CTituloRelatorioENS5_ISE_EEEERKNS_2md15estadoaplicacao20CDadoCorrespondenciaE");

namespace {

// Stands for fns 11946, 12105 and 12110, the target callers of vota::CLogVota::LogaGerandoRelatorio (fn 1047) not
// written (11943, the fourth, is in the link). They pass the report and 0 before it, the report and 1 after it.
__attribute__((noinline)) int GeracoesRelatorios(char* log, int relatorio)
{
    w1047(reinterpret_cast<int>(log), relatorio, 0);
    w1047(reinterpret_cast<int>(log), relatorio + 11, 1);
    return log[4] + relatorio;
}

// Stands for fn 11946, a target caller of vota::CRelVotaUtil::CriaCabecalho (fn 5977) not written (11943, the other, is
// in the link). The first argument is the address of the std::shared_ptr it returns, the second the title.
__attribute__((noinline)) int Cabecalhos(char* formularios, char* titulo)
{
    w5977(reinterpret_cast<int>(formularios), reinterpret_cast<int>(titulo));
    w5977(reinterpret_cast<int>(formularios) + 8, reinterpret_cast<int>(titulo) + 12);
    return formularios[1] + titulo[11];
}

// Stands for fn 11946, which calls vota::CriaCabecalhoDetalheZE (fn 3873) three times and vota::CriaDetalheCandidato
// (fn 3872) twice with 0, and for fn 12110, the other caller of 3872; neither is written.
__attribute__((noinline)) int Detalhes(char* formularios, int comVotos)
{
    w3873(reinterpret_cast<int>(formularios));
    w3873(reinterpret_cast<int>(formularios) + 16);
    w3872(reinterpret_cast<int>(formularios) + 8, 0);
    w3872(reinterpret_cast<int>(formularios) + 24, comVotos);
    return formularios[2] - comVotos;
}

// Stands for fn 11946, a target caller of comum::CRelUtil::FormRodapeZeresima (fn 5579) not written (11943, the other,
// is in the link).
__attribute__((noinline)) int Rodapes(char* formularios, char* separador, char* rodape, char* correspondencia)
{
    w5579(reinterpret_cast<int>(formularios), reinterpret_cast<int>(separador), reinterpret_cast<int>(rodape),
          reinterpret_cast<int>(correspondencia));
    w5579(reinterpret_cast<int>(formularios) + 8, reinterpret_cast<int>(separador) + 12, reinterpret_cast<int>(rodape),
          reinterpret_cast<int>(correspondencia));
    return separador[11] + rodape[3];
}

// Stands for fn 11946, a target caller of vota::CriaPartesExtratoRDV (fn 5971) not written (11943, the other, is in the
// link). It passes the address of the std::vector the function returns and the phase's separator.
__attribute__((noinline)) int PartesExtratoRDV(char* partes, char* separador)
{
    w5971(reinterpret_cast<int>(partes), reinterpret_cast<int>(separador));
    w5971(reinterpret_cast<int>(partes) + 12, reinterpret_cast<int>(separador) + 12);
    return partes[3] + separador[7];
}

// Stands for fns 11946 and 12110, the target callers of comum::CriaTituloCargo (fn 3699) not written; fn 5971 is the
// third, in the link.
__attribute__((noinline)) int TitulosCargo(char* formulario, char* titulo)
{
    w3699(reinterpret_cast<int>(formulario) + 4, reinterpret_cast<int>(titulo));
    return formulario[5] - titulo[2];
}

// Stands for fn 11946, the target caller of comum::CRelUtil::FormCabecalhoEleicao (fn 5580) not written; fn 5971 is
// the other, in the link.
__attribute__((noinline)) int CabecalhosEleicao(char* formulario)
{
    w5580(reinterpret_cast<int>(formulario) + 16);
    return formulario[6] * 3;
}

// Stands for fn 11946's call of std::vector<std::shared_ptr<api::IReportPart>>::__insert_with_size (11946 not
// written): the target's 2875, one body with RHVoice's vector<shared_ptr<correction>> instance, has the callers 11943,
// 11946, 1245 and 813, and in our link 11943's builder is the instance's one caller, which binaryen inlines it into
// (fragment 325 has the measurement). The result is not read, as no target caller reads it ((i32 x5)->()).
__attribute__((noinline)) int InsercoesPartes(char* partes, char* outras)
{
    w2875(reinterpret_cast<int>(partes), reinterpret_cast<int>(partes) + 8, reinterpret_cast<int>(outras),
          reinterpret_cast<int>(outras) + 16, 2);
    return outras[1] - partes[3];
}

const void* volatile geradores_zeresima_sink;

struct SGeradoresZeresimaRoots {
    SGeradoresZeresimaRoots()
    {
        geradores_zeresima_sink = reinterpret_cast<const void*>(&GeracoesRelatorios);
        geradores_zeresima_sink = reinterpret_cast<const void*>(&Cabecalhos);
        geradores_zeresima_sink = reinterpret_cast<const void*>(&Detalhes);
        geradores_zeresima_sink = reinterpret_cast<const void*>(&Rodapes);
        geradores_zeresima_sink = reinterpret_cast<const void*>(&PartesExtratoRDV);
        geradores_zeresima_sink = reinterpret_cast<const void*>(&TitulosCargo);
        geradores_zeresima_sink = reinterpret_cast<const void*>(&CabecalhosEleicao);
        geradores_zeresima_sink = reinterpret_cast<const void*>(&InsercoesPartes);
    }
} geradores_zeresima_roots;

} // namespace
