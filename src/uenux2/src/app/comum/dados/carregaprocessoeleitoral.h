#pragma once

// The reconstruction's notes, not TSE's text: comum's load of the processo eleitoral from its files, target fns 3771
// and 5778 (carregaprocessoeleitoral.cpp says what each holds). No record names these functions or the file: the
// names, the path and their being free functions of namespace comum are chosen.
#include <filesystem>
#include <string>

#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "app/comum/dados/md/processoeleitoral/cpleito.h"
#include "app/comum/dados/md/processoeleitoral/cpleitodto.h"
#include "app/comum/dados/md/processoeleitoral/cprocessoeleitoral.h"
#include "app/comum/eflashorigem.h"
#include "app/comum/eurnafase.h"

namespace comum {

md::CProcessoEleitoral CarregaProcessoEleitoral(const md::estadoaplicacao::CEstadoGeral& estadoGeral,
    const EFlashOrigem origem);

md::CPleito CarregaPleito(const EUrnaFase fase, const std::string& uf, const std::filesystem::path& diretorio,
    const md::CPleitoDTO& dto);

} // namespace comum
