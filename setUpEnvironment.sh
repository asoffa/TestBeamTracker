#!/bin/bash

# Directory containing TestBeamTracker package
export TESTBEAMTRACKER_DIR="$( cd "$(dirname "${BASH_SOURCE[0]}")" && pwd )"
export LD_LIBRARY_PATH="${TESTBEAMTRACKER_DIR}/TestBeamTracker_run/lib64:$LD_LIBRARY_PATH"

# TODO: allow for more general options instead of hardcoding lxplus setup
# lxplus setup
source TestBeamTracker/external/acts-core/CI/setup_lcg94.sh


################################################################################
# Location-specific settings: set the following environment variables to the as
# indicated.
#

# NB: The version of the default `cmake` with the above lxplus setup is too low.
# Directory containing cmake executable
export PATH="$HOME/software/cmake-3.11.0-install/bin:$PATH"


## ROOT
#echo "Configuring ROOT..."
#export ROOTSYS="$HOME/software/root"
#export LD_LIBRARY_PATH="$ROOTSYS/lib:$LD_LIBRARY_PATH:$ROOTSYS"
#export PATH="$ROOTSYS/bin:$PATH"


# End of location-specific settings
################################################################################

export PATH="$TESTBEAMTRACKER_DIR/TestBeamTracker_run/bin:$PATH"

echo "Done."
