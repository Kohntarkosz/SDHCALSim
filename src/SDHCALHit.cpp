#include "SDHCALHit.h"

#include <G4Step.hh>
#include <G4TouchableHistory.hh>

#include "SDHCALRPC.h"

SDHCALHit::SDHCALHit()
{
}

SDHCALHit::SDHCALHit(const G4Step* step , SDHCALRPC* _rpc)
{
	rpc = _rpc ;
	if ( !rpc->isTransformComputed() )
		rpc->setCoordTransform( step->GetPreStepPoint()->GetTouchable()->GetHistory()->GetTopTransform() ) ;

	beginPos = step->GetPreStepPoint()->GetPosition() ;
	endPos = step->GetPostStepPoint()->GetPosition() ;
	deltaPos = endPos - beginPos ;
	trackID = step->GetTrack()->GetTrackID() ;
	pdgID = step->GetTrack()->GetDynamicParticle()->GetPDGcode() ;
	energyDeposited = step->GetTotalEnergyDeposit() ;

	RPCID = rpc->getID() ;
	isEnteringStep = (step->GetPreStepPoint()->GetStepStatus() == fGeomBoundary) ;
	isLeavingStep = (step->GetPostStepPoint()->GetStepStatus() == fGeomBoundary) ;
	time = step->GetPreStepPoint()->GetGlobalTime() ;
	trueLength = deltaPos.mag() ;
	charge = step->GetTrack()->GetDynamicParticle()->GetCharge() ;
	trackStatus = step->GetTrack()->GetTrackStatus() ;

	//I , J and coordInPad are computed when hit is finalized
}

void SDHCALHit::computePosition()
{
	G4ThreeVector globalPosition = 0.5*( endPos + beginPos ) ;
	G4ThreeVector posInRPC = rpc->globalToRpcCoordTransform(globalPosition) ;

	I = rpc->localCoordToIJ(posInRPC).at(0) ;
	J = rpc->localCoordToIJ(posInRPC).at(1) ;
	coordInPad = posInRPC - rpc->IJToLocalCoord(I,J) ;
}

void SDHCALHit::updateWith(const G4Step* step)
{
	endPos = step->GetPostStepPoint()->GetPosition() ;
	deltaPos = endPos - beginPos ;
	energyDeposited += step->GetTotalEnergyDeposit() ;
	isLeavingStep = (step->GetPostStepPoint()->GetStepStatus() == fGeomBoundary) ;
	trueLength += step->GetDeltaPosition().mag() ;

	if( trackStatus < step->GetTrack()->GetTrackStatus() )
		trackStatus = step->GetTrack()->GetTrackStatus() ;
}

void SDHCALHit::finalize()
{
	computePosition() ;
}

void SDHCALHit::Print()
{
	std::cout << "Hit at " << "I:" << I << " J:" << J << " K:" << RPCID << " at pos " << endPos-beginPos << std::endl ;
}




OldSDHCALHit::OldSDHCALHit(const G4Step* step , SDHCALRPC* _rpc)
	: SDHCALHit()
{
	energyDeposited = step->GetTotalEnergyDeposit() ;
	beginPos = step->GetPreStepPoint()->GetPosition() ;
	endPos = step->GetPostStepPoint()->GetPosition() ;
	deltaPos = step->GetDeltaPosition() ;

	rpc = _rpc ;
	RPCID = rpc->getID() ;

	if ( !rpc->isTransformComputed() )
		rpc->setCoordTransform( step->GetPreStepPoint()->GetTouchable()->GetHistory()->GetTopTransform() ) ;

	isEnteringStep = (step->GetPreStepPoint()->GetStepStatus() == fGeomBoundary) ;
	isLeavingStep = (step->GetPostStepPoint()->GetStepStatus() == fGeomBoundary) ;
	pdgID = step->GetTrack()->GetDynamicParticle()->GetPDGcode() ;
	time = step->GetPostStepPoint()->GetGlobalTime() ;
	momentum = step->GetTrack()->GetMomentum() ;
	trackID = step->GetTrack()->GetTrackID() ;
	parentID = step->GetTrack()->GetParentID() ;
	trackStatus = step->GetTrack()->GetTrackStatus() ;
	trueLength = (endPos - beginPos).mag() ;
	charge = static_cast<int>( step->GetTrack()->GetDynamicParticle()->GetCharge() ) ;
	trackVertexVolumeName = step->GetTrack()->GetLogicalVolumeAtVertex()->GetName() ;

	computePosition() ;
}

bool OldSDHCALHit::shouldBeLinkedTo(OldSDHCALHit* hit) const
{
	if ( trackID == hit->trackID && rpc == hit->rpc )
		return true ;
	else
		return false ;
}

void OldSDHCALHit::updateWith(OldSDHCALHit* hit)
{
	energyDeposited += hit->energyDeposited ;
	if( beginPos.z() > hit->beginPos.z() )
		beginPos = hit->beginPos ;
	if( endPos.z() < hit->endPos.z() )
		endPos = hit->endPos ;

	deltaPos = endPos - beginPos ;
	trueLength += hit->trueLength ;
	if( trackStatus < hit->trackStatus )
		trackStatus = hit->trackStatus ;

	computePosition() ;
}
