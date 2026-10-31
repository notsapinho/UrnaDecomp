// api::CLoga (/home/rubio/tse/uenux2/src/api/uelog/cloga.cpp). Its one record is a record of the target:
//   433  static void loga(ELogAplicativos, ESeveridade, const std::string &)  record at line 26, column 36
// The reconstruction's notes are in unit 111's fragment.

#include "api/uelog/cloga.h"

#include "api/pattern/cpolysingleton.h"

namespace api {

// (original lines 11-23: content not recovered)
#line 24
void CLoga::loga(ELogAplicativos aplicativo, ESeveridade severidade, const std::string& mensagem)
{
    CEscritorLog& escritorDeLogs = CPolySingleton<CEscritorLog>::instance();
    escritorDeLogs.loga(aplicativo, severidade, mensagem);
}

} // namespace api
