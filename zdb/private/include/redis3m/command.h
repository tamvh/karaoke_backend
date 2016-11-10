// Copyright (c) 2014 Luca Marturana. All rights reserved.
// Licensed under Apache 2.0, see LICENSE for details

#pragma once

#include <string>
#include <vector>
#include <map>

namespace redis3m
{

class command
{
public:
    inline command() {}

    inline command(std::string arg)
    {
        _args.push_back(std::move(arg));
    }

	template<typename Type>
	inline command& operator<<(const Type arg)
	{
		_args.push_back(std::to_string(arg));
		return *this;
	}
        
        template<typename T>
        command& operator<<(const std::vector<T>& arg);

        template<typename K, typename V>
        command& operator<<(const std::map<K,V>& arg);

	template<typename Type>
	inline command& operator()(const Type arg)
	{
		_args.push_back(std::to_string(arg));
		return *this;
	}

    inline operator const std::vector<std::string>& () {
        return _args;
    }

    inline std::string toDebugString() {
        std::string ret = "[redis args: ( ";
        bool first = true;
        for(std::vector<std::string>::iterator iterator = _args.begin(); iterator != _args.end(); ++iterator) {
            if(!first) ret += ", ";
            first = false;
            ret += "'" + *iterator + "'";
        }
        ret += " )]";
        return ret;
    }

private:
    std::vector<std::string> _args;
};
template<>
inline command& command::operator<<(const char* arg)
{
    _args.push_back(arg);
    return *this;
}

template<typename T>
inline command& command::operator<<(const std::vector<T>& arg)
{
    for (auto item : arg) {
        _args.push_back(item);
    }
    return *this;
}

template<typename T, typename V>
inline command& command::operator<<(const std::map<T,V>& arg)
{
    for (auto item : arg) {
        _args.push_back(item.first);
        _args.push_back(item.second);
    }
    return *this;
}

template<>
inline command& command::operator()(const char* arg)
{
    _args.push_back(arg);
    return *this;
}

template<>
inline command& command::operator<<(std::string arg)
{
    _args.push_back(std::move(arg));
    return *this;
}

template<>
inline command& command::operator()(std::string arg)
{
	_args.push_back(std::move(arg));
    return *this;
}
}
