# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kezekiel <kezekiel@student.21-schoo>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/19 13:58:11 by kezekiel          #+#    #+#              #
#    Updated: 2022/03/23 14:30:00 by kezekiel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

RM = rm -rf

FLAGS = -Wall -Wextra -Werror 

ODIR = objs

INC = philo.h

SRC = init.c action.c condition.c error.c params.c philo.c time.c utils.c

OBJ = $(SRC:.c=.o)

OFIX = $(addprefix $(ODIR)/, $(OBJ))

all: $(NAME)

$(ODIR)/%.o: %.c $(INC)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(ODIR) $(OFIX)
	$(CC) $(OFIX) $(FLAGS) -o $(NAME)

$(ODIR):
	mkdir -p $(ODIR)

clean:
	$(RM) $(ODIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
