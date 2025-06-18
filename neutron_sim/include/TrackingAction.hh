#ifndef TRACKINGACTION_HH
#define TRACKINGACTION_HH
#include "G4UserTrackingAction.hh"
#include "EventAction.hh"

class TrackingAction : public G4UserTrackingAction
{
public:
    TrackingAction(EventAction *eventAction);
    virtual ~TrackingAction();
    virtual void PreUserTrackingAction(const G4Track *track) override;
    virtual void PostUserTrackingAction(const G4Track *track) override;
    int trackCount_ = 0;

private:
    EventAction *eventAction_ = nullptr;
};

#endif