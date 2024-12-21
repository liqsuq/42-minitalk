NAME := server client
BNAME := server_bonus client_bonus
OBJECT := server.o client.o
BOBJECT := server_bonus.o client_bonus.o
LFTDIR := libft
LFT := $(LFTDIR)/libft.a
CFLAGS := -Wall -Wextra -Werror -I$(LFTDIR)
LDFLAGS := -L$(LFTDIR)
LDLIBS := -lft

all: $(LFT) $(NAME)

bonus: $(LFT) $(BNAME)

server: server.o

client: client.o

server_bonus: $(LFT) server_bonus.o

client_bonus: $(LFT) client_bonus.o

$(LFT): | $(LFTDIR)
	$(MAKE) -C $(LFTDIR) all

$(LFTDIR):
	git clone https://github.com/liqsuq/libft

clean:
	$(MAKE) -C $(LFTDIR) clean
	$(RM) $(OBJECT) $(BOBJECT)

fclean: clean
	$(RM) -r $(LFTDIR)
	$(RM) $(NAME) $(BNAME)

re: fclean all