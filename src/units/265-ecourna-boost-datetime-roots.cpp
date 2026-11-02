// Roots of fragment 265: callers for ecourna::api::security::FormataData (fn 2687) and ConverteDataHoraSemSeparador
// (fn 2685), the fragment's api/security/conversaodatahora.cpp.
//
// 2687 has one direct caller in the target, vota::CImpressaoPU::StartState (fn 11902, a trap in unit 176), which calls
// it four times: Datas stands for it with two calls.
// 2685 has one direct caller in the target, fn 7787, which calls it four times and is not written: Carimbos stands for
// it with two calls, so that binaryen keeps 2685 out of line and merges it with ConverteDataHora (9220) into the body
// the target holds as fn 6155.
//
// Declared through asm labels, so this TU needs no ecourna header and instantiates nothing; compiled with
// APP_CXXFLAGS. The strings the functions return through a pointer are left as they are, as nothing calls these.
extern "C" {
void w265_data(void* resultado, const void* dataHora) __asm__(
    "_ZN7ecourna3api8security11FormataDataERKN5boost10posix_time5ptimeE");
void w265_carimbo(void* resultado, const void* dataHora) __asm__(
    "_ZN7ecourna3api8security28ConverteDataHoraSemSeparadorERKN5boost10posix_time5ptimeE");
}

namespace {

const void* volatile boost_datetime_sink;

// stands for fn 11902
__attribute__((noinline)) int Datas(const void* inicio, const void* fim)
{
    char texto[12];
    char outro[12];
    w265_data(texto, inicio);
    w265_data(outro, fim);
    return texto[11] - outro[11] * 3;
}

// stands for fn 7787
__attribute__((noinline)) int Carimbos(const void* inicio, const void* fim)
{
    char texto[12];
    char outro[12];
    w265_carimbo(texto, inicio);
    w265_carimbo(outro, fim);
    return texto[11] * 7 + outro[11];
}

struct SBoostDatetimeRoots {
    SBoostDatetimeRoots()
    {
        boost_datetime_sink = reinterpret_cast<const void*>(&Datas);
        boost_datetime_sink = reinterpret_cast<const void*>(&Carimbos);
    }
} boost_datetime_roots;

} // namespace
