#include "TestBeamTracker/EventReader.hpp"
#include "TestBeamTracker/common_includes.hpp"
#include "TTree.h"

namespace TestBeamTracker {
//------------------------------------------------------------------------------

EventReader::EventReader(const string & fileName)
  : inputFile {fileName.c_str()}
{
  cout << "INFO  Fetching trees from `" << fileName << '\n';
  for (int iPlane=0; iPlane<N_PLANES; ++iPlane) {
    string treeName = "Plane"+to_string(iPlane)+"/Hits";
    trees[iPlane] = (TTree*) inputFile.Get(treeName.c_str());
    if (!trees[iPlane]) {
      throw std::runtime_error {"Unable to read tree `"+treeName+"` from file `"+inputFile.GetName()+"`"};
    }
    trees[iPlane]->SetBranchAddress("NHits", &nHits[iPlane]);
    trees[iPlane]->SetBranchAddress("PixX", &pixCol[iPlane][0]);
    trees[iPlane]->SetBranchAddress("PixY", &pixRow[iPlane][0]);
    cout << "INFO  Loaded tree `" << treeName << "` from "
         << inputFile.GetName() << " with " << trees[iPlane]->GetEntries() << " entries.\n";
  }
}

//------------------------------------------------------------------------------

ulong EventReader::getEntries() {
  ulong nEntries  = trees[0]->GetEntries();
  for (TTree * tree : trees) {
    if (tree->GetEntries() != nEntries) {
      throw runtime_error {"All input trees must have the same number of entries."};
    }
  }
  return nEntries;
}

//------------------------------------------------------------------------------

void EventReader::getEntry(ulong iEntry) {
  for (TTree * tree : trees) {
    tree->GetEntry(iEntry);
  }
}

//------------------------------------------------------------------------------
}

