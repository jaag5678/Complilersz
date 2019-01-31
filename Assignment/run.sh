#!/bin/bash
flex -o Scan.c Scanner.l
gcc -o Sc Scan.c -lfl
