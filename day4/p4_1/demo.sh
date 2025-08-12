#!/bin/bash

# Demo script for Merge Sort Program
echo "=========================================="
echo "       MERGE SORT DEMONSTRATION"
echo "=========================================="

cd /workspaces/daa-lab/day4/p4_1

echo -e "\n1. Testing with Ascending Data:"
echo "1" | ./p4_1 | head -20

echo -e "\n2. Testing with Descending Data:"
echo "2" | ./p4_1 | head -20

echo -e "\n3. Testing with Random Data:"
echo "3" | ./p4_1 | head -20

echo -e "\n=========================================="
echo "All output files created successfully!"
echo "Files in directory:"
ls -la *.dat

echo -e "\n=========================================="
echo "Sample content from sorted files:"
echo -e "\nFirst 10 elements from outMergeRand.dat:"
head -1 outMergeRand.dat | tr ' ' '\n' | head -10
echo -e "\nLast 10 elements from outMergeRand.dat:"
head -1 outMergeRand.dat | tr ' ' '\n' | tail -10
