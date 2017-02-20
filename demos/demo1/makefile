PROGS1= demo

MAIN1= demo1.cpp

INCLUDES= -I../../

CFLAGS= -O3 -std=c++11

LDFLAGS=

CC=g++

STDLIBS = -lm
LIBSRC =

all: $(PROGS1)
.PHONY:all
$(PROGS1):$(MAIN1)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(PROGS1) $(MAIN1) $(LIBSRC) $(LDFLAGS) $(STDLIBS)
