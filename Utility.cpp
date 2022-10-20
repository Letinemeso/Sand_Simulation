#include "Utility.h"

unsigned int Utility::get_int_from_char_array(unsigned char* _arr, unsigned int _length)
{
	unsigned int result = 0;
	unsigned char* result_as_char = (unsigned char*)(&result);

	for(unsigned int i=0; i<_length; ++i)
		result_as_char[i] = _arr[i];

	return result;
}

void Utility::set_char_array_from_int(unsigned char* _arr, unsigned int _value, unsigned int _length)
{
	unsigned char* value_as_char = (unsigned char*)(&_value);

	for(unsigned int i=0; i<_length; ++i)
		_arr[i] = value_as_char[i];
}
