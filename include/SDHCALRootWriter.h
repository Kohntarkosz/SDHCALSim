#ifndef SDHCALRootWriter_h
#define SDHCALRootWriter_h

#include <TFile.h>
#include <TTree.h>

#include <G4ThreeVector.hh>
#include <globals.hh>

#include <vector>

class SDHCALRootWriter
{
		//singleton stuff
		static SDHCALRootWriter* instance ;
	protected :
		SDHCALRootWriter() ;
		void static initInstance() { new SDHCALRootWriter ; }
		~SDHCALRootWriter() { instance = NULL ; }
	public :
		static SDHCALRootWriter* Instance()
		{
			if ( !instance )
				initInstance() ;
			return instance ;
		}

		static void deleteInstance()
		{
			if ( !instance )
			{
				std::cout << "WARNING in SDHCALRootWriter::deleteInstance() : No instance of SDHCALRootWriter -> do nothing" << std::endl ;
				return ;
			}
			delete instance ;
		}


	public :
		void createRootFile( std::string fileName ) ;
		void closeRootFile() ;

		void fillTree() ;

		inline void setEventNumber(int value) { eventNumber = value ; }
		inline void setNHit(int value) { nHit = value ; }
		inline void setNOldHit(int value) { nOldHit = value ; }
		inline void setPrimaryEnergy(double value) { primaryEnergy = value ; }
		void setPrimaryPos(G4ThreeVector value) { primaryPos[0] = value.x() ; primaryPos[1] = value.y() ; primaryPos[2] = value.z() ; }
		void setPrimaryMom(G4ThreeVector value) { primaryMom[0] = value.x() ; primaryMom[1] = value.y() ; primaryMom[2] = value.z() ; }
		inline void setDepositedEnergy(double value) { depositedEnergy = value ; }
		inline void setLeakedEnergy(double value) { leakedEnergy = value ; }
		inline void setEmFraction(double value) { emFraction = value ; }
		inline void setComputingTime(double value) { computingTime = value ; }
		inline void setStepCosAngle(std::vector<double> value) { stepCosAngle = value ; }
		inline void setStepLength(std::vector<double> value) { stepLength = value ; }
		inline void setStepTime(std::vector<double> value) { stepTime = value ; }


	protected :
		TFile* file ;
		TTree* tree ;

		int eventNumber ;
		int nHit ;
		int nOldHit ;
		double primaryEnergy ;
		double primaryPos[3] ;
		double primaryMom[3] ;
		double depositedEnergy ;
		double leakedEnergy ;
		double emFraction ;
		double computingTime ;

		std::vector<double> stepCosAngle ;
		std::vector<double> stepLength ;
		std::vector<double> stepTime ;


} ;


#endif //SDHCALRootWriter_h
