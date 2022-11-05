#ifndef UTILITY_H
#define UTILITY_H

#include <stdlib.h>


namespace Utility
{

	extern inline unsigned int get_int_from_char_array(unsigned char* _arr, unsigned int _length);

	extern inline void set_char_array_from_int(unsigned char* _arr, unsigned int _value, unsigned int _length);

	extern inline unsigned int limited_rand(unsigned int _min, unsigned int _max);

}


#endif // UTILITY_H
