NAME := server client
BNAME := server_bonus client_bonus
OBJECT := server.o client.o
BOBJECT := server_bonus.o client_bonus.o
LFTDIR := libft
LFTLIB := $(LFTDIR)/libft.a
CFLAGS := -Wall -Wextra -Werror -I$(LFTDIR)
LDFLAGS := -L$(LFTDIR)
LDLIBS := -lft

all: $(NAME)

bonus: $(BNAME)

server: server.o $(LFTLIB)

client: client.o $(LFTLIB)

server_bonus: server_bonus.o $(LFTLIB)

client_bonus: client_bonus.o $(LFTLIB)

$(LFTLIB):
	make -C $(LFTDIR) all

clean:
	make -C $(LFTDIR) clean
	rm -f $(OBJECT)

fclean:
	make -C $(LFTDIR) fclean
	rm -f $(NAME)

re: fclean all