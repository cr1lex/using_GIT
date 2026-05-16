#!/bin/sh
zip -r "$1.zip" "$1" -x@ "$1/.gitignore"