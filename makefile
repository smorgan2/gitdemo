
CFLAGS		= -g -Wall
OBJS		= LLNode.o main.o


numberLines : $(OBJS)
	$(CC) $(CFLAGS) -o numberLines $(OBJS)

clean :
	- rm -f $(OBJS)
	- rm -f numberLines
	- rm -f tags

tags : dummy
	ctags *.c

dummy:
