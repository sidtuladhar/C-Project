CC = gcc
CFLAGS = -Wall -I/opt/homebrew/Cellar/openssl@3/3.3.2/include
LDFLAGS = -L/opt/homebrew/Cellar/openssl@3/3.3.2/lib -lssl -lcrypto
TARGET = blockchain
SRCS = src/hash.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

# Rule to compile the source file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link the object files and create the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Clean rule to remove generated object files and executable
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean