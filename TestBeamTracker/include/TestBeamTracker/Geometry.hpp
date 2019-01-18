#pragma once

#include "TestBeamTracker/EventReader.hpp"
#include "Acts/Utilities/Definitions.hpp"
#include "Acts/Utilities/Units.hpp"
#include "Acts/Detector/TrackingGeometry.hpp"
#include "Acts/Surfaces/Surface.hpp"
#include <memory>
#include <vector>
#include <map>

namespace Acts {
  class TrackingGeometry;
}

namespace TestBeamTracker {
  /// 
  /// Struct for holding test beam telescope geometry configuration.
  /// 
  struct Geometry {
    Acts::Vector3D  trackerDimensions = {
      //20.0 * Acts::units::_mm, 16.8 * Acts::units::_mm, 1000.0 * Acts::units::_mm
      2000.0*Acts::units::_mm, 30.0*Acts::units::_mm, 30.0*Acts::units::_mm
    };
    //Acts::Vector3D trackerCenter = {0.0, 0.0, 450.0 * Acts::units::_mm};
    //Acts::Vector3D trackerCenter = {450.0*Acts::units::_mm, 0.0, 0.0};
    Acts::Vector3D trackerCenter = {1000.0*Acts::units::_mm, 0.0, 0.0};
    uint    nPlanes       = EventReader::N_PLANES;   //! Number of tracking planes.
    uint    nColumns      = EventReader::N_COLUMNS;  //! Number of pixel columns.
    uint    nRows         = EventReader::N_ROWS;     //! Number of pixel rows.
    double  columnPitch   = 0.250 * Acts::units::_mm;  //! Column pitch.
    double  rowPitch      = 0.050 * Acts::units::_mm;  //! Row pitch.

    ///
    /// Plane index in event data read-in.
    ///
    static std::vector<uint> planeNumbers;

    /// 
    /// Global (z,x,y) coordinates of the centers of the tracking planes.
    /// 
    static std::vector<Acts::Vector3D> planePos;

    /// 
    /// Unit vector pointing in direction of increasing local coordinate u of each
    /// tracking plane in terms of global coordinates (z,x,y).
    /// 
    static std::vector<Acts::Vector3D> planeDirU;

    /// 
    /// Unit vector pointing in direction of increasing local coordinate v of each
    /// tracking plane in terms of global coordinates (z,x,y).
    /// 
    static std::vector<Acts::Vector3D> planeDirV;

    /// 
    /// Instance of ACTS tracking geometry (used when employing ACTS machinery).
    /// Instantiated upon construction.
    /// 
    std::shared_ptr<const Acts::TrackingGeometry> detector;

    /// 
    /// Default constructor. Populates `detector` with default ACTS cuboid tracking
    /// volume and detector planes as specified by `nPlanes`, `planePos`, `planeDirU`,
    /// and `planeDirV`.
    /// 
    Geometry();

    double width()  { return nColumns * columnPitch; }
    double height() { return nRows * rowPitch; }
    bool   isValid();

    Acts::Vector2D localPos(int pixelColumn, int pixelRow);
    std::map<uint, std::shared_ptr<const Acts::Surface>> surfaces();

  private:
    // These utility methods must be static to be callable by
    // `Acts::TrackingGeometry::visitSurfaces`.
    static std::map<uint, std::shared_ptr<const Acts::Surface>> _surfMap;
    static uint planeNumber(const Acts::Surface & surf);
    static void surfaceVisitor(const Acts::Surface * surf);
  };

}

