#!/bin/bash

export TOP_DIR=$(cd $(dirname ${BASH_SOURCE[0]}); pwd)
export COMMON_DIR=$TOP_DIR/common
echo "Set COMMON_DIR to $COMMON_DIR"
export PATH=$PATH:$COMMON_DIR/bin
export LD_LIBRARY_PATH=$COMMON_DIR/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$COMMON_DIR/lib/python3/dist-packages:$PYTHONPATH
source $TOP_DIR/rosws/devel/setup.sh
alias pccmake='cmake .. -DCMAKE_INSTALL_PREFIX=$COMMON_DIR'
