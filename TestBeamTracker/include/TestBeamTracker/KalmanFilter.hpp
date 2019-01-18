#pragma once

#include "TestBeamTracker/Geometry.hpp"
#include "TestBeamTracker/EventReader.hpp"

#include "Acts/Utilities/Definitions.hpp"
#include "Acts/Detector/TrackingGeometry.hpp"
#include "Acts/EventData/Measurement.hpp"
#include "Acts/EventData/TrackParameters.hpp"
#include "Acts/EventData/TrackState.hpp"
#include "Acts/Extrapolator/Navigator.hpp"
#include "Acts/Extrapolator/SurfaceCollector.hpp"
#include "Acts/Fitter/GainMatrixSmoother.hpp"
#include "Acts/Fitter/GainMatrixUpdator.hpp"
#include "Acts/Fitter/KalmanFitter.hpp"
#include "Acts/MagneticField/ConstantBField.hpp"
#include "Acts/Propagator/EigenStepper.hpp"
#include "Acts/Propagator/Propagator.hpp"
#include "Acts/Propagator/StraightLineStepper.hpp"
#include "Acts/Propagator/detail/DebugOutputActor.hpp"
#include "Acts/Propagator/detail/StandardAborters.hpp"
#include "Acts/Surfaces/Surface.hpp"
#include "Acts/Utilities/BinningType.hpp"
#include "Acts/Utilities/GeometryID.hpp"
#include <boost/optional.hpp>
#include <algorithm>
#include <random>
#include <math.h>
#include <vector>

namespace TestBeamTracker {
  using namespace Acts;
  using Identifier = GeometryID;
  using Jacobian   = ActsMatrixD<5, 5>;

  template <ParID_t... params>
  using MeasuredTrackState
      = MeasuredTrackState<Identifier, BoundParameters, Jacobian, params...>;
  using VariantTrackState
      = VariantTrackState<Identifier, BoundParameters, Jacobian>;


  class KalmanFilter {
    std::unique_ptr<Geometry> m_geometry;
    std::vector<MeasuredTrackState<eLOC_0, eLOC_1>> m_cachedMeasuredTrackStates;
    bool debugMode = false;

  public:
    KalmanFilter();
    //std::vector<MeasuredTrackState<eLOC_0, eLOC_1>> measuredTrackStates(EventReader & reader);
    std::vector<VariantTrackState> measuredTrackStates(EventReader & reader);
    boost::optional<BoundParameters> run(EventReader & reader);
  };
}

