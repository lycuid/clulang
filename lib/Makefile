include ../config.mk

IDIR:=.
BIN:=$(BUILD)/lib$(NAME).a

override CXXFLAGS+=$(FLAGS) -I$(IDIR)

OBJS:=$(ODIR)/$(NAME)/lexer.o         \
      $(ODIR)/$(NAME)/lexer/token.o   \
      $(ODIR)/$(NAME)/reader.o        \
      $(ODIR)/$(NAME)/trie.o          \

all: $(OBJS) ; @mkdir -p $(shell dirname $(BIN))
	$(AR) rcs $(BIN) $^

$(ODIR)/%.o: $(IDIR)/%.cc $(IDIR)/%.hh ; @mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -fPIC -o $@ $<

.PHONY: clean compile_flags
clean: ; rm -rf $(BUILD)
compile_flags: ; echo $(CXXFLAGS) | xargs -n1 > compile_flags.txt
