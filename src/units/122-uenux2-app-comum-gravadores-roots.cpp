// Roots: reach unit 122's functions the way the target's callers do, until they land. Every stand-in here has a body no
// target function has: each calls the unit's functions with its own arguments and folds their results, and none is
// called. Each function below has direct callers in the target, so each gets two call sites in our link and stays out
// of line, and the stand-ins pass what the target's callers vary as variables or as different constants, so that
// binaryen folds no argument:
// - comum::CGravadorWSQ's constructor (fn 3796): fn 12098 calls it three times, with the extension 16, 17 and 18, the
//   SAVD file 48, 49 and 50 and the type of biometrics 0, 1 and 2;
// - comum::IGravador's constructor (fn 1396): fns 3796, 5856 and 12098; 3796 and 5856 (unit 160) are written, the
//   stand-in is for 12098;
// - comum::CGravadorUtil::ConverteFase (fn 2274): fns 3796, 5856 and 12098, the same way;
// - comum::CGravadorUtil::DeterminaNomeArquivo (fn 3798): fns 1276, 1396 and 12134; 1396 and 1276 (unit 160) are
//   written;
// - comum::asn::ConverteSerialFlash and DesconverteSerialFlash (fns 3605, 3604) need none: their callers, fns 10287,
//   10291 and 11399, and 10284, 10290 and 11400, are written (units 160 and 172);
// - comum::md::CVersoesArquivos's constructor (fn 5867): fn 12098 (10263 is in the link); and libc++'s hinted emplace
//   into a std::map<std::string, std::string> (fn 1221), which the constructor's copy of the map calls: fns 5867 and
//   12098 (3689 and 4625 are in the link). The constructors' results are not read, as the target's callers do not read them
//   (fn 5867 returns nothing);
// - comum::GetPathWsqNaoRegistrado (fn 3793) needs none now: its callers, fns 5374 (unit 214) and 10451 (unit 221),
//   are written, and the stand-in for 10451 went.
// - the other WSQ directories of pathwsq.cpp (fns 5819, 5818, 3795, 5817, 5816 and 3794) need none now: fns 5821 and
//   10425 call each, and 5382 calls 3795 and 3794; 5821 (CGravadorWSQ::CompactaWsq), 5382 (unit 135) and 10425 (unit
//   142) are written, and the stand-in for 10425 went.
// - comum::GetPathWsqRegistrado (fn 5815) needs none now: fns 3614 (unit 221) and 5382 (unit 135) are written.
// - comum::CGravadorRCSecao's vtable (@1554740), whose deleting destructor (fn 11615) the target reaches only through
//   it: the constructor that stores it (inlined into fn 12098, which is not written) is written but unrooted, so its
//   address goes into a sink, which stands for 12098.
// IGravador is abstract, so its constructor (declared with the object's int result) is called through an asm label.
#include <filesystem>
#include <map>
#include <new>
#include <string>
#include <vector>

#include "app/comum/carquivosresultado.h"
#include "app/comum/gravadores/cgravadorutil.h"
#include "app/comum/gravadores/cgravadorwsq.h"
#include "app/comum/gravadores/md/cversoesarquivos.h"
#include "app/comum/gravadores/pathwsq.h"

extern "C" int w122_igravador(void* objeto, unsigned int municipio, unsigned int zona, unsigned int local,
    unsigned int secao, int fase, int extensao, int arquivoSavd)
    __asm__("_ZN5comum9IGravadorC2EjtjtcNS_25EExtensaoArquivoResultadoENS_14ESavdArquivoUEE");

extern "C" const char w122_vt_rcsecao[] __asm__("_ZTVN5comum16CGravadorRCSecaoE");

namespace {

// stands for fn 12098
__attribute__((noinline)) int w122_wsq(const api::CDateTime& dataHora, comum::TMunicipioID municipio, comum::TZonaID zona,
    comum::TLocalID local, comum::TSecaoID secao, char fase, bool externa)
{
    comum::CGravadorWSQ* bio = new comum::CGravadorWSQ(dataHora, municipio, zona, local, secao, fase,
        comum::EXTENSAO_WSQBIO_JEZ, static_cast<comum::ESavdArquivoUE>(48), comum::TIPO_BIOMETRIA_HABILITADO, externa);
    comum::CGravadorWSQ* man = new comum::CGravadorWSQ(dataHora, municipio, zona, local, secao, fase,
        comum::EXTENSAO_WSQMAN_JEZ, static_cast<comum::ESavdArquivoUE>(49), comum::TIPO_BIOMETRIA_NAO_HABILITADO,
        !externa);
    return (bio == man) ? 3 : 5;
}

// stands for fn 12098 (5856 is written)
__attribute__((noinline)) int w122_gravador(void* objeto, unsigned int municipio, unsigned int zona, unsigned int local,
    unsigned int secao, char fase)
{
    const int faseUrna = comum::CGravadorUtil::ConverteFase(fase);
    return w122_igravador(objeto, municipio, zona, local, secao, fase, comum::EXTENSAO_BU_DAT, 35) + faseUrna;
}

// stands for fn 12134
__attribute__((noinline)) int w122_nome(comum::TMunicipioID municipio, comum::TZonaID zona, comum::TSecaoID secao, char fase,
    comum::EExtensaoArquivoResultado extensao)
{
    return static_cast<int>(comum::CGravadorUtil::DeterminaNomeArquivo(municipio, zona, secao, fase, extensao).size()) + 7;
}

// stands for fn 12098 (10263 is in the link); its copy of a map, which stood for fn 4625's call of libc++'s hinted
// emplace into a std::map<std::string, std::string> (fn 1221), went: 4625 is in the link (unit 168)
__attribute__((noinline)) int w122_versoes(const std::string& tag, const comum::md::CVersoesArquivos::TMapVersoes& versoes,
    const std::string& outra)
{
    new comum::md::CVersoesArquivos(tag, versoes);
    new comum::md::CVersoesArquivos(outra, versoes);
    return static_cast<int>(versoes.size()) + 11;
}

int (*volatile w122_sink_wsq)(const api::CDateTime&, comum::TMunicipioID, comum::TZonaID, comum::TLocalID, comum::TSecaoID,
    char, bool);
int (*volatile w122_sink_gravador)(void*, unsigned int, unsigned int, unsigned int, unsigned int, char);
int (*volatile w122_sink_nome)(comum::TMunicipioID, comum::TZonaID, comum::TSecaoID, char, comum::EExtensaoArquivoResultado);
int (*volatile w122_sink_versoes)(const std::string&, const comum::md::CVersoesArquivos::TMapVersoes&, const std::string&);
const void* volatile w122_sink_vt_rcsecao;

struct SW122Roots {
    SW122Roots()
    {
        w122_sink_wsq = w122_wsq;
        w122_sink_gravador = w122_gravador;
        w122_sink_nome = w122_nome;
        w122_sink_versoes = w122_versoes;
        w122_sink_vt_rcsecao = w122_vt_rcsecao;
    }
} w122_roots;

} // namespace
