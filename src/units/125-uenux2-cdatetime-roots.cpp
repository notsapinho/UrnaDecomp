// Roots: keep api::CDate's, api::CDateTime's and api::CTime's members that cdate.cpp, cdatetime.cpp and ctime.cpp
// define in the skeleton link, the way the target reaches them. Their callers outside those files are not reconstructed
// yet (ledger/callgraph.tsv and the element section, read at the commit this unit starts from):
// - the constructors from a string, CDate's (target fn 3649) and CDateTime's (fn 5475), each fill one slot of the table
//   (`wasm-objdump -x -j Elem target/vota_web_wasm.wasm`): their addresses are taken. 3649's direct callers 2765 and 5475
//   and 5475's direct caller 2764 are this unit's. So are FormatCurrentDate's and FormatCurrentTime's (fns 5472, 5473):
//   5343 and 7787, not reconstructed, pass their slots 1103 and 1104 to api::CMTFormBuilder::AddTextField (fn 651) and
//   to fn 3058, and their one direct caller, 11216, is unit 123's.
// - every other function here is called directly, and gets more than one call site in our link, the unit's own callers
//   and the other units' counted: Format (fn 706, 15 target callers: 5472, and two stand-ins for the others), CDate()
//   (fn 1382: 1000 and a stand-in for 1543, 5586, 5626, ...), CDateTime::ConvertFromLocalTime (fn 5476: 1000 and a
//   stand-in for 11862), CDateTime(time_t) (fn 1000: Now, 5472 and 5473, and a stand-in for 10870, ...),
//   CDateTime::Now (fn 479, 33 target callers: 11198, and two stand-ins for the others), ConvertToLocalTime (fn 1381:
//   unit 101's Ajusta, 10875, 10403, and a stand-in for 5841, 7160, 7306, 10710), CDateTime's operator+= (fn 2233,
//   callers 5412, 5474, 5959, 10566 and 11825, of which 5959 and 11825 are in the link: two stand-ins),
//   std::to_string(long long) (fn
//   4658: ConvertFromLocalTime and
//   unit 152's 3612, so it stays out of line as the target's does), ConvertFromTimestamp (fn 2764: its only caller
//   7787 calls it four times, one stand-in calls it twice), CDate's operator<=> (fn 1261: 759, 11198 through
//   comum::md::CHorarioVerao::Contem, and a stand-in for 1543, ...), CDateTime's (fn 759, 15 target callers: two
//   stand-ins), CTime::Format (fn 779, 13 target callers: 5473, and two stand-ins for the others), CDate's operator+=
//   (fn 5478: operator-= and a stand-in for 654) and operator- (fn 3648, callers 654, 11861, 11862: two stand-ins).
// - the rest have two callers in the unit already and no stand-in: IsValidDate (fn 5479: 3649 and the check 5475
//   inlines), CDate(dia, mes, ano) (fn 2765: 5475, 5476 and 2233), CTime() (fn 2230: 1000 and 5475), operator-= (fn 5477:
//   operator+= and operator-). IsValidDateTime is left unrooted: its only caller is 5475, into which the target's
//   binaryen inlined it.
// Each stand-in reads the result where a target caller does, passes its arguments through, and has a body no target
// function has. Declared through asm labels with the object's signatures (a constructor returns `this`, a class returned
// by value is the address of the result, a std::string passed by reference is its address); the callers are
// address-taken from a static constructor. Compiled as uenux2 code.
#include <string>

