// Roots: nothing in the skeleton reaches the SQLite DAO. The target builds the connection in fns 3768 and 7787 (the
// latter twice): `new CSqlConnection(path)` into a std::shared_ptr<ISqlConnection>, the
// __shared_ptr_pointer<CSqlConnection*, ...> vptr 1559008 stored right after the constructor's call (3515). These two
// stand-ins do the same, with different bodies, and are address-taken from a static constructor: two call sites keep
// the constructor out of line. CSqlConnection::Prepare builds the CSqlStatement and its Execute the CSqlResultSet, so
// the two other vtables follow from the first.
//
// As units 29 and 58 do for make_shared, this TU includes the class header: the control block it instantiates,
// __shared_ptr_pointer<CSqlConnection*, ...> (fns 11539, 11538, whose vtable lies in uenux2's data band: the target's
// copy is a uenux2 caller's) comes from celeitordinamicodao.cpp.o, the real caller, earlier in the link. The
// class's inline members still come from the unit's object, earlier on the link line. Compiled with APP_CXXFLAGS and
// Boost's headers, which isqlresultset.hpp includes.
#include <memory>
#include <string>

#include "ecourna/api/sql/sqlite/csqlconnection.hpp"

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

void* volatile rsql_sink;

struct SRsqlRoots {
    SRsqlRoots()
    {
        rsql_sink = reinterpret_cast<void*>(&AbreConexao);
        rsql_sink = reinterpret_cast<void*>(&ConexaoFechada);
    }
} rsql_roots;

} // namespace
