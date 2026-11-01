#pragma once

#include <cstddef>
#include <sys/time.h>

namespace api {

/**
 * Espera por um intervalo de tempo.
 */
class CWait {
public:
    explicit CWait(const size_t milissegundos);

    // Fn 5446: no record, slot or caller's record names it; the name is chosen from what it does.
    void Wait();

private:
    size_t m_microssegundos;
    timeval m_inicio;
};

} // namespace api
