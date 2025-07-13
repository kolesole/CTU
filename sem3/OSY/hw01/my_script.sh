#!/usr/bin/env bash

#function that writes out help when given an arg -h
print_help() {
    echo -e "This script processes the input paths,\n\
that start with the word PATH and writes:\n\
- on stdout what each path leads to a directory,\n\
file, etc. (if this path exists);\n\
- on stderr if path leads to a non-existent\n\
directory, file, etc.\n\
\n\
use -h for help;\n\
use -z for packing valid files into the output.tgz archive"
}

#flag to check if arg -z is given
flagz=false

#loop that checks all args
for arg in "$@"; do
    case $arg in
    -h)
        print_help
        exit 0;
        ;;
    -z)
        flagz=true
        ;;
    *)
        exit 2;
        ;;        
    esac
done

#array to save input
lines=()

OLD_IFS=$IFS
IFS=$'\n'

#loop for reading input
while read -r line; do
    if [ "$line" = "EOF" ]; then
        break;
    fi

    lines+=("$line")
done

IFS=$OLD_IFS

#array and loop to save all lines that start with rhw word path
paths=()
for line in "${lines[@]}"; do
    substring=${line:0:5}

    if [ "$substring" != "PATH " ]; then
        continue
    fi

    paths+=("${line#PATH }")
done

#if an argument -z is given an array is creating to write existing files
if $flagz; then
    files=()
fi   

#flag to check if some ERROR was written out
flag_error=false
#loop to process each path
for path in "${paths[@]}"; do
    if [ -L "$path" ]; then
        echo "LINK '$path' '$(readlink "$path")'"
    elif [ -f "$path" ]; then
        if [ ! -r "$path" ]; then
            exit 2
        fi

        if $flagz; then
            files+=("$path")
        fi    

        echo "FILE '$path' $(wc -l < "$path") '$(awk 'NR==1' "$path")'"
    elif [ -d "$path" ]; then
        echo "DIR '$path'"
    else
        flag_error=true
        echo "ERROR '$path'" >&2
    fi  
done

#if arg -z is given 
#checks if output.tgz exists and is writable, if no --> exit 2
#if yes or doesnt exist --> write all existing files in output.tgz   
if $flagz; then
    if [ -e output.tgz ] &&  [ ! -w output.tgz ]; then 
        exit 2
    fi

    tar czf output.tgz "${files[@]}" 
fi

#if any error was written --> exit 1
if $flag_error; then
    exit 1
fi    

exit 0
