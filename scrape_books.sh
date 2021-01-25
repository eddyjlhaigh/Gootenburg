#!/bin/bash

for i in {1..100000}
do
    wget -N https://www.gutenberg.org/files/$i/$i-0.txt -P ./Books/
done

for filename in ./Books/*.txt;
do
    TITLE="$(grep Title: "$filename" | sed 's/^.*: //')"
    mv $filename ./Books/"${TITLE%%[[:cntrl:]]}"
done
    