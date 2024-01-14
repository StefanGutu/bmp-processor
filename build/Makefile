CC := gcc
C_FLAGS := -Wall -Wextra -Wpedantic \
								-Wformat=2 -Wno-unused-parameter \
								-Wshadow -Wwrite-strings -Wstrict-prototypes \
								-Wold-style-definition -Wredundant-decls \
								-Wnested-externs -Wmissing-include-dirs \
								-O2
SRC_PATH := ../src
SRC_FILES := $(wildcard $(SRC_PATH)/*.c)
SRC_OFILES 	:= 	$(patsubst $(SRC_PATH)/%.c,%.o,$(SRC_FILES))
APP := sbmp3

PADDING 				:= 		............................................................
	
all: clear_term build clean
	@printf "\nFinished project "
	@printf "%0.41s" $(PADDING)
	@printf "%s\n\n" " PASSED"

.PHONY: clear_term

clear_term:
	@clear

build: $(SRC_OFILES)
	@$(CC) -o $(APP) $^

%.o: $(SRC_PATH)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $<

	@printf "%s" "Building $(shell basename $@ .o) "
	@file=$@ && printf "%0.$$((50 - $${#file}))s" $(PADDING)
	@printf "%s\n" " PASSED"

clean:
	@rm -rf $(SRC_OFILES)

cleanall:
	@rm -rf $(SRC_OFILES) $(APP)
