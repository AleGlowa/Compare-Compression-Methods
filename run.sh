#!/usr/bin/env bash
# it can only be executed, do not allow to source
# and crash in a controlled way if some unbound variable is used

[[ $- == *i* ]] && echo "Shell Interactive" || echo "Shell Not interactive"
if [[ $0 != "$BASH_SOURCE" ]]; then
    echo "ERROR: I'm a script forcing you to execute. Don't source me!" >&2
    return 1
else
    # if I am OK to execute, force that the script stops if variables are not defined
    # this catches bugs in the code when you think a variable has value, but it is empty
    set -eu
fi

#############################################################################################
### Configuration
#############################################################################################

DEBUG="0"
VERBOSE="0"

DO_CMAKE_AND_MAKE="1"
DO_ONLY_MAKE="0"
DO_EXIT_AFTER_COMPILATION="0"

DO_RUN="1"
SAVE_PLOTS="1"
INSTALL_MATPLOTLIB="1"

#############################################################################################
### Compilation
#############################################################################################

# cmake + make
if [[ ${DO_CMAKE_AND_MAKE} == "1" ]]; then
    COMMAND="cd code && cd build && rm -rf * && cmake ../source && make && cd .. && cd .."
    echo "COMMAND=${COMMAND}"
    eval ${COMMAND}    
fi

# only make
if [[ ${DO_ONLY_MAKE} == "1" ]]; then
    COMMAND="make -C code/build"
    echo "COMMAND=${COMMAND}"
    eval ${COMMAND}
fi

# exit, safer to be on while we are compiling for the first time, to move to running only once we expect compilation to work
if [[ ${DO_EXIT_AFTER_COMPILATION} == "1" ]]; then
    COMMAND="exit"
    echo "COMMAND=${COMMAND}"
    eval ${COMMAND}
fi

#############################################################################################
### Running
#############################################################################################

if [[ ${DO_RUN} == "0" ]]; then
    exit 0
fi

# if here, you also want to run

# FORMAT: x_uncompressed, y_uncompressed, z_uncompressed, r_uncompressed, x_decompressed,
# y_decompressed, z_decompressed, r_decompressed, distance, r_difference (10 columns)
comp_symbols=( "A" "B" "C" )
for symbol in "${comp_symbols[@]}"; do
    COMMAND="./code/build/orderPoints Car_XYZI_decompressed_ASCII_${symbol}.ply > ./output/${symbol}ordered.txt"
    echo "COMMAND=${COMMAND}"
    eval ${COMMAND}
done

# print metrics for every compress method
for symbol in "${comp_symbols[@]}"; do
    COMMAND="./code/build/metrics < ./output/${symbol}ordered.txt > ./output/${symbol}metrics.txt"
    echo "COMMAND=${COMMAND}"
    eval ${COMMAND}
    
    COMMAND="cat ./output/${symbol}metrics.txt"
    echo "COMMAND=${COMMAND}"
    eval ${COMMAND}
done
echo

COMMAND="echo 1.B, 2.A, 3.C > ./output/methodsRanking.txt"
echo "COMMAND=${COMMAND}"
eval ${COMMAND}


if [[ ${SAVE_PLOTS} == "1" ]]; then
    # make sure if matplotlib is installed
    if [[ ${INSTALL_MATPLOTLIB} == "1" ]]; then
        COMMAND="pip3 install -r ./code/source/requirements.txt"
        echo
        echo "COMMAND=${COMMAND}"
        eval ${COMMAND}
    fi

    # save plots
    COMMAND="python3 ./code/source/create_plots.py"
    echo "COMMAND=${COMMAND}"
    eval ${COMMAND}
    echo "Plots have been saved"
    echo
fi

#############################################################################################
### Done
#############################################################################################

echo "Done ./run.sh!"
