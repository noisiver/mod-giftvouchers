#!/usr/bin/env bash
MOD_GIFTVOUCHERS_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )/" && pwd )"

source $MOD_GIFTVOUCHERS_ROOT"/conf/conf.sh.dist"

if [ -f $MOD_GIFTVOUCHERS_ROOT"/conf/conf.sh" ]; then
    source $MOD_GIFTVOUCHERS_ROOT"/conf/conf.sh"
fi
