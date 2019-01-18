#!/bin/bash
echo $0
flex -o $2 $1
gcc -o $3 $2 -lfl