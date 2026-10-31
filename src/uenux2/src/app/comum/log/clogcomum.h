#pragma once

// comum::CLogComum: the log calls the applications share. The records of clogcomum.cpp name the class and its members,
// and their text has no `static`, so they are members; binaryen removed the `this` none of them reads. A one-byte
// object: fn 948, called just before fns 5875 and 5876 with its result dropped (fns 10226, 12098), is GetInst, one of the
// four thunks of fn 2900 that allocate one byte and keep it in a static std::unique_ptr under a static std::mutex.
// The constructor and the destructor are out of line and GetInst is in the class: unit 111's fragment has the
// measurement. GetInst and its statics' names are chosen, from the project's other singletons. EStatusOperacaoRelatorio: the record
// names it, unqualified; fn 12098 passes 0 before it writes a result and 1 after, and fn 5876 prints "Início" for 0 and
// "Término" otherwise, so its enumerators' names are chosen from those texts. This header's path is chosen, beside
// clogcomum.cpp, and only the members written here are declared.

#include <memory>
#include <mutex>

#include "app/comum/carquivosresultado.h"
#include "ecourna/api/uetypes.hpp"

namespace comum {

enum EStatusOperacaoRelatorio {
    STATUS_OPERACAO_INICIO = 0,
    STATUS_OPERACAO_TERMINO = 1,
};

class CLogComum {
public:
    ~CLogComum();

    static CLogComum& GetInst()
    {
        std::lock_guard<std::mutex> trava(s_mutex);
        if (!s_instancia) {
            s_instancia.reset(new CLogComum);
        }
        return *s_instancia;
    }

    void LogaCopiandoArqResParaFI(EExtensaoArquivoResultado extensao);
    void LogaResultadoCopiadoResFE(EExtensaoArquivoResultado extensao);
    void LogaGerandoResultados(EExtensaoArquivoResultado extensao, EStatusOperacaoRelatorio status);
    void LogaNivelBateria(uebyte fonte, uebyte status);

private:
    CLogComum();

    static std::unique_ptr<CLogComum> s_instancia;
    static std::mutex s_mutex;
};

} // namespace comum
