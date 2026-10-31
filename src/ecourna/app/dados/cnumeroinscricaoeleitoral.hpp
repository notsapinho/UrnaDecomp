#pragma once
#include <string>

#include "ecourna/app/dados/iidentificadoreleitor.hpp"

namespace ecourna::app::dados {

class CNumeroInscricaoEleitoral final : public IIdentificadorEleitor {
public:
    explicit CNumeroInscricaoEleitoral(const std::string& numero);

    ~CNumeroInscricaoEleitoral() override;

    std::string Formatado() const override;
};

} // namespace ecourna::app::dados
