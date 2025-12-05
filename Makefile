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

CURRENT_VERSION:=$(shell awk -F'"' '/version/ {print $$2}' mix.exs)

.PHONY: publish/release
publish/release: modest_ex-$(CURRENT_VERSION).tar
	#
	# authenticate with hex
	#
	mix hex.user auth
	#
	# publish package
	#
	mix hex.publish
	

# .PHONY: publish/bump-version
# publish/bump-version:
# 	#
# 	# bump version $(CURRENT_VERSION) to $(NEW_VERSION)
# 	#
# 	sed -i '' 's/{vsn, "$(CURRENT_VERSION)"}/{vsn, "$(NEW_VERSION)"}/g' src/lexbor_erl.app.src
# 	sed -i '' 's/{lexbor_erl, "$(CURRENT_VERSION)"}/{lexbor_erl, "$(NEW_VERSION)"}/g' README.md
# 	sed -i '' 's/{lexbor_erl, "$(CURRENT_VERSION)"}/{lexbor_erl, "$(NEW_VERSION)"}/g' demo/rebar.config
