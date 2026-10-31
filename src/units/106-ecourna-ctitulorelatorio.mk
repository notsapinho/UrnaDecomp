# ecourna ecourna::app::dados::CTituloRelatorio's constructor, in app/dados/parametrizacaourna/ctitulorelatorio.cpp.
# It has no target index of its own: binaryen inlines it into fn 9145, CConversorTituloRelatorio::DoDeconverte, its one
# caller. Evidence: 9145 opens with an outer block that closes at its last row, and leaves the string copy with `br 1`
# where a body of its own has `return`. binaryen's inliner wraps the callee in a block and sets the parameters inside it,
# so the block starts where the arguments start, here the function's first row. With the constructor inline in the
# header, 9145 differs in those rows alone (533 rows against 531); out of line it matches. In cconversortitulorelatorio.cpp
# clang inlines it as it does from the header, which is why it needs a TU of its own (measured on the object).
# Chosen: the path, from the header's directory (how-to step 3, rule 1): no record names this class. The parameter forms
# are the header's and were not varied.
ECOURNA_SRCS += app/dados/parametrizacaourna/ctitulorelatorio.cpp
