BIN_NAME	:= game

CC			:= gcc
STD			:= c11
PLATFORM	:= win64
ARCH		:= i386:x86-64

SRCS	:= main.c
LEVELS	:= level0

ifeq ($(PLATFORM),win64)
    LIBS := raylib gdi32 opengl32 winmm
	EXEC := pe-x86-64
endif

SRCS_PATHS	:= $(addprefix src/,$(SRCS))
LEVEL_PATHS	:= $(addsuffix .obj,$(addprefix bin/,$(LEVELS)))
INC_PATHS	:= $(addprefix -I,$(wildcard deps/$(PLATFORM)/*/include))
LIB_PATHS	:= $(addprefix -L,$(wildcard deps/$(PLATFORM)/*/lib))

all: $(LEVEL_PATHS)
	$(CC) $(SRCS_PATHS) $(LEVEL_PATHS) $(INC_PATHS) $(LIB_PATHS) $(addprefix -l,$(LIBS)) -o bin/$(BIN_NAME) -std=$(STD)

bin/%.obj: assets/levels/% | bin/
	objcopy -I binary -O $(EXEC) -B $(ARCH) $< $@

bin/:
	mkdir -p bin

clean:
	rm -rf bin

.PHONY: all clean