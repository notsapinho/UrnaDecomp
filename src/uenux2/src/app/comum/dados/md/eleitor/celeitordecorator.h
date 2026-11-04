#pragma once

#include <string>
#include <vector>

#include "app/comum/asn/util.h"
#include "app/comum/dados/md/eleitor/celeitor.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "ecourna/app/dados/tiposbasicos.hpp"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// A voter's register data. Recovered: the layout, 108 bytes, from its destructor (fn 379): the identities at +8, a
// std::vector of 16-byte CEleitorIdentidade (fn 708), strings at +24, +36, +52 and +68 and a vector of a trivial element
// at +80; fn 5764 reads a type at +104, and CEleitorDetalhe's optional follows at +108. The first 104 bytes are an
// md::CEleitor (celeitor.h), the same members at the same offsets: CEleitores::LoadEleitorDetalhe (fn 5764, record
// celeitores.cpp:719, which takes a `const md::CEleitorDecorator &`) copies them through fn 946, CEleitor's implicit copy
// constructor, then the word at +104 apart, and comum::CEleitorDetalhe::GetBiometria (fn 1937) holds
// CEleitor::GetOffsetBiometria's record (celeitor.cpp:79) on the decorator at +0 of a CEleitorDetalhe. That CEleitor is
// a public base and not a member is chosen: both give these offsets. With no member of its own that has a destructor,
// the class has no D2 of its own in the object: fn 379 is CEleitor's implicit one (measured: unit 110's fragment).
// CEleitores's members read more of it: fns 11528 and 11527 format the 32-bit word at +0 as an int and the 16-bit one at
// +4 as unsigned, 11526 tests the word at +48 against 0, 11529 reads the strings at +24 and +36, and 5765 passes the word
// at +104 to GetIdentidadePorTipo, so it is an identifier's type. Fn 946 copies 32 bits at +0, 16 at +4 and nothing at
// +6, which is padding. The widths and signedness are the bodies'; the accessors, their names, their reading the base's
// members (protected in celeitor.h, a choice) and m_tipoIdentificador's name are chosen.
class CEleitorDecorator : public CEleitor {
public:
    CEleitorIdentidade GetIdentidadePorTipo(ecourna::app::dados::ETipoIdentificadorEleitor tipo) const;

    int GetSequencial() const { return m_sequencial; }
    ueword GetSecao() const { return m_secao; }
    const std::vector<CEleitorIdentidade>& GetIdentidades() const { return m_identidades; }
    const std::string& GetNome() const { return m_nome; }
    const std::string& GetNomeUrna() const { return m_nomeSocial; }
    // The transfer's kind, the word at +48 (CTransferenciaTemporaria's), as an int: 0 for none.
    int GetTipoTransferencia() const { return m_transferencia.GetTipo(); }
    bool IsTTE() const { return GetTipoTransferencia() != 0; }
    ecourna::app::dados::ETipoIdentificadorEleitor GetTipoIdentificador() const { return m_tipoIdentificador; }
    // The word at +20 is the voter's special need: comum::asn::CConversorEntidadeEleitores::ConverteNecessidadeEspecial
    // (record cconversorentidadeeleitores.cpp:38, inlined into fn 11411) maps ModuloEleitores' semNecessidade to 0 and
    // necessitaAudio to 1 (its br_table), and vota::impl::CInformacaoThreadOperador's slot 5 (fn 10579) reads +20 and
    // compares it with 1 (evidence). The accessor's name is chosen, and so is comparing here: an accessor that returns
    // the word, compared with 1 by its caller, gives the same object.
    bool NecessitaAudio() const { return m_necessidadeEspecial == 1; }
    // fn 3721 (callers 2824, 5761 and 7377, the last through GetCurrentAbrangenciaEleitor): 0 for a voter with no
    // temporary transfer or one to the municipality given, 1 for one to the state given, 2 otherwise. The three
    // callers keep the call, which their file (celeitores.cpp) would inline, so it is out of line in another TU (a
    // reading); this file, the name and the parameters' names and types are chosen.
    ETipoAbrangencia GetAbrangencia(const std::string& uf, uedword municipio) const;
    // Target fn 5665: the year of birth, CStringUtils::ToDWord (fn 1523) of the first four characters of the date of
    // birth (CEleitor::GetDataNascimento, the string at +68; a std::string of up to 4 built in place, then freed). Its
    // callers, vota::CVerificaDadoEleitor::ProcessInput (fn 10443) and vota::CPedeAnoNascimentoSemBiometria::ProcessInput
    // (fn 10489), compare it with the year the operator types and log "Ano de nascimento digitado é igual ao do
    // cadastro" or "... diferente do cadastro", which is the evidence for the string's role. Its file is a reading: in
    // use band 2 it comes right after celeitor.cpp's constructors (fns 5668, 5667, 5666) and before celeitordinamico.cpp's
    // (5664, 5663), and the eleitor directory's objects link in name order; out of celeitor.cpp, its call of the
    // accessor stays a call that binaryen inlines, the target's unfolded `+ 68`. No record names it: its name, its being
    // a const member of the decorator and its uedword result (ToDWord's) are chosen.
    uedword GetAnoNascimento() const;

private:
    ecourna::app::dados::ETipoIdentificadorEleitor m_tipoIdentificador;
};

} // namespace comum::md
