// comum::CGeradorBU (/home/rubio/tse/uenux2/src/app/comum/relatorios/cgeradorbu.cpp, its records' file). This comment
// is the reconstruction's. The file's records are CriaQRCode's (line 124) and DefineTipo's (line 161), both held by fn
// 12110, and ImprimePreTexto's (line 257, fn 11256); none of them is reconstructed, and their lines stay blank. The one
// function written here is the destructor, fns 3698 (D2) and 11258 (D0), which has no record; its line is a choice,
// above the records.
#include "app/comum/relatorios/cgeradorbu.h"

#include "app/comum/relatorios/ccalculacv.h"

namespace comum {

CGeradorBU::~CGeradorBU()
{
    CCalculaCV::DestroyInst();
}

} // namespace comum
