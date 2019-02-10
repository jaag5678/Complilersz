#!/bin/bash
bison -d Parser.y
flex -o Scan.c Scanner_Update.l
gcc Scan.c Parser.tab.c tree.c pretty_print.c symbol_table.c code_gen.c -o Scan -lfl

name="${2%.*}"
ext=".c"
c_file=$name$ext
./Scan "$1" $c_file < "$2"