#!/bin/bash

for i in {1..10}
do
    time -p ./thread_ex_4.out 10000000 $i
done