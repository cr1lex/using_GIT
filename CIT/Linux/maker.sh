#!/bin/sh
if [ "$1" = "build" ]; then
    mkdir -p Build && g++ "$2" -o "Build/$(basename "$2" .cpp)"
fi
if [ "$1" = "run" ]; then
    mkdir -p Build && g++ "$2" -o "Build/$(basename "$2" .cpp)" && ./"Build/$(basename "$2" .cpp)"
fi
if [ "$1" = "clean" ]; then
    rm -rf Build
fi

# -p --> создается вся цеопчка каталогов сразу, без проверки на то, есть ли уже какая-либо директория, если есть - игнорирует, не выдает ошибки
# ./"Build/$(basename "$2" .cpp)"  --> при запуске файла убираем .cpp, чтобы это было именно ИСПОЛНЯЕМЫЙ файл, а не файл .cpp файл