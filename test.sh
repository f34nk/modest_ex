#!/bin/bash

current=`pwd`

# check=`find target \( -name libmodest_static.a -o -name libmodest.so \)`
# if [ ! -z "$check" ]
# then

# 	echo "Test Modest..."

# 	cd target/Modest
# 	make test
# 	cd $current
# 	echo "done"
# fi

check=`find priv -name modest_client`
if [ ! -z "$check" ]
then
	echo "Test modest_client..."
	cd target/modest_client/build
	make test
	cd $current
	echo "done"

	logs=( `find target/modest_client -name LastTest.log` )
	for i in "${logs[@]}"
	do
		echo $current/$i
	done
fi