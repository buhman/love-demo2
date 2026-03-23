#!/bin/sh

set -eux

rm -rf dist/
mkdir dist/
[ -f "test.so" ] && cp test.so dist/
[ -f "test.dll" ] && cp test.dll dist/
cp Suite.mp3 conf.lua main.lua dist/

( cd dist/ ; zip -r ../test.zip . )
