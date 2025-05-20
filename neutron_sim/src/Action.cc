#include "Action.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization(){}

ActionInitialization::~ActionInitialization(){}

void ActionInitialization::Build() const
{
  auto generator = new PrimaryGenerator();
  SetUserAction(generator);

  auto runAction = new RunAction();
  SetUserAction(runAction);

  auto eventAction = new EventAction(runAction);
  SetUserAction(eventAction);

  SetUserAction(new SteppingAction(eventAction));
}

void ActionInitialization::BuildForMaster() const
{
  auto runAction = new RunAction();
  SetUserAction(runAction);
}



