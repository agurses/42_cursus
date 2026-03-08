#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

#include <cstdint>
#include <iostream>
#include "Data.hpp"

class Serializer{
	private:
		Serializer();
		Serializer(const Serializer &str);
		Serializer& operator=(const Serializer &str);
		~Serializer();
	public:

		static uintptr_t serialize(Data* ptr);
		static Data* deserialize(uintptr_t str);
};

#endif