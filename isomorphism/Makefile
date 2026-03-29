CC      = gcc
CFLAGS  = -Wall -Wextra -Werror

TARGET  = graph_isomorphism
SRCS    = backtracking_core.c graph_construction.c main_entry_point.c \
        main.c preprocessing.c rejection_filters.c \

OBJS    = $(SRCS:.c=.o)

HEADER = graph_isomorphism.h

# ── default target ─────────────────────────────────────────────
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# ── compile each .c into a .o ──────────────────────────────────
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# ── remove build artifacts ─────────────────────────────────────
clean:
	rm -f $(OBJS) $(TARGET)

# ── rebuild from scratch ───────────────────────────────────────
re: clean all

# ── run the program ────────────────────────────────────────────
run: all
	./$(TARGET)

# ── prevent conflicts with files named clean / run / re ────────
.PHONY: all clean re run