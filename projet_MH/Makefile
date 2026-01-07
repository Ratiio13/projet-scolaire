# --- Compiler & flags ---
CXX       := g++
STD       := -std=c++17
WARN      := -Wall -Wextra
OPT       := -O2
CXXFLAGS  := $(STD) $(WARN) $(OPT)
CPPFLAGS  := -Iinclude
LDFLAGS   :=
LDLIBS    :=

# Optionnels : ex. make SAN=address (asan), SAN=undefined, etc.
ifneq ($(SAN),)
CXXFLAGS  += -fsanitize=$(SAN)
LDFLAGS   += -fsanitize=$(SAN)
endif

# --- Paths & files ---
SRCDIR    := src
OBJDIR    := build/obj
BINDIR    := build/bin
TARGET    := $(BINDIR)/prog.exec

# Liste explicite (selon ta commande)
SOURCES   := \
  $(SRCDIR)/main.cpp \
  $(SRCDIR)/traitement_instance.cpp \
  $(SRCDIR)/heuristique_init.cpp \
  $(SRCDIR)/meta.cpp \
  $(SRCDIR)/hard.cpp \
  $(SRCDIR)/penalite.cpp

OBJECTS   := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
DEPS      := $(OBJECTS:.o=.d)

# --- Default target ---
.PHONY: all
all: $(TARGET)

# Link
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# Compile (with dep generation)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@

# Dirs
$(OBJDIR) $(BINDIR):
	mkdir -p $@

# Convenience targets
.PHONY: run debug release clean distclean
run: $(TARGET)
	./$<

debug: CXXFLAGS := $(STD) $(WARN) -O0 -g3
debug: $(TARGET)

release: CXXFLAGS := $(STD) $(WARN) -O2 -DNDEBUG
release: $(TARGET)

clean:
	$(RM) -r $(OBJDIR)

distclean: clean
	$(RM) -r $(BINDIR)

# Include auto-generated deps
-include $(DEPS)
