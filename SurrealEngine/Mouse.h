#ifndef MOUSE_H_
#define MOUSE_H_

#include <d3d9.h>

class Mouse
{
public:
	Mouse(HWND*);
	virtual ~Mouse();

	virtual bool DoAcquire();
};

#endif