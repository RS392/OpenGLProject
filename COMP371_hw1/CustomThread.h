#pragma once
#include <thread>
#include "Scene.h"
class CustomThread : public thread
{
public:
	bool done;
	CustomThread();
	~CustomThread();
};

