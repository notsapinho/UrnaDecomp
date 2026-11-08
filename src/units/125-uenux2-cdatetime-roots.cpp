// Roots: keep api::CDate's, api::CDateTime's and api::CTime's members that cdate.cpp, cdatetime.cpp and ctime.cpp
// define in the skeleton link, the way the target reaches them. Their callers outside those files are not reconstructed
// yet (ledger/callgraph.tsv and the element section, read at the commit this unit starts from):
// - the constructors from a string, CDate's (target fn 3649) and CDateTime's (fn 5475), each fill one slot of the table
//   (`wasm-objdump -x -j Elem target/vota_web_wasm.wasm`): their addresses are taken. 3649's direct callers 2765 and 5475
//   and 5475's direct caller 2764 are this unit's. So are FormatCurrentDate's and FormatCurrentTime's (fns 5472, 5473):
//   5343 (unit 165's, matched) and 7787 (not reconstructed) pass their slots 1103 and 1104 to
//   api::CMTFormBuilderBase::AddTextField (fn 651) and to fn 3058, and their one direct caller, 11216, is unit 123's.
// - every other function here is called directly, and gets more than one call site in our link, the unit's own callers
//   and the other units' counted: Format (fn 706, 15 target callers: 5472, and a stand-in for 12110), CDate() (fn
//   1382: its eight target callers, 1000, 1543, 5586, 5626, 5782, 7160, 11902 and 14478, are in the link, no
//   stand-in), CDateTime::ConvertFromLocalTime (fn 5476: 1000 and 11862, in the link, no stand-in), CDateTime(time_t)
//   (fn 1000: its eleven target callers, Now, 5472, 5473, 10870, 10401, 10402 and 11914 among them, are in the link,
//   no stand-in), CDateTime::Now (fn 479, 33 target callers: 11198, and two stand-ins for the others),
//   ConvertToLocalTime (fn 1381: unit 101's Ajusta, 10875, 10403, 7160, unit 329's, 10710, unit 277's, 7306, unit
//   104's, and 5841, unit 122's, all in the link, no stand-in), CDateTime's operator+= (fn 2233: its callers 5412,
//   5474, 5959, 10566 and 11825 are in the link, no stand-in), std::to_string(long long) (fn 4658:
//   ConvertFromLocalTime and unit 152's 3612, so it stays out of line as the target's does), ConvertFromTimestamp (fn
//   2764: its only caller 7787 calls it four times, one stand-in calls it twice), CDate's operator<=> (fn 1261: its
//   nine target callers, 759, 11198 through comum::md::CHorarioVerao::Contem, 1543 and 11902 among them, are in the
//   link, no stand-in), CDateTime's (fn 759, 15 target callers: two stand-ins), CTime::Format (fn 779, 13 target
//   callers: 5473 and 7787's two calls, which unit 443's constructor makes, no stand-in; HoraFormatada stood for
//   7787's until then) and CDate's operator- (fn 3648, callers 654, 11861, 11862: 654,
//   CTradutorFrase::Traduz, and 11861 and 11862, CPreZeresima's GetEstadoSemTeste and GetTela (unit 138), are in the
//   link, no stand-in).
// - the rest have two callers in the link already and no stand-in: IsValidDate (fn 5479: 3649 and the check 5475
//   inlines), CDate(dia, mes, ano) (fn 2765: 5475, 5476 and 2233), CTime() (fn 2230: 1000 and 5475), operator-= (fn 5477:
//   operator+= and operator-), CDate's operator+= (fn 5478: operator-= and 654). IsValidDateTime is left unrooted: its
//   only caller is 5475, into which the target's binaryen inlined it.
// Each stand-in reads the result where a target caller does, passes its arguments through, and has a body no target
// function has. Declared through asm labels with the object's signatures (a constructor returns `this`, a class returned
// by value is the address of the result, a std::string passed by reference is its address); the callers are
// address-taken from a static constructor. Compiled as uenux2 code.
#include <string>

extern "C" {
void w706_format(void*, const void*, const void*) __asm__("_ZNK3api5CDate6FormatERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
int* w3649_data(void*, const void*) __asm__("_ZN3api5CDateC1ERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void w479_agora(void*) __asm__("_ZN3api9CDateTime3NowEv");
int* w5475_texto(void*, const void*) __asm__("_ZN3api9CDateTimeC1ERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void w2764_timestamp(void*, const void*) __asm__("_ZN3api9CDateTime20ConvertFromTimestampERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
int w759_compara(const void*, const void*) __asm__("_ZNK3api9CDateTimessERKS0_");
void w5472_data(void*, const void*) __asm__("_ZN3api9CDateTime17FormatCurrentDateERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void w5473_hora(void*, const void*) __asm__("_ZN3api9CDateTime17FormatCurrentTimeERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
}

namespace {

__attribute__((noinline)) void DataFormatada(void* texto, const void* data, const void* formato)
{
    w706_format(texto, data, formato);
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

void* volatile w125_sink;

struct SW125Roots {
    SW125Roots()
    {
        w125_sink = reinterpret_cast<void*>(&w3649_data);
        w125_sink = reinterpret_cast<void*>(&w5475_texto);
        w125_sink = reinterpret_cast<void*>(&w5472_data);
        w125_sink = reinterpret_cast<void*>(&w5473_hora);
        w125_sink = reinterpret_cast<void*>(&DataFormatada);
        w125_sink = reinterpret_cast<void*>(&DataHoraAgora);
        w125_sink = reinterpret_cast<void*>(&DuasDataHorasAgora);
        w125_sink = reinterpret_cast<void*>(&DoisTimestamps);
        w125_sink = reinterpret_cast<void*>(&DataHoraAnterior);
        w125_sink = reinterpret_cast<void*>(&DataHoraPosterior);
    }
} w125_roots;

} // namespace
