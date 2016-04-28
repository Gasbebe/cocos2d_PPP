#include "Monster.h"

Monster::Monster(double hp, double maxhp, double def) {
	bool bOk = initWithTexture(nullptr, Rect::ZERO);
	if (bOk) {
		this->autorelease();
	}
	//this->setTexture("Player/33.png");
}