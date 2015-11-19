#ifndef DEF_NETEXCEPTION_H
#define DEF_NETEXCEPTION_H

#include <exception>
#include <string>
#include <sstream>

namespace nsNetEngine
{
	class NetException: public std::exception
    {
        public:
            NetException(const char* p_message, unsigned int p_line)
            {
                std::ostringstream oss;
                oss << "[" << p_line << "] " << p_message;
                this->m_message = oss.str(); 
            }
            virtual ~NetException() noexcept
            {}
            virtual const char* what() const noexcept
            { return this->m_message.c_str(); }

        private:
            std::string m_message;
    };
}

#endif
