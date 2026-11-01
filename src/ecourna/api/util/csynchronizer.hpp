#pragma once

#include <memory>

namespace ecourna::api::util {

// Process-wide switch deciding whether CFile::Sync() really fsyncs its descriptor.
class CSynchronizer {
public:
    static void CreateInst(bool habilitado);

    static CSynchronizer& GetInst()
    {
        if (s_instancia == nullptr) {
            CreateInst(true);
        }
        return *s_instancia;
    }

    int Sync(int descritor) const;

private:
    explicit CSynchronizer(bool habilitado) : m_habilitado(habilitado) {}

    bool m_habilitado;

    // A unique_ptr: target fn 9268, table slot 6618, destroys the word CFile::Sync (5181) reads through fn 349, the
    // reset-and-free body that other static unique_ptrs' destructors share (CAguardaMensagem::s_inst's). Its name is
    // chosen.
    static std::unique_ptr<CSynchronizer> s_instancia;
};

} // namespace ecourna::api::util
