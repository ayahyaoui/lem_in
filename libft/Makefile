# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emuckens <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 16:46:27 by emuckens          #+#    #+#              #
#    Updated: 2018/10/20 02:02:27 by emuckens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS_CHARS = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_tolower.c ft_toupper.c

SRCS_CONV = ft_atoi.c ft_atoi_index.c ft_itoa.c ft_uitoa.c ft_lltoa.c

SRCS_LISTS = ft_lstadd.c ft_lstaddend.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_lstnewf.c ft_lstsize.c

SRCS_MEM = ft_bzero.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c

SRCS_OUT = $(addprefix ft_printf/, $(FTPRINTF_SRCS)) ft_display_error.c ft_mdisplay.c ft_print_inttab.c ft_printstrarr.c ft_putchar.c ft_putchar_fd.c ft_putcnl.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbrnl.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c

SRCS_NUM = ft_abs.c ft_base_to_deci.c ft_beyond_limiti.c ft_dabs.c ft_dsqrt.c ft_endien_btl.c ft_fabs.c ft_llabs.c ft_lllen.c ft_llpow.c ft_maxint.c ft_nblen.c ft_nbwords.c ft_pow.c ft_sort_int_tab.c ft_strarrlen.c ft_swap.c ft_swapd.c

SRCS_STR = get_next_line2.c ft_strcat.c ft_strchr.c ft_strchri.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strcstr.c ft_strdel.c ft_strdup.c ft_strdupf.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strjoinf.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strnbc.c ft_strnbci.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c ft_strsubf.c ft_strtrim.c

SRCS_VEC = ft_44maddd.c ft_44maddrows.c ft_44mcpy.c ft_44minit.c ft_44mrow_addd.c ft_44mswap_rows.c ft_44mtrxmtrx_mul.c ft_44mtranspose.c ft_4fvcpy.c ft_4fvinit.c ft_4ivcpy.c ft_4ivinit.c ft_4mtrxvect_mul.c ft_4vcpy.c ft_4vectvect_mul.c ft_4vinit.c ft_get4mcol.c ft_get4mrow.c ft_getmval.c ft_swap4v.c

FTPRINTF_SRCS = add_prefix.c add_sign.c add_to_buffer.c ft_strncpyi.c apply_specs.c apply_specs_cs.c colors.c ft_printbit.c ft_itoa_base_cust.c itoa_cust_var.c unicode.c attributes_tools.c read_until_arg.c ft_printf.c init_or_clear.c read_attributes.c read_until_arg.c getarg_int.c getarg_nomod.c getarg_uns.c nblen.c negative_arg.c ft_bigc.c ft_bigo.c ft_bigu.c ft_c.c ft_i.c ft_o.c ft_u.c ft_bigd.c ft_bigs.c ft_bigx.c ft_d.c ft_noconv.c ft_p.c ft_s.c ft_x.c ft_n.c ft_b.c mng_nullarg.c ftp_abs.c ftp_isalpha.c ftp_isdigit.c ftp_maxint.c ftp_nblen.c ftp_strcstr.c ftp_strequ.c ftp_strlen.c ftp_strnequ.c ftp_toupper.c ftp_strcmp.c ftp_strncmp.c

SRCS = $(addprefix chars/, $(SRCS_CHARS)) \
	   $(addprefix conversion/, $(SRCS_CONV)) \
	   $(addprefix lists/, $(SRCS_LISTS)) \
	   $(addprefix memory/, $(SRCS_MEM)) \
	   $(addprefix output/, $(SRCS_OUT)) \
	   $(addprefix numbers/, $(SRCS_NUM)) \
	   $(addprefix strings/, $(SRCS_STR)) \
	   $(addprefix vectors_matrices/, $(SRCS_VEC))

%.o : $(OBJ)

OBJ = $(addprefix srcs/, $(patsubst %.c, %.o, $(SRCS))) 

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

.PHONY: all clean fclean re

LIBFT_HEADDIR = includes/

$(NAME) : $(OBJ) Makefile includes/ft_printf/ft_printf.h includes/gnl/get_next_line.h includes/libft.h
	@echo "building $(NAME)..."
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "$(NAME) READY !\n"

%.o:%.c
	@echo "$(NAME) : generating $@"
	@gcc $(CFLAGS) -c $^ -o $@ -I $(LIBFT_HEADDIR)

clean:
	@echo "cleaning $(NAME) binaries..."
	@rm -f $(OBJ)

fclean: clean
	@echo "cleaning $(NAME) executable..."
	@rm -f $(NAME)

re:
	@make fclean
	@make -s all
