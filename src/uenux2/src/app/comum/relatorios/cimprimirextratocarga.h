#pragma once

#include <string>
#include <vector>

#include "api/gui/cpaperformbuilder.h"
#include "app/comum/dados/md/chorarioverao.h"
#include "app/comum/dados/md/estadoaplicacao/cdadocorrespondencia.h"
#include "app/comum/dados/md/processoeleitoral/cpleito.h"
#include "ecourna/app/dados/parametrizacaourna/cparametrosurna.hpp"

namespace comum {

// Reconstruction notes, not TSE's text. comum::CImprimirExtratoCarga: RTTI names the class (typeinfo @1576380, a class
// with no base) and its one derived class, comum::CRelatorioTesteImpressora, whose vtable (@1576652) holds its 26
// slots. No record names a member, a slot or this file: every name below, the slots' const, this header's path and the
// file of the out-of-line member are chosen. What the evidence gives:
// - The class has a key function in an object of its own. Its typeinfo lies alone between cgeradorrelversaopacotedados.cpp's
//   data and cpartecandidatos.cpp's (ledger/vtables.json, ledger/classes.json), where cimprimirextratocarga.cpp sorts in
//   app/comum/relatorios/, and its vtable is not in the target: nothing stores its vptr once the derived constructor
//   (fn 5586) overwrites it. Slot 25's body (fn 11216) sits in the same place of the use-1 band, between
//   CGeradorRelVersaoPacoteDados's functions (11224-11217) and cpartecandidatos.cpp's (11215-11210): so slot 25 is this
//   class's member, out of line in that file. That it is the key function is a choice: another out-of-line member there
//   would be one of the slots below whose bodies binaryen shares, which no place shows. cimprimirextratocarga.cpp holds
//   it, the only function written there.
// - Slots 0 and 1 of the derived class are fn 174 (returns this, nothing else) and fn 144 (a free of this): the
//   destructor is inline and empty here, and the derived class's implicit (docs/how-to-decompile.md step 5).
// - The slots' signatures come from their one caller, fn 5591 (8678 B, not reconstructed: it builds the report on an
//   api::CPaperFormBuilder and calls every slot from 2 to 25), and from the derived class's bodies: slot 6 returns a
//   vector of strings (5591 walks it 12 bytes at a time and destroys each string), slot 9 a CDadoCorrespondencia by
//   value (fn 11197 calls its copy constructor, fn 1249, on the result), slot 15 a vector of strings, 23 to 25 take the
//   builder 5591 passes. The names follow what 5591 prints around each call: slot 24 right after the title (slot 21)
//   and its separator (slot 20), slot 25 before "RESUMO DA CORRESPONDENCIA", slot 23 after that summary.
// - Slots 4, 6, 23 and 24 hold bodies binaryen shares with other classes (434, return 1; 902, a zeroed 12-byte result;
//   425, an empty body), so their place says nothing of their class. They are written here as the base's defaults, a
//   choice; overrides in the derived class were not linked.
// - The destructor is declared inline, as docs/how-to-decompile.md step 5 says for a class with no base; the in-class
//   form without inline was not linked.
class CImprimirExtratoCarga {
public:
    inline virtual ~CImprimirExtratoCarga() = default;

    virtual bool EhTreinamento() const = 0;
    virtual bool TemHorarioVerao() const = 0;
    virtual bool TemQRCode() const { return true; }
    virtual std::string GetConteudoQRCode() const = 0;
    virtual std::vector<std::string> GetConteudosQRCodeAdicionais() const { return {}; }
    virtual const md::CHorarioVerao& GetHorarioVerao() const = 0;
    virtual bool EstaEmHorarioVerao() const = 0;
    virtual md::estadoaplicacao::CDadoCorrespondencia GetCorrespondencia() const = 0;
    virtual void InicializaTradutorFrase() const = 0;
    virtual const ecourna::app::dados::CParametrosUrna::TVectorTituloRelatorio& GetCabecalho() const = 0;
    virtual bool EhEleicaoComunitaria() const = 0;
    virtual std::string GetNomeEleicao() const = 0;
    virtual const md::CPleito& GetPleito() const = 0;
    virtual std::vector<std::string> GetDadosLocal() const = 0;
    virtual std::string GetUF() const = 0;
    virtual std::string GetTipoUrna() const = 0;
    virtual std::string GetMensagemEncerramento() const = 0;
    virtual std::string GetMensagemCondicoes() const = 0;
    virtual std::string GetSeparadorFase() const = 0;
    virtual std::string GetTitulo() const = 0;
    virtual bool EhModoDemonstracao() const = 0;
    virtual void ImprimeComplementoCorrespondencia(api::CPaperFormBuilder& builder) const {}
    virtual void ImprimeComplementoTitulo(api::CPaperFormBuilder& builder) const {}
    virtual void ImprimeDataHoraEmissao(api::CPaperFormBuilder& builder) const;
};

} // namespace comum
