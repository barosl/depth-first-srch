NAME = depth-first-search
OBJS = main.o graph.o

CFLAGS = -Wall -Werror

.PHONY: all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f $(NAME) $(OBJS)
