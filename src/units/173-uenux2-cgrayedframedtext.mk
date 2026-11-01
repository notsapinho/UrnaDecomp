# uenux2 api/gui: api::CGrayedFramedText::MaskText (target fn 5534, record cgrayedframedtext.cpp 29:15), in the file its
# record names, with the 4918 enumerator of EUeGuiError. It calls CFramedText's DrawChar (5537), FillCell (5536) and
# DrawFrame (2779), unit 92's (api/gui/cframedtext.cpp). Its lines but the throw's are a choice. Evidence: the second loop
# starts from the text's size, read again after the first loop, with an index of its own; one index shared by both loops
# gave 75 over 157 rows (the throw after the loops, a second epilogue), the two loops 10 over 131, all operand rows until
# DrawChar had its name (`pnpm wasm score` in the plain link).
# Not written: the constructor (fn 5535). It passes CFramedText's constructor the address of a constant SFont {40, 0} at
#   474880, in the data of an app/vota object (unit 92's fragment has the measurement), so it waits for that object.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
API_GUI173_SRCS := src/api/gui/cgrayedframedtext.cpp
UENUX2_SRCS += $(API_GUI173_SRCS)
# the constructor that stores CGrayedFramedText's vtable is not written: 173-uenux2-cgrayedframedtext-roots.cpp takes the
# vtable's address; it includes no header
$(ROOT)/$(APP)/173-uenux2-cgrayedframedtext-roots.o: $(ROOT)/src/units/173-uenux2-cgrayedframedtext-roots.cpp $(ROOT)/src/units/173-uenux2-cgrayedframedtext.mk $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/173-uenux2-cgrayedframedtext-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/173-uenux2-cgrayedframedtext-roots.o
