# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 14:37:49 by cleblais          #+#    #+#              #
#    Updated: 2023/01/20 16:53:20 by cleblais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		fdf

SRCS		=		main.c fdf_utils.c fdf_maps1.c fdf_maps2.c fdf_maps3.c\
					fdf_events.c get_next_line/get_next_line.c \
					get_next_line/get_next_line_utils.c fdf_list_utils.c \
					fdf_list.c fdf_draw.c fdf_bresenham.c

OBJS		= 		$(SRCS:.c=.o)


CC			=		gcc

LIB			= 		ft_printf/libftprintf.a libft/libft.a

CFLAGS		=		-Wall -Wextra -Werror -g

RM			= 		rm -f

all			:		$(NAME)

$(NAME)		:		$(OBJS) $(LIB)
					$(CC) $(CFLAGS) $(OBJS) $(LIB) -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(LIB)		:
					@make -C libft
					@make fclean -C libft
					@make -C ft_printf
					@make fclean -C ft_printf

clean		:
					$(RM) $(OBJS) $(OBJS_BONUS)

fclean		:		clean
					$(RM) $(NAME)

re			:		fclean all
