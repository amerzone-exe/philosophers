# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 11:08:12 by jpiquet           #+#    #+#              #
#    Updated: 2025/04/24 18:47:31 by jpiquet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

NAME = philo

#FLAGS = -Wall -Wextra -Werror -pthread -g3
FLAGS = -pthread -g3

INCDIR = inc

SRCDIR = src
SRC = 	$(SRCDIR)/main.c \
		$(SRCDIR)/parsing.c \
		$(SRCDIR)/utils.c \

OBJDIR = obj
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

all : $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(FLAGS) -I $(INCDIR) -o $(NAME) $(OBJ)

$(OBJDIR)/%.o : $(SRCDIR)/%.c | $(OBJDIR)
			$(CC) $(FLAGS) -I $(INCDIR) -o $@ -c $<

$(OBJDIR) :
		mkdir -p $(OBJDIR)

clean :
	rm -rf $(OBJDIR)

fclean : clean
	rm -f $(NAME)

re : fclean all