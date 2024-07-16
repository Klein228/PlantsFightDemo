#pragma once
class Player
{
public:
	enum playerType
	{
		sunflower,
		peashooter
	};
	Player(){}
	~Player(){}
	virtual void on_updata(int delta){}
	virtual void on_draw(){}
private:
	
};
