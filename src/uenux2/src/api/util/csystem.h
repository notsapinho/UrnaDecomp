#pragma once

#include <string>

#include "ecourna/api/uetypes.hpp"

namespace api {

/**
 * Operações sobre arquivos e diretórios do sistema.
 */
class CSystem {
public:
    static uedword GetFileSize(const std::string& arquivo);
};

} // namespace api
