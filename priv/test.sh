#!/bin/bash

current=`pwd`

echo "Test ModestEx target from $current"

# check=`find target \( -name libmodest_static.a -o -name libmodest.so \)`
# if [ ! -z "$check" ]
# then

#   echo "Test Modest..."

#   cd target/Modest
#   make test
#   cd $current
#   echo "done"
# fi

check=`find priv -name modest_worker`
if [ ! -z "$check" ]
then
  echo "Test modest_worker..."
  cd target/modest_worker/build
  make test
  cd $current
  echo "done"

  logs=( `find target/modest_worker -name LastTest.log` )
  for i in "${logs[@]}"
  do
    echo $current/$i
  done

  logs=( `find target/modest_worker -name LastTestsFailed.log` )
  for i in "${logs[@]}"
  do
    echo $current/$i
  done
fi