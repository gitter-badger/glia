#!/usr/bin/env bash

function usage()
{
    echo "usage: npm run build -- [-h] [--cmake_build_type]"
    echo ""
    echo "options arguments:"
    echo "  -h, --help              show this help message and exit"
    echo "  --cmake_build_type      valid options: Debug, Release, RelWithDebInfo, MinSizeRel"
    echo ""
}

for i in "$@"; do
    case ${i} in
        -h|--help)
            usage
            exit 0
            ;;
        --cmake_build_type)
            CMAKE_BUILD_TYPE=${2}
            shift
            ;;
        *)
            ;;
    esac
done

if [ -z "${CMAKE_BUILD_TYPE}" ]; then
    echo "this should not happen"
    CMAKE_BUILD_TYPE=Debug
fi

cmake_build_types=(Debug Release RelWithDebInfo MinSizeRel)
for i in "${cmake_build_types[@]}"; do
    if [ "${i}" == "${CMAKE_BUILD_TYPE}" ]; then
        cmake -H. -Bbuild/${CMAKE_BUILD_TYPE}/ -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        cmake --build build/${CMAKE_BUILD_TYPE}/
        exit 0
    else
        continue
    fi
done

usage
exit 1
