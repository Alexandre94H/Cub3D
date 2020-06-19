# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/18 23:00:35 by ahallain          #+#    #+#              #
#    Updated: 2020/06/19 19:10:25 by ahallain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

SRCS	=	main/cub3d.c \
			main/utils.c \
			parse/load.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \
			parse/edit.c \
			parse/check.c \
			runtime/mlx.c \
			runtime/game.c \
			runtime/event.c \
			runtime/exit.c \
			runtime/update_position.c \
			runtime/update_screen.c \
			runtime/floor.c \
			runtime/wall.c \
			runtime/bitmap.c \
			engine/raycaster.c

OBJS	=	${SRCS:.c=.o}

CFLAGS	=	-Werror -Wextra -Wall

LIBS	=	-lmlx -lX11 -lXext -lbsd -lm

.c.o:
	@printf "Compiling $@"
	@gcc ${CFLAGS} -c $< -o ${<:.c=.o}
	@printf "\033[50G✓\n"

${NAME}:
	@printf "\033[1;33mCompiling ${NAME}...\033[0m\n"
	@make --no-print-directory ${OBJS}
	@printf "Compiling $@"
	@gcc ${CFLAGS} ${OBJS} ${LIBS} -o ${NAME}
	@printf "\033[50G✓\n"
	@printf "\033[1;32mDone\033[0m"
	@printf "\e[100m\e[30m\n\n"
	@make --no-print-directory rabbit
	@printf "\033[0m\n"

all: ${NAME}

offline_clean:
	@printf "Removing .o"
	@rm -rf ${OBJS}
	@printf "\033[50G✓\n"

clean:
	@printf "\033[1;31mRemoving compilation file...\033[0m\n"
	@make --no-print-directory offline_clean
	@printf "\033[1;32mDone\033[0m\n"

fclean:
	@printf "\033[1;31mRemoving compilation file...\033[0m\n"
	@make --no-print-directory offline_clean
	@printf "Removing ${NAME}"
	@rm -rf ${NAME}
	@printf "\033[50G✓\n"
	@printf "\033[1;32mDone\033[0m\n"

re: fclean all

tank:
	@echo '	......( \_/ )'
	@echo '	......( o_o )'
	@echo '	..../""""""""""""\======░ ▒▓▓█D'
	@echo '	/"""""""""""""""""""\'
	@echo '	\_@_@_@_@_@_@_@_@_@_/'

42:
	@echo '                ,*******              .,,****,,'
	@echo '              *(*//*////@(        *#**//(###((((##%#.'
	@echo '            .#((/*,***/*@#      (/*,**/(((//((#((((((&*'
	@echo '           /(/**/(*..,.*@#     #,,.,,/(/**/((//////(((&('
	@echo '         ,%#((//*,.**...@#    *.. .**,,*@@&((&*//((####@*'
	@echo '       #####((/(*,. .. @#    (  .. ...&@,    %((######@#'
	@echo '      ((((/////@@//*,.. @#     /&&&&&&&%*    ((########@#'
	@echo '    ,%####(((&@%%,...   @#                 ,#((((#####@@,'
	@echo '  .####(((/#@&, #....   @#              .((((((######@@*'
	@echo ' /%####(((@@(  .#***,,. @#            *#///////((((@@%.'
	@echo '*(((((((#####((((/*.... . ../       (*. .*//(###%@@#.'
	@echo '*%%%#########((*,**,, .. . .@*    (. ,,//(*,*(@@&*'
	@echo '*##########(//(/*//../... ,.@*  **...,.**/(&@@(.'
	@echo '*%%%####(((#((((/,,(/.**.,**@* (,**,*,*/,/(/(#####(((((&( '
	@echo ' ./((((((((((((#&(#*,//.@&((/./,,///**/*(/*/(((####%###&&.'
	@echo '                %(**((**@#   ,/**//((//(//((//(#######%@&.'
	@echo '                #//#(/*(@#   /(////((((/((((#(((#######&&.'
	@echo '                 .*******.     ,************************.'

rabbit:
	@echo '	{\__/}'
	@echo '	( •.•)'
	@echo '	/ > ❤️'

.PHONY: all offline_clean clean fclean re