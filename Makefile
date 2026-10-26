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

.PHONY: demo
demo: demo/run demo/all

.PHONY: demo/run
demo/run:
	cd demo && mix deps.get && mix run -e "Demo.run"

.PHONY: demo/all
demo/all:
	cd demo && mix deps.get && mix run -e "Demo.run_all"

.PHONY: demo/clean
demo/clean:
	rm -rf demo/_build demo/deps demo/mix.lock

NEW_VERSION:=$(shell tr -d '[:space:]' < VERSION)
CURRENT_VERSION:=$(shell sed -n 's/.*{:modest_ex, "~> *\([^"]*\)"}.*/\1/p' demo/mix.exs | head -1)

.PHONY: publish/build
publish/build: clean install compile
	#
	# build package
	#
	mix hex.build
	#
	# generate documentation
	#
	mix docs

.PHONY: publish/bump-version
publish/bump-version:
	#
	# bump version $(CURRENT_VERSION) to $(NEW_VERSION)
	#
	@test -n "$(NEW_VERSION)" || (echo "VERSION is empty" && exit 1)
	@test -n "$(CURRENT_VERSION)" || (echo "Could not detect current version from demo/mix.exs" && exit 1)
	sed -i '' 's/{:modest_ex, "~> $(CURRENT_VERSION)"}/{:modest_ex, "~> $(NEW_VERSION)"}/g' README.md
	sed -i '' 's/{:modest_ex, "~> $(CURRENT_VERSION)"}/{:modest_ex, "~> $(NEW_VERSION)"}/g' demo/mix.exs
	@echo "mix.exs version is read from VERSION ($(NEW_VERSION))"

.PHONY: publish/tag
publish/tag:
	VERSION=$$(tr -d '[:space:]' < VERSION) && \
	test -n "$$VERSION" && \
	git tag -a v$$VERSION -m v$$VERSION && \
	git push origin v$$VERSION

.PHONY: publish/release
publish/release:
	#
	# authenticate with hex
	#
	mix hex.user auth
	#
	# publish package
	#
	mix hex.publish
