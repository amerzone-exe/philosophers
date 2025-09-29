# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amerzone <amerzone@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 11:08:12 by jpiquet           #+#    #+#              #
#    Updated: 2025/09/28 15:04:20 by amerzone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

NAME = philo

FLAGS = -Wall -Wextra -Werror -pthread -g -O2

INCDIR = inc

SRCDIR = src
SRC = 	$(SRCDIR)/main.c \
		$(SRCDIR)/action.c \
		$(SRCDIR)/exit.c \
		$(SRCDIR)/fork.c \
		$(SRCDIR)/free.c \
		$(SRCDIR)/init.c \
		$(SRCDIR)/mutex_lib.c \
		$(SRCDIR)/parsing.c \
		$(SRCDIR)/routine.c \
		$(SRCDIR)/time.c \
		$(SRCDIR)/utils.c \
		$(SRCDIR)/watcher.c \

OBJDIR = obj
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

all : $(NAME)

$(NAME) : $(OBJ) 
		$(CC) $(FLAGS) -I $(INCDIR) -o $(NAME) $(OBJ)

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCDIR)/*.h | $(OBJDIR)
			$(CC) $(FLAGS) -I $(INCDIR) -o $@ -c $<

$(OBJDIR) :
		mkdir -p $(OBJDIR)

clean :
	rm -rf $(OBJDIR)

fclean : clean
	rm -f $(NAME)

re : fclean all