# ecourna::api::sql::sqlite DAO (csqlconnection / csqlresultset / csqlstatement) + the shared sqlite error helper.
# (sqlite3.h and boost come from the include dirs src/mk/ecourna-flags.mk adds)
ECOURNA_SRCS += api/sql/sqlite/csqlconnection.cpp
ECOURNA_SRCS += api/sql/sqlite/csqlresultset.cpp
ECOURNA_SRCS += api/sql/sqlite/csqlstatement.cpp
ECOURNA_SRCS += api/sql/sqlite/sqliteutils.cpp
# placeholder definitions of CStringUtils::ToLower/Replace (see the file header); path is relative to src/ecourna
ECOURNA_SRCS += ../units/12-ecourna-api-sql-sqlite-externs.cpp
# nothing in the skeleton reaches the unit: 12-ecourna-api-sql-sqlite-roots.cpp builds the connection as the target's
# callers do, and the class header it includes needs Boost's
$(ROOT)/$(APP)/12-ecourna-api-sql-sqlite-roots.o: $(ROOT)/src/units/12-ecourna-api-sql-sqlite-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -I$(BOOST_HDR) -c src/units/12-ecourna-api-sql-sqlite-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/12-ecourna-api-sql-sqlite-roots.o
