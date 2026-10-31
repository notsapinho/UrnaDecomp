#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "api/gui/iimage.h"

namespace api {

// RTTI: an si_class of api::IImage, vtable @1530264 [8563, 8554, 4975]; the string constructor's signature is the
// record's (cfixedimage.cpp:24, in fn 2246). The target builds it with std::make_shared (fns 1263 and 8633). Recovered:
// the layout and the members the bodies show. +4 holds the image's bytes, a std::vector<uint8_t>: GetData (fn 4975)
// returns a copy of it, and simulador::CWasmResource's slot 2 (fn 8633) builds the object around a vector it moves in
// (IImage, an interface, holds no data). That constructor has no target function of its own, and the class has no key
// function: its vtable and typeinfo (1530264, 1530284) lie right after CWasmResource's and the
// std::__shared_ptr_emplace<CFixedImage> that slot 2 instantiates, as a first user's copy does. So GetData and the
// vector constructor are inline here, the destructor implicit (8563 and 8554 are thunks of binaryen's shared bodies
// 3937 and 3936, a D2 and a D0 that store the vptr they are given and free one vector at +4). The string constructor is
// not reconstructed. Not final: the block's __on_zero_shared goes through the vtable (fn 411). The member's name, that
// the vector constructor takes its parameter by value, and its being in the class are chosen.
class CFixedImage : public IImage {
public:
    explicit CFixedImage(const std::string& arquivo);
    explicit CFixedImage(std::vector<uint8_t> dados) : m_dados(std::move(dados)) {}

    std::vector<uint8_t> GetData() const override { return m_dados; }

private:
    std::vector<uint8_t> m_dados;
};

} // namespace api
