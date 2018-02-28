#!/bin/bash

mix_env=$1
current=`pwd`
echo "Compiling ModestEx target from $current"

modest_client="modest_client"

check=`find target \( -name libmodest_static.a -o -name libmodest.so \)`
if [ -z "$check" ]
then
	echo "Compiling Modest..."
	# Modest
	# https://github.com/lexborisov/Modest/blob/master/INSTALL.md
	cd target/Modest
	make library
	cd $current
	echo "done"
fi

function compile_modest_client()
{
	echo "Compiling modest_client..."
	rm priv/modest_client
	mkdir -p target/$modest_client/build
	cd target/$modest_client/build
	rm -rf *
	cmake -DERLANG_PATH=`erl -eval 'io:format("~s", [lists:concat([code:root_dir(), "/erts-", erlang:system_info(version)])]), halt()' -s init stop -noshell` ..
	make
	mv modest_client $current/priv
	cd $current
	echo "done"
}

if [ "$mix_env" = "dev" ] || [ "$mix_env" = "test" ]
then
	echo $mix_env
	compile_modest_client
else
	check=`find priv -name modest_client`
	if [ -z "$check" ]
	then
		compile_modest_client
	fi
fi