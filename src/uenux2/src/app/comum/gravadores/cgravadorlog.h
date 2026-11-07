#pragma once

#include <filesystem>
#include <string>

#include "app/comum/gravadores/igravador.h"

namespace comum {

// RTTI: an si_class of comum::IGravador. vota::CGravaResultado::StartState (fn 12098) builds it as a
// std::shared_ptr<IGravador>(new CGravadorLog), whose control block's __on_zero_shared is the shared call through the
// vtable (fn 172), so the class is not final. Recovered: the layout, 76 bytes (12098 allocates it with f137(76)), and
// the virtual members. The constructor, which 12098 holds inlined with no frame of its own (no target index; written in
// cgravadorlog.cpp, unrooted), calls IGravador's constructor (fn 1396) with the extension 13 and the SAVD file 60 and
// copies three strings to +40, +52 and +64, which the base-object destructor (fn 5823, slot 0) frees in reverse: it
// copies, not moves, from three string temporaries 12098 frees after it (const references, a choice: by-value strings
// copied into the members would read the same). 12098 makes them from the log directory (GetPathLog's
// code, app/comum/cpath.h) joined with "arquivados/" (+40), CPath::GetPathLog() (fn 5899) joined with "logd.dat" (+52)
// and CPath::GetPathTrab(FLASH_INTERNA) (+64), and GravaResultado reads +40 as a directory whose regular files it zips,
// +52 as one file it zips first, and +64 as the directory it writes the zip to; the members' names follow those
// roles. The destructor is defined in the class without `inline`: the deleting one (fn 11583, slot 1) calls the
// base-object one and frees what it returns, where the implicit destructor, measured in unit 136's link, inlines that
// body into it (docs/reference/facts/reading.md R5). R5's probe gives `= default` and `{}` the same object; `=
// default` is a choice. GravaResultado (slot 7, fn 11584) is out of line, so it is the key function; its file,
// cgravadorlog.cpp, is chosen (no record names this class's file), and its object emits the vtable and the two
// destructors. Every member name is chosen, and so are the constructor's parameters (their order, and the extension and
// the SAVD file as its own constants rather than 12098's arguments: one call cannot tell them apart).
class CGravadorLog : public IGravador {
public:
    CGravadorLog(TMunicipioID municipio, TZonaID zona, TLocalID local, TSecaoID secao, char fase,
        const std::string& diretorioArquivados, const std::string& arquivoLog, const std::string& diretorioTrabalho);
    ~CGravadorLog() override = default;

    virtual void GravaResultado(api::CFile& arquivo) const override;

private:
    std::string m_diretorioArquivados;
    std::string m_arquivoLog;
    std::string m_diretorioTrabalho;
};

// The directory of the archived logs, CPath::GetPathLog() joined with "arquivados/": fn 12098 holds it inlined behind a
// 32-byte frame of its own (pnpm wasm fn's folded readout of 12098, lines 2226 to 2265: GetPathLog's code, then the
// join, into the path 12098 converts to the constructor's first string). No index, record or slot names it: its name,
// its being a free function of comum and its file (cgravadorlog.cpp, beside the class that takes its result) are
// chosen; external, so that clang keeps it out of line for binaryen to inline into its one caller.
std::filesystem::path GetPathLogArquivados();

} // namespace comum
