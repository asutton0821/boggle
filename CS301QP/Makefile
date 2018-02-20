COMPILE_FLAGS	:= -Wstrict-prototypes -Wshadow -Wpointer-arith -Wcast-qual \
   -Wcast-align -Wwrite-strings -Wnested-externs -Winline \
   -W -Wundef -Wmissing-prototypes  -O0 -g
LIBS		:= -lm

LINK_FLAGS	:= $(LIBS)

#
# Programs
#
all:	boggle

boggle:	boggle.o
	 $(CC) $(LINK_FLAGS) -o $@ $^

#
# Objects
#

%.o: %.c
	$(CC) $(CFLAGS) $(COMPILE_FLAGS) -c $< -o $@

clean:
	rm -f *.o boggle

