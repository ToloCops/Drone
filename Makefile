# Dichiarazione delle variabili
CC := g++
SRCDIR := src
OBJDIR := obj
BINDIR := bin
TARGET := $(BINDIR)/drone_simulation
SRCEXT := cpp
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -std=c++11 -Wall
LIB :=

# Compilazione del target
$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $^ -o $(TARGET) $(LIB)

# Compilazione dei file oggetto
$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

# Pulizia dei file oggetto e dell'eseguibile
clean:
	@echo "Pulizia..."
	$(RM) -r $(OBJDIR) $(BINDIR)

# Esecuzione dell'applicazione
run: $(TARGET)
	@echo "Esecuzione dell'applicazione..."
	@$(TARGET)

.PHONY: clean run
