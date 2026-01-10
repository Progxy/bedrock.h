FLAGS = -Wall -Wextra -pedantic -fsanitize=undefined -fsanitize=address
# TODO: Maybe shouldn't rely on gnu11
FLAGS += -std=gnu11

test: bedrock.h test.c
	gcc $(FLAGS) test.c -o test
