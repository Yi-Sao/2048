
TARGET := main
SRC := $(wildcard *.c)
DEPEND := $(patsubst %.c, %.o, $(SRC))
INCLUDE += ./
LIB += ./
INSTALLPATH := /home/china/Tftpboot
CC := arm-linux-gcc

$(TARGET): $(DEPEND)
	$(CC) -o $@ $^ -I $(INCLUDE) -L $(LIB)


clean:
	rm $(TARGET) -rf
	rm *.o -rf

install:
	cp $(TARGET) $(INSTALLPATH)


















