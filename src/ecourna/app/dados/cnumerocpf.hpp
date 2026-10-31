#pragma once
#include <string>

#include "ecourna/app/dados/iidentificadoreleitor.hpp"

namespace ecourna::app::dados {

class CNumeroCPF final : public IIdentificadorEleitor {
public:
    explicit CNumeroCPF(const std::string& numero);

    ~CNumeroCPF() override;

    std::string Formatado() const override;
};

} // namespace ecourna::app::dados
