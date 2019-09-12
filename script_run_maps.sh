#!/usr/bin/env bash
prog=$1
dir=$2

for file in ${dir}/*
do
	echo	"Now running with ${file}"
	${prog} < ${file}
	echo "\n"
done