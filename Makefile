include config.mk

BIN:=$(BUILD)/bin/$(NAME)
IDIR:=src
OBJS:=
CXXFLAGS+=$(FLAGS) -Ilib -I$(IDIR)
LDFLAGS+=$(LDFLAGS) -Llib/$(BUILD) -l$(NAME)

all: $(IDIR)/main.cc lib ; @mkdir -p $(shell dirname $(BIN))
	$(CXX) $(CXXFLAGS) -o $(BIN) $< $(LDFLAGS)

.PHONY: lib
lib:
	$(MAKE) -j -C $@

run: $(BIN) ; ./$(BIN)

.PHONY: clean compile_flags
clean: ; rm -rf $(BUILD)
	$(MAKE) -C lib $@

compile_flags: ; echo $(CXXFLAGS) | xargs -n1 > compile_flags.txt
	$(MAKE) -C lib $@
