#!/bin/bash

# Settings
SRCDIR=../src


echo "Rebuilding the $1 header files..."
rm -rf $1
mkdir $1
for header in $(find $SRCDIR/$1/ -name '*.h') ; do ln -sf ../$header $1/$(echo $header | awk -F '/' '{print $NF}') ; done
for header in $(find $SRCDIR/$1/ -name '*.inl') ; do ln -sf ../$header $1/$(echo $header | awk -F '/' '{print $NF}') ; done
for header in $(find $SRCDIR/$1/ -name '*.mcr') ; do ln -sf ../$header $1/$(echo $header | awk -F '/' '{print $NF}') ; done

