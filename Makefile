
NAME = fractol

CC = gcc

CFLAGS = -Wall -Wextra -O3

GL = -lm -lmlx -framework OpenGL -framework AppKit

INCLUDES = fractol.h

SRCS =   fractol.c \
        julia_set.c \
        mandelbrot_set.c \
        peacock_set.c \
        burning_ship.c \
        mouse.c \
        keyboard.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ) 
	$(CC) $(CFLAGS) $(GL) $(OBJ) -o $(NAME)

%.o: %.c $(INCLUDES) 
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDES)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
