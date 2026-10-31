#pragma once

#include <string>

#include "api/gui/iresource.h"

namespace simulador {

// Recovered: RTTI names the class (an si_class of api::IResource, vtable @1530176), the wasm build's resources, read
// with std::ifstream from emscripten's file system. Its object is the vptr alone: fn 8302 allocates 4 bytes and stores
// it. Slots 2 to 6 are its members (api/gui/iresource.h names them, chosen); the destructors are the shared empty ones
// (slots 0 and 1: 174, 144), left implicit. All five are out of line, in slot order: 8633, 8611, 8605, 8600 and 8591
// run in that order in their use band, and the vtable and typeinfo (1530176, 1530212) lie after CWasmInputMT's and
// before the std::__shared_ptr_emplace<api::CFixedImage> and api::CFixedImage's vtable that slot 2's make_shared
// brings, so this class's own TU emits them.
class CWasmResource : public api::IResource {
public:
    virtual api::SharedIImage GetImage(const std::string& nome, int, int) override;
    virtual api::SharedVector GetFile(const std::string& nome) override;
    virtual api::CMovie GetMovie(const std::string& nome) override;
    virtual bool Exists(const std::string& nome) override;
    virtual bool IsResource(const std::string& nome) override;
};

} // namespace simulador
