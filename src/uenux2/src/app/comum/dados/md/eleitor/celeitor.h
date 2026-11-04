#pragma once

#include <optional>
#include <string>
#include <vector>

#include "app/comum/dados/md/cindexer.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "app/comum/dados/md/eleitor/ctransferenciatemporaria.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// A voter. The records name the class, ValidaCriacao (celeitor.cpp:103 to :113), GetOffsetBiometria (:79) and the nested
// enum ENecessidadeEspecial (CConversorEntidadeEleitores::ConverteNecessidadeEspecial's, which returns one).
// Recovered: the layout, 104 bytes, from the two constructors (target fns 5666 and 5668, whose only caller is
// CConversorEntidadeEleitores's slot 2, fn 11411) and the implicit copy constructor (fn 946): a word at +0, a 16-bit word
// at +4, the identities at +8, the special need at +20 (ValidaCriacao accepts 0 and 1), strings at +24 and +36 (the
// name, which ValidaCriacao trims, and the social name), the transfer at +48, a string at +68 (the date of birth,
// which CEleitorDecorator::GetAnoNascimento reads), a byte vector at +80 and
// an optional CIndexer at +92, its flag at +100: fn 946 copies +92 to +103 as plain bytes, fn 5666 leaves the vector
// and the optional empty and fn 5668 copies both from its last two parameters. comum::md::CEleitorDecorator
// (celeitordecorator.h) derives from it. The constructors' parameter types are the widths and the copies the bodies
// make, but for the first one's signedness, which no width tells: its `int` (the `i` in 5666's and 5668's symbols)
// against `uedword` is chosen; every member and parameter name, the enum's lack of enumerators and the vector's element
// type are chosen, and so is the data members' being protected, which lets the decorator's accessors read them.
class CEleitor {
public:
    enum ENecessidadeEspecial : int;

    CEleitor(int sequencial, ueword secao, const std::vector<CEleitorIdentidade>& identidades,
        ENecessidadeEspecial necessidadeEspecial, const std::string& nome, const std::string& nomeSocial,
        const CTransferenciaTemporaria& transferencia, const std::string& dataNascimento);
    CEleitor(int sequencial, ueword secao, const std::vector<CEleitorIdentidade>& identidades,
        ENecessidadeEspecial necessidadeEspecial, const std::string& nome, const std::string& nomeSocial,
        const CTransferenciaTemporaria& transferencia, const std::string& dataNascimento, const std::vector<uebyte>& biometria,
        const CIndexer& offsetBiometria);

    // GetOffsetBiometria throws when the optional is empty (record celeitor.cpp:79). TemBiometria, the test of the
    // optional's flag (+100), and GetBiometria, the byte vector at +80, are what comum::CEleitorDetalhe::GetBiometria
    // (fn 1937) reads; their names and their being inline are chosen.
    bool TemBiometria() const { return m_offsetBiometria.has_value(); }
    const std::vector<uebyte>& GetBiometria() const { return m_biometria; }
    const CIndexer& GetOffsetBiometria() const;
    // The date of birth, the string at +68, which md::CEleitorDecorator::GetAnoNascimento (fn 5665) reads through this
    // accessor out of line (celeitor.cpp): no target index, binaryen inlines its one call, and 5665 keeps its `this +
    // 68` unfolded after its own prologue, where an inline accessor gives the loads' offsets folded (72, 79: measured).
    // Its name, the member's (m_dataNascimento, read from 5665's use) and its line are chosen.
    const std::string& GetDataNascimento() const;

private:
    void ValidaCriacao() const;

protected:
    int m_sequencial;
    ueword m_secao;
    std::vector<CEleitorIdentidade> m_identidades;
    ENecessidadeEspecial m_necessidadeEspecial;
    std::string m_nome;
    std::string m_nomeSocial;
    CTransferenciaTemporaria m_transferencia;
    std::string m_dataNascimento;
    std::vector<uebyte> m_biometria;
    std::optional<CIndexer> m_offsetBiometria;
};

} // namespace comum::md
