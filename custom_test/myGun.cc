#include "myGun.hh"

MyGun::MyGun() {}
MyGun::~MyGun() {}

void MyGun::Build() const
{
    MyGen* generator = new MyGen();
    SetUserAction(generator);

    MyRunAction* runAction = new MyRunAction();
    SetUserAction(runAction);
}
