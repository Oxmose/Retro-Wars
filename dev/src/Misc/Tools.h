#ifndef DEF_TOOLS_H
#define DEF_TOOLS_H

#include <vector>
#include <string>

#include <iostream>

#include "../NetEngine/Structures.h"

namespace nsTools
{
	inline std::vector<nsNetEngine::NetPackage> splitMessages(const nsNetEngine::NetPackage &p_package)
	{
		std::vector<nsNetEngine::NetPackage> resultMsg;
		unsigned int stringSize = p_package.message.size();
		
		unsigned int i = 0;
		unsigned int end = 0;

		while (i < stringSize)
		{
			if ((252 * (i + 1) > stringSize))
				end = stringSize;
			else
				end = 252 * (i + 1);

			nsNetEngine::NetPackage np;
			np.message = p_package.message.substr(252 * i, end);
		
			resultMsg.push_back(np);
			i += 252;
		}
		
		return resultMsg;
	}

	inline std::vector<std::string> splitString(const std::string &p_string, const std::string &p_delimiter)
	{
		std::vector<std::string> result;
		
		size_t pos = 0;
		std::string s = p_string;
		while ((pos = s.find(p_delimiter)) != std::string::npos)
		{
			result.push_back(s.substr(0, pos));
			s.erase(0, pos + p_delimiter.length());
		}
		result.push_back(s);
		return result;
	}

	inline std::string cleanMessage(const std::string &p_message)
	{
		// Message should be size/msg[100]
		std::vector<std::string> splited = splitString(p_message, "/");
		std::cout << stoi(splited[0]) << " IS " << splited[1].substr(0, stoi(splited[0]));
		return splited[1].substr(0, stoi(splited[0]));
	}
}

#endif
