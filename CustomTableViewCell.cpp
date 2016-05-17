#include "CustomTableViewCell.h"

USING_NS_CC;

void CustomTableViewCell::draw(Renderer *renderer,const Mat4 &tranform, uint32_t flags){
	TableViewCell::draw(renderer, tranform, flags);
}