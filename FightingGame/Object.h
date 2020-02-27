#pragma once
#include "Core.h"

class Master;

/*
some sort of master class for Actor. I'm not really sure what else would
inherit from this asides from Actor, but i felt this should be here.
*/
class Object
{
public:
	static Master* master;
};

