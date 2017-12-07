#ifndef TERRAIN_H_
#define TERRAIN_H_

class Terrain
{
public:
	Terrain();
	~Terrain();
	bool LoadBMP(char* argFileName);
private:
	//BYTE* heightData;
};

#endif // !TERRAIN_H_