#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/12 18:06:35 by rduclos           #+#    #+#              #
#    Updated: 2014/05/17 23:08:35 by rduclos          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SERV_NAME = server
FLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes/

CC = g++

DIROBJ = obj/
DIRSRV = server_d/

SERV_SRC =	buf_circle.cpp client_init.cpp clients.cpp main.cpp \
			server_init.cpp server_start.cpp

SERV_OBJ = $(SERV_SRC:%.cpp=$(DIROBJ)%.o)

all: $(SERV_NAME)

$(SERV_NAME): $(SERV_OBJ)
	@echo "==> Compiling $(SERV_NAME)"
	@$(CC) $(FLAGS) -o $@ $(SERV_OBJ) $(INCLUDES)
	@sleep .5
	@tput cuu1
	@echo "\033[2K\t\033[1;36m$(SERV_NAME)\t\t\033[0;32m[Ready]\033[0m"

$(DIROBJ)%.o: $(DIRSRV)%.cpp
	@echo "--> Compiling $<"
	@$(CC) $(FLAGS) -o $@ -c $< $(INCLUDES)

clean:
	@rm -f $(SERV_OBJ)
	@echo "[$(SERV_NAME)]--> Objects removed"

fclean: clean
	@echo "[$(SERV_NAME)]--> Program removed"
	@rm -f $(SERV_NAME)

re: fclean all
