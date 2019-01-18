#!/bin/bash

#-------------------------------------------------------------------------------

printUsage() {
    echo "Usage: source make.sh [--clean]"
}

#-------------------------------------------------------------------------------

makeTestBeamTracker() {

    if [ -z $TESTBEAMTRACKER_DIR ]; then
        local testBeamTrackerDir="$( cd "$(dirname "${BASH_SOURCE[0]}")" && pwd )"
        echo 'Sourcing `'"${testBeamTrackerDir}/setUpEnvironment.sh"'` to set up the environment...'
        source ${testBeamTrackerDir}/setUpEnvironment.sh
    fi

    if [ "$2" != "" ]; then
        printUsage
        return 1
    fi
    if [ "$1" == "--clean" ]; then
        echo "Wiping ${TESTBEAMTRACKER_DIR}/TestBeamTracker_build, ${TESTBEAMTRACKER_DIR}/TestBeamTracker_run..."
        rm -rf ${TESTBEAMTRACKER_DIR}/TestBeamTracker_build ${TESTBEAMTRACKER_DIR}/TestBeamTracker_run
    elif [ "$1" != "" ]; then
        printUsage
        return 1
    fi

    cd $TESTBEAMTRACKER_DIR
    echo "Now working in ${TESTBEAMTRACKER_DIR}..."
    
    mkdir -p TestBeamTracker_build TestBeamTracker_run/include


    cd TestBeamTracker_build
    echo "Now working in ${TESTBEAMTRACKER_DIR}/TestBeamTracker_build..."
    
    cmake -DCMAKE_INSTALL_PREFIX="${TESTBEAMTRACKER_DIR}/TestBeamTracker_run" ${TESTBEAMTRACKER_DIR}/TestBeamTracker
    make && make install

    cp -i ${TESTBEAMTRACKER_DIR}/TestBeamTracker/settings.json ${TESTBEAMTRACKER_DIR}/TestBeamTracker_run/

    echo "Setup complete."
    
    cd ${TESTBEAMTRACKER_DIR}/TestBeamTracker_run
    echo "Now working in ${TESTBEAMTRACKER_DIR}/TestBeamTracker_run..."
    echo 'You can now run executables in the `bin` directory:'
    echo "  ./bin/<EXECUTABLE> [OPTIONS]"
}

#-------------------------------------------------------------------------------

makeTestBeamTracker $@

