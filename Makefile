CC = gcc
CFLAGS = -Wall -Iinclude
SRCDIR = src
BUILDDIR = build
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))
TARGET = $(BUILDDIR)/app

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS)	-o $@	$^

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	mkdir	-p	$(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)
