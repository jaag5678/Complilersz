#!/bin/bash
bison -d Parser.y
flex -o Scan.c Scanner_Update.l
gcc Scan.c Parser.tab.c tree.c pretty_print.c symbol_table.c -o Scan -lfl
