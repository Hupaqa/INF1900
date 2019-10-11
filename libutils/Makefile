src= $(wildcard *.cpp) \
	$(wildcard *.c)
obj= $(src:.cpp=.o) \
	$(src:.c=.o)
trg=libutils.a

MCU=atmega324pa
CC=avr-gcc
CFLAGS=-I. -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-Wall   

CXXFLAGS=-fno-exceptions   


all: $(trg)
$(trg):$(obj)
	ar -crs $(trg) $(obj)

%.o:%.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c -o $@ $<

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o
	rm -f *.a

vars:
	@echo src
	@echo obj
	@echo trg



