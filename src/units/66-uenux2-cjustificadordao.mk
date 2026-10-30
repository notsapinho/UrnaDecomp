# uenux2 comum::dao::CJustificadorDAO: slot 3, the INSERT of a justified absence (target fn 11473), slot 2, Clone (11468,
# a thunk into binaryen's 3894, which forms with unit 91's two), slots 5 and 6, ExcluirID and Atualizar (11472, 11471,
# with the header app/comum/justificativa/euecomumjustificativaerror.h), and the destructor and deleting destructor
# (target fns 1704 and 3767, slots 0 and 1 of its vtable @1560760) in src/app/comum/justificativa/dao/cjustificadordao.cpp,
# the file the records of ExcluirID and Atualizar name (lines 56 and 63). The headers cjustificadordao.h and
# ijustificadordao.h beside it, and the bases src/api/persistencia/iuenuxgenericdao.h, the file the records of the base's
# defaults name, and idao.h beside it. The class chain is RTTI's: CJustificadorDAO, IJustificadorDAO,
# IUenuxGenericDAO<CIdentificacaoJustificativa, std::string>, IDAO. Slot 4 is the base's default (11467, unit 91's row).
#
# Read from the bytes:
# - slot 3: the calls are ISqlConnection's slot 5 (Prepare) and ISqlStatement's slots 3, 2, 10 and 12 (SetInt64, SetInt,
#   Execute, Close) of src/ecourna/api/sql/, and the 83-byte string is built inline and freed last, so it is a named
#   local: passed to Prepare as a temporary it is freed before SetInt64 (measured, 3 more rows and another order). The
#   identifier's std::shared_ptr and the number's std::string are temporaries of the SetInt64 statement: the target
#   loads the statement before it calls 2669 and releases both before SetInt; a block with a named shared_ptr calls
#   2669 first, a named std::string keeps the number to the end of the function (both measured, both differ).
# - final, the destructor out of line, the object's 12 bytes, m_conexao in this class and not in a base: cjustificadordao.h
#   and idao.h say why. A member in IDAO is ruled out: 1704 stores no vptr, and a std::shared_ptr member in IDAO adds
#   IDAO's vptr store to this class's D2 (measured with this class final). 1704 and 3767 fill slots 0 and 1 of all
#   three DAOs: binaryen merged their destructors. This unit's alone give the same two bodies.
#
# Chosen, no evidence names them: Inserir (slot 3), Clone (slot 2), RecuperarID and RecuperarTodos (slots 7 and 8, whose
# result types the bytes give), the const of those four, every parameter and member name, the paths of
# cjustificadordao.h, ijustificadordao.h, idao.h and euecomumjustificativaerror.h, the enumerators of
# EUeComumJustificativaError, and the pure slots of the bases. The destructor declared first is
# the key function: a choice, as ExcluirID and Atualizar are out of line in the same file too.
#
# Lines: ExcluirID and Atualizar throw on their records' lines, 56 and 63. Evidence: Inserir stands before line 56, as
# band uses 1 of ledger/ordinals.tsv runs 11473, 11472 (line 56), 11471 (line 63) downwards. Chosen: its exact line,
# Clone's, and the destructors' place at the top of the file. That band says nothing of the destructors: 1704 is in uses 7, 3767 in uses 3. Only a sibling
# speaks for their place, and it corroborates, no more: in uses 3 the adjacent 3768, 3767, 3766 are, in link order,
# CEleitorDinamicoDAO's constructor, the D0 and that class's slot 8.
#
# Other forms that give the same bytes (each compiled, the unit's functions compared row by row with
# wasm-objdump -d, addresses aside): std::string and the statement not const; `const auto` for the statement; the
# string's `sql(...)` or `sql{...}` initializer; the literal split in two adjacent strings; `m_conexao.get()->` for the
# call of Prepare; .Get() or static_cast<int> on the birth year; a local reference to the record; a const m_conexao;
# `~CJustificadorDAO() final` in a class not marked final; `CJustificadorDAO::~CJustificadorDAO() {}`; a covariant
# `CJustificadorDAO* Clone() const override`, with the same symbol and the same vtable of 0x2c bytes (the target's
# __dynamic_cast shows the slot's result in IDAO, not the override's).
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 and ecourna header.
CJUSTIFICADORDAO_SRCS := src/app/comum/justificativa/dao/cjustificadordao.cpp
UENUX2_SRCS += $(CJUSTIFICADORDAO_SRCS)
# src/ecourna/api/sql/isqlstatement.hpp and isqlresultset.hpp include Boost, and UENUX2_CXXFLAGS has no Boost path. An
# include path is not a flag of the code (asmlift-wasm/benchmark/README.md "The compile setups").
$(ROOT)/$(APP)/uenux2/$(CJUSTIFICADORDAO_SRCS).o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# slots 7 and 8 are not reconstructed: 66-uenux2-cjustificadordao-pending.cpp gives the vtable trapping bodies,
# compiled with the unit's flags, and says what each waits for
$(ROOT)/$(APP)/66-uenux2-cjustificadordao-pending.o: $(ROOT)/src/units/66-uenux2-cjustificadordao-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/66-uenux2-cjustificadordao.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -I$(BOOST_HDR) -c src/units/66-uenux2-cjustificadordao-pending.cpp -o $(R)
# nothing reconstructed stores the vtable's address, and the target reaches slot 3 and the deleting destructor only
# through it: 66-uenux2-cjustificadordao-roots.cpp keeps the vtable, as the constructor inlined into fn 7787 does
$(ROOT)/$(APP)/66-uenux2-cjustificadordao-roots.o: $(ROOT)/src/units/66-uenux2-cjustificadordao-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/66-uenux2-cjustificadordao.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/66-uenux2-cjustificadordao-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/66-uenux2-cjustificadordao-pending.o $(APP)/66-uenux2-cjustificadordao-roots.o
