.PHONY: all
all: clean install compile test

.PHONY: install
install:
	mix deps.get

.PHONY: compile
compile:
	mix compile

.PHONY: test
test:
	mix test

.PHONY: clean
clean:
	mix clean
	rm -rf _build deps