extern "C" {
void w706_format(void*, const void*, const void*) __asm__("_ZNK3api5CDate6FormatERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
int* w1382_hoje(void*) __asm__("_ZN3api5CDateC1Ev");
int* w3649_data(void*, const void*) __asm__("_ZN3api5CDateC1ERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void w5478_soma(void*, int) __asm__("_ZN3api5CDatepLEi");
void w3648_menos(void*, const void*, int) __asm__("_ZNK3api5CDatemiEi");
int w1261_compara(const void*, const void*) __asm__("_ZNK3api5CDatessERKS0_");
void w479_agora(void*) __asm__("_ZN3api9CDateTime3NowEv");
int* w1000_tempo(void*, long long) __asm__("_ZN3api9CDateTimeC1Ex");
int* w5475_texto(void*, const void*) __asm__("_ZN3api9CDateTimeC1ERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void w5476_converte(void*, long long) __asm__("_ZN3api9CDateTime20ConvertFromLocalTimeEx");
void w2764_timestamp(void*, const void*) __asm__("_ZN3api9CDateTime20ConvertFromTimestampERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
int w759_compara(const void*, const void*) __asm__("_ZNK3api9CDateTimessERKS0_");
long long w1381_tempo(const void*) __asm__("_ZNK3api9CDateTime18ConvertToLocalTimeEv");
void w2233_soma(void*, int) __asm__("_ZN3api9CDateTimepLEi");
void w779_format(void*, const void*, const void*) __asm__("_ZNK3api5CTime6FormatERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void w5472_data(void*, const void*) __asm__("_ZN3api9CDateTime17FormatCurrentDateERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void w5473_hora(void*, const void*) __asm__("_ZN3api9CDateTime17FormatCurrentTimeERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
}

namespace {

__attribute__((noinline)) void DataFormatada(void* texto, const void* data, const void* formato)
{
    w706_format(texto, data, formato);
}

__attribute__((noinline)) void DataFormatadaDuasVezes(void* texto, void* outro, const void* data, const void* formato)
{
    w706_format(texto, data, formato);
    w706_format(outro, data, formato);
}

__attribute__((noinline)) int DiaDeHoje()
{
    int data[2];
    return *w1382_hoje(data) & 0xffff;
}

__attribute__((noinline)) void SomaDias(void* data, int dias)
{
    w5478_soma(data, dias + 1);
}

__attribute__((noinline)) void DiasAntes(void* resultado, const void* data, int dias)
{
    w3648_menos(resultado, data, dias);
}

__attribute__((noinline)) void SemanaAntes(void* resultado, const void* data)
{
    w3648_menos(resultado, data, 7);
}

__attribute__((noinline)) bool DataAnterior(const void* data, const void* outra)
{
    return static_cast<signed char>(w1261_compara(data, outra)) < 0;
}

__attribute__((noinline)) void DataHoraAgora(void* dataHora)
{
    w479_agora(dataHora);
}

__attribute__((noinline)) void DuasDataHorasAgora(void* dataHora, void* outra)
{
    w479_agora(dataHora);
    w479_agora(outra);
}

__attribute__((noinline)) int DataHoraDoTempo(void* dataHora, long long tempo)
{
    return *w1000_tempo(dataHora, tempo + 1);
}

__attribute__((noinline)) void ConverteTempo(void* dataHora, long long tempo)
{
    w5476_converte(dataHora, tempo * 2);
}

__attribute__((noinline)) void DoisTimestamps(void* dataHora, void* outra, const void* timestamp, const void* outro)
{
    w2764_timestamp(dataHora, timestamp);
    w2764_timestamp(outra, outro);
}

__attribute__((noinline)) bool DataHoraAnterior(const void* dataHora, const void* outra)
{
    return static_cast<signed char>(w759_compara(dataHora, outra)) < 0;
}

__attribute__((noinline)) bool DataHoraPosterior(const void* dataHora, const void* outra)
{
    return static_cast<signed char>(w759_compara(outra, dataHora)) < 0;
}

__attribute__((noinline)) void HoraFormatada(void* texto, const void* hora, const void* formato)
{
    w779_format(texto, hora, formato);
}

__attribute__((noinline)) void HoraFormatadaDuasVezes(void* texto, void* outro, const void* hora, const void* formato)
{
    w779_format(texto, hora, formato);
    w779_format(outro, hora, formato);
}

__attribute__((noinline)) long long TempoDaDataHora(const void* dataHora)
{
    return w1381_tempo(dataHora);
}

__attribute__((noinline)) void SomaSegundos(void* dataHora, int segundos)
{
    w2233_soma(dataHora, segundos);
}

__attribute__((noinline)) void SomaMinutos(void* dataHora, int minutos)
{
    w2233_soma(dataHora, minutos * 60);
}

void* volatile w125_sink;

struct SW125Roots {
    SW125Roots()
    {
        w125_sink = reinterpret_cast<void*>(&w3649_data);
        w125_sink = reinterpret_cast<void*>(&w5475_texto);
        w125_sink = reinterpret_cast<void*>(&w5472_data);
        w125_sink = reinterpret_cast<void*>(&w5473_hora);
        w125_sink = reinterpret_cast<void*>(&DataFormatada);
        w125_sink = reinterpret_cast<void*>(&DataFormatadaDuasVezes);
        w125_sink = reinterpret_cast<void*>(&DiaDeHoje);
        w125_sink = reinterpret_cast<void*>(&SomaDias);
        w125_sink = reinterpret_cast<void*>(&DiasAntes);
        w125_sink = reinterpret_cast<void*>(&SemanaAntes);
        w125_sink = reinterpret_cast<void*>(&DataAnterior);
        w125_sink = reinterpret_cast<void*>(&DataHoraAgora);
        w125_sink = reinterpret_cast<void*>(&DuasDataHorasAgora);
        w125_sink = reinterpret_cast<void*>(&DataHoraDoTempo);
        w125_sink = reinterpret_cast<void*>(&ConverteTempo);
        w125_sink = reinterpret_cast<void*>(&DoisTimestamps);
        w125_sink = reinterpret_cast<void*>(&DataHoraAnterior);
        w125_sink = reinterpret_cast<void*>(&DataHoraPosterior);
        w125_sink = reinterpret_cast<void*>(&HoraFormatada);
        w125_sink = reinterpret_cast<void*>(&HoraFormatadaDuasVezes);
        w125_sink = reinterpret_cast<void*>(&TempoDaDataHora);
        w125_sink = reinterpret_cast<void*>(&SomaSegundos);
        w125_sink = reinterpret_cast<void*>(&SomaMinutos);
    }
} w125_roots;

} // namespace
