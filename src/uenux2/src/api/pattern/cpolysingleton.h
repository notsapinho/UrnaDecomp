#pragma once

// api::CPolySingleton<T> (/home/rubio/tse/uenux2/src/api/pattern/cpolysingleton.h). Its one record is the throw, line
// 78, column 19, in 44 instantiations. The reconstruction's notes are in unit 100's fragment. T must be complete: typeid
// does not take an incomplete type. The parameters are the records'; their names, local among them, are chosen.

#include <memory>
#include <source_location>
#include <string>
#include <typeinfo>

#include "api/pattern/cpolysingletonlist.h"
#include "ecourna/api/pattern/epatternerror.hpp"

namespace api {

// (original lines 17-70: content not recovered)
#line 71
template <typename T>
class CPolySingleton {
public:
    static T& instance(TPolySingletonsInfo& info = g_polySingletonsInfo(), const std::source_location& local = std::source_location::current())
    {
        using namespace std::string_literals;
        if (!CPolySingletonList::has<T>()) {
            throw ecourna::api::pattern::CPatternError(ecourna::api::pattern::EPE_INSTANCIA_NAO_CRIADA,
                "PolySingleton - solicitada uma instancia nao criada "s + typeid(T).name() + " ["s + local.file_name() + ":" + std::to_string(local.line()) + "]");
        }
        return CPolySingletonList::instance<T>(info);
    }

    static void set(std::unique_ptr<T> instancia, TPolySingletonsInfo& info = g_polySingletonsInfo())
    {
        CPolySingletonList::remove<T>(info);
        CPolySingletonList::push(std::move(instancia), info);
    }
};

} // namespace api
