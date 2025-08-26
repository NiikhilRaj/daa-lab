#!/bin/bash
# Demo script for quicksort (p4_2)

echo "Running quicksort demo for Ascending Data:"
./p4_2 < <(echo 1)

echo "Running quicksort demo for Descending Data:"
./p4_2 < <(echo 2)

echo "Running quicksort demo for Random Data:"
./p4_2 < <(echo 3)
