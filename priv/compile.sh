#!/bin/bash

mix_env=$1
current=`pwd`
echo "Compiling ModestEx target from $current $mix_env"

modest_worker="modest_worker"

check=`find target \( -name libmodest_html.a \)`
if [ -z "$check" ]
then
	echo "Compiling modest_html..."
	
	cd target/modest_html
	./configure && cd build && make
	cd $current
	echo "done"
fi

function compile_modest_worker()
{
	echo "Compiling modest_worker..."
	rm priv/modest_worker
	mkdir -p target/$modest_worker/build
	cd target/$modest_worker/build
	rm -rf *
	cmake -DERLANG_PATH=`erl -eval 'io:format("~s", [lists:concat([code:root_dir(), "/erts-", erlang:system_info(version)])]), halt()' -s init stop -noshell` ..
	make
	mv modest_worker $current/priv
	cd $current
	echo "done"
}

if [ "$mix_env" = "dev" ] || [ "$mix_env" = "test" ]
then
	echo $mix_env
	compile_modest_worker
else
	check=`find priv -name modest_worker`
	if [ -z "$check" ]
	then
		compile_modest_worker
	fi
fi