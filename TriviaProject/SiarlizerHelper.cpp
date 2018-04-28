#include "SiarlizerHelper.h"

Buffer SerializerHelper::removeHashtagsFromRequest(Buffer b)
{
	for (int i = 0; i < b.buffer.size(); i++)
	{
		if (b.buffer[i] == '#')
		{
			b.buffer.erase(b.buffer.begin + i);
		}
	}
	return b;
}

int SerializerHelper::getRequestCode(Buffer b)
{
	int code = 0;
	//b.buffer[]
}
