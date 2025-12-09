#!/usr/bin/env bash

name=$1

# Verify input
if [[ $# -eq 2 ]]; then
	lang=$2
elif [[ $# -gt 2 ]]; then
	echo Illegal amount of arguments 1>&2
	exit 1
fi

# Verify (optional) language
if [[ ($lang == "c" || $lang == "C") && $# -eq 2 ]]; then
	echo Chosen Template: C
elif [[ $lang == "rust" ]]; then
    echo Chosen Template: Rust
elif [[ $# -eq 2 ]]; then
	echo "Unknown Template: $lang" 1>&2
	exit 1
fi


# Create basic folder structure
mkdir $name
cd $name
mkdir input
mkdir src
touch input.txt example.txt
touch run-pt1.sh run-pt2.sh
chmod +x run*
mv *.txt ./input
cd src

# Copy language specific templates
if [[ $# -eq 2 && ($lang == "c" || $lang == "C") ]]; then
	cp ../../templates/main.c ./
	mv main.c $name.c
	echo "$name.c created successfully! Enjoy the puzzle :)"
	exit 0
elif [[ $# -eq 2 && $lang == "rust" ]]; then
    cargo new $name --quiet
    mv $name/* .
    rm -rf $name
    cd src
    echo "$name.rs created successfully! Enjoy the puzzle :)"
    exit 0
fi
