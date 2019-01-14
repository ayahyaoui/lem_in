# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emuckens <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/20 17:52:27 by emuckens          #+#    #+#              #
#    Updated: 2019/01/14 18:42:16 by anyahyao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME := lem-in

#==============================================================================#
#					 		 	  COMPILATION								   
#==============================================================================#

FLAGS		:= -Wall -Werror -Wextra -g
FSANI		:= -fsanitize=address
CC		:= gcc $(FLAGS)
CCF		:= $(CC) $(FSANI)

#==============================================================================#
#								DIRECTORIES									    
#==============================================================================#

BIN_DIR 	:= bin
HEAD_DIR 	:= includes
SRC_DIR 	:= srcs
EXE_DIR		:= programs
LIB_DIR 	:= libft

#==============================================================================#
#								    FILES									   
#==============================================================================#

_SRC	= debug.c display.c env.c error.c file.c free.c \
	get_ants.c get_comment.c  get_room.c get_tube.c initial.c  versionopti.c\
	options.c  main.c read.c utils.c translate.c move.c repartAnt.c besttab.c\

_HEAD	= lemin.h lem_in.h
SRC 	= $(patsubst %, $(SRC_DIR)/%, $(_SRC))
HEAD	= $(patsubst %, $(HEAD_DIR)/$, $(_HEAD))
BIN	= $(patsubst %.c, $(BIN_DIR)/%.o, $(_SRC))
LIBFT	:= $(LIB_DIR)/libft.a

#==============================================================================#
#							       MISC										    
#==============================================================================#

NB = $(words $(SRC))
INDEX := 0

#==============================================================================#
#							       RULES									    
#==============================================================================#


.PHONY: all clean fclean re simple debug

all: 
	@make $(NAME)
#	cp $(NAME) test/

$(NAME): $(BIN) $(LIBFT)
	@$(CC) -o $(NAME) $(BIN) -lft -L $(LIB_DIR)
	@echo "\r>>> \033[01;32m$(NAME) READY              \033[0m"

$(LIBFT):
	@make -j3 -C $(LIB_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(HEAD) Makefile | $(BIN_DIR)
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/($(NB))))))
	@$(CC) -I $(HEAD_DIR) -I $(LIB_DIR)/$(HEAD_DIR) -o $@ -c $<
	@printf "\033[22;35mgenerating binary.... [ %d%% ]\033[0m\r" $(PERCENT) 
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

clean:
	@echo "cleaning $(NAME) binaries..."
	@rm -f $(BIN)
	@rm -rf $(BIN_DIR)
	@make clean -C $(LIB_DIR)
	@echo "\033[01;34mBinaries removed from all folders.\n\033[0m"

fclean: clean
	@echo "cleaning $(NAME) executable..."
	@rm -f $(NAME)
	@echo "cleaning $(LIBFT) executable..."
	@rm -f $(LIBFT)
	@echo "\033[01;34mAll directories now clean.\n\033[0m"

re:
	@make -s fclean
	@make -s all

remo:
	@make all
	@rm -f $(BIN)
	@echo "\033[01;34mBinaries removed from all folders.\n\033[0m"

debug: $(BIN) $(LIBFT)
	@echo "\033[01;31mbuilding $(NAME) in DEBUG MODE...\033[0m"
	@$(CCF) -o $(NAME) $(BIN) -lft -L $(LIB_DIR)
	@echo "\033[01;32m$(NAME) READY\033[0m"
