# Contributing to ModestEX

<!--
#### Table Of Contents

[Howto add a new feature?](#howto-add-a-new-feature)
-->

## Howto add a new feature?

The ModestEx module implements the interface you need for a great user experience. The core functionality however, is implemented in `C` in the `target/modest_client` folder.

### fork and branch

fork repo, clone it and create new branch

	git clone git@github.com:YOUR-GITHUB-USERNAME/modest_ex.git
	git branch feature-XY
	cd feature-XY

update submodule, get dependencies and compile

	git submodule update --init --recursive --remote
	mix deps.get
	mix compile
	mix test

### target and binding

add files

	target/modest_client/modest_XY.h
	target/modest_client/modest_XY.c
	target/modest_client/handle_XY.h
	target/modest_client/handle_XY.c
	target/modest_client/test/modest_XY_test.c

add sources `modest_XY.c` and `handle_XY.c` to

	target/modest_client/CMakeLists.txt

add `modest_XY_test.c` to

	target/modest_client/test/CMakeLists.txt

add handler to

	repos/modest_ex/target/modest_client/handlers.c

implement feature in `modest_XY.c`
implement feature test in `modest_XY_test.c`
implement feature binding in `handle_XY.c`

### integration

add files

	lib/modest_ex/XY.ex
	lib/modest_ex/safe/XY.ex
	test/modest_ex_XY_test.exs

add feature and spec in `lib/modest_ex`

implement pattern matching for method in `lib/modest_ex/XY.ex`
implement cnode call in `lib/modest_ex/safe/XY.ex`
implement integration test in `test/modest_ex_XY_test.exs`
implement pipe test in `test/pipe_test.exs`

### test target

compile

	priv/compile.sh dev

execute only the feature test

	target/modest_client/build/modest_XS_test

execuet all target test

	priv/test.sh

or

	mix test.target

### test integration

	mix compile
	mix test

### add documentation

add feature description and example to

	FEATURES.md

### submit

Push changes to your branch `feature-XY` and submit `Compare & pull request`.