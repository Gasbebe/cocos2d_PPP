#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "CustomTableViewCell.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class MainScene : public cocos2d::Layer, 
				  public cocos2d::extension::TableViewDataSource,
	              public cocos2d::extension::TableViewDelegate
{
public:
	static cocos2d::Scene* createScene();
	//~MainScene();
	virtual bool init();

	int stageNum;
	bool flag;
	cocos2d::Sprite* sprite;
	CREATE_FUNC(MainScene);
	cocos2d::Size winSize;

	void selcetStage(int num);
	void moveScene(cocos2d::Ref* pSender);
	
	virtual void scrollViewDidScroll(ScrollView* view) {};
	virtual void scrollViewDidZoom(ScrollView* view) {};
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	virtual Size tableCellSizeForIndex(TableView* table, ssize_t idx);
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView* table);

};
#endif