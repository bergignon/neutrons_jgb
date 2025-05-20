#ifndef ACTION_H
#define ACTION_H

#include "G4VUserActionInitialization.hh"

#include "Generator.hh"
#include "RunAction.hh"

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization();
    ~ActionInitialization();

    virtual void Build() const;
    virtual void BuildForMaster() const;
};

#endif
