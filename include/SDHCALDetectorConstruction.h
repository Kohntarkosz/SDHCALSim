#ifndef SDHCALDetectorConstruction_h
#define SDHCALDetectorConstruction_h

#include <G4VUserDetectorConstruction.hh>
#include <SDHCALSteppingAction.h>



class SDHCALDetectorConstruction : public G4VUserDetectorConstruction
{
	public :
		SDHCALDetectorConstruction() ;
		~SDHCALDetectorConstruction() ;

		G4VPhysicalVolume* Construct() ;

		static G4double sizeX ;
		static G4double sizeZ ;

	protected :



} ;


#endif //SDHCALDetectorConstruction_h
