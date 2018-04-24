#!/bin/bash

current=`pwd`

echo "Clean ModestEx target from $current"

check=`find target \( -name libmodest_html.a \)`
if [ ! -z "$check" ]
then
	echo "Clean modest_html..."
	cd target/modest_html/build
	make clean
	cd $current
	rm -rf target/modest_html/build
	echo "done"
fi

check=`find target \( -name libmodest_static.a \)`
if [ ! -z "$check" ]
then
	echo "Clean Modest..."
	cd target/modest_html/libs/Modest
	make clean
	cd $current
	echo "done"
fi

check=`find priv -name modest_worker`
if [ ! -z "$check" ]
then
	echo "Clean modest_worker..."
	cd target/modest_worker/build
	make clean
	cd $current
	rm -rf target/modest_worker/build
	echo "remove modest_worker..."
	cd priv
	rm modest_worker
	cd $current
	echo "done"
fi