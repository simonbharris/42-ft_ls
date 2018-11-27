# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sharris <sharris@student.42.us.org>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/15 02:29:22 by sharris           #+#    #+#              #
#    Updated: 2018/11/15 02:29:24 by sharris          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC_DIR = src/
OBJ_DIR = obj/

# file names without extentions or directories.
SRC_RAW =	main \
			print_ls \
			set_opt_flags \
			ft_ls \
			ft_ls_file_util \
			ft_ls_sort \
			skip_hidden_files \
			ft_ls_put_longlist \
			print_basic_long_list \
			ft_ls_mode_util \
			ftls_put_dirs

SRC = $(SRC_RAW:%=$(SRC_DIR)%.c)
OBJ = $(SRC_RAW:%=$(OBJ_DIR)%.o)

INC_DIR = includes/
FTLS_HEADER = $(INC_DIR)ft_ls.h

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a
FT_PRINTF = $(LIBFT_DIR)libftprintf.a

LIB_DIR = $(LIBFT_DIR)
LIB_FLAGS = -L $(LIB_DIR) -lft -lftprintf

INC = -I $(INC_DIR)
LIBFT_INC = -I $(LIBFT_DIR)includes
INC_FLAGS = $(INC) $(LIBFT_INC)

all: $(NAME)

debug: $(LIBFT) $(FT_PRINTF)
	gcc -g $(INC_FLAGS) libft/src/*.c libft/src/ft_printf/src/* $(SRC) -o $(NAME)

$(NAME): $(LIBFT) $(FT_PRINTF) $(OBJ_DIR) $(OBJ)
	gcc $(INC_FLAGS) $(LIB_FLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR):
	mkdir obj

$(OBJ): $(OBJ_DIR)%.o : $(SRC_DIR)%.c $(FTLS_HEADER)
	gcc -c $(INC_FLAGS) $< -o $@

$(LIBFT):
	make -C libft/

$(FT_PRINTF):
	make -C libft/src/ft_printf/

clean:
	rm -Rf obj/

fclean: clean
	rm $(NAME)
	make fclean -C libft/

re: clean all