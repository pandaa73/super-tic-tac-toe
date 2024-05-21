rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

BUILD_DIR	:= ./build
INC_DIR		:= ./include
SRC_DIR		:= ./src

BINARY		:= $(BUILD_DIR)/game

C_SOURCES	:= $(call rwildcard, $(SRC_DIR), *.c)
C_OBJECTS	:= $(patsubst %.c, %.o, $(C_SOURCES))
C_DEPENDS	:= $(patsubst %.c, %.d, $(C_SOURCES))

LD			:= gcc
LD_FLAGS	:= -lraylib

CC			:= gcc
CC_FLAGS	:= -c -I$(INC_DIR)

RM			:= rm -f
RMDIR		:= rm -rf

all: game run

game: $(BINARY)

run:
	$(BINARY)

clean:
	$(RM) $(C_OBJECTS) $(C_DEPENDS)
	$(RMDIR) $(BUILD_DIR)

$(BINARY): $(C_OBJECTS) $(C_HEADERS)
	mkdir -p $(dir $@)
	$(LD) -o $@ $^ $(LD_FLAGS)

-include $(C_DEPENDS)

%.o : %.c Makefile
	$(info $(OBJECTS))
	$(CC) -o $@ $< $(CC_FLAGS) -MMD -MP

.PHONY: all game run clean