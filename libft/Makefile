# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/18 19:14:28 by anyahyao          #+#    #+#              #
#    Updated: 2018/08/06 06:48:01 by anyahyao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME := libft.a
PARSING := parsing.c arg_1.c arg_2.c option.c ft_process.c
OPTION := flag.c specifier.c utile.c
PUT := put_base.c put_int_1.c put_string.c put_unsigned_1.c \
	put_void.c put_adress.c put_unicode.c
LIBFT := ft_printbit ft_printbit_rev ft_printnbit ft_printnbit_rev\
		ft_itoa_base ft_strcjoin ft_strmerge ft_affichetab ft_swap\
		ft_atoi ft_bzero ft_memccpy ft_memchr ft_memcpy ft_memmove\
		ft_sortinttab ft_printbase ft_isupper ft_islower ft_printf\
		ft_memset ft_memcmp ft_strcat ft_strcmp ft_strchr ft_strcpy\
		ft_isascii ft_isdigit ft_isprint ft_strclr ft_max ft_strdel\
		ft_power2 ft_itoa_base2 ft_lennbr_base ft_strrev ft_isspace\
		ft_lstdelone ft_lstiter ft_lstrev ft_realloc ft_atol ft_div\
		ft_putnbr ft_lstnew ft_isalpha ft_lstdel ft_lstmap ft_lstadd\
		ft_tolower ft_toupper ft_memalloc ft_memdel ft_striter ft_abs\
		ft_strjoin ft_strtrim ft_strsplit ft_itoa ft_putchar ft_putstr\
		ft_strdup ft_strlcat ft_strlen ft_strncat ft_strncmp ft_strnew\
		ft_striteri ft_strmap ft_strmapi ft_strequ ft_strnequ ft_strsub\
		ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putendl ft_putnbr_fd\
		ft_strncpy ft_issort ft_tri_fusion_iterative ft_tri_fusion_recursive\
		ft_logarithme2 ft_strnstr ft_strrchr ft_strstr ft_isalnum ft_isinteger\
		ft_min ft_strlen_dim2 ft_del_dim2 get_next_line ft_affiche_string_dim2\
		ft_strcmerge ft_isintab

INCLUDES := includes/
FLAGS := -Wall -Wextra
INCF := -I $(INCLUDES)

_SLIBFT = $(addsuffix .c,$(LIBFT))
SRC = $(_SLIBFT)
SRC += $(addprefix pars/, $(PARSING))
SRC += $(addprefix put/, $(PUT))
SRC += $(addprefix option/, $(OPTION))
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

%.o : %.c
	gcc  $(FLAGS) -c $< -o $@ $(INCf)

clean:
	@/bin/rm -rf $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

norme: fclean
	@norminette $(SRC) includes/libft.h includes/ft_printf.h
