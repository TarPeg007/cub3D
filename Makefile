# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/15 17:58:46 by sfellahi          #+#    #+#              #
#    Updated: 2025/03/02 19:36:23 by sfellahi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
BONUS_NAME = cub3D_bonus

MANDATORY_SRCS = Mandatory/game/main.c\
		Mandatory/parsing/parser.c\
		Mandatory/parsing/parser1.c\
		Mandatory/parsing/parser2.c\
		Mandatory/parsing/parser3.c\
		Mandatory/parsing/parsing1.c\
		Mandatory/parsing/parsing2.c\
		Mandatory/parsing/get_next_line.c\
		Mandatory/parsing/get_next_line_utils.c\
		Mandatory/parsing/libft_function.c\
		Mandatory/parsing/libft_function1.c\
		Mandatory/parsing/libft_function2.c\
		Mandatory/parsing/libft_function3.c\
		Mandatory/parsing/libft_function4.c\
		Mandatory/parsing/libft_function5.c\
		Mandatory/parsing/parsing3.c\
		Mandatory/parsing/parsing4.c\
		Mandatory/parsing/parsing5.c\
		Mandatory/parsing/parsing6.c\
		Mandatory/game/mz_draw.c\
		Mandatory/game/mz_init.c\
		Mandatory/game/mz_utils1.c\
		Mandatory/game/mz_dda.c\
		Mandatory/game/mz_dda1.c\
		Mandatory/game/mz_dda2.c\
		Mandatory/game/mz_key.c

BONUS_SRCS = Bonus/bonus_file/gun.c\
		Bonus/bonus_file/gun1.c\
		Bonus/bonus_file/gun2.c\
		Bonus/bonus_file/music.c\
		Bonus/bonus_file/music1.c\
		Bonus/bonus_file/crosshaire.c\
		Bonus/parsing/get_next_line.c\
		Bonus/parsing/get_next_line_utils.c\
		Bonus/parsing/libft_function.c\
		Bonus/parsing/libft_function1.c\
		Bonus/parsing/libft_function2.c\
		Bonus/parsing/libft_function3.c\
		Bonus/parsing/libft_function4.c\
		Bonus/parsing/libft_function5.c\
		Bonus/parsing/parser.c\
		Bonus/parsing/parser1.c\
		Bonus/parsing/parser2.c\
		Bonus/parsing/parsing1.c\
		Bonus/parsing/parsing2.c\
		Bonus/parsing/parsing3.c\
		Bonus/parsing/parsing4.c\
		Bonus/parsing/parsing5.c\
		Bonus/parsing/parsing6.c\
		Bonus/game/main.c\
		Bonus/game/mz_dda.c\
		Bonus/game/mz_dda1.c\
		Bonus/game/mz_dda2.c\
		Bonus/game/mz_dda3.c\
		Bonus/game/mz_draw.c\
		Bonus/game/mz_draw1.c\
		Bonus/game/mz_draw2.c\
		Bonus/game/mz_draw3.c\
		Bonus/game/mz_init.c\
		Bonus/game/mz_key.c\
		Bonus/game/mz_norm.c\
		Bonus/game/mz_utils1.c\
		

CC = cc
CFLAGS = -Ofast -g3 -O3 -Wall -Wextra -Werror 
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit -framework Cocoa -framework IOKit 
MLX_FLAGS_B = -lmlx -framework OpenGL -framework AppKit -framework Cocoa -framework IOKit

MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

FRAMEWORK= -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
MLX = MLX42/build

all : mlx $(NAME)

bonus : mlx  $(BONUS)

mlx : $(MLX) $(MLX)/libmlx42.a

$(MLX)/libmlx42.a :
	make -C $(MLX)

$(MLX) :
	cmake -S ./MLX42 -B $(MLX)

bonus: $(BONUS_NAME)

$(NAME): $(MANDATORY_OBJS)
	$(CC) $(CFLAGS)  $(MANDATORY_OBJS) ./MLX42/Build/libmlx42.a $(FRAMEWORK)  -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(CFLAGS)  $(BONUS_OBJS) ./MLX42/Build/libmlx42.a $(FRAMEWORK)  -o $(BONUS_NAME)

%.o: %.c Cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)
	@if [ -d "$(MLX)" ]; then \
		make -C $(MLX) $@ ; \
	fi

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	rm -rf ./MLX42/build

re: fclean all

.PHONY: all bonus clean fclean re