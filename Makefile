BIN_NAME	:= game

CC			:= gcc
STD			:= c11
PLATFORM	:= win64
ARCH		:= i386:x86-64

LEVELS	:= level0

ifeq ($(PLATFORM),win64)
    LIBS := raylib gdi32 opengl32 winmm
	EXEC := pe-x86-64
endif

LEVEL_PATHS	:= $(addsuffix .obj,$(addprefix bin/,$(LEVELS)))
INC_PATHS	:= $(addprefix -I,$(wildcard deps/$(PLATFORM)/*/include))
LIB_PATHS	:= $(addprefix -L,$(wildcard deps/$(PLATFORM)/*/lib))

all: $(LEVEL_PATHS)
	$(CC) src/main.c $(LEVEL_PATHS) $(INC_PATHS) $(LIB_PATHS) $(addprefix -l,$(LIBS)) -o bin/$(BIN_NAME) -std=$(STD)

bin/%.obj: assets/levels/%.level | bin/
	objcopy -I binary -O $(EXEC) -B $(ARCH) $< $@

assets/levels/%.level: assets/levels/%
	python scripts/compile_assets.py $<

bin/:
	mkdir -p bin

clean:
	rm -rf bin

.PHONY: all clean