# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/02 15:17:44 by jinhyeop          #+#    #+#              #
#    Updated: 2023/09/10 21:53:39 by dongkseo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3
CLIB = -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework Appkit -Imlx -lm

NAME = minirt

MAN_DIR = ./srcs
MAN_FILE = minirt.c mlx_utils.c intersection.c raycasting.c parse.c \
		vector.c simple_vec_cal.c color.c angle.c shadow.c
BONUS_DIR = ./bonus
BONUS_FILE = 
MAN_SRCS = $(addprefix $(MAN_DIR)/, $(MAN_FILE))
BONUS_SRCS = $(addprefix $(BONUS_DIR)/, $(BONUS_FILE))
MAN_OBJS = $(MAN_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

ifdef BONUS
	OBJS = $(BONUS_OBJS)
else
	OBJS = $(MAN_OBJS)
endif

MLX_NAME = mlx
MLX_DIR = ./mlx
MLX = $(addprefix $(MLX_DIR)/, libmlx.a)

LIBFT_NAME = libft
LIBFT_DIR = ./libft
LIBFT = $(addprefix $(LIBFT_DIR)/, libft.a)

all: $(NAME)

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I includes/

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) all
	$(MAKE) -C $(MLX_DIR) all
	$(CC) $(CFLAGS) $(CLIB) $^ -o $@ -I includes/

bonus:
	$(MAKE) BONUS=1 $(NAME)

clean:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) clean
	@rm -f $(MAN_OBJS)
	@rm -f $(BONUS_OBJS)
	@echo "All object files removed"

fclean: clean
	@rm -f $(NAME)
	@echo "Executable file removed"

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all bonus clean fclean re
