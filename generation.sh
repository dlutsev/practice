#!/bin/bash

for b in 100000 1000000 10000000; do
  for i in $(seq -w 1 100); do
    ./gen_rand_bytes $b test_data/rand/rand_${b}_$i.bin
  done
done
echo "Generation rand_c completed!"

for b in 100000 1000000 10000000; do
  bytes=$(( (b + 7) / 8 ))
  for i in $(seq -w 1 100); do
    head -c $bytes /dev/urandom > test_data/urandom/urandom_${b}_$i.bin
  done
done

echo "Generation dev/urandom completed!"


for b in 100000 1000000 10000000; do
  for i in $(seq -w 1 100); do
    ./gen_lcg $b test_data/lcg/lcg_${b}_$i.bin
  done
done


echo "Generation lcg completed!"
