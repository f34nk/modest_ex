#!/bin/bash

current=`pwd`

echo "Clean ModestEx target from $current"

check=`find target \( -name libmodest_static.a -o -name libmodest.so \)`
if [ ! -z "$check" ]
then
	echo "Clean Modest..."
	cd target/Modest
	make clean
	cd $current
	echo "done"
fi

check=`find priv -name modest_client`
if [ ! -z "$check" ]
then
	echo "Clean modest_client..."
	cd target/modest_client/build
	make clean
	rm -rf *
	cd $current
	echo "remove modest_client..."
	cd priv
	rm modest_client
	cd $current
	echo "done"
fi