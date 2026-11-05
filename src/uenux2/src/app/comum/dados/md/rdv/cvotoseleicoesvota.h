#pragma once

#include <functional>
#include <map>
#include <source_location>
#include <string>
#include <utility>

#include "app/comum/dados/euerdverror.h"
#include "app/comum/dados/md/rdv/cvotoscargos.h"

namespace comum::md {

class CVotosEleicoesVota {
public:
    using TMapa = std::map<TEleicaoID, CVotosCargos>;
    using TMapaCargoEleicao = std::map<TCargoID, TEleicaoID>;

    explicit CVotosEleicoesVota(TMapa mapa);

    const CVotosCargos& GetVotos(TEleicaoID eleicao) const;
    // The name is chosen: comum::asn::CConversorEleicoesVota::DoConverte (fn 11350) walks the map.
    const TMapa& GetMapa() const { return m_votos; }
    TQtdVoto Comparecimento(TEleicaoID eleicao) const;
    TQtdVoto Candidato(TCargoID cargo, const std::string& numero) const;
    TQtdVoto Legenda(TCargoID cargo, const std::string& numero) const;
    TQtdVoto Partido(TCargoID cargo, const std::string& numero) const;
    TQtdVoto Nominais(TCargoID cargo) const;
    TQtdVoto Legendas(TCargoID cargo) const;
    TQtdVoto Nulos(TCargoID cargo) const;
    TQtdVoto Brancos(TCargoID cargo) const;
    TQtdVoto Cargo(TCargoID cargo) const;
    // comum::CRdvVota's Desconverte and Confere (fns 11487, 11486) test a decoded RDV against theirs with it (fn 5638).
    // The name is chosen.
    bool Compativel(const CVotosEleicoesVota& outro) const;
    // comum::CRdvVota::Confere (fn 11486) holds it inlined after Compativel: m_votos, then m_eleicoes, each map's size
    // and then its pairs.
    bool operator==(const CVotosEleicoesVota& outro) const = default;
    // Record cvotoseleicoesvota.cpp:215, column 27: the Votos call with that location, error 4735; fn 4454 holds it.
    void RecebeCedula(const CRdvPosicionador& posicionador, TEleicaoID eleicao, const CCedula& cedula);

private:
    using TTotalCargo = std::function<TQtdVoto(const CVotosCargos&, TCargoID)>;
    using TTotalNumero = std::function<TQtdVoto(const CVotosCargos&, TCargoID, const std::string&)>;

    const CVotosCargos& Votos(api::EUeRdvError erro, TEleicaoID eleicao,
                              std::source_location local = std::source_location::current()) const;
    // The non-const access RecebeCedula needs: the target calls the const Votos (fn 3708) there, which this inline
    // overload gives. A const_cast of the const call in RecebeCedula is the other form; neither was compiled against
    // the other, and the overload is chosen.
    CVotosCargos& Votos(api::EUeRdvError erro, TEleicaoID eleicao,
                        std::source_location local = std::source_location::current())
    {
        return const_cast<CVotosCargos&>(std::as_const(*this).Votos(erro, eleicao, local));
    }
    TQtdVoto Total(TCargoID cargo, const TTotalCargo& total, api::EUeRdvError erro,
                   std::source_location local = std::source_location::current()) const;
    TQtdVoto Total(TCargoID cargo, const std::string& numero, const TTotalNumero& total, api::EUeRdvError erro,
                   std::source_location local = std::source_location::current()) const;

    TMapa m_votos;
    TMapaCargoEleicao m_eleicoes;
};

} // namespace comum::md
