#include "Button.h"

Button::Button() {

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(Button::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Button::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	bool bOk = initWithTexture(nullptr, Rect::ZERO);
	if (bOk) {
		this->autorelease();
	}

}

bool Button::onTouchBegan(Touch* touch, Event* event) {

	auto touchPoint = touch->getLocation();
	bool bTouch = this->getBoundingBox().containsPoint(touchPoint);

	if (bTouch) {
		this->setOpacity(100.0f);
		log("button press sprite");
	}

	return true;
}

void Button::onTouchEnded(Touch* touch, Event* event) {

	this->setOpacity(200.0f);
	log("button exit");
	atkCommnad->ViewCommand(1);

}
void Button::setCommand(Command* command) {
	atkCommnad = command;
}

