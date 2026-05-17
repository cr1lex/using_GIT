#!/bin/sh
find . -not -name "*.cpp" -a -not -name "*.hpp" -a -not -name "iloveonlycpp.sh" -exec rm -rf {} \+

#cd "$1"
#script_name=$(basename "$0")
#find . -type f ! \( -name "*.cpp" -o -name "*.hpp" -o -name "$script_name" \) -delete
#find . -type d -empty -delete