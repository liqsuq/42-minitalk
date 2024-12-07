NAME := server client
OBJECT := server.o client.o
LFTDIR := libft
LFTLIB := $(LFTDIR)/libft.a
CFLAGS := -Wall -Wextra -Werror -I$(LFTDIR)
LDFLAGS := -L$(LFTDIR)
LDLIBS := -lft

all: $(NAME)

server: server.o $(LFTLIB)

client: client.o $(LFTLIB)

$(LFTLIB):
	make -C $(LFTDIR) all

clean:
	make -C $(LFTDIR) clean
	rm -f $(OBJECT)

fclean:
	make -C $(LFTDIR) fclean
	rm -f $(NAME)

re: fclean all