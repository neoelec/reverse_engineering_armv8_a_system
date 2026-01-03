#!/bin/bash

IMG=${1}
TMP=$(mktemp -u)$(echo ${IMG} | perl -pe 's/^.+(\.[^\.]+$)/$1/')

convert "${IMG}" -trim +repage ${TMP}
convert ${TMP} -bordercolor black -border 30 "${IMG}"

rm -f ${TMP}
