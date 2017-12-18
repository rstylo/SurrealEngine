#ifndef RECTOBJ_H_
#define RECTOBJ_H_

#include "Object.h"

const int VERTICESSIZE = 8;
const int INDICIESSIZE = 36;


class RectObj : public Object
{
public:
	RectObj();
	virtual ~RectObj();

	virtual bool EditObject(LPDIRECT3DDEVICE9, float, float, float, float, float, float);

private:
	ObjectVertex vertices[VERTICESSIZE];
	bool initialized = true;
};

#endif // !RECTOBJ_H_
