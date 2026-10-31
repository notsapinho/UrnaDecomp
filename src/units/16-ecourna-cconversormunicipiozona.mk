# ecourna: ecourna::app::dados::asn::CConversorMunicipioZona::DoConverte and DoDeconverte (target fns 9131, 9130) in
# app/dados/asn/cconversormunicipiozona.cpp, and the CMunicipioZona data class it reads (app/dados/cmunicipiozona.hpp).
# No record names the file: the class's vtable (ledger/vtables.json @1130576) places 9131 and DoDeconverte 9130, and the
# path follows its siblings in app/dados/asn.
MUNICIPIOZONA_SRCS := app/dados/asn/cconversormunicipiozona.cpp
ECOURNA_SRCS += $(MUNICIPIOZONA_SRCS)
# prerequisites only (no recipe: the generic rule compiles them): the ASN.1 headers, which the generic rule does not name
$(foreach u,$(MUNICIPIOZONA_SRCS),$(eval $(ROOT)/$(APP)/ecourna/$(subst /,_,$(u)).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
