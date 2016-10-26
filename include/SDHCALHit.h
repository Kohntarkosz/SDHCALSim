#ifndef SDHCALHit_h
#define SDHCALHit_h

#include <G4VHit.hh>
#include <G4ThreeVector.hh>
#include <G4THitsCollection.hh>

#include "SDHCALRPC.h"

class G4Step ;

class SDHCALHit : public G4VHit
{
	public :
		SDHCALHit(const G4Step* step, SDHCALRPC* _rpc) ;
		virtual ~SDHCALHit() { ; }

		void updateWith(const G4Step* step) ;
		void finalize() ;
		virtual void computePosition() ;


		inline const G4ThreeVector getPos() const { return 0.5*(endPos + beginPos) ; }
		inline const G4ThreeVector& getBeginPos() const { return beginPos ; }
		inline const G4ThreeVector& getEndPos() const { return endPos ; }
		inline const G4ThreeVector& getDeltaPos() const { return deltaPos ; }

		inline G4int getTrackID() const { return trackID ; }
		inline G4int getPdgID() const { return pdgID ; }
		inline G4double getEnergyDeposited() const { return energyDeposited ; }
		inline SDHCALRPC* getRPC() const { return rpc ; }
		inline G4int getRPCID() const { return RPCID ; }
		inline G4int getI() const { return I ; }
		inline G4int getJ() const { return J ; }
		inline G4bool isEntering() const { return isEnteringStep ; }
		inline G4bool isLeaving() const { return isLeavingStep ; }
		inline G4double getTime() const { return time ; }
		inline G4double getTrueLength() const { return trueLength ; }
		inline G4double getCharge() const { return charge ; }
		inline const G4ThreeVector& getCoordInPad() const { return coordInPad ; }
		inline G4int getTrackStatus() const { return trackStatus ; }

		virtual void Print() ;


	protected :
		SDHCALHit() ;
		G4ThreeVector beginPos ;
		G4ThreeVector endPos ;
		G4ThreeVector deltaPos ;
		G4int trackID ;
		G4int pdgID ;
		G4double energyDeposited ;
		SDHCALRPC* rpc ;
		G4int RPCID ;
		G4int I ;
		G4int J ;
		G4bool isEnteringStep ;
		G4bool isLeavingStep ;
		G4double time ;
		G4double trueLength ;
		G4double charge ;
		G4ThreeVector coordInPad ;

		G4int trackStatus ;
} ;

typedef G4THitsCollection<SDHCALHit> SDHCALHitCollection ;

class OldSDHCALHit : public SDHCALHit
{
	public :
		OldSDHCALHit(const G4Step* step, SDHCALRPC* _rpc) ;
		virtual ~OldSDHCALHit() { ; }

		G4int getParentID() const { return parentID ; }
		const G4ThreeVector& getMomentum() const { return momentum ; }
		G4String getTrackVertexVolumeName() const { return trackVertexVolumeName ; }

//		virtual void computePosition() ;
		bool shouldBeLinkedTo(OldSDHCALHit* hit) const ;
		void updateWith(OldSDHCALHit* hit) ;


	protected :

		G4String processName ;
		G4int parentID ;
		G4ThreeVector momentum ;
		G4String trackVertexVolumeName ;

} ;

typedef G4THitsCollection<OldSDHCALHit> OldSDHCALHitCollection ;

#endif //SDHCALHit_h
