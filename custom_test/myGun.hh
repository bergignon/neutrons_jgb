#ifndef MYGUN_HH
#define MYGUN_HH

#include "G4VUserActionInitialization.hh"
#include "myGen.hh"
#include "run.hh"

class MyGun : public G4VUserActionInitialization
{
public:
    MyGun();
    ~MyGun();

    virtual void Build() const;

};
#endif // MYGUN_HH
