# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lstepany <lstepany@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/08 00:17:28 by lstepany          #+#    #+#              #
#    Updated: 2021/04/08 00:17:29 by lstepany         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



SRC = 	main.c \
		line_data_obj.c \
		helping_ft.c \
		hooks.c \
		vector_rot.c \
		intersect_sphere.c  \
		intersect_cylinder.c \
		intersect_cone.c \
		intersect_plane.c \
		line_data.c \
		cylinder.c \
		cone.c \
		sphere.c \
		plane.c \
		vector.c \
		vector_xz.c \
		initialiser.c \
		find_objects.c
OBJ =	main.o \
		line_data_obj.o \
		helping_ft.o \
		hooks.o \
		vector_rot.o \
		intersect_sphere.o  \
		intersect_cylinder.o \
		intersect_cone.o \
		intersect_plane.o \
		line_data.o \
		cylinder.o \
		cone.o \
		sphere.o \
		plane.o \
		vector.o \
		vector_xz.o \
		initialiser.o \
		find_objects.o
#SRC = $(addprefix ./src/, $(FILE_C))
#OBJ = $(addprefix ./obj/, $(FILE_O))
MLX =	-I /usr/local/include -L /usr/local/lib/ -lmlx -I /usr/include/X11 -L \
		/usr/lib/x86_64-linux-gnu -lXext -lX11
FLAGS = -Wall -Wextra -Werror
all: rtv1
rtv1: $(OBJ)
	make -C libft
	gcc  $(FLAGS) -g -o RTv1 $(OBJ) -L libft/ -lft -lm $(MLX) 
$(OBJ):%.o: %.c rt.h
	#gcc $(FLAGS) -c $<
	gcc -c $<

libft:
	make -C libft
clean:
	make fclean -C libft
	rm -rf *~ *.o
fclean: clean
	rm -f RTv1
re:fclean all
