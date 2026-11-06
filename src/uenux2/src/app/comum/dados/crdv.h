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

    // No target index: steps of fn 7174 (vota::impl::CSincronismoVotoEleitor::Sincroniza), their one caller, which
    // holds each behind a 48-byte frame of its own, as binaryen inlined them: Converte's bytes saved to the RDV's
    // ".tmp" path, and that file read back and passed to Confere. They read m_cifrador and call slots, so being
    // CRdv's members is a reading; their names and const are chosen (src/units/381-uenux2-crdv.mk).
    void SalvaTemporarioInterno() const;
    bool ConfereTemporarioInterno() const;
    void SalvaTemporarioExterno() const;
    bool ConfereTemporarioExterno() const;

    // Target fns 5737 and 5736: Salva of GetArquivoRdvInterno's or GetArquivoRdvExterno's path. No record, slot or RTTI
    // names them; the names and const are chosen. crdv.cpp defines them (src/units/381-uenux2-crdv.mk).
    void SalvaInterno() const;
    void SalvaExterno() const;
    // CarregaInterno: the RDV read back from the internal flash's "rdv.dat" and handed to Desconverte (slot 12, through
    // the vtable): fn 6734 holds it behind a 48-byte prologue, on CRdvVota::GetInst()'s result
    // (src/units/386-uenux2-carregaeleitores.mk). No record names it: the name, after SalvaInterno, is chosen.
    void CarregaInterno();

protected:
    md::RdvPosicionadorPtr m_posicionador;
    ecourna::api::security::TSharedSymmetricCipher m_cifrador;
    uebyte m_digitosPartido;

private:
    // The file's bytes read through an api::CEncryptedFile over m_cifrador, and those bytes passed to Confere. No
    // target function is their own: the two ConfereTemporario members hold them as clang inlines them, their file and
    // bytes above the caller's path (src/units/241-uenux2-app-vota-eleitor.mk has the frame), and Carrega holds Le the
    // same way for fn 6734 (src/units/386-uenux2-carregaeleitores.mk). Names and const chosen.
    std::vector<uebyte> Le(const std::string& arquivo) const;
    bool ConfereArquivo(const std::string& arquivo) const;

    // Converte's bytes written through an api::CEncryptedFile over m_cifrador and saved to the path given. No target
    // function is its own: SalvaInterno and SalvaExterno hold its code, its locals above their string, as clang inlines
    // it (src/units/381-uenux2-crdv.mk). It reads m_cifrador and calls Converte through the vtable (slot 11), on a
    // class that is not final, so it is CRdv's member; its name, const and being private are chosen.
    void Salva(const std::string& arquivo) const;
    // Carrega: CarregaInterno's body, which clang inlines (one frame): Salva's other direction, Le's bytes handed to
    // Desconverte, its existence, name and being private chosen.
    void Carrega(const std::string& arquivo);
};

// The path of "rdv.dat" in the work directory of the internal flash (target fn 1551) and of the external one (fn
// 1701), as a string: CPath::GetPathTrab of that flash with the name appended. No record, slot or RTTI names them;
// their names and their being free functions (they read no class state) are chosen, and crdv.cpp is a reading: their
// bands allow clocal.cpp's tail too, and CRdv's 5736 and 5737 beside them give this file. Each is a thunk of a body
// binaryen merged with celeitores.h's function of the same flash: 1551 and 2826 call 6036, 1701 and 5762 6035.
std::string GetArquivoRdvInterno();
std::string GetArquivoRdvExterno();

// The ".tmp" companions of those paths, which clang inlines into their users in crdv.cpp, and the ".tmp" file moved
// over the RDV's through api::CSystem::ReplaceFile with an empty backup name, which binaryen inlines into fn 7174, its
// one caller, behind a 48-byte frame. No target index; their names and their being free functions are chosen.
std::string GetArquivoRdvTemporarioInterno();
std::string GetArquivoRdvTemporarioExterno();
void SubstituiRdvInterno();
void SubstituiRdvExterno();

} // namespace comum
