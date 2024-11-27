# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-flem <mle-flem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 08:36:52 by mle-flem          #+#    #+#              #
#    Updated: 2024/11/27 19:41:40 by mle-flem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GNL_PATH = ..

SRC = src/utils.c \

INCLUDE = include/ \
		  $(GNL_PATH)/ \

MANDATORY_SRC = $(GNL_PATH)/get_next_line.c \
				$(GNL_PATH)/get_next_line_utils.c \

BONUS_SRC = $(GNL_PATH)/get_next_line_bonus.c \
			$(GNL_PATH)/get_next_line_utils_bonus.c \

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

CFLAGS += -Wall -Wextra -Werror -g
CFLAGS += $(INCLUDE:%=-I%)

ifneq ($(shell which valgrind),)
VALGRIND = valgrind -q --leak-check=full
endif

.PHONY: all
all: mandatory .separator bonus

.PHONY: mandatory
mandatory: .mandatory-msg mandatory-1 mandatory-42 mandatory-10M mandatory-default

.PHONY: .mandatory-msg
.mandatory-msg:
	@printf "\033[0;1;93m[ MANDATORY ]\033[0m\n"

.PHONY: mandatory-1
mandatory-1: CFLAGS += -DBUFFER_SIZE=1
mandatory-1:
	@printf "\n\033[0;1;94mBUFFER_SIZE=1\033[0m\n"
	@$(CC) $(CFLAGS) tests/mandatory.c $(SRC) $(MANDATORY_SRC)
	@$(VALGRIND) ./a.out; $(RM) ./a.out

.PHONY: mandatory-42
mandatory-42: CFLAGS += -DBUFFER_SIZE=42
mandatory-42:
	@printf "\n\033[0;1;94mBUFFER_SIZE=42\033[0m\n"
	@$(CC) $(CFLAGS) tests/mandatory.c $(SRC) $(MANDATORY_SRC)
	@$(VALGRIND) ./a.out; $(RM) ./a.out

.PHONY: mandatory-10M
mandatory-10M: CFLAGS += -DBUFFER_SIZE=10000000
mandatory-10M:
	@printf "\n\033[0;1;94mBUFFER_SIZE=10000000\033[0m\n"
	@$(CC) $(CFLAGS) tests/mandatory.c $(SRC) $(MANDATORY_SRC)
	@$(VALGRIND) ./a.out; $(RM) ./a.out

.PHONY: mandatory-default
mandatory-default:
	@printf "\n\033[0;1;94mBUFFER_SIZE=???\033[0m\n"
	@$(CC) $(CFLAGS) tests/mandatory.c $(SRC) $(MANDATORY_SRC)
	@$(VALGRIND) ./a.out; $(RM) ./a.out

.PHONY: .separator
.separator:
	@printf "\n"

.PHONY: bonus
bonus: .bonus-msg bonus-1 bonus-42 bonus-10M bonus-default

.PHONY: .bonus-msg
.bonus-msg:
	@printf "\033[0;1;93m[ BONUS ]\033[0m\n"

.PHONY: bonus-1
bonus-1: CFLAGS += -DBUFFER_SIZE=1
bonus-1:
	@printf "\n\033[0;1;94mBUFFER_SIZE=1\033[0m\n"
	@$(CC) $(CFLAGS) tests/mandatory.c $(SRC) $(BONUS_SRC)
	@$(VALGRIND) ./a.out; $(RM) ./a.out
	@$(CC) $(CFLAGS) tests/bonus.c $(SRC) $(BONUS_SRC)
	@$(VALGRIND) ./a.out; $(RM) ./a.out

.PHONY: bonus-42
bonus-42: CFLAGS += -DBUFFER_SIZE=42
bonus-42:
	@printf "\n\033[0;1;94mBUFFER_SIZE=42\033[0m\n"
	@$(CC) $(CFLAGS) tests/mandatory.c $(SRC) $(BONUS_SRC)
	@$(VALGRIND) ./a.out; $(RM) ./a.out
	@$(CC) $(CFLAGS) tests/bonus.c $(SRC) $(BONUS_SRC)
	@$(VALGRIND) ./a.out; $(RM) ./a.out

.PHONY: bonus-10M
bonus-10M: CFLAGS += -DBUFFER_SIZE=10000000
bonus-10M:
	@printf "\n\033[0;1;94mBUFFER_SIZE=10000000\033[0m\n"
	@$(CC) $(CFLAGS) tests/mandatory.c $(SRC) $(BONUS_SRC)
	@$(VALGRIND) ./a.out; $(RM) ./a.out
	@$(CC) $(CFLAGS) tests/bonus.c $(SRC) $(BONUS_SRC)
	@$(VALGRIND) ./a.out; $(RM) ./a.out

.PHONY: bonus-default
bonus-default:
	@printf "\n\033[0;1;94mBUFFER_SIZE=???\033[0m\n"
	@$(CC) $(CFLAGS) tests/mandatory.c $(SRC) $(BONUS_SRC)
	@$(VALGRIND) ./a.out; $(RM) ./a.out
	@$(CC) $(CFLAGS) tests/bonus.c $(SRC) $(BONUS_SRC)
	@$(VALGRIND) ./a.out; $(RM) ./a.out

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
