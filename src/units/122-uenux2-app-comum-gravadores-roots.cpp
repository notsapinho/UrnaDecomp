// Roots: reach unit 122's functions the way the target's callers do, until they land. Every stand-in here has a body no
// target function has: each calls the unit's functions with its own arguments and folds their results, and none is
// called. Each function below has direct callers in the target, so each gets two call sites in our link and stays out
// of line, and the stand-ins pass what the target's callers vary as variables or as different constants, so that
// binaryen folds no argument:
// - comum::CGravadorWSQ's constructor (fn 3796): fn 12098 calls it three times, with the extension 16, 17 and 18, the
//   SAVD file 48, 49 and 50 and the type of biometrics 0, 1 and 2;
// - comum::IGravador's constructor (fn 1396): fns 3796, 5856 and 12098; 3796 is written, the stand-in is for the others;
// - comum::CGravadorUtil::ConverteFase (fn 2274): fns 3796, 5856 and 12098, the same way;
// - comum::CGravadorUtil::DeterminaNomeArquivo (fn 3798): fns 1276, 1396 and 12134; 1396 is written;
// - comum::asn::ConverteSerialFlash and DesconverteSerialFlash (fns 3605, 3604): fns 10287, 10291 and 11399, and 10284,
//   10290 and 11400;
// - comum::md::CVersoesArquivos's constructor (fn 5867): fns 10263 and 12098; and libc++'s hinted emplace into a
//   std::map<std::string, std::string> (fn 1221), which the constructor's copy of the map calls: fns 3689, 4625, 5867 and
//   12098. The constructors' results are not read, as the target's callers do not read them (fn 5867 returns nothing);
// - comum::CGravadorRCSecao::CriaIdentidadeEleitor (fn 5845): fn 11616, GravaResultado.
// - comum::CGravadorRCSecao's vtable (@1554740), whose deleting destructor (fn 11615) the target reaches only through
//   it: the constructor that stores it (inlined into fn 12098) is not written, so its address goes into a sink.
// IGravador and CGravadorRCSecao are abstract, so IGravador's constructor (declared with the object's int result) and
// the private CriaIdentidadeEleitor are called through asm labels.
#include <map>
#include <string>
#include <vector>

#include "app/comum/carquivosresultado.h"
#include "app/comum/gravadores/asn/util.h"
#include "app/comum/gravadores/cgravadorutil.h"
#include "app/comum/gravadores/cgravadorwsq.h"
#include "app/comum/gravadores/md/cversoesarquivos.h"

extern "C" int w122_igravador(void* objeto, unsigned int municipio, unsigned int zona, unsigned int local,
    unsigned int secao, int fase, int extensao, int arquivoSavd)
    __asm__("_ZN5comum9IGravadorC2E9CBaseTypeIjLj0ELj99999ELi6EES1_ItLt0ELt9999ELi7EES1_IjLj0ELj9999ELi8EES1_ItLt0ELt9999ELi9EEcNS_25EExtensaoArquivoResultadoENS_14ESavdArquivoUEE");

extern "C" void w122_cria(void* resultado, const void* gravador, const void* identidade)
    __asm__("_ZNK5comum16CGravadorRCSecao21CriaIdentidadeEleitorERKNS_2md18CEleitorIdentidadeE");

extern "C" const char w122_vt_rcsecao[] __asm__("_ZTVN5comum16CGravadorRCSecaoE");

