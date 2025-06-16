#include "Action.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "TrackingAction.hh"

ActionInitialization::ActionInitialization() {}

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::Build() const
{
  auto generator = new PrimaryGenerator();
  SetUserAction(generator);

  auto runAction = new RunAction();
  SetUserAction(runAction);

  auto eventAction = new EventAction(runAction);
  SetUserAction(eventAction);

  SetUserAction(new SteppingAction(eventAction));
  SetUserAction(new TrackingAction());
}

void ActionInitialization::BuildForMaster() const
{
  auto runAction = new RunAction();
  SetUserAction(runAction);
}
