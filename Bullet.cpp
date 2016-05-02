#include "Bullet.h"


Bullet::Bullet() {

	bool bOk = initWithTexture(nullptr, Rect::ZERO);
	if (bOk) {
		this->autorelease();
	}
	//this->setTexture("UI/command2.png");

	

}

