#include "SDHCALMaterials.h"

#include <G4NistManager.hh>


void buildSDHCALMaterials()
{
	G4NistManager* man = G4NistManager::Instance() ;

//	G4Material* Air = man->FindOrBuildMaterial("G4_AIR") ;
//	G4Material* Vacuum = man->FindOrBuildMaterial("G4_Galactic") ;

	G4Material* Fer = man->FindOrBuildMaterial("G4_Fe") ;
	G4Material* Cr = man->FindOrBuildMaterial("G4_Cr") ;
	G4Material* Ni = man->FindOrBuildMaterial("G4_Ni") ;
	G4Material* Mo = man->FindOrBuildMaterial("G4_Mo") ;
	G4Material* Mn = man->FindOrBuildMaterial("G4_Mn") ;

	G4double steeldensity = 7.85*CLHEP::g/CLHEP::cm3 ;
	G4double fractionMassFe = 0.70611 ;
	G4double fractionMassCr = 0.18784 ;
	G4double fractionMassNi = 0.10605 ;
	G4Material* Steel = new G4Material("SDHCAL_Steel" , steeldensity , 3) ;
	Steel->AddMaterial(Fer,fractionMassFe) ;
	Steel->AddMaterial(Cr,fractionMassCr) ;
	Steel->AddMaterial(Ni,fractionMassNi) ;

	//316L stainless steel
	G4double steelDensity = 8.00*CLHEP::g/CLHEP::cm3 ;
	G4double fractionFe316L = 0.665 ;
	G4double fractionCr316L = 0.170 ;
	G4double fractionNi316L = 0.120 ;
	G4double fractionMo316L = 0.025 ;
	G4double fractionMn316L = 0.020 ;
	G4Material* Steel316L = new G4Material("SDHCAL_Steel316L", steelDensity, 5) ;
	Steel316L->AddMaterial(Fer,fractionFe316L) ;
	Steel316L->AddMaterial(Cr,fractionCr316L) ;
	Steel316L->AddMaterial(Ni,fractionNi316L) ;
	Steel316L->AddMaterial(Mo,fractionMo316L) ;
	Steel316L->AddMaterial(Mn,fractionMn316L) ;

	//304L stainless steel
	G4double fractionFe304L = 0.695 ;
	G4double fractionCr304L = 0.185 ;
	G4double fractionNi304L = 0.100 ;
	G4double fractionMn304L = 0.020 ;
	G4Material* Steel304L = new G4Material("SDHCAL_Steel304L", steelDensity, 4) ;
	Steel304L->AddMaterial(Fer,fractionFe304L) ;
	Steel304L->AddMaterial(Cr,fractionCr304L) ;
	Steel304L->AddMaterial(Ni,fractionNi304L) ;
	Steel304L->AddMaterial(Mn,fractionMn304L) ;

//	G4Material* glass = man->FindOrBuildMaterial("G4_Pyrex_Glass") ;
//	G4Material* mylar = man->FindOrBuildMaterial("G4_MYLAR") ;
//	G4Material* graphite = man->FindOrBuildMaterial("G4_GRAPHITE") ;

	//Definition du g10
	double a=1.01*CLHEP::g/CLHEP::mole ;
	G4Element *elH = new G4Element("Hydrogen","H",1,a) ;

	a=12.01*CLHEP::g/CLHEP::mole ;
	G4Element *elC = new G4Element("Carbon","C",6,a) ;

	a=16.00*CLHEP::g/CLHEP::mole ;
	G4Element *elO = new G4Element("Oxygen","O",8,a) ;

	a=32.06*CLHEP::g/CLHEP::mole ;
	G4Element *elS = new G4Element("Sulfur","S",16,a) ;

	a=19.00*CLHEP::g/CLHEP::mole ;
	G4Element *elF = new G4Element("Fluor","F",9,a) ;

	G4double epoxydensity = 1.3*CLHEP::g/CLHEP::cm3 ;
	G4Material* epoxy=new G4Material("SDHCAL_epoxy",epoxydensity,3) ;
	epoxy->AddElement(elC,15) ;
	epoxy->AddElement(elO,7) ;
	epoxy->AddElement(elH,44) ;

	G4Material* Si02 = man->FindOrBuildMaterial("G4_SILICON_DIOXIDE") ;
	G4Material* Cl = man->FindOrBuildMaterial("G4_Cl") ;

	G4double g10density = 1.7*CLHEP::g/CLHEP::cm3;
	G4Material* g10 = new G4Material("SDHCAL_g10", g10density, 3) ;
	g10->AddMaterial(epoxy,14.7*CLHEP::perCent) ;
	g10->AddMaterial(Cl,8*CLHEP::perCent) ;
	g10->AddMaterial(Si02,77.3*CLHEP::perCent) ;

	//Definition du gaz
	//Le SF6:
	G4double  SF6density = 6.27e-3*CLHEP::g/CLHEP::cm3 ;
	G4Material* SF6 = new G4Material("SF6",SF6density,2) ;
	SF6->AddElement(elS,1) ;
	SF6->AddElement(elF,6) ;

	//Isobutane:
	G4double  Isobutanedensity = 2.51e-3*CLHEP::g/CLHEP::cm3 ;
	G4Material* Isobutane = new G4Material("Isobutane",Isobutanedensity,2) ;
	Isobutane->AddElement(elC,4) ;
	Isobutane->AddElement(elH,10) ;
	//CO2
	G4double  CO2density = 1.799e-3*CLHEP::g/CLHEP::cm3 ;
	G4Material* CO2 = new G4Material("CO2",CO2density,2) ;
	CO2->AddElement(elC,1) ;
	CO2->AddElement(elO,2) ;

	//TFE:
	G4double  TFEdensity = 4.25e-3*CLHEP::g/CLHEP::cm3 ;
	G4Material* TFE = new G4Material("SDHCAL_TFE",TFEdensity,3) ;
	TFE->AddElement(elC,2) ;
	TFE->AddElement(elH,2) ;
	TFE->AddElement(elF,4) ;

	//RPCGaz
	G4double  RPCGazdensity = 4.13e-3*CLHEP::g/CLHEP::cm3 ;
	G4Material* RPCGaz = new G4Material("SDHCAL_RPCGaz",RPCGazdensity,3) ;
	RPCGaz->AddMaterial(TFE,93*CLHEP::perCent) ;
	RPCGaz->AddMaterial(Isobutane,5*CLHEP::perCent) ;
	RPCGaz->AddMaterial(SF6,2*CLHEP::perCent) ;
}
