#!/bin/bash

make

ARG=$(cat input)

./push_swap $ARG
