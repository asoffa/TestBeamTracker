#pragma once

#include "TFile.h"

class TTree;

namespace TestBeamTracker {

  /**
   * Class for reading in ROOT trees from UniGE test beam simulations.
   */
  class EventReader {
  public:
    static constexpr size_t N_PLANES   = 7;
    static constexpr size_t N_ROWS     = 336;
    static constexpr size_t N_COLUMNS  = 80;
    static constexpr size_t N_MAX_HITS = 50;
    TFile inputFile;
    TTree * trees [N_PLANES];

    int nHits [N_PLANES];
    int pixCol [N_PLANES][N_MAX_HITS];
    int pixRow [N_PLANES][N_MAX_HITS];

    EventReader(const std::string & fileName);
    ulong getEntries();
    void getEntry(ulong iEntry);
  };

}

