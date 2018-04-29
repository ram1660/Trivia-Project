#pragma once
#include "Buffer.h"
class SerializerHelper
{
public:
	static Buffer removeHashtagsFromRequest(Buffer b);
	static int getRequestCode(Buffer b);

};