namespace {

// stands for fn 12098
__attribute__((noinline)) int w122_wsq(const api::CDateTime& dataHora, comum::TMunicipioID municipio, comum::TZonaID zona,
    comum::TLocalID local, comum::TSecaoID secao, char fase, bool externa)
{
    comum::CGravadorWSQ* bio = new comum::CGravadorWSQ(dataHora, municipio, zona, local, secao, fase,
        comum::EXTENSAO_WSQBIO_JEZ, static_cast<comum::ESavdArquivoUE>(48), 0, externa);
    comum::CGravadorWSQ* man = new comum::CGravadorWSQ(dataHora, municipio, zona, local, secao, fase,
        comum::EXTENSAO_WSQMAN_JEZ, static_cast<comum::ESavdArquivoUE>(49), 1, !externa);
    return (bio == man) ? 3 : 5;
}

// stands for fns 5856 and 12098
__attribute__((noinline)) int w122_gravador(void* objeto, unsigned int municipio, unsigned int zona, unsigned int local,
    unsigned int secao, char fase)
{
    const int faseUrna = comum::CGravadorUtil::ConverteFase(fase);
    return w122_igravador(objeto, municipio, zona, local, secao, fase, comum::EXTENSAO_BU_DAT, 35) + faseUrna;
}

// stands for fns 1276 and 12134
__attribute__((noinline)) int w122_nome(comum::TMunicipioID municipio, comum::TZonaID zona, comum::TSecaoID secao, char fase,
    comum::EExtensaoArquivoResultado extensao)
{
    return static_cast<int>(comum::CGravadorUtil::DeterminaNomeArquivo(municipio, zona, secao, fase, extensao).size()) + 7;
}

// stands for fns 10287, 10291 and 11399, and 10284, 10290 and 11400
__attribute__((noinline)) int w122_serial(const std::string& serial, const std::string& outro, const std::vector<char>& flash,
    const std::vector<char>& outra)
{
    return static_cast<int>(comum::asn::ConverteSerialFlash(serial).size() + comum::asn::ConverteSerialFlash(outro).size() +
        comum::asn::DesconverteSerialFlash(flash).size() + comum::asn::DesconverteSerialFlash(outra).size());
}

// stands for fns 10263 and 12098, and, with its copy of a map, for fns 3689 and 4625, which call libc++'s hinted emplace
// into a std::map<std::string, std::string> (fn 1221) as the constructor's copy does
__attribute__((noinline)) int w122_versoes(const std::string& tag, const comum::md::CVersoesArquivos::TMapVersoes& versoes,
    const std::string& outra)
{
    new comum::md::CVersoesArquivos(tag, versoes);
    new comum::md::CVersoesArquivos(outra, versoes);
    const comum::md::CVersoesArquivos::TMapVersoes copia(versoes);
    return static_cast<int>(copia.size()) + 11;
}

// stands for fn 11616
__attribute__((noinline)) int w122_identidade(const void* gravador, const void* eleitor, const void* principal)
{
    alignas(8) unsigned char a[8];
    alignas(8) unsigned char b[8];
    w122_cria(a, gravador, eleitor);
    w122_cria(b, gravador, principal);
    return a[0] + b[4];
}

int (*volatile w122_sink_wsq)(const api::CDateTime&, comum::TMunicipioID, comum::TZonaID, comum::TLocalID, comum::TSecaoID,
    char, bool);
int (*volatile w122_sink_gravador)(void*, unsigned int, unsigned int, unsigned int, unsigned int, char);
int (*volatile w122_sink_nome)(comum::TMunicipioID, comum::TZonaID, comum::TSecaoID, char, comum::EExtensaoArquivoResultado);
int (*volatile w122_sink_serial)(const std::string&, const std::string&, const std::vector<char>&, const std::vector<char>&);
int (*volatile w122_sink_identidade)(const void*, const void*, const void*);
int (*volatile w122_sink_versoes)(const std::string&, const comum::md::CVersoesArquivos::TMapVersoes&, const std::string&);
const void* volatile w122_sink_vt_rcsecao;

struct SW122Roots {
    SW122Roots()
    {
        w122_sink_wsq = w122_wsq;
        w122_sink_gravador = w122_gravador;
        w122_sink_nome = w122_nome;
        w122_sink_serial = w122_serial;
        w122_sink_versoes = w122_versoes;
        w122_sink_identidade = w122_identidade;
        w122_sink_vt_rcsecao = w122_vt_rcsecao;
    }
} w122_roots;

} // namespace
