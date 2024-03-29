# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adrperez <adrperez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 13:52:47 by adrperez          #+#    #+#              #
#    Updated: 2023/03/16 12:19:13 by adrperez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Exit
NAME		= 	pipex

#Sources
SRCS		= 	src/paths.c \
				src/main.c \
				src/ft_pipex.c \
				src/error_mngmnt.c \
				src/ft_files.c \
				utils/ft_memcmp.c \
				utils/ft_split.c \
				utils/ft_strdup.c \
				utils/ft_strlen.c \
				utils/ft_calloc.c \
				utils/ft_strlcat.c \
				utils/ft_strjoin.c \
				utils/ft_bzero.c \
				utils/ft_putstr_fd.c \

#Sources
SRCS_BONUS	= 	src/paths_bonus.c \
				src/main_bonus.c \
				src/ft_pipex_bonus.c \
				src/error_mngmnt.c \
				src/ft_files.c \
				utils/ft_memcmp.c \
				utils/ft_split.c \
				utils/ft_strdup.c \
				utils/ft_strlen.c \
				utils/ft_calloc.c \
				utils/ft_strlcat.c \
				utils/ft_strjoin.c \
				utils/ft_bzero.c \
				utils/ft_putstr_fd.c \
				

OBJS		= 	$(SRCS:.c=.o)
OBJS_BONUS	= 	$(SRCS_BONUS:.c=.o)

#Compilation
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address

#Include
INC			= ./include

#Erase
RM			= 	rm -rf

#Default target
all:		$(NAME)
			
%.o:%.c
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I$(INC)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)		

bonus: $(OBJS_BONUS)
		$(CC) $(CFLAGS)  -o $(NAME) $(OBJS_BONUS)

#Cleaning objects (Eliminacion de objetos)
clean:
			$(RM) $(OBJS)

#Cleaning objects and executable 
fclean:		clean
			$(RM) $(NAME) $(OBJS_BONUS) $(OBJS)

#Cleaning all and then compilation
re:			fclean all

#Exectute no matter name is
.PHONY: all clean fclean re bonus