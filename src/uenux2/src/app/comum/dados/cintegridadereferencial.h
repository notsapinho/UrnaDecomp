#pragma once

#include <map>
#include <string>
#include <utility>

#include "app/comum/dados/md/processoeleitoral/ccargo.h"
#include "ecourna/api/uetypes.hpp"

namespace comum {

class CCandidaturas;
class CFotos;
class CPartidos;
class CRdv;
class CRespostas;

namespace md {
class CCandidatura;
} // namespace md

// Only Lanca (target fn 2263) is reconstructed. TResultado's spelling is the record's and its layout the body's and its
// caller 2543's: a byte tested at +0, a std::string at +4, 16 bytes. That it is a std::pair is chosen; a struct of those
// two members and a std::tuple give the same bytes (the fragment has the measurement).
class CIntegridadeReferencial {
public:
    using TResultado = std::pair<bool, std::string>;

    static void Lanca(const TResultado& resultado);
};

// fn 5747: whether a candidatura's post is among the posts and is a candidates' post with as many substitutes as the
// candidatura; it leaves the post found (or the end) in cargo. Its two calls are in fn 7787's integrity tests: the
// caller sets the iterator to null first, passes the map fn 2834 builds from CCargos::GetInst() (fn 273),
// gives the result to Lanca (fn 2263) or reads the post's detail through the iterator. The map's types are the node's:
// a byte key compared unsigned, and a value at +20 whose +84 flag and fn 1388 (CCargo::GetDetalheCandidato) are
// CCargo's. Its name, its being a free function of comum with external linkage and the parameters' names are chosen.
CIntegridadeReferencial::TResultado VerificaCargoCandidatura(const md::CCandidatura& candidatura,
                                                            const std::map<md::TCargoID, md::CCargo>& cargos,
                                                            std::map<md::TCargoID, md::CCargo>::const_iterator& cargo);

// fn 5746: whether the photo of a candidatura's holder (ordem 0) or of its substitute ordem is among the photos, by the
// candidate's code; a holder whose situation is not 0 passes. Its two calls are in fn 7787's integrity tests, which pass
// it CFotos::GetInst() (fn 2819) as the photos and hand its result to Lanca (fn 2263). Its name, its
// being a free function of comum with external linkage, and its parameters' types past what the body reads are chosen.
CIntegridadeReferencial::TResultado VerificaFotoCandidatura(const md::CCandidatura& candidatura, uebyte ordem,
                                                           const CFotos& fotos);

// fn 11514: the RDV's votes held against the posts, candidacies, parties and answers, the first failure with its
// message (one of ten literals only this target function loads) or {true, ""}. Its one target caller, fn 2543 (below),
// passes it CRdvVota::GetInst() (fn 555; the body calls CRdv's slot 0 through the vtable), the map
// CCargos::GetMapaCargos (fn 2834) builds and the GetInst() of CCandidaturas, CPartidos and CRespostas (fns 521, 819,
// 2812). Its name, its being a free function of comum with external linkage, the parameters' names and their types past
// what the body reads are chosen. It is written and does not match yet, and our link inlines it into 2543, its one
// caller there: src/units/98-uenux2-app-comum-dados.mk has what differs and what 2543 waits for.
CIntegridadeReferencial::TResultado VerificaVotos(const CRdv& rdv, const std::map<md::TCargoID, md::CCargo>& cargos,
                                                  const CCandidaturas& candidaturas, const CPartidos& partidos,
                                                  const CRespostas& respostas);

// fn 2543: hands VerificaVotos' result to Lanca (fn 2263). Its target callers are vota::CEstadoAudio::CarregaEleitores
// (fn 6734), vota::impl::CSincronismoVotoEleitor::Sincroniza (fn 7174, twice) and vota::CGravaResultado::StartState (fn
// 12098). No record names it: its name and its being a free function of comum with external linkage are chosen. It is
// written and does not match yet (src/units/98-uenux2-app-comum-dados.mk says what it waits for).
void VerificaIntegridadeVotos();

} // namespace comum
