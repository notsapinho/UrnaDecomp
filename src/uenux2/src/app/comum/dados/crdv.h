#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "app/comum/dados/md/rdv/cvotoscargos.h"

namespace ecourna::api::security {
class ISymmetricCipher;
using TSharedSymmetricCipher = std::shared_ptr<ISymmetricCipher>;
} // namespace ecourna::api::security

namespace comum {

namespace md {
class CRdvPosicionador;
using RdvPosicionadorPtr = std::unique_ptr<CRdvPosicionador>;
} // namespace md

// The 14 virtuals are pure (the CRdv vtable is all __cxa_pure_virtual); the names of slots 0, 11 and 13 are not
// recorded in the binary. Slots 0 and 1 return a map from each cargo to its votes by value: comum::CRdvVota's (fns 5733
// and 11490) fill the result their first parameter points at, whose 32-byte nodes hold the cargo's byte at +16 and an
// md::CVotos at +20. Chosen: slot 0's name, an overload of slot 1's, and the alias's name.
class CRdv {
public:
    using TVotosCargo = std::map<md::TCargoID, md::CVotos>;

    CRdv(md::RdvPosicionadorPtr posicionador, const std::vector<uebyte>& chave, uebyte digitosPartido);

    virtual TVotosCargo GetVotos() const = 0;
    virtual TVotosCargo GetVotos(md::TEleicaoID eleicao) const = 0;
    virtual md::TQtdVoto Comparecimento(md::TEleicaoID eleicao) const = 0;
    virtual md::TQtdVoto Candidato(md::TCargoID cargo, uedword numero, uebyte digitos) const = 0;
    virtual md::TQtdVoto Legenda(md::TCargoID cargo, int numero) const = 0;
    virtual md::TQtdVoto Partido(md::TCargoID cargo, int numero) const = 0;
    virtual md::TQtdVoto Nominais(md::TCargoID cargo) const = 0;
    virtual md::TQtdVoto Legendas(md::TCargoID cargo) const = 0;
    virtual md::TQtdVoto Nulos(md::TCargoID cargo) const = 0;
    virtual md::TQtdVoto Brancos(md::TCargoID cargo) const = 0;
    virtual md::TQtdVoto Cargo(md::TCargoID cargo) const = 0;
    virtual std::vector<uebyte> Converte() const = 0;
    virtual void Desconverte(const std::vector<uebyte>& dados) = 0;
    virtual bool Confere(const std::vector<uebyte>& dados) const = 0;

protected:
    md::RdvPosicionadorPtr m_posicionador;
    ecourna::api::security::TSharedSymmetricCipher m_cifrador;
    uebyte m_digitosPartido;
};

} // namespace comum
