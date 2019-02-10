#!/usr/bin/env bash

cd $1

printf "cppEH:\n"
./cppEH

printf "\n---------------------\n"
printf "dynlinking:\n"
./dynlinking

printf "\n---------------------\n"
printf "fptr:\n"
./fptr

printf "\n---------------------\n"
printf "impExpData:\n"
./impExpData

printf "\n---------------------\n"
printf "indirect-tailcall:\n"
./indirect-tailcall

printf "\n---------------------\n"
printf "jit:\n"
./jit

printf "\n---------------------\n"
printf "linux-callback:\n"
./linux-callback

printf "\n---------------------\n"
printf "linux-hw-except:\n"
./linux-hw-except

printf "\n---------------------\n"
printf "linux-PLTcall:\n"
./linux-PLTcall

printf "\n---------------------\n"
printf "ret:\n"
./ret

printf "\n---------------------\n"
printf "switch:\n"
./switch

printf "\n---------------------\n"
printf "vtablecall:\n"
./vtablecall
echo


