#include "TestBeamTracker/Geometry.hpp"
#include "TestBeamTracker/common_includes.hpp"
#include <vector>
#include <memory>
#include "Acts/Material/Material.hpp"
#include "Acts/Tools/CuboidVolumeBuilder.hpp"
#include "Acts/Utilities/Definitions.hpp"
#include "Acts/Utilities/Units.hpp"

namespace TestBeamTracker {
using namespace Acts; // TODO: remove this & replace w/ `Acts::` qualifier
//------------------------------------------------------------------------------

std::vector<uint> Geometry::planeNumbers = { 6, 5, 4, 0, 3, 2, 1 }; 

std::vector<Acts::Vector3D> Geometry::planePos = {
  //{0.0000000000000000, 0.0000000000000000, 0.0000000000000000},
  //{0.66139840704955066, -1.7351962693193332, 100.50613379500690},
  //{-1.2782066076189480, 0.76577027338912718, 200.53340996208263},
  //{0.32012103785691259, -0.24600216250640017, 499.51825382438506},
  //{-1.0298738572108768, -0.29759448154141843, 651.86442031662079},
  //{0.96974371713907281, -1.2780269284105472, 748.14576064120047},
  //{-1.3868291665321006, 0.20013615629889792, 848.98847384979979},
  {848.98847384979979, -1.3868291665321006, 0.20013615629889792},
  {748.14576064120047, 0.96974371713907281, -1.2780269284105472},
  {651.86442031662079, -1.0298738572108768, -0.29759448154141843},
  {499.51825382438506, 0.32012103785691259, -0.24600216250640017},
  {200.53340996208263, -1.2782066076189480, 0.76577027338912718},
  {100.50613379500690, 0.66139840704955066, -1.7351962693193332},
  {0.0000000000000000, 0.0000000000000000, 0.0000000000000000},
};

std::vector<Acts::Vector3D> Geometry::planeDirU = {
  //{-1.0000000000000000, 2.6417838165512304e-12, 9.8592714263513941e-12},
  //{-0.014594158865488273, -0.99971382129056308, -0.018954842326679312},
  //{-0.99883754613423636, 0.044258095684670352, 0.019099146549096474},
  //{-0.99967570796398852, -0.024918495533133696, 0.0052485700017738642},
  //{0.99983084061803329, 0.0094149790477556471, 0.015800263243608871},
  //{0.030921470011736410, -0.99931081706333602, 0.020536640244228473},
  //{0.99989515225182291, -0.0074019273977785384, 0.012445721116195322},
  {0.012445721116195322, 0.99989515225182291, -0.0074019273977785384},
  {0.020536640244228473, 0.030921470011736410, -0.99931081706333602},
  {0.015800263243608871, 0.99983084061803329, 0.0094149790477556471},
  {0.0052485700017738642, -0.99967570796398852, -0.024918495533133696},
  {0.019099146549096474, -0.99883754613423636, 0.044258095684670352},
  {-0.018954842326679312, -0.014594158865488273, -0.99971382129056308},
  {9.8592714263513941e-12, -1.0000000000000000, 2.6417838165512304e-12},
};

std::vector<Acts::Vector3D> Geometry::planeDirV = {
  //{-0.0000000000000000, -0.96592582629148982, 0.25881904509348330},
  //{0.96651315459258824, -0.018961712110865305, 0.25591556317134800},
  //{-0.037755059984084696, -0.96464095276580997, 0.26084935823702654},
  //{0.024902796146584329, -0.99968526842850680, -0.0030355940285342648},
  //{0.013380808571165624, -0.96173460377195563, -0.27365581643659892},
  //{-0.97213574009291415, -0.034844571243611462, -0.23181449197332557},
  //{-0.0038861759015310720, -0.96512093110108732, -0.26177564055395347},
  {-0.26177564055395347, -0.0038861759015310720, -0.96512093110108732},
  {-0.23181449197332557, -0.97213574009291415, -0.034844571243611462},
  {-0.27365581643659892, 0.013380808571165624, -0.96173460377195563},
  {-0.0030355940285342648, 0.024902796146584329, -0.99968526842850680},
  {0.26084935823702654, -0.037755059984084696, -0.96464095276580997},
  {0.25591556317134800, 0.96651315459258824, -0.018961712110865305},
  {0.25881904509348330, -0.0000000000000000, -0.96592582629148982},
};

//------------------------------------------------------------------------------

Geometry::Geometry() {

  CuboidVolumeBuilder cvb;

  std::vector<CuboidVolumeBuilder::SurfaceConfig> surfaceConfigs;
  for (uint iPlane=0; iPlane<nPlanes; ++iPlane) {
    // Position of the surfaces
    CuboidVolumeBuilder::SurfaceConfig cfg;
    cfg.position = planePos[iPlane];

    // Rotation of the surfaces
    // TODO: Fix rotation issue -- currently getting `LayerArrayCreator` error
    //       indicating overlapping surfaces, which should not be the case.
    double   rotationAngle = M_PI * 0.5;
    Vector3D xPos(cos(rotationAngle), 0., sin(rotationAngle));
    Vector3D yPos(0., 1., 0.);
    Vector3D zPos(-sin(rotationAngle), 0., cos(rotationAngle));
    RotationMatrix3D xzRot;
    xzRot.col(0) = xPos;
    xzRot.col(1) = yPos;
    xzRot.col(2) = zPos;
    RotationMatrix3D uvRot;
    Acts::Vector3D  uHat = planeDirU[iPlane];
    Acts::Vector3D  vHat = planeDirV[iPlane];
    uvRot.col(0) = uHat.cross(vHat);
    uvRot.col(1) = uHat;
    uvRot.col(2) = vHat;
    //cfg.rotation = xzRot; //TODO: Change this to `uvRot * xzRot` after debugging.
    cfg.rotation = uvRot * xzRot;
    //cfg.rotation.col(0) = uHat;
    //cfg.rotation.col(1) = vHat;
    //cfg.rotation.col(2) = uHat.cross(vHat);

    // Boundaries of the surfaces
    cfg.rBounds = std::make_shared<const RectangleBounds>(
        RectangleBounds {0.5*width(), 0.5*height()} );

    // Material of the surfaces
    // TODO: Update these material properties (currently using default values)
    MaterialProperties matProp(
        352.8, 407., 9.012, 4., 1.848e-3, 0.5 * units::_mm);
    cfg.surMat = std::shared_ptr<const SurfaceMaterial>(
        new HomogeneousSurfaceMaterial(matProp));

    // Thickness of the detector element
    cfg.thickness = 1. * units::_um;
    surfaceConfigs.push_back(cfg);
  }

  std::vector<CuboidVolumeBuilder::LayerConfig> layerConfigs;
  for (auto& sCfg : surfaceConfigs) {
    CuboidVolumeBuilder::LayerConfig cfg;
    cfg.surfaceCfg = sCfg;
    layerConfigs.push_back(cfg);
  }

  CuboidVolumeBuilder::VolumeConfig volumeConfig;
  volumeConfig.position = trackerCenter;
  volumeConfig.length   = trackerDimensions;
  volumeConfig.layerCfg = layerConfigs;
  volumeConfig.name     = "Test beam telescope";

  CuboidVolumeBuilder::Config config;
  config.position  = trackerCenter;
  config.length    = trackerDimensions;
  config.volumeCfg = {volumeConfig};

  cvb.setConfig(config);
  TrackingGeometryBuilder::Config tgbCfg;
  tgbCfg.trackingVolumeBuilders.push_back(
      std::make_shared<const CuboidVolumeBuilder>(cvb));
  TrackingGeometryBuilder tgb(tgbCfg);

  detector = std::move(tgb.trackingGeometry());

}

//------------------------------------------------------------------------------

bool Geometry::isValid() {
  if (planeNumbers.size() != nPlanes) return false;
  if (planePos.size()     != nPlanes) return false;
  if (planeDirU.size()    != nPlanes) return false;
  if (planeDirV.size()    != nPlanes) return false;
  return true;
}

//------------------------------------------------------------------------------

Acts::Vector2D Geometry::localPos(int pixelColumn, int pixelRow) {
  return {
    columnPitch * (pixelColumn - 0.5*(nColumns-1)),
    rowPitch * (pixelRow - 0.5*(nRows-1))
  };
}

//------------------------------------------------------------------------------

std::map<uint, std::shared_ptr<const Acts::Surface>> Geometry::surfaces() {
  if (_surfMap.size() > 0) return _surfMap;
  detector->visitSurfaces(surfaceVisitor);
  return _surfMap;
}

//------------------------------------------------------------------------------
// Private utility methods
// (must be static to be callable by `Acts::TrackingGeometry::visitSurfaces`)

uint Geometry::planeNumber(const Acts::Surface & surf) {

  // Allow wiggle room from center position due to rotation.
  double eps = 30.0 * Acts::units::_mm;

  Acts::Vector3D center = surf.center();

  for (uint i=0; i<planePos.size(); ++i) {
    if (fabs(planePos[i].x() - center.x()) < eps) return planeNumbers[i];
  }

  return -1;

}

std::map<uint, std::shared_ptr<const Acts::Surface>> Geometry::_surfMap;

void Geometry::surfaceVisitor(const Acts::Surface * surf) {
  if (!surf) {
    throw runtime_error {"Null surface encountered. This should never happen.\n"};
  }

  _surfMap[planeNumber(*surf)] = surf->getSharedPtr();
}

//------------------------------------------------------------------------------
}
