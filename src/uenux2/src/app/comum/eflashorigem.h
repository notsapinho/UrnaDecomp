#pragma once

namespace comum {

// The flash a path is rooted in. The name is the records' (comum::CPath::GetPathRootSemSA, GetPathResult and GetPathTrab,
// comum::CHV::CreateInst, comum::CPE::CreateInst, comum::CConfiguracaoEleicao::CreateInst). The values are evidence:
// CPath::GetPathRootSemSA (target fn 634) switches on 0 and 1 and builds "/dsk/fi/" and "/dsk/fe/" from them, and the
// table of flash roots its siblings index (1838576, 12 bytes an entry) holds those two paths in that order. The
// enumerators' names, the comum:: scope (the records print the type unqualified, as they do EUrnaTurno) and this path are
// chosen.
enum EFlashOrigem {
    FLASH_INTERNA = 0,
    FLASH_EXTERNA = 1,
};

} // namespace comum
