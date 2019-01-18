#include "TestBeamTracker/common_includes.hpp"
#include "TestBeamTracker/KalmanFilter.hpp"
#include "TestBeamTracker/Geometry.hpp"


namespace TestBeamTracker {
//------------------------------------------------------------------------------

std::normal_distribution<double> gauss(0., 1.);
std::default_random_engine       generator(42);

/////
///// @brief Simplified material interaction effect by pure gaussian deflection
/////
//struct MaterialScattering
//{
//  /// @brief Constructor
//  MaterialScattering() = default;

//  /// @brief Main action list call operator for the scattering on material
//  ///
//  /// @todo deal momentum in a gaussian way properly
//  ///
//  /// @tparam propagator_state_t State of the propagator
//  /// @param [in] state State of the propagation
//  template <typename propagator_state_t>
//  void
//  operator()(propagator_state_t& state) const
//  {
//    // Check if there is a surface with material and a covariance is existing
//    if (state.navigation.currentSurface
//        && state.navigation.currentSurface->associatedMaterial()
//        && state.stepping.cov != ActsSymMatrixD<5>::Zero()) {
//      // Sample angles
//      std::normal_distribution<double> scatterAngle(
//          0., 0.017);  //< \approx 1 degree
//      double dPhi = scatterAngle(generator), dTheta = scatterAngle(generator);

//      // Update the covariance
//      state.stepping.cov(ePHI, ePHI) += dPhi * dPhi;
//      state.stepping.cov(eTHETA, eTHETA) += dTheta * dTheta;

//      // Update the angles
//      double theta = std::acos(state.stepping.direction().z());
//      double phi   = std::atan2(state.stepping.direction().y(),
//                              state.stepping.direction().x());

//      state.stepping.update(
//          state.stepping.position(),
//          {std::sin(theta + dTheta) * std::cos(phi + dPhi),
//           std::sin(theta + dTheta) * std::sin(phi + dPhi),
//           std::cos(theta + dTheta)},
//          std::max(state.stepping.p
//                       - std::abs(gauss(generator)) * units::_MeV,
//                   0.));
//    }
//  }
//};

KalmanFilter::KalmanFilter()
  : m_geometry {make_unique<Geometry>()}
{
}

//------------------------------------------------------------------------------

//std::vector<MeasuredTrackState<eLOC_0, eLOC_1>> KalmanFilter::measuredTrackStates(EventReader & reader) {
std::vector<VariantTrackState> KalmanFilter::measuredTrackStates(EventReader & reader) {

  //std::vector<MeasuredTrackState<eLOC_0, eLOC_1>> measurements;
  std::vector<VariantTrackState> measurements;

  for (uint iPlane=0; iPlane<EventReader::N_PLANES; ++iPlane) {
    for (uint iHit=0; iHit<reader.nHits[iPlane]; ++iHit) {
      double sU = m_geometry->columnPitch;
      double sV = m_geometry->rowPitch;
      ActsSymMatrixD<2> cov2D;
      cov2D << sU*sU, 0., 0., sV*sV;
      Acts::Vector2D localPos = m_geometry->localPos(
          reader.pixCol[iPlane][iHit], reader.pixRow[iPlane][iHit]);

      if (m_geometry->surfaces().count(iPlane) < 1) {
        throw std::runtime_error {"TestBeamTracker::KalmanFilter::measuredTrackStates: no surface found for plane "+std::to_string(iPlane)};
      }
      std::shared_ptr<const Acts::Surface> surface = m_geometry->surfaces()[iPlane];
      auto geoID = surface->geoID();

      Measurement<Identifier, eLOC_0, eLOC_1> meas {
          surface,
          geoID,
          cov2D,
          localPos.x(),
          localPos.y()
      };

      measurements.push_back(MeasuredTrackState<eLOC_0, eLOC_1>(std::move(meas)));
    }
  }

  return measurements;

}

//------------------------------------------------------------------------------

boost::optional<BoundParameters> KalmanFilter::run(EventReader & reader) {
  //std::vector<MeasuredTrackState<eLOC_0, eLOC_1>> measurements = measuredTrackStates(reader);
  std::vector<VariantTrackState> measurements = measuredTrackStates(reader);

  // The KalmanFitter - we use the eigen stepper for covariance transport
  // Build navigator for the measurement creatoin
  Navigator rNavigator {m_geometry->detector};
  rNavigator.resolvePassive   = false;
  rNavigator.resolveMaterial  = true;
  rNavigator.resolveSensitive = true;

  // Configure propagation with deactivated B-field
  ConstantBField bField(Vector3D(0., 0., 0.));
  using RecoStepper = EigenStepper<ConstantBField>;
  RecoStepper rStepper(bField);
  using RecoPropagator = Propagator<RecoStepper, Navigator>;
  RecoPropagator rPropagator(rStepper, rNavigator);

  // Set initial parameters for the particle track
  ActsSymMatrixD<5> cov;
  cov << 1000. * units::_um, 0., 0., 0., 0., 0., 1000. * units::_um, 0., 0.,
      0., 0., 0., 0.05, 0., 0., 0., 0., 0., 0.05, 0., 0., 0., 0., 0., 0.01;

  auto covPtr = std::make_unique<const ActsSymMatrixD<5>>(cov);

  Vector3D rPos(-3. * units::_m,
                10. * units::_um * gauss(generator),
                100. * units::_um * gauss(generator));
  Vector3D rMom(1. * units::_GeV,
                0.025 * units::_GeV * gauss(generator),
                0.025 * units::_GeV * gauss(generator));

  SingleCurvilinearTrackParameters<ChargedPolicy> rStart(
      std::move(covPtr), rPos, rMom, 1.);

  const Surface* rSurface = &rStart.referenceSurface();

  using Updator      = GainMatrixUpdator<BoundParameters, Jacobian>;
  using Smoother     = GainMatrixSmoother<BoundParameters, Jacobian>;
  using KalmanFitter = KalmanFitter<RecoPropagator, Updator, Smoother>;

  KalmanFitter kFitter(rPropagator);

  // Fit the track
  auto fittedTrack      = kFitter.fit(measurements, rStart, rSurface);
  auto fittedParameters = fittedTrack.fittedParameters.get();
  //auto params = fittedParameters.parameters();
  return fittedParameters;
}

//------------------------------------------------------------------------------
}
