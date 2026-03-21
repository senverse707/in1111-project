CC = gcc
CFLAGS = -Wall -Wextra -I include
SRC = main.c src/actions.c src/categories.c src/claims.c \
      src/found_item.c src/lost_item.c src/resolved_cases.c src/staff.c
OBJ = $(SRC:.c=.o)
TARGET = lost_and_found

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q $(subst /,\,$(OBJ)) $(TARGET).exe 2>nul || true

.PHONY: all clean
