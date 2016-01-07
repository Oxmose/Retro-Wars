#ifndef DEF_TOOLS_H
#define DEF_TOOLS_H

// STD LIBS
#include <vector>
#include <string>
#include <ctype.h>

// OTHER INCLUDES FROM PROJECT
#include "../NetEngine/Structures.h"

namespace nsTools
{
    // Splits messages in packages of 256 bits each
    inline std::vector<nsNetEngine::NetPackage> splitMessages(const nsNetEngine::NetPackage &p_package)
    {
        std::vector<nsNetEngine::NetPackage> resultMsg;
        unsigned int stringSize = p_package.message.size();
        
        unsigned int i = 0;
        unsigned int end = 0;

        // Proceed to cut the message
        while(i < stringSize)
        {
            if (252 * (i + 1) > stringSize)
                end = stringSize;
            else
                end = 252 * (i + 1);

            nsNetEngine::NetPackage np;
            np.message = p_package.message.substr(252 * i, end);        
            resultMsg.push_back(np);

            i += 252;
        }
        
        // Return the vector of messages
        return resultMsg;
    } // inline splitMessages()

    // Split strings according to a delimiter
    inline std::vector<std::string> splitString(const std::string &p_string, const std::string &p_delimiter)
    {
        std::vector<std::string> result;        
        size_t pos = 0;
        std::string s = p_string;

        // Cut the string at each occurence of the delimiter
        while ((pos = s.find(p_delimiter)) != std::string::npos)
        {
            result.push_back(s.substr(0, pos));
            s.erase(0, pos + p_delimiter.length());
        }

        result.push_back(s);
    
        // Return the vector containing the splited string
        return result;
    } // inline splitString()

    // Clean a net message
    inline std::string cleanMessage(const std::string &p_message)
    {
        // Message should be size/msg[|||], removethe size/
        std::vector<std::string> splited = splitString(p_message, "/");

        return splited[1].substr(0, stoi(splited[0]));
    } // inline cleanMessage()

    // Tell if p_str is a number
    inline bool isNumber(const std::string &p_str)
    {
        for(unsigned int i = 0; i < p_str.size(); ++i)
        {
            if(!isdigit(p_str[i]))
                return false;
        }
        return true;
    } // inline isNumber()

    // Validate IP address
    inline bool validateIP(const std::string &p_ip)
    {
        std::vector<std::string> splited = splitString(p_ip, ".");

        if(splited.size() != 4)
            return false;
        for(std::string ip_pack : splited)
        {
            if(!isNumber(ip_pack) || stoi(ip_pack) < 0 || stoi(ip_pack) > 255)
                return false;
        }

        return true;
    } // inline validateIP()

    
} // nsTools

#endif // DEF_TOOLS_H
