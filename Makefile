
CC = gcc
FLAGS = -Wall -Wextra -Werror
LIBS = -lm -lncurses
FILES = main.c
TITLE = Ray-Casting-ASCII

all: clang_format $(TITLE)

$(TITLE): $(FILES)
	@$(CC) $(FILES) $(LIBS) -o $(TITLE)

with_flags: $(FILES)
	@$(CC) $(FLAGS) $(FILES) $(LIBS) -o $(TITLE)

clang_format:
	@clang-format -i --style=file:.clang-format $(FILES)

leaks: rebuild
	@valgrind --leak-check=full --show-leak-kinds=all ./$(TITLE) $(FILES)

clean:
	@rm -rf $(TITLE)

rebuild: clean all

