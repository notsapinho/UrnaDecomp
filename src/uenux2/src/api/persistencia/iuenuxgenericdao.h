#pragma once
#include <memory>
#include <vector>

#include "api/persistencia/idao.h"

namespace api::persistencia {

// The DAO of one data class, DADO, and its key, ID: the template parameters, the typedefs and the signatures of
// Excluir, ExcluirID and Atualizar are the records' (lines 41, 49 and 57 of this file). Slots 3, 7 and 8 have no
// record: their names are chosen, Inserir from the INSERT each override runs, RecuperarID and RecuperarTodos from
// their SELECTs (slot 7's has a WHERE on the key, slot 8's none); their const follows the three recorded members.
// Their parameters and results are what fns 11473, 11470 and 11469 use: a const reference to the data; a
// std::shared_ptr that takes a `new` copy of the row; a std::vector filled row by row. Pure is chosen: the three
// DAOs override them, and the target has no vtable of this template to show the slots.
//
// Excluir, ExcluirID and Atualizar are declared so that their records' lines stay free. Their defaults, defined here
// in the original with each throw on its record's line at column 15, are not written: all five instantiated ones go
// through fn 2297, binaryen's merge of them, so they match together, with CEleitorDinamicoDAO and
// CComparecimentoMesarioDAO. Each throws a CBaseError<api::EUePersistenciaError, {6800, 6850}>.
template <typename DADO, typename ID>
class IUenuxGenericDAO : public IDAO {
public:
    typedef DADO TDado;
    typedef ID TDadoID;

    virtual void Inserir(const TDado& dado) const = 0;

    // (original lines 29-38: content not recovered)
#line 39
    virtual void Excluir(const TDado& dado) const;

    // (original lines 41-46: content not recovered)
#line 47
    virtual void ExcluirID(const TDadoID& id) const;

    // (original lines 49-54: content not recovered)
#line 55
    virtual void Atualizar(const TDado& dado) const;



    virtual std::shared_ptr<TDado> RecuperarID(const TDadoID& id) const = 0;
    virtual std::vector<TDado> RecuperarTodos() const = 0;
};

} // namespace api::persistencia

// <stubs>
// f11540 · 25 B · unmatched · placement: link order · name unknown
// void f11540(i32, i32) { ... }

// f10398 · 25 B · unmatched · placement: link order · name unknown
// void f10398(i32, i32) { ... }

// f10397 · 25 B · unmatched · placement: link order · name unknown
// void f10397(i32, i32) { ... }

// f10396 · 25 B · unmatched · placement: link order · name unknown
// void f10396(i32, i32) { ... }
// </stubs>
