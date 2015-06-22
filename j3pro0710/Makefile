VPATH = ./src ./

TARGET = No0710_1
SRCS = main.c list.c

OBJS = $(SRCS:.c=.o)
OBJS_PATH = $(SRCS:%.c=$(DEST_DIR)/%.o)
DEST_DIR = ./bin

default : $(TARGET)

all : $(TARGET)

run : $(DEST_DIR)/$(TARGET)
	$(DEST_DIR)/$(TARGET)

.c.o:
	$(CC) $(CFLAGS) -c -o $(DEST_DIR)/$@ $^

clean :
	rm -f $(DEST_DIR)/*

$(OBJS) : $(SRCS)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS_PATH) -o $(DEST_DIR)/$@

main.c :
