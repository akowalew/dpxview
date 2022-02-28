#!/bin/sh

CFLAGS="$CFLAGS -Wall -Wextra -Wpedantic -Wshadow -Wundef -Werror -Wconversion -Wfatal-errors -Wmissing-field-initializers"
CFLAGS="$CFLAGS -Wno-unused-function -Wno-unused-parameter -Wno-pointer-arith -Wno-unused-but-set-variable -Wno-unused-variable -Wno-long-long"
CFLAGS="$CFLAGS -g -ggdb -g3"
# CFLAGS="$CFLAGS -std=c++11"

set -ex

g++ $CFLAGS linux_dpxview.cpp -o dpxview
g++ $CFLAGS test.cpp -o test
./test
