#include "stdafx.h"
#include "RandomAttributeGenerator.h"

RandomAttributeGenerator::RandomAttributeGenerator()
{
	srand(time(NULL));
	generatedOnce = false;
}


RandomAttributeGenerator::~RandomAttributeGenerator()
{
}
void RandomAttributeGenerator::setRadius(int rad) {
	radius = rad;
}
void RandomAttributeGenerator::setPlayerPos(vec3 pos) {
	playerPos = pos;
}
void RandomAttributeGenerator::setOldPlayerPos(vec3 pos) {
	oldPlayerPos = pos;
}
unsigned int RandomAttributeGenerator::generateRandomInt(unsigned long a, unsigned long b, unsigned long c) {
	
		a = a - b;  a = a - c;  a = a ^ (c >> 13);
		b = b - c;  b = b - a;  b = b ^ (a << 8);
		c = c - a;  c = c - b;  c = c ^ (b >> 13);
		a = a - b;  a = a - c;  a = a ^ (c >> 12);
		b = b - c;  b = b - a;  b = b ^ (a << 16);
		c = c - a;  c = c - b;  c = c ^ (b >> 5);
		a = a - b;  a = a - c;  a = a ^ (c >> 3);
		b = b - c;  b = b - a;  b = b ^ (a << 10);
		c = c - a;  c = c - b;  c = c ^ (b >> 15);
		return c;

}
void RandomAttributeGenerator::randomizeObject(Object original, objects &copies) {

	//srand(generateRandomInt(clock(), time(NULL), GetCurrentProcessId()));
	int min, max, nbOfCopies;
	distanceTraveled = playerPos - oldPlayerPos;
	//cout << distanceTraveled[2] << endl;
	// double multiplier = 5;

	if (original.type.find("tree") != string::npos) {
		float mult = title->getMultiplier();
		if ( mult == 1.2) {
			mult = 1.1;
		}
		min = 600 * mult;
		max = 800 * mult;
	}
	else if (original.type.find("pinet") != string::npos) {
		float mult = title->getMultiplier();
		if (mult == 1.2) {
			mult = 1.1;
		}
		min = 1200 * mult;
		max = 1600 * mult;
	}
	else if (original.type.find("fern") != string::npos) {
		min = 400 * title->getMultiplier();
		max = 500 * title->getMultiplier();
	}
	else if (original.type.find("flow") != string::npos) {
		min = 1000 * title->getMultiplier();
		max = 2000 * title->getMultiplier();
	}
	else if (original.type.find("shr") != string::npos) {
		min = 300 * title->getMultiplier();
		max = 400 * title->getMultiplier();
	}
	else if (original.type.find("weed") != string::npos) {
		min = 250 * title->getMultiplier();
		max = 400 * title->getMultiplier();
	}
	else if (original.type.find("grass") != string::npos){

		min = 13000 * title->getMultiplier();
		max = 17500 * title->getMultiplier();
	}
	
//	min /= 3;
//    max /= 3;
	maxDist = playerPos.z + radius;
	nbOfCopies = rand() % (max-min) + min;
	cout << "Creating " << nbOfCopies << " " << original.type << endl;

	for (int i = 0; i < nbOfCopies; ++i) {
		Object obj = original;
		//thread t(&RandomAttributeGenerator::alterObj, this, ref(obj), ref(copies));
		//t.detach();
		alterObj(obj, copies);
		//changeObjectLocation(obj);
		//if (type != 'g')
		//	changeObjectSize(obj);
		if (i == nbOfCopies / 4)
			cout << "25%...";
		else if (i == nbOfCopies / 2)
			cout << "50%...";
		else if (i == nbOfCopies - nbOfCopies / 4)
			cout << "75%...";
	//	cout << obj.verts[2][2] << endl;
		
		//copies.push_back(obj);
	}
	cout << "Done."<< endl;

}
void RandomAttributeGenerator::alterObj(Object &obj, objects &copies) {
//	cout << "trying to do one object" << endl;
	m.lock();
//	cout << "doing one object" << endl;
	
	//cout << obj.verts[2][2] << endl;
	
	//cout << obj.verts[2][2] << endl;
	changeObjectSize(obj);
	changeObjectLocation(obj);
	changeObjectAttributes(obj);
	Object* pObj = new Object(obj);
	copies.push_back(pObj);
	m.unlock();
}
void RandomAttributeGenerator::changeObjectAttributes(Object& obj) {
	//if (obj.type == "pinet2") {
		double x = (-5 + obj.xTranslation);
		double y = 0;
		double z = (-5 + obj.zTranslation);

		obj.position = vec3(x, y, z);
		
		double xx = (20);
		double yy = 185;
		double zz = (20);
		obj.boundingBox = vec3(xx, yy, zz);
	//}
}
void RandomAttributeGenerator::changeObjectLocation(Object &obj) {

	if (generatedOnce == false) {
		int xTranslation = (rand() % (radius * 2) - radius) + playerPos.x;
		int zTranslation = (rand() % (radius * 2)) + playerPos.z;
		obj.xTranslation = xTranslation;
		obj.zTranslation = zTranslation;
		
		for (int i = 0; i < obj.verts.size(); i++) {
			obj.verts[i][0] += (float)xTranslation;
			obj.verts[i][2] += (float)zTranslation;
		}
		/*
		for (int i = 0; i < obj.vertSize; ++i) {
			if (i == )
			obj.vxuvs[i] = (double)xTranslation;


		}*/
	}
	else {
		
		int xTranslation = 0;
		
		xTranslation = (rand() % (radius * 2) - radius) + playerPos.x;
		int zTranslation = 0;
		if (forward.z < 0)
			zTranslation = -(rand() % (radius)) + playerPos.z - radius + distanceTraveled.z;
		else
			zTranslation = (rand() % (radius)) + playerPos.z  + distanceTraveled.z;
		obj.xTranslation = xTranslation;
		obj.zTranslation = obj.zTranslation;
		for (int i = 0; i < obj.verts.size(); i++) {
			obj.verts[i][0] += (float)xTranslation;
			obj.verts[i][2] += (float)zTranslation;
		}
	}
}
void RandomAttributeGenerator::changeObjectSize(Object &obj) {
	
	//	int xScale = (rand() % 5 + 1) / 10 + 1;
//		int yScale = (rand() % 10 + 1) / 10 + 1;
	//	int zScale = (rand() % 5 + 1) / 10 + 1;

	float yScale = 1;
	float xScale = 1;
	float zScale = 1;
		 if (obj.type.find("grass") != string::npos)
			yScale = 1.8;
		 else if (obj.type.find("tree") != string::npos) {
			 yScale = 0.3;
			 xScale = 0.5;
			 zScale = 0.5;
		 }
		 else if (obj.type.find("flow") != string::npos) {
			 yScale = 8;
			 xScale = 8;
			 zScale = 8;
		 }
		 else if (obj.type.find("weed4") != string::npos || obj.type.find("weed1") != string::npos || obj.type.find("shr9") != string::npos) {
			 yScale = 8;
			 xScale = 8;
			 zScale = 8;
		 }
		 else if (obj.type.find("shr") != string::npos || obj.type.find("weed") != string::npos) {
			 yScale = 3;
			 xScale = 3;
			 zScale = 3;
		 }
		
		else {
			yScale = 1;
			xScale = 1;
			zScale = 1;
		}
		obj.xScale = xScale;
		obj.yScale = yScale;
		obj.zScale = zScale;
		for (int i = 0; i < obj.verts.size(); i++) {
			obj.verts[i][0] /= (float)xScale;
			obj.verts[i][1] /= (float)yScale;
			obj.verts[i][2] /= (float)zScale;
		}
}

void RandomAttributeGenerator::setTitle(UserInput* t) {
	title = t;
}