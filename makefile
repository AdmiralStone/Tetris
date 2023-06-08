CC = g++
CPPFLAGS = -I/opt/homebrew/include -IHeaders -Isrc -Wall -Wextra -std=c++20
LDFLAGS = `pkg-config --libs raylib`

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

main: $(OBJECTS)
	$(CC) $(CPPFLAGS) -o $(BINDIR)/$@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/main


