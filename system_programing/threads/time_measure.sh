#!/bin/bash

for i in {1..10}
do
    time -p ./thread_ex_4.out 12 $i
done