BIN_NAME	:= game
LEVELS		:= level0
PLATFORM	:= windows
STD			:= c11

LIBS := raylib
ifeq ($(PLATFORM),windows)
    LIBS += gdi32 opengl32 winmm
	EXEC := pe-x86-64
	OBJ_EXT := .obj
else ifeq ($(PLATFORM),linux)
	LIBS += m X11
	EXEC := elf64-x86-64
	OBJ_EXT := .o
endif

LEVEL_PATHS	:= $(addsuffix $(OBJ_EXT),$(addprefix bin/,$(LEVELS)))
INC_PATHS	:= $(addprefix -I,$(wildcard deps/$(PLATFORM)/*/include))
LIB_PATHS	:= $(addprefix -L,$(wildcard deps/$(PLATFORM)/*/lib))

all: start $(LEVEL_PATHS)
	gcc src/main.c $(LEVEL_PATHS) $(INC_PATHS) $(LIB_PATHS) $(addprefix -l,$(LIBS)) -std=$(STD) -o bin/$(BIN_NAME)

start:
	@echo === Building for $(PLATFORM) ===

bin/%$(OBJ_EXT): assets/levels/% | bin/
	objcopy -I binary -O $(EXEC) -B i386:x86-64 $< $@

assets/levels/%: assets/levels/%.level
	python3 scripts/compile_assets.py $<

bin/:
	mkdir -p bin

clean:
	rm -rf bin

.PHONY: start all clean