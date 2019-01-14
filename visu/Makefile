# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emuckens <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/20 17:52:27 by emuckens          #+#    #+#              #
#    Updated: 2019/01/14 13:46:54 by emuckens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME := visu

#==============================================================================#
#					 		 	  COMPILATION								   
#==============================================================================#

FLAGS		:= -Wall -Wextra -g
FSANI		:= -fsanitize=address
CC		:= gcc $(FLAGS)
CCF		:= $(CC) $(FSANI)
FRAMEWORKS = -framework OpenGL -framework AppKit
FRAMEWORKS_L = -lm -lmlx -L $(MLXDIR) -lXext -lX11

#==============================================================================#
#								DIRECTORIES									    
#==============================================================================#

BIN_DIR 	:= bin
LIB_DIR 	:= ../libft
MLX_DIR 	:= /usr/local
X11DIR = /usr/include/X11/
#==============================================================================#
#								    FILES									   
#==============================================================================#

SRC	= main.c image.c window.c deal_key.c env.c plot.c matrices_center.c \
matrices_scale.c matrices_trans.c matrices_rot.c transform_points.c \
  get_room.c get_tube.c get_comment.c read.c display.c free.c get_ants.c error.c utils.c 
#  matrices_rot.c 
HEAD	= visu.h

BIN	= $(patsubst %.c, $(BIN_DIR)/%.o, $(SRC))
LIBFT	:= $(LIB_DIR)/libft.a

#==============================================================================#
#							       MISC										    
#==============================================================================#

NB = $(words $(SRC))
INDEX := 0

#==============================================================================#
#							       RULES									    
#==============================================================================#

##only for linux
LIBMLX = $(addprefix $(MLXDIR), libmlx.a)
MLXDIR = minilibx



.PHONY: all clean fclean re simple debug

all: 
	@make $(NAME)


#$(NAME): $(BIN) $(LIBFT) $(LIBMLX)
#	@$(CCF) -o $(NAME) $(BIN) -lft -L $(LIB_DIR)	 $(FRAMEWORKS_L)
#	@echo "\r>>> \033[01;32m$(NAME) READY              \033[0m"

$(NAME): $(BIN) $(LIBFT)
	@$(CC) -o $(NAME) $(BIN) -lmlx -L $(MLX_DIR)/lib -lft -L $(LIB_DIR) $(FRAMEWORKS) 	
	@echo "\r>>> \033[01;32m$(NAME) READY              \033[0m"

$(LIBMLX):
	make -C $(MLXDIR)

$(LIBFT):
	@make -C $(LIB_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(BIN_DIR)/%.o: %.c $(HEAD) Makefile | $(BIN_DIR)
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/($(NB))))))
	@$(CC) -I . -I $(LIB_DIR)/includes -o $@ -c $<
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
	@$(CCF) -o $(NAME) $(BIN) -lmlx -L $(MLX_DIR)/lib -lft -L $(LIB_DIR)  $(FRAMEWORKS)
	@echo "\033[01;32m$(NAME) READY\033[0m"
