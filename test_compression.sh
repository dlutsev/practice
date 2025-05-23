#!/bin/bash

echo "file,original,gzip,rar,xz" > compression_results.csv

for gen in rand urandom lcg; do
  for file in test_data/$gen/*.bin; do
    orig_size=$(stat -c%s "$file")

    gzip -c "$file" > "$file.gz"
    gzip_size=$(stat -c%s "$file.gz")
    rm "$file.gz"

    rar a -inul "$file.rar" "$file"
    rar_size=$(stat -c%s "$file.rar")
    rm "$file.rar"

    xz -c "$file" > "$file.xz"
    xz_size=$(stat -c%s "$file.xz")
    rm "$file.xz"

    echo "$file,$orig_size,$gzip_size,$rar_size,$xz_size" >> compression_results.csv
  done
done
