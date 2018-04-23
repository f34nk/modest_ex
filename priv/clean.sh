#!/bin/bash

current=`pwd`

echo "Clean ModestEx target from $current"

check=`find target \( -name libmodest_html.a \)`
if [ ! -z "$check" ]
then
	echo "Clean modest_html..."
	cd target/modest_html/build
	rm libmodest_html.a
	make clean
	rm -rf *
	cd $current
	echo "done"
fi

check=`find priv -name modest_worker`
if [ ! -z "$check" ]
then
	echo "Clean modest_worker..."
	cd target/modest_worker/build
	make clean
	rm -rf *
	cd $current
	echo "remove modest_worker..."
	cd priv
	rm modest_worker
	cd $current
	echo "done"
fi