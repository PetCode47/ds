#!/bin/bash
for i in { 1 .. $1 } ; do ./mem_val ./a.out $i ; done;
sleep 10;
for i in { 1 .. $1 } ; do cat $i.log | grep "definitely lost" ; done;
