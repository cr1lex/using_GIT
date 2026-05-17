#!/bin/sh
find . -name "*.cpp" -exec grep -l "#include <vector>" {} \+