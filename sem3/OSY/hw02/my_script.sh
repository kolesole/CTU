#!/usr/bin/env bash

#function that writes out help when given an arg -h or wrong arg
print_help() {
    echo -e "This script works only with arguments:\n\
\n\
use -h for help;\n\
use -a to find all pdf files in a directory;\n\
use -b to find all lines that start with a number;\n\
use -c to find the longest sentences;\n\
use -d <prefix> to replace all file names in all #include derictives so that <prefix> is added to the beginning."
}

#reading an arg
getopts ":habcd:" opt
#execute commands depending on arg
case $opt in
h)
    print_help
    ;;
a)
    ls -a | grep -i '\.pdf$' | sort
    ;;
b)
    sed -n 's/^[+-]\?[[:digit:]]\+\(.*\)/\1/p'
    ;;
c)
    tr '\n' ' ' | grep -o '[[:upper:]][^.!?]*[.!?]'
    ;;
d)
    sed -E -e "s|#([[:space:]]*)include([[:space:]]*)\"([^\"]*)\"|#\1include\2\"${OPTARG}\3\"|g" \
           -e "s|#([[:space:]]*)include([[:space:]]*)<([^>]*)>|#\1include\2<${OPTARG}\3>|g"
    ;;      
*)
    print_help
    exit 1
    ;;
esac

exit 0
