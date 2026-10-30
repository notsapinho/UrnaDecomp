#include "ecourna/api/sql/sqlite/csqlstatement.hpp"

#include <mutex>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <sqlite3.h>

#include "ecourna/api/sql/esqlerror.hpp"
#include "ecourna/api/sql/sqlite/csqlresultset.hpp"
#include "ecourna/api/sql/sqlite/sqliteutils.hpp"
#include "ecourna/api/util/cstringutils.hpp"

namespace ecourna::api::sql::sqlite {

namespace {

std::mutex s_mutex;

} // namespace

CSqlStatement::CSqlStatement(sqlite3* db, sqlite3_stmt* stmt) : m_db(db), m_stmt(stmt), m_fechado(false)
{
    s_mutex.lock();
    m_numeroParametros = sqlite3_bind_parameter_count(m_stmt);
}

CSqlStatement::~CSqlStatement()
{
    if (!m_fechado) {
        try {
            Close();
        } catch (...) {
        }
    }
}

// (original lines 37-47: content not recovered)
#line 48
void CSqlStatement::SetInt(int indice, int valor)
{
    VerifyParameterIndex(indice);
    const int resultado = sqlite3_bind_int(m_stmt, indice, valor);
    if (resultado != SQLITE_OK) {
        throw CSqlError(ESE_SET_INT, ObterMensagemErro(m_db));
    }
}


void CSqlStatement::SetInt64(int indice, ueint64 valor)
{
    VerifyParameterIndex(indice);
    const int resultado = sqlite3_bind_int64(m_stmt, indice, valor);
    if (resultado != SQLITE_OK) {
        throw CSqlError(ESE_SET_INT64, ObterMensagemErro(m_db));
    }
}


void CSqlStatement::SetDouble(int indice, double valor)
{
    VerifyParameterIndex(indice);
    const int resultado = sqlite3_bind_double(m_stmt, indice, valor);
    if (resultado != SQLITE_OK) {
        throw CSqlError(ESE_SET_DOUBLE, ObterMensagemErro(m_db));
    }
}


void CSqlStatement::SetText(int indice, const std::string& valor)
{
    VerifyParameterIndex(indice);
    const int resultado = sqlite3_bind_text(m_stmt, indice, valor.c_str(), valor.size(), SQLITE_TRANSIENT);
    if (resultado != SQLITE_OK) {
        throw CSqlError(ESE_SET_TEXT, ObterMensagemErro(m_db));
    }
}

void CSqlStatement::SetDateTime(int indice, const boost::posix_time::ptime& valor)
{
    std::string texto = boost::posix_time::to_iso_extended_string(valor);
    util::CStringUtils::Replace(texto, 'T', " ");

    SetText(indice, texto);
}

void CSqlStatement::SetBool(int indice, bool valor)
{
    SetInt(indice, valor);
}

// (original lines 100-103: content not recovered)
#line 104
void CSqlStatement::SetBlob(int indice, const std::vector<uebyte>& valor)
{
    VerifyParameterIndex(indice);
    const int resultado = sqlite3_bind_blob(m_stmt, indice, valor.data(), valor.size(), SQLITE_TRANSIENT);
    if (resultado != SQLITE_OK) {
        throw CSqlError(ESE_SET_BLOB, ObterMensagemErro(m_db));
    }
}


void CSqlStatement::SetNull(int indice)
{
    VerifyParameterIndex(indice);
    const int resultado = sqlite3_bind_null(m_stmt, indice);
    if (resultado != SQLITE_OK) {
        throw CSqlError(ESE_SET_NULL, ObterMensagemErro(m_db));
    }
}

TSharedSqlResultSet CSqlStatement::Execute()
{
    return TSharedSqlResultSet(new CSqlResultSet(m_db, m_stmt));
}


void CSqlStatement::Reset()
{
    const int resultado = sqlite3_reset(m_stmt);
    if (resultado != SQLITE_OK) {
        throw CSqlError(ESE_RESET, ObterMensagemErro(m_db));
    }
}

// (original lines 137-138: content not recovered)
#line 139
void CSqlStatement::Close()
{
    try {
        if (sqlite3_finalize(m_stmt) != SQLITE_OK) {
            throw CSqlError(ESE_FECHAR_COMANDO, ObterMensagemErro(m_db));
        }

        m_fechado = true;
        s_mutex.unlock();
    } catch (...) {
        s_mutex.unlock();
        throw;
    }
}


void CSqlStatement::VerifyParameterIndex(int indice) const
{
    if (indice <= 0 || indice > m_numeroParametros) {
        throw CSqlError(ESE_INDICE_PARAMETRO, "Índice do parâmetro fora do intervalo válido.");
    }
}

bool CSqlStatement::IsClosed() const
{
    return m_fechado;
}

} // namespace ecourna::api::sql::sqlite
