# ecourna: the urna-schedule converter CConversorHorariosUrna (app/dados/asn/cconversorhorariosurna.cpp, DoConverte =
# target fn 9133, DoDeconverte = target fn 9132) and the data class it builds, CHorariosUrna (app/dados/processoeleitoral/chorariosurna.cpp, whose
# constructor binaryen inlines into fn 9132, its only caller).
HORARIOS_SRCS := app/dados/asn/cconversorhorariosurna.cpp app/dados/processoeleitoral/chorariosurna.cpp
ECOURNA_SRCS += $(HORARIOS_SRCS)
# prerequisites only (no recipe: the generic rule compiles them): this fragment, and the sources and the app/dados/asn,
# processoeleitoral and api/asn headers, which src/Makefile's generic prerequisites (each object's source, every ecourna
# header) cover as well
$(foreach u,$(HORARIOS_SRCS),$(eval $(ROOT)/$(APP)/ecourna/$(subst /,_,$(u)).o: $(ROOT)/src/ecourna/$(u) $(ROOT)/src/units/15-ecourna-cconversorhorariosurna.mk $(wildcard $(ROOT)/src/ecourna/app/dados/asn/*.hpp $(ROOT)/src/ecourna/app/dados/processoeleitoral/*.hpp $(ROOT)/src/ecourna/api/asn/*.hpp)))
