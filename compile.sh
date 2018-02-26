#!/bin/bash

mix_env=$1
current=`pwd`
modest_client="modest_client"

check=`find target \( -name libmodest_static.a -o -name libmodest.so \)`
if [ -z "$check" ]
then
	# if [ -z `which libtool` ]
	# then
	# 	echo "Please install libtool:
	# 	sudo apt-get install libtool"
	# 	exit 1
	# fi
	echo "Compiling Modest..."
	# Modest
	# https://github.com/lexborisov/Modest/blob/master/INSTALL.md
	cd target/Modest
	make library
	cd $current
	echo "done"
fi

# check=`find target \( -name libgq.a -o -name libgq.so \)`
# if [ -z "$check" ]
# then
# 	if [ -z `which cmake` ]
# 	then
# 		echo "Please install cmake:
# 		sudo apt-get install cmake"
# 		exit 1
# 	fi
# 	echo "Compiling gumbo-query..."
# 	# gumbo-query
# 	# https://github.com/lazytiger/gumbo-query#installation
# 	mkdir -p target/gumbo-query/build
# 	cd target/gumbo-query/build
# 	cmake -IGumbo_INCLUDE_DIR="$current/target/gumbo-parser/src" -DGumbo_LIBRARY="$current/target/gumbo-parser/.libs/libgumbo.so" -DGumbo_static_LIBRARY="$current/target/gumbo-parser/.libs/libgumbo.a" ..
# 	make
# 	cd $current
# 	echo "done"
# fi

# check=`find target \( -name libGQ.a -o -name libGQ.so \)`
# check=`find target -name libGQ.a`
# if [ -z "$check" ]
# then
# 	if [ -z `which cmake` ]
# 	then
# 		echo "Please install cmake:
# 		sudo apt-get install cmake"
# 		exit 1
# 	fi

# 	echo "Compiling GQ..."
# 	# GQ
# 	# https://github.com/lazytiger/gumbo-query#installation
# 	#
# 	# uses -std=c++14
# 	# update to g++ v5
# 	# 	sudo apt-get install g++-5
# 	# set symlink /usr/bin/g++ -> /usr/bin/g++-5
# 	# 	sudo ln -sf /usr/bin/g++-5 /usr/bin/g++
# 	#
# 	mkdir -p target/GQ/build
# 	cd target/GQ/build
# 	rm -rf *
# 	cmake -IGUMBO_INCLUDE_DIRS="$current/target/gumbo-parser/src" -IGUMBO_LIBRARY_DIRS="$current/target/gumbo-parser/.libs" ..
# 	# cmake -IGUMBO_INCLUDE_DIRS="$current/target/gumbo-parser/src" -IGUMBO_INCLUDE_DIRS="$current/target/gumbo-parser/src" -DGumbo_LIBRARY="$current/target/gumbo-parser/.libs/libgumbo.so" -DGumbo_static_LIBRARY="$current/target/gumbo-parser/.libs/libgumbo.a" ..
# 	make
# 	cd $current
# 	echo "done"
# fi

function compile_modest_client()
{
	echo "Compiling modest_client..."
	mkdir -p priv
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