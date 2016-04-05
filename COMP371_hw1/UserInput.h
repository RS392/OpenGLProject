#pragma once
class UserInput
{
private:
	double multiplier;
	string numChoice;
	string forestChoice;
	//int terrain;
	bool submitObject = false;
	bool submitForest = false;

public:
	UserInput();
	~UserInput();
	double getMultiplier();
	void titleScreen();
	//void terrainType();
	void header();
	//void executeOrder();
};

