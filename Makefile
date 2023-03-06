# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 13:52:47 by adrperez          #+#    #+#              #
#    Updated: 2023/03/06 13:38:50 by adrperez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Exit
NAME		= 	pipex

#Sources
SRCS		= 	src/paths.c \
				src/main.c \
				utils/ft_memcmp.c \
				utils/ft_split.c \
				utils/ft_strdup.c \
				utils/ft_strlen.c \
				utils/ft_calloc.c \
				utils/ft_strlcat.c \
				utils/ft_strjoin.c \
				utils/ft_bzero.c \

OBJS		= 	$(SRCS:.c=.o)

#Compilation
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g

#Include
INC			= ./include

#Erase
RM			= 	rm -rf

#Default target
all:		$(NAME)
			
%.o:%.c
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I$(INC)

$(NAME): $(OBJS)
		$(CC) -o $(NAME) $(OBJS)		

#Cleaning objects (Eliminacion de objetos)
clean:
			$(RM) $(OBJS)

#Cleaning objects and executable 
fclean:		clean
			$(RM) $(NAME)

#Cleaning all and then compilation
re:			fclean all

#Exectute no matter name is
.PHONY: all clean fclean re