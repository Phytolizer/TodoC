CC := clang-16
GENJSON := 1
CFLAGS := -std=c2x \
	-MMD -MP \
	-Wall -Wextra \
	-g3 -Og
LDFLAGS :=

.PHONY: all clean re run scan

FILES := main \
	ansi_esc
OBJ_PAT := obj/%.o
OBJ := $(patsubst %,$(OBJ_PAT),$(FILES))
FRAG_PAT := build/frag-%.txt
JSON := $(patsubst %,$(FRAG_PAT),$(FILES))

all: bin/todo build/compile_commands.json
bin/todo: $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_PAT) $(FRAG_PAT) &: %.c
	@mkdir -p $(@D) build
	$(CC) $(CPPFLAGS) $(CFLAGS) -MJ $(patsubst %.c,$(FRAG_PAT),$<) -c -o $(patsubst %.c,$(OBJ_PAT),$<) $<

build/compile_commands.json: $(JSON)
	@mkdir -p $(@D)
	$(info Generating $@)
	@sed 's/,$$//' $(JSON) | \
		jq --slurp --compact-output . \
		> $@

-include $(OBJ:.o=.d)

clean:
	rm -vfr build obj

scan: 
	scan-build --keep-cc -o build/scan $(MAKE) -B
