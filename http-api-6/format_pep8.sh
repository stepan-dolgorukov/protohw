#!/usr/bin/env bash

for pyfile in `find -iname '*.py'`; do
  echo $pyfile
  /usr/bin/autopep8 -ia $pyfile
done