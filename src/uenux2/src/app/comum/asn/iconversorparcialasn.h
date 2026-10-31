#pragma once

#include <memory>

namespace api {
class CFile;
}

namespace comum::asn {

// Converts the part of a generated ASN.1 entity a visitor collects while the partial BER decoder reads it (records
// iconversorparcialasn.h:52, the throw of Desconverte(const api::CFile &, const std::shared_ptr<TVisitor> &), which
// target fns 7787 and 11523 hold inlined; it is not reconstructed). Only the class's head is recovered: the RTTI of
// comum::asn::CIndexadorFotos names this base, whose vtable slot 2 (target fn 11441) takes the entity and the visitor
// (its address, fn 11441's fourth parameter). The record prints TDado and TVisitor; the slot's name, its parameters'
// form and TEntidade's name are chosen, after IConversorASN's.
template <typename ENTIDADE, typename DADO, typename VISITOR>
class IConversorParcialASN {
public:
    typedef ENTIDADE TEntidade;
    typedef DADO TDado;
    typedef VISITOR TVisitor;

    virtual ~IConversorParcialASN() {}

    TDado Desconverte(const api::CFile& arquivo, const std::shared_ptr<TVisitor>& visitante) const;

protected:
    virtual TDado DoDesconverte(const TEntidade& entidade, const TVisitor& visitante) const = 0;
};

} // namespace comum::asn
