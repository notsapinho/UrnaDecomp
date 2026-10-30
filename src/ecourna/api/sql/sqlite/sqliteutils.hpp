#pragma once
#include <string>

struct sqlite3;

namespace ecourna::api::sql::sqlite {

// The target has this as one out-of-line function (fn 9411) that the connection, statement and result-set TUs call;
// no record names its file, so this file and its name are chosen.
std::string ObterMensagemErro(sqlite3* db);

} // namespace ecourna::api::sql::sqlite
