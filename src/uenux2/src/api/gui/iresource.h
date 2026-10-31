#pragma once

// api::IResource: the application's resources (images, files, movies) by name. RTTI gives the class and no base; it has
// no vtable of its own in the target, so its slots are read from its one implementation, simulador::CWasmResource
// (vtable @1530176). The virtual destructor is in the first slot, as the control block's __on_zero_shared shows (fn 172
// calls vtable + 4); slots 0 and 1 of CWasmResource are the shared empty bodies (174, 144), the inline default. Each of
// slots 2 to 6 takes a resource's name: slot 2 makes an image of it (fn 8633), slot 3 returns its bytes (8611), slot 4
// a movie (8605), slot 5 says whether it exists (8600) and slot 6 whether the name is a resource name, one that starts
// with ':' (8591). This header's records are three free functions that call those slots: getResourceFile (line 82, in
// fn 2246, slot 3), getResourceMovie (line 87, in fns 1593 and 3076, slot 4) and isResource (line 97, in fn 2246, slot
// 6). They are not reconstructed, and the class ends before line 82, so their lines stay free. The record spells
// getResourceFile's result `SharedVector`; the alias's scope (api) is chosen, and its type is the
// std::shared_ptr<std::vector<unsigned char>> that slot 3 builds. The member names are chosen after those functions',
// and so are slot 2's two int parameters, which its one body ignores, and that no member is const.

#include <memory>
#include <string>
#include <vector>

#include "api/gui/cmovie.h"
#include "api/gui/iimage.h"
#include "ecourna/api/uetypes.hpp"

namespace api {

using SharedVector = std::shared_ptr<std::vector<uebyte>>;

class IResource {
public:
    virtual ~IResource() = default;

    virtual SharedIImage GetImage(const std::string& nome, int, int) = 0;
    virtual SharedVector GetFile(const std::string& nome) = 0;
    virtual CMovie GetMovie(const std::string& nome) = 0;
    virtual bool Exists(const std::string& nome) = 0;
    virtual bool IsResource(const std::string& nome) = 0;
};

} // namespace api
