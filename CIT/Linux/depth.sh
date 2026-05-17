#!/bin/sh
find . -name "how_far_are_you.txt" | grep -o '/' | wc -l | awk '{print $1-1}'

