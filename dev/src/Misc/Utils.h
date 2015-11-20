#ifndef DEF_UTILS_H
#define DEF_UTILS_H

#include <vector>
#include "../NetEngine/Structures.h"

using namespace nsNetEngine;

namespace nsUtils
{
	std::vector<NetPackage> splitMessage(const NetPackage &p_package)
	{
		std::vector<NetPackage> resultMsg;
		unsigned int stringSize = p_package.message.size();

		unsigned int i = 0;
		unsigned int end = 0;
		while (i < stringSize)
		{
			if ((256 * (i + 1)) > stringSize)
				end = stringSize;
			else
				end = 256 * (i + 1);
			NetPackage np;
			np.message = p_package.message.substr(256 * i, end);

			resultMsg.push_back(np);
			i += 256;
		}

		return resultMsg;
	}
}

#endif
