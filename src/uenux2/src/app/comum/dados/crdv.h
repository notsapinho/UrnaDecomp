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

    // Target fns 5737 and 5736: Salva of GetArquivoRdvInterno's or GetArquivoRdvExterno's path. No record, slot or RTTI
    // names them; the names and const are chosen. crdv.cpp defines them (src/units/381-uenux2-crdv.mk).
    void SalvaInterno() const;
    void SalvaExterno() const;

protected:
    md::RdvPosicionadorPtr m_posicionador;
    ecourna::api::security::TSharedSymmetricCipher m_cifrador;
    uebyte m_digitosPartido;

private:
    // Converte's bytes written through an api::CEncryptedFile over m_cifrador and saved to the path given. No target
    // function is its own: SalvaInterno and SalvaExterno hold its code, its locals above their string, as clang inlines
    // it (src/units/381-uenux2-crdv.mk). It reads m_cifrador and calls Converte through the vtable (slot 11), on a
    // class that is not final, so it is CRdv's member; its name, const and being private are chosen.
    void Salva(const std::string& arquivo) const;
};

// The path of "rdv.dat" in the work directory of the internal flash (target fn 1551) and of the external one (fn
// 1701), as a string: CPath::GetPathTrab of that flash with the name appended. No record, slot or RTTI names them;
// their names and their being free functions (they read no class state) are chosen. Their bands put them in crdv.cpp.
// In the target each is a thunk of a body binaryen merged with celeitores.h's function of the same flash: 1551 and
// 2826 call fn 6036, 1701 and 5762 fn 6035 (src/units/381-uenux2-crdv.mk).
std::string GetArquivoRdvInterno();
std::string GetArquivoRdvExterno();

} // namespace comum
