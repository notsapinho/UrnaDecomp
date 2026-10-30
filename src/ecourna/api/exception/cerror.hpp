#pragma once
#include <exception>
#include <source_location>
#include <string>
#include <utility>

namespace ecourna::api::exception {

class CError : public std::exception {
public:
    CError(int codigo, std::string mensagem, std::source_location local);

    // Reconstruction note: one constructor per error enum, which CBaseError's calls. It holds the second move of the
    // message that fns 1011 and 710 inline, and is fn 2379 out of line. src/units/94-ecourna-cbaseerror.mk has the evidence.
    template <typename E>
    CError(E codigo, std::string mensagem, std::source_location local)
        : CError(static_cast<int>(codigo), std::move(mensagem), local)
    {
    }

    const char* what() const noexcept override { return m_descricao.c_str(); }
    int GetCodigo() const { return m_codigo; }
    const std::string& GetMensagem() const { return m_mensagem; }
    const std::source_location& GetLocal() const { return m_local; }

private:
    int m_codigo;
    std::string m_mensagem;
    std::source_location m_local;
    unsigned int m_reservado;
    std::string m_descricao;
};

} // namespace ecourna::api::exception
