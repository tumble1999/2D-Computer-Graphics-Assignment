#pragma once

#include <iostream>

class Util
{
public:
	Util();
	~Util();

	template<class T, class U>
	static void Log(T& source, U s) {
		std::cout << "[" << typeid(source).name() << "] " << s << std::endl;
	}
};
