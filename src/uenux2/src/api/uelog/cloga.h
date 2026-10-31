#pragma once

// api::CLoga: the application's entry to the log. Its one member's record is cloga.cpp:26, so the class and the member
// are the target's; that the class holds nothing else, and this header's path, beside cloga.cpp, are chosen.

#include <string>

#include "api/uelog/cescritorlog.h"

namespace api {

class CLoga {
public:
    static void loga(ELogAplicativos aplicativo, ESeveridade severidade, const std::string& mensagem);
};

} // namespace api
