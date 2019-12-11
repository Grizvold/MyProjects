#!/bin/bash

for i in {1..100}
do
    time -p ./thread_ex_4.out 100000000 $i
done