OBJS	= flowctl.o sysvars.o
SOURCE	= client.c flowctl.c sysvars.c
HEADER	= flowctl.h sysvars.h
OUT	= rkb_client
CC	 = cc
FLAGS	 = -c
LFLAGS	 = -lcurl

all: $(OBJS)
	$(CC) client.c $(OBJS) -o $(OUT) $(LFLAGS) && rm $(OBJS)

flowctl.o: flowctl.c
	$(CC) $(FLAGS) flowctl.c

sysvars.o: sysvars.c
	$(CC) $(FLAGS) sysvars.c


clean:
	rm -f $(OBJS) $(OUT)
