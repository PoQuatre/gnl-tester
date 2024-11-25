# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-flem <mle-flem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 08:36:52 by mle-flem          #+#    #+#              #
#    Updated: 2024/11/25 13:06:44 by mle-flem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GNL_PATH = gnl

SRC = src/utils.c \

INCLUDE = include/ \
		  $(GNL_PATH)/ \

MANDATORY_SRC = $(GNL_PATH)/get_next_line.c \
				$(GNL_PATH)/get_next_line_utils.c \
				tests/mandatory.c \

BONUS_SRC = $(GNL_PATH)/get_next_line_bonus.c \
			$(GNL_PATH)/get_next_line_utils_bonus.c \
			tests/bonus.c \

OBJ = $(SRC:%.c=%.o)
MANDATORY_OBJ = $(MANDATORY_SRC:%.c=%.o)
BONUS_OBJ = $(BONUS_SRC:%.c=%.o)

DEP = $(SRC) $(MANDATORY_SRC) $(BONUS_SRC)
DEP := $(wildcard $(DEP))
DEP := $(DEP:%.c=%.d)
IDEP = $(wildcard $(DEP))

COMPDB = $(DEP:%.d=%.c)
COMPDB := $(wildcard $(COMPDB))
COMPDB := $(COMPDB:%.c=%.compdb.json)

CC = gcc
RM = rm -f

CFLAGS += -Wall -Wextra -Werror
CFLAGS += $(INCLUDE:%=-I%)

ifneq ($(shell which valgrind),)
VALGRIND = valgrind -q --leak-check=full
endif

.PHONY: all
all: mandatory bonus

.PHONY: mandatory
mandatory: $(OBJ) $(MANDATORY_OBJ)
	$(CC) $^
	$(VALGRIND) ./a.out || true
	$(RM) ./a.out

.PHONY: bonus
bonus: $(OBJ) $(BONUS_OBJ)
	$(CC) $^
	$(VALGRIND) ./a.out || true
	$(RM) ./a.out

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: deps
deps: dclean $(DEP)

%.d: %.c
	$(CC) $(CFLAGS) -MF $@ -MM -MG -MP -MT '$*.o $@' $<

ifeq ($(filter dclean deps,$(MAKECMDGOALS)),)
-include $(IDEP)
endif

.PHONY: compdb
compdb: $(COMPDB)
	@printf "[\n" > compile_commands.json
	@sed -e 's/^}$$/},/' -e 's/^/  /' $(COMPDB) | sed -e '$$ s/},$$/}/' >> compile_commands.json
	@printf "\n]" >> compile_commands.json
	@$(RM) $^

%.compdb.json: %.c
	@printf "{\n\
	  \"directory\": \"$$(pwd)\",\n\
	  \"file\": \"$<\",\n\
	  \"output\": \"$*.o\",\n\
	  \"command\": \"$(CC) $(CFLAGS) -o $*.o -c $<\"\n\
	}" > $@

.PHONY: clean
clean:
	$(RM) $(OBJ) $(MANDATORY_OBJ) $(BONUS_OBJ)

.PHONY: dclean
dclean:
	$(RM) $(DEP)

.PHONY: fclean
fclean: clean dclean
