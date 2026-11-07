#pragma once

#include <memory>
#include <mutex>

#include "app/comum/dados/asn/rdv/cconversoreleicoesvota.h"
#include "app/comum/dados/asn/rdv/cconversorregistrodigitalvoto.h"
#include "app/comum/dados/crdv.h"
#include "app/comum/dados/md/rdv/ccedula.h"
#include "app/comum/dados/md/rdv/crdvposicionador.h"
#include "app/comum/dados/md/rdv/cvotoseleicoesvota.h"

namespace comum {

// RTTI gives the name and the base; no record names a file. crdvvota.cpp defines the member and emits the vtable
// (src/units/13-uenux2-crdvvota.mk has the evidence); that the class is declared here is chosen.
class CRdvPosicionadorVota : public md::CRdvPosicionador {
public:
    size_t Posicao(const std::vector<md::CVoto>& votos, const md::CVoto& voto) const override;
};

class CRdvVota final : public CRdv {
public:
    ~CRdvVota();

    static CRdvVota& GetInst();
    static void CreateInst();

    TVotosCargo GetVotos() const override;
    TVotosCargo GetVotos(md::TEleicaoID eleicao) const override;
    md::TQtdVoto Comparecimento(md::TEleicaoID eleicao) const override;
    md::TQtdVoto Candidato(md::TCargoID cargo, uedword numero, uebyte digitos) const override;
    md::TQtdVoto Legenda(md::TCargoID cargo, int numero) const override;
    md::TQtdVoto Partido(md::TCargoID cargo, int numero) const override;
    md::TQtdVoto Nominais(md::TCargoID cargo) const override;
    md::TQtdVoto Legendas(md::TCargoID cargo) const override;
    md::TQtdVoto Nulos(md::TCargoID cargo) const override;
    md::TQtdVoto Brancos(md::TCargoID cargo) const override;
    md::TQtdVoto Cargo(md::TCargoID cargo) const override;
    std::vector<uebyte> Converte() const override;
    void Desconverte(const std::vector<uebyte>& dados) override;
    bool Confere(const std::vector<uebyte>& dados) const override;

    // The largest of the elections' Comparecimento over CConfiguracaoEleicao's elections: target fn 1269, no slot (it is
    // called directly, on GetInst()'s result, by eight vota functions: 1956, 5972, 10569, 10797, 11835, 11849, 12098,
    // 12110; 12098 compares it with CEleitores' own count). No record names it: its name, an overload of slot 2's, and
    // its being a member (it reads m_votos) are chosen.
    md::TQtdVoto Comparecimento() const;
    // Splits a voter's ballot by election and hands each part to m_votos.RecebeCedula with m_posicionador: fn 4454
    // holds it behind a 32-byte prologue of its own. It reads private state, so it is a member; its name is chosen.
    void RecebeCedula(const md::CCedula& cedula);

private:
    md::CVotosEleicoesVota m_votos;
    // Recovered: the RDV's converter at +44, which the destructor (fn 5734) destroys first; the name is chosen.
    asn::CConversorRegistroDigitalVoto<asn::CConversorEleicoesVota> m_conversor;

    static std::mutex s_mutex;
    static std::unique_ptr<CRdvVota> s_instancia;
};

// Each of the pleito's elections, by its id, with a copy of its cargos (CConfiguracaoEleicao::GetCargos with false, fn
// 3775): target fn 5735, out of line. Its one caller, fn 7787, calls it twice, both after its store of CRdvVota's vptr
// (@1560172) in the construction it holds inlined (a reading: 7787 holds crdvvota.cpp:92's record, CreateInst's). The
// map is CConversorEleicoesVota's TCargosEleicao: 5735's 32-byte nodes hold the key at +16, compared unsigned, and the
// vector of 140-byte cargos at +20, and 7787 destroys the first result with fn 1160, that map's destroy. No record
// names it: its name, its being a free function, its file, its external linkage and this spelling of the map's type
// (TCargosEleicao is the same type) are chosen (src/units/13-uenux2-crdvvota.mk says what places it).
std::map<md::TEleicaoID, std::vector<md::CCargo>> CargosPorEleicao();

} // namespace comum
