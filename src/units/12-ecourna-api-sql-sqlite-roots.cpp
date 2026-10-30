// Roots: nothing in the skeleton reaches the SQLite DAO. The target builds the connection in fns 3768 and 7787 (the
// latter twice): `new CSqlConnection(path)` into a std::shared_ptr<ISqlConnection>, the
// __shared_ptr_pointer<CSqlConnection*, ...> vptr 1559008 stored right after the constructor's call (3515). These two
// stand-ins do the same, with different bodies, and are address-taken from a static constructor: two call sites keep
// the constructor out of line. CSqlConnection::Prepare builds the CSqlStatement and its Execute the CSqlResultSet, so
// the two other vtables follow from the first.
//
// As units 29 and 58 do for make_shared, this TU includes the class header: the control block it instantiates,
// __shared_ptr_pointer<CSqlConnection*, ...> (fns 11539, 11538, whose vtable lies in uenux2's data band: the target's
// copy is a uenux2 caller's) is this object's own, and it moves to the real callers' objects when they land. The
// class's inline members still come from the unit's object, earlier on the link line. Compiled with APP_CXXFLAGS and
// Boost's headers, which isqlresultset.hpp includes.
//
// Two library helpers the externs call have a second caller in the target that is not reconstructed, as unit 07's
// roots do for std::regex: std::set<int>'s initializer-list constructor (fn 5157, called by 5158 and 3509) and
// string::replace(pos, n, const char*, n) (fn 4667, called by 9398 and 9407). One stand-in each keeps them out of
// line, declared through asm labels so this TU instantiates neither.
#include <memory>
#include <string>

#include "ecourna/api/sql/sqlite/csqlconnection.hpp"

extern "C" int rsql_set_ctor(int, int, int) __asm__("_ZNSt3__23setIiNS_4lessIiEENS_9allocatorIiEEEC2B8ne210108ESt16initializer_listIiERKS2_");
extern "C" int rsql_string_replace(int, int, int, int, int) __asm__("_ZNSt3__212basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE7replaceEmmPKcm");

namespace {

using ecourna::api::sql::TSharedSqlConnection;
using ecourna::api::sql::sqlite::CSqlConnection;

__attribute__((noinline)) TSharedSqlConnection AbreConexao(const std::string& caminho)
{
    return TSharedSqlConnection(new CSqlConnection(caminho));
}

// asks the connection something, so the two callers differ
__attribute__((noinline)) bool ConexaoFechada(const std::string& caminho)
{
    TSharedSqlConnection conexao(new CSqlConnection(caminho));
    return conexao->IsClosed();
}

__attribute__((noinline)) void TrocaTrecho(int texto, int posicao, int tamanho, int novo)
{
    rsql_string_replace(texto, posicao, tamanho, novo, tamanho + 1);
}

__attribute__((noinline)) int ConjuntoDeInteiros(int conjunto, int lista, int comparador)
{
    return rsql_set_ctor(conjunto, lista + 4, comparador);
}

void* volatile rsql_sink;

struct SRsqlRoots {
    SRsqlRoots()
    {
        rsql_sink = reinterpret_cast<void*>(&AbreConexao);
        rsql_sink = reinterpret_cast<void*>(&ConexaoFechada);
        rsql_sink = reinterpret_cast<void*>(&TrocaTrecho);
        rsql_sink = reinterpret_cast<void*>(&ConjuntoDeInteiros);
    }
} rsql_roots;

} // namespace
