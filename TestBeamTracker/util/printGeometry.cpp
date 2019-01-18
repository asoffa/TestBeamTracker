#include "TestBeamTracker/Geometry.hpp"
#include "TestBeamTracker/common_includes.hpp"
#include "Acts/Surfaces/Surface.hpp"

#include <cstdlib>

using namespace TestBeamTracker;

//------------------------------------------------------------------------------

void usage(const string & executable) {
  cout << "Usage: " << executable << " [options]" << "\n"
       << "Options:\n"
       << "  -h/--help                      print help\n"
       << "  -i/--input FILE_NAME           path to input ROOT file\n"
       << "  -n/--nEntries N_ENTRIES        number of entries from input to process\n"
       << "\n";
}

//------------------------------------------------------------------------------

/// 
/// Function specifying what to do at each surface of detector.
/// Note: The detector consists of:
///         * Tracking volume
///         * Layers
///         * Surfaces
/// 
void surfaceVisitor(const Acts::Surface * surf) {
  if (!surf) {
    cout << "        Surface is null!\n";
    return;
  }

  Acts::Vector3D center = surf->center();
  Acts::Vector3D normal = surf->normal();
  cout << "        Surface(center=(" << center.x() << ','
                                     << center.y() << ','
                                     << center.z() << "),\n"
       << "                normal=(" << normal.x() << ','
                                     << normal.y() << ','
                                     << normal.z() << "))\n";
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

  cout << "INFO  Printing geometry info for UniGE test beam setup.\n";

  Geometry geo;
  cout << "INFO  Surfaces populated:\n";
  for (const auto & it : geo.surfaces()) {
    cout << "        " << it.first << " => ";
    if (!it.second) {
      cout << "null!\n";
    } else {
      Acts::Vector3D center = it.second->center();
      Acts::Vector3D normal = it.second->normal();
      cout << "center = (" <<center.x() << ',' << center.y() << ',' << center.z() << ")\n";
      cout << "            normal = " << "(" << normal.x() << ',' << normal.y() << ',' << normal.z() << ")\n";
    }
  }

}

