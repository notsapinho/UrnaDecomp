#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "api/util/cdate.h"
#include "api/util/cdatetime.h"
#include "app/comum/eurnaturno.h"
#include "ecourna/api/uetypes.hpp"

namespace comum {

// The header of the boletim de urna's QR code. The class and its file come from the record of fn 2791, the lambda of
// preBuild() in ccabecalhoqrcodebuilder.cpp, line 284 (preBuild's const is chosen: clang's record prints a const
// member's name the same way). 2791's only caller is fn 5604, which passes it the fields of this object:
// comum::CGeradorBUQRCodeVota's constructor (fn 5603, by the vptrs it stores) copies the object to its +4 with fn 5608,
// and fns 1956 and 12110 fill it through fns 5618, 5620, 5621, 5623 and 5622 first.
//
// The layout: fn 5608 copies 33 std::strings at a stride of 12 and fn 5624, which those two callers construct it with,
// zeroes 396 bytes, so nothing else fits. 25 of the strings are named after the labels 5604 passes with them, in the
// four tables it gives fn 2791, and the other eight (+132 and the seven from +264, which no table names) after the
// labels comum::CGeradorBUQRCodeVota::Slot2 (fn 11242) formats into them (AGRE, HBBM, HBBG, HBSB, DTAB, HRAB, DTFC,
// HRFC); every name is chosen. The setters' names are chosen from the same labels: no record names them. The two tests
// (fns 5617, 5616, which fn 5604 calls on its copy of the object) compare m_origem with "ORIG:{} " over "SA" and over
// "RED"; their names are chosen from those texts. The setters' integer types are chosen beyond their widths: fn 12110
// loads zona and secao as 16-bit values. comum::CGeradorBUQRCode::GetCabecalho (inlined into fn 5604) calls eight more
// setters on its copy, each binaryen-inlined there with a frame of its own, then build(), which checks the fields in
// four tables through preBuild's lambda (fn 2791) and appends them; build() and preBuild() leave no frame, so their
// being separate functions is a choice. The ORLC field takes "COM" or "LEG" in two inlined frames, one per branch on
// the configuration's origin, each with its literal as a constant: two one-caller setters give that, one setter called
// with either text gives one frame and a select (measured), so there are two; their names are chosen from the texts, as
// the tests' are. DefineTurno's parameter is the load's EUrnaTurno, cast to char inside: GetCabecalho loads the turn as
// a 32-bit word.
class CCabecalhoQRCodeBuilder {
public:
    CCabecalhoQRCodeBuilder();

    void DefineCodigoCarga(const std::string& codigoCarga);
    // Returns the builder, a reading measured on fn 5622's locals: the target's type is (i32 i32)->(), and a result its
    // callers (fns 1956, 12110) drop is one binaryen's dead-argument elimination removes after the locals were laid out
    // (docs/reference/facts/reading.md R10). Declared void, clang gives the loop's iterator this's local, which the
    // target keeps apart; src/units/93-uenux2-estadoaplicacao.mk has the scores. Chosen: the type (a pointer or a const
    // reference gives the same object) and the other setters' void (all returning the builder give the same link).
    CCabecalhoQRCodeBuilder& DefineHistoricoCarga(const std::vector<std::string>& cargas);
    void DefineIdUrna(uedword idUrna);
    void DefineSecao(ueword secao);
    void DefineZona(ueword zona);

    void DefineOrigemProcessoEleitoralCOM();
    void DefineOrigemProcessoEleitoralLEG();
    void DefineProcessoEleitoral(unsigned processo);
    void DefineDataPleito(const api::CDate& data);
    void DefinePleito(unsigned pleito);
    void DefineTurno(EUrnaTurno turno);
    void DefineFase(char fase);
    void DefineUF(const std::string& uf);
    void DefineVersaoSoftware(const std::string& versao);

    // The setters comum::CGeradorBUQRCodeVota::Slot2 (target fn 11242) calls, each binaryen-inlined there with a frame
    // of its own (the class's header note has the reading): the ORIG field takes "RED" or "VOTA" in two frames, one per
    // branch on the generator's flag, each with its literal as a constant, so there are two, as for ORLC;
    // DefineAbertura, DefineFechamento and DefineEmissao each set a date and a time field in one 416-byte frame, from
    // one api::CDateTime. The names are chosen from the labels, as the others'; the integer types beyond their widths
    // too (APTO and FALT are masked to 16 bits at the call, LOCA and MUNI are 32-bit loads).
    void DefineOrigemRED();
    void DefineOrigemVOTA();
    void DefineAgregadas(const std::vector<ueword>& agregadas);
    void DefineLocal(uedword local);
    void DefineQtdeAptos(ueword qtde);
    void DefineQtdeAptosDaSecao(ueword qtde);
    void DefineQtdeAptosTTE(ueword qtde);
    void DefineQtdeCompareceram(ueword qtde);
    void DefineMunicipio(uedword municipio);
    void DefineQtdeHabilitacaoBiometrica(ueword qtde);
    void DefineQtdeHabilitacaoBiografica(ueword qtde);
    void DefineQtdeHabilitacaoSemBiometria(ueword qtde);
    void DefineQtdeFaltosos(ueword qtde);
    void DefineAbertura(const api::CDateTime& dataHora);
    void DefineFechamento(const api::CDateTime& dataHora);
    void DefineEmissao(const api::CDateTime& dataHora);

    bool IsOrigemSA() const;
    bool IsOrigemRED() const;

    std::string build() const;

private:
    // const chosen (the class's header note).
    void preBuild() const;

    std::string m_origem;
    std::string m_origemProcessoEleitoral;
    std::string m_processoEleitoral;
    std::string m_dataPleito;
    std::string m_pleito;
    std::string m_turno;
    std::string m_fase;
    std::string m_uf;
    std::string m_municipio;
    std::string m_zona;
    std::string m_secao;
    std::string m_agregadas;
    std::string m_idUrna;
    std::string m_codigoCarga;
    std::string m_historicoCarga;
    std::string m_versaoSoftware;
    std::string m_local;
    std::string m_qtdeAptos;
    std::string m_qtdeAptosDaSecao;
    std::string m_qtdeAptosTTE;
    std::string m_qtdeCompareceram;
    std::string m_qtdeFaltosos;
    std::string m_qtdeHabilitacaoBiometrica;
    std::string m_qtdeHabilitacaoBiografica;
    std::string m_qtdeHabilitacaoSemBiometria;
    std::string m_dataAbertura;
    std::string m_horaAbertura;
    std::string m_dataFechamento;
    std::string m_horaFechamento;
    std::string m_junta;
    std::string m_turma;
    std::string m_dataEmissao;
    std::string m_horaEmissao;
};

} // namespace comum
