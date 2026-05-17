#!/bin/sh
find . \( -name "*.cpp" -o -name "*.h" \) -exec cat {} \+ | wc -l
