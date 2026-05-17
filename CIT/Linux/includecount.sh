#!/bin/sh
grep -o "#include" "$1" | wc -l

# grep -c "#include" "$1"    , выводит кол-во совпадений а не сами строки

