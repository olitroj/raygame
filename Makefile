BIN_NAME	:= raygame
PLATFORM	:= windows
BUILD		:= debug
STD			:= c11

LEVELS		:= level0
TILEMAPS	:= summer
BACKDROPS	:= sunny

LIBS	:= raylib
ifeq ($(PLATFORM),windows)
    LIBS += gdi32 opengl32 winmm
	EXEC := pe-x86-64
	OBJ_EXT := .obj
else ifeq ($(PLATFORM),linux)
	LIBS += m X11
	EXEC := elf64-x86-64
	OBJ_EXT := .o
endif

CFLAGS	:= 
ifeq ($(BUILD),debug)
	CFLAGS += -g -O0 -DDEBUG
else ifeq ($(BUILD),release)
	CFLAGS += -O2
endif

LEVEL_PATHS	:= $(addsuffix $(OBJ_EXT),$(addprefix bin/l_,$(LEVELS)))
TILE_PATHS	:= $(addsuffix $(OBJ_EXT),$(addprefix bin/t_,$(TILEMAPS)))
BDROP_PATHS	:= $(addsuffix $(OBJ_EXT),$(addprefix bin/b_,$(BACKDROPS)))
INC_PATHS	:= $(addprefix -I,$(wildcard deps/$(PLATFORM)/*/include))
LIB_PATHS	:= $(addprefix -L,$(wildcard deps/$(PLATFORM)/*/lib))

all: start $(LEVEL_PATHS) $(TILE_PATHS) $(BDROP_PATHS)
	gcc src/main.c $(LEVEL_PATHS) $(TILE_PATHS) $(BDROP_PATHS) $(INC_PATHS) $(LIB_PATHS) $(addprefix -l,$(LIBS)) -std=$(STD) $(CFLAGS) -o bin/$(BIN_NAME)

bin/l_%$(OBJ_EXT): assets/l_% | bin
	objcopy -I binary -O $(EXEC) -B i386:x86-64 $< $@
assets/l_%: assets/levels/%.txt
	python3 scripts/compile_level.py $< assets

bin/t_%$(OBJ_EXT): assets/t_% | bin
	objcopy -I binary -O $(EXEC) -B i386:x86-64 $< $@
assets/t_%: assets/tilemaps/%
	python3 scripts/compile_tilemap.py $< assets

bin/b_%$(OBJ_EXT): assets/b_% | bin
	objcopy -I binary -O $(EXEC) -B i386:x86-64 $< $@
assets/b_%: assets/backdrops/%.png
	python3 scripts/compile_backdrop.py $< assets

start:
	@echo === Building for $(PLATFORM) \($(BUILD)\) ===
bin:
	mkdir -p $@
clean:
	rm -rf bin

.PHONY: start all clean bin