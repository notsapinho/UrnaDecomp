#pragma once

#include <string>

#include "app/comum/eurnafase.h"
#include "ecourna/api/uetypes.hpp"
#include "ecourna/app/dados/cfaseid.hpp"
#include "ecourna/app/dados/resultadournacadastro/cresultadournacadastro.hpp"

namespace comum {

// The section identifiers as app/comum/gravadores/iresultado.h declares them in comum (the records spell them
// unqualified); that this header repeats its aliases is a choice.
using TMunicipioID = uedword;
using TSecaoID = ueword;
using TZonaID = ueword;

// Declared in iresultado.h; its enumerators are in app/comum/carquivosresultado.h.
enum EExtensaoArquivoResultado : int;

// Recovered: the static members whose records the file holds (cgravadorutil.cpp:28 to :38 and :97), with the names and
// types the records print, and DeterminaNomeArquivo (target fn 3798), whose name is chosen: no record names it, and it
// builds DeterminaNomeArquivoSemLetra's name with the extension comum::CArquivosResultado gives (IResultado's
// constructor, fn 1396, stores it as the file name). ConverteFaseEcourna and ConverteSituacaoArquivoEcourna (records
// :113 and :129, with the types they print) have no target index: fn 12098 holds both inlined in CGravadorRCSecao's
// constructor, each behind a stack frame of its own (cgravadorutil.cpp says what each body rests on). That the class has
// no other member is not known.
class CGravadorUtil {
public:
    static std::string DeterminaNomeArquivoSemLetra(TMunicipioID municipio, TZonaID zona, TSecaoID secao, char fase);
    static std::string DeterminaNomeArquivo(TMunicipioID municipio, TZonaID zona, TSecaoID secao, char fase,
        EExtensaoArquivoResultado extensao);
    static EUrnaFase ConverteFase(const char fase);
    static ecourna::app::dados::TFaseID ConverteFaseEcourna(char fase);
    static ecourna::app::dados::CResultadoUrnaCadastro::ESituacaoArquivo ConverteSituacaoArquivoEcourna(char situacao);
};

} // namespace comum
