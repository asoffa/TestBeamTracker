#include "TestBeamTracker/EventReader.hpp"
#include "TestBeamTracker/common_includes.hpp"

#include "TROOT.h"
#include "TSystem.h"
#include "TGraph.h"

#include <cstdlib>

using namespace TestBeamTracker;

//------------------------------------------------------------------------------

void usage(string executable) {
  cout << "Usage: " << executable << " [options]" << "\n"
       << "Options:\n"
       << "  -h/--help                      print help\n"
       << "  -i/--input FILE_NAME           path to input ROOT file\n"
       << "  -n/--nEntries N_ENTRIES        number of entries from input to process\n"
       << "\n";
}

//------------------------------------------------------------------------------

int main(int argc, char ** argv) {
  string input = "";
  long   nEntries = 10;

  int iOpt = 1;
  while (iOpt < argc) {
    string sw = argv[iOpt];
    if      (sw=="-h" || sw=="--help"      ) { usage(argv[0]); return 0; }
    else if (sw=="-i" || sw=="--input"     ) { input = argv[++iOpt]; }
    else if (sw=="-n" || sw=="--nEntries"  ) { nEntries = stoi(argv[++iOpt]); }
    else {
      cout << "Unknown switch: " << sw << "\n";
      usage(argv[0]);
      return 1;
    }
    ++iOpt;
  }
  cout << "Flags:\n"
    << "------\n"
    << "  nEntries   = " << nEntries   << '\n'
    << "  input      = " << input      << '\n'
    << '\n';

  cout << "INFO  Setting up input from file `" << input << '\n';
  EventReader reader {input};

  for (int iEntry=0; iEntry<reader.getEntries(); ++iEntry) {
    // Test with only first 10 events.
    if (nEntries>-1 && iEntry>nEntries) break;

    cout << "INFO  Processing event " << iEntry << '\n';
    reader.getEntry(iEntry);
    for (size_t iPlane=0; iPlane<reader.N_PLANES; ++iPlane) {
      cout << "      Read " << reader.nHits[iPlane] << " hits in Plane " << iPlane << ":\n";
      for (int iHit=0; iHit<reader.nHits[iPlane]; ++iHit) {
        cout << "        Hit(" << reader.pixCol[iPlane][iHit] << ',' << reader.pixRow[iPlane][iHit] << ")\n";
      }
    }
  }

}

