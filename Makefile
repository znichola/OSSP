MAGIC_RAYLIB_FLAGS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11

CFLAGS=-Wall -Werror -Wextra -std=c11 -g

F=orbital.c main.c

FILES=$(addprefix src/, $(F))

build :
	gcc $(CFLAGS) $(FILES) -o app -Llibs/raylib/src/ -Ilibs/raylib/src/ $(MAGIC_RAYLIB_FLAGS)

raylib :
	make -C libs/raylib/src


#  gcc src/main.c -o app.exe -O1 -Wall -std=c99 -Wno-missing-braces -Ilibs/raylib/src -Llibs/raylib/src -lraylib -lGL -lm -lpthread -ldl -lrt -lX11