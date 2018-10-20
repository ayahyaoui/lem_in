# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emuckens <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/20 17:52:27 by emuckens          #+#    #+#              #
#    Updated: 2018/10/20 17:26:37 by emuckens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := lem-in

SRCS := main.c display.c read.c env.c error.c  get_room.c get_tube.c get_comment.c \
	get_ants.c

BIN := $(addprefix srcs/, $(patsubst %.c, %.o, $(SRCS)))
BIN_DIR := bin

HEADDIR := includes
HEAD	:= $(HEADDIR)/lemin.h

LIBFTDIR := libft
LIBFT := $(LIBFTDIR)/libft.a

FLAGS := -Wall -Werror -Wextra
FSANI := -fsanitize=address

CC := gcc -g

.PHONY: all clean fclean re simple debug

$(NAME): $(HEAD) $(BIN)
	@echo "building $(NAME)..."
	@$(CC) $(FLAGS) -o $(NAME) $(BIN) -lft -L $(LIBFTDIR)
	@echo "$(NAME) READY ! Enjoy :)"

$(LIBFT):
	@make -s -C $(LIBFTDIR)

%.o: %.c
	@echo "generating $@"
	@$(CC) -I $(HEADDIR) -I $(LIBFTDIR)/$(HEADDIR) $(FLAGS) -o $@ -c $^

all:
	make -s -C $(LIBFTDIR)
	make -s $(NAME)

clean:
	@echo "cleaning $(NAME) binaries..."
	@rm -f $(BIN)
	@make clean -C $(LIBFTDIR)
	@echo "Binaries removed from all folders.\n"

fclean: clean
	@echo "cleaning $(NAME) executable..."
	@rm -f $(NAME)
	@echo "cleaning $(LIBFT) executable..."
	@rm -f $(LIBFT)
	@echo "All directories now clean.\n"

re:
	@make -s fclean
	@make -s all

simple:
	@echo "cleaning $(NAME) binaries..."
	@rm -f $(BIN)
	@make all
	@echo "Binaries removed from all folders.\n"


debug: $(BIN) $(HEAD) 
	@echo "building $(NAME) in DEBUG MODE..."
	@gcc $(FLAGS) $(FSANI) -o $(NAME) $(BIN) -lft -L $(LIBFTDIR)
	@echo "$(NAME) READY ! Enjoy :)"
