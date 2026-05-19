#!/bin/sh
sed "s/^PRETTY_NAME=//; s/\"//g" /etc/os-release
# выводит результат, файл не трогает


#awk -F= '/^PRETTY_NAME/ {print $2}' /etc/os-release | tr -d '"'
