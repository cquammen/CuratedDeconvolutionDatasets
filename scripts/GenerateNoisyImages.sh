#!/bin/bash

# Add Gaussian noise
for STDEV in 0.02 0.04 0.06 0.08 0.10 0.12 0.14
do
    ./AddNoise --input "$1" --output "$1-Noise-${STDEV}.nrrd" --noise Gaussian --stdev "${STDEV}"
done