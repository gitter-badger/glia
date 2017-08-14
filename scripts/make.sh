#!/usr/bin/env bash

CMAKE_BUILD_TYPE=

args=`cat << EOF | python3.6 - ${@}
import argparse
import os

parser = argparse.ArgumentParser(
    add_help=False,
    formatter_class=argparse.RawTextHelpFormatter
)
parser.add_argument('-h', '--help', action="help")
parser.add_argument(
    '--cmake_build_type',
    metavar='',
    default='Debug',
    choices=['Debug','Release', 'RelWithDebInfo', 'MinSizeRel'],
    help='choose the compilation build type. [Debug]'
)
args = parser.parse_args()

print('CMAKE_BUILD_TYPE="%s";' % args.cmake_build_type)
EOF
`
eval ${args}

cmake -H. -Bbuild/${CMAKE_BUILD_TYPE}/ -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}