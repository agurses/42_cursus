#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <exception>

template<typename T>
class Array
{
	private:
		T* _array;
		unsigned int _size;
	public:
		Array() : _array(0), _size(0)
		{

		}

		Array(unsigned int n): _array(new T[n]()), _size(n)
		{

		}

		Array(const Array &other) : 
			_array(new T[other._size]()), _size(other._size)
		{
			unsigned int i = 0;

			while (i < other._size)
			{
				_array[i] = other._array[i];
				i++;
			}
		}

		Array& operator=(const Array &other)
		{
			if (this != &other)
			{
				T* new_array = new T[other._size]();
				for (unsigned int i = 0; i < other._size; i++)
					new_array[i] = other._array[i];
				delete[] _array;
				_array = new_array;
				_size = other._size;
			}
			return *this;
		}

		~Array()
		{
			delete[] _array;
		}

		T& operator[](unsigned int index)
		{
			if (index >= _size || index < 0)
				throw std::exception();

			return _array[index];
		}

		const T& operator[](unsigned int index) const
		{
			if (index >= _size || index < 0)
				throw std::exception();

			return _array[index];
		}

		unsigned int size() const
		{
			return _size;
		}
};

#endif