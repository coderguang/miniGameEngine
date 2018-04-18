#!/bin/bash

dir=`pwd`
echo "add ldconfig $dir"
echo $dir >/etc/ld.so.conf.d/boost.conf
ldconfig
