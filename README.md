# TestBeamTracker

Tracking package for test beam telescope geometry.


## Prerequisites

The following are required:
 * [cmake (version 3.5 or later)](https://cmake.org)
 * [Boost (version 1.62 or later](https://www.boost.org)
 * [Eigen (version 3.2.9 or later)](http://eigen.tuxfamily.org)
 * [ROOT (version 6)](https://root.cern.ch)
 * [A Common Tracking Software (ACTS)](http://acts.web.cern.ch/ACTS)

The `Boost`, `Eigen`, and `ROOT` dependencies are available by setting up the
default `lxplus` environment in `set_up_environment.sh` (see below), and the
`ACTS` dependency is installed by running the `make.sh` build script (see below).
Therefore, if working on lxplus, the only dependency that needs manual
installation is `cmake`.


## Installation

After setting the environment variables in the `set_up_environment.sh` script
to the correct locations, run
```
source make.sh  # sources `set_up_environment.sh`
```
to set up the environment and compile the `TestBeamTracker` package.

If the above completes successfully, `TestBeamTracker` should be installed and you
should be taken to the `TestBeamTracker_run` directory, where you can run
```
./bin/find_tracks -i FILENAME [other flags]  # or just `find_tracks [flags]`
```
where `FILENAME` is the name of a test beam simulation file containing the trees
`Plane0/Hits`, `Plane1/Hits`, ..., `Plane6/Hits`.

To set up the environment in a new shell, run
```
source set_up_environment.sh
```

For a list of all available options, run
```
./bin/printHits --help
```

To do a clean rebuild of `TestBeamTracker` run
```
source make.sh --clean
```
This wipes the `TestBeamTracker_build` and `TestBeamTracker_run` directories and
compiles `TestBeamTracker` and its dependencies from scratch.


## Configuration settings

Configuration options are specified in the `settings.json` file **in the `TestBeamTracker_run` directory**.

 | Feature       | Setting             | Description
 |:--------------|:--------------------|:-------------------------------------------
 |         input | fileName            | Name of test beam simulation ROOT file.
 |               |                     |
 |        output | fileName            | Name of output ROOT file.
 |               |                     |
 |         debug | chain               | Set to `true` to print diagnostic info about the input chain.
 |               |                     |
 |               | hits                | Set to `true` to print diagnostic info about the input hits.
 |               |                     |
 |               | trackFinding        | Set to `true` to print diagnostic info related to track finding.
 |               |                     |
 |               | trackFitting        | Set to `true` to print diagnostic info related to track fitting.
 |               |                     |
 |        events | eventNumberStart    | Event (entry) number to start at (-1 to start with first event)
 |               |                     |
 |               | eventNumberEnd      | Event (entry) number to end at (-1 to end with last event)
 |               |                     |
 |  trackFinding | method              | Options:
 | (in progress) |                     |   `none`   | disable track finding
 |               |                     |   `truth`  | use truth tracks
 |               |                     |   `global` | use global chi-square approach
 |               |                     |   `seed`   | use seed finder
 |               |                     |   `kalman` | use sequential Kalman filter
 |               |                     |
 |  trackFitting | method              | Options (overridden to `none` if track finding is disabled)
 | (in progress) |                     |   `none`   | disable track fitting
 |               |                     |   `global` | use global chi-square approach
 |               |                     |   `kalman` | use Kalman filter

