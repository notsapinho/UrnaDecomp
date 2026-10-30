#pragma once

// api::CPolySingletonList, the registry behind api::CPolySingleton (/home/rubio/tse/uenux2/src/api/pattern/
// cpolysingletonlist.h; the records' lines are 99, 105 and 129). The reconstruction's notes are in unit 100's fragment.
//
// Only has and instance are written, and what they call. push (record at line 129; fn 3882 is one of its bodies) is
// not, so that line is blank. TPolySingletonsInfo is the records' name; every other name here is chosen unless the fragment
// says otherwise. The offsets are the bytes': a vector of 24-byte entries at +0 (fns 6161, 6779), a byte at +12 that fn
// 11265 sets and fn 14476 reads, the lock at +16, 148 bytes in all (fn 11265's guard follows). An entry is a string at
// +0, a std::type_info pointer at +12 (fn 512 reads the name through it) and a std::shared_ptr at +16.

#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <format>
#include <memory>
#include <ranges>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>

#include <cxxabi.h>
#include <syslog.h>
#include <unistd.h>

#include "api/pattern/cmutexcompartilhado.h"
#include "api/pattern/euepatternerror.h"

namespace api {

struct SPolySingletonInfo {
    std::string m_nome;
    const std::type_info* m_tipo;
    std::shared_ptr<void> m_instancia;
};

struct TPolySingletonsInfo {
    std::vector<SPolySingletonInfo> m_lista;
    bool m_depuracao = false;
    mutable CMutexCompartilhado m_mutex;
};

extern TPolySingletonsInfo& (*g_polySingletonsInfo)();

// (original lines 47-88: content not recovered)
#line 89
class CPolySingletonList {
public:
    template <typename INTERFACE>
    static INTERFACE& instance(TPolySingletonsInfo& info)
    {
        CTravaLeitura trava(info.m_mutex);
        const std::string nome = typeid(INTERFACE).name();
        const auto [encontrada, it] = find(nome, info);
        if (!encontrada) {
            trace(__func__, nome, "find");
            throw CUePatternError(EUE_PATTERN_INSTANCIA_NAO_CRIADA,
                std::format("{}: solicitada uma instância não criada de {}", __func__, nome));
        }

        if (*it->m_tipo != typeid(INTERFACE)) {
            trace(__func__, nome, "typeid");
            throw CUePatternError(EUE_PATTERN_INSTANCIA_INCOMPATIVEL,
                std::format("{}: instância {} não corresponde a interface solicitada de {}", __func__, it->m_nome, nome));
        }
        const auto instancia = std::static_pointer_cast<INTERFACE>(it->m_instancia);
        return *instancia;
    }

    template <typename INTERFACE>
    static bool has(const TPolySingletonsInfo& info = g_polySingletonsInfo())
    {
        const std::string nome = typeid(INTERFACE).name();
        CTravaLeitura trava(info.m_mutex);
        return find(nome, info).first;
    }

private:
    // fn 212 in the target, the executable TU's copy, so it matches from no object of ours
    static void trace(const std::string& funcao, const std::string& nome, const std::string& acao)
    {
        const std::string legivel = demangle(nome);
        std::string chamadas;
        if (funcao.substr(0, 4) != "list") {
            chamadas = std::string("");
        }
        debug("CPolySingletonList::%s(%s[%s])[%s] %s%s", funcao.c_str(), nome.c_str(), legivel.c_str(), acao.c_str(),
            chamadas.empty() ? "" : "{calls}", chamadas.c_str());
    }

    // the head of fn 212, which binaryen inlined there
    static std::string demangle(const std::string& nome)
    {
        int status = 0;
        std::unique_ptr<char, void (*)(void*)> texto(abi::__cxa_demangle(nome.c_str(), nullptr, nullptr, &status), std::free);
        std::string legivel;
        if (status == 0) {
            legivel = texto.get();
        } else {
            legivel = std::string("...");
        }
        return legivel;
    }

    // fn 13156. Its printf of a 140-byte local before the vprintf is not written: nothing in the target fills that buffer
    static void debug(const char* formato, ...)
    {
        static int s_urna = -1;
        if (s_urna == -1) {
            s_urna = access("/dev/urna", F_OK) == 0;
        }
        va_list argumentos;
        va_start(argumentos, formato);
        if (s_urna) {
            vsyslog(LOG_INFO, formato, argumentos);
        } else if (getenv("DEBUG_UENUX")) {
            vprintf(formato, argumentos);
        }
        va_end(argumentos);
    }

    // fns 305 (instance's) and 608 (has's), the executable TU's copies, under one merged body, fn 6161. The constness is chosen
    template <typename TInfo>
    static auto find(const std::string& nome, TInfo& info)
    {
        const auto it = std::ranges::find_if(info.m_lista, [nome](const SPolySingletonInfo& e) { return e.m_nome == nome; });
        return std::make_pair(it != info.m_lista.end(), it);
    }
};

} // namespace api
