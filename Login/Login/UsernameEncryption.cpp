#include "UsernameEncryption.h"
#include <iostream>

void UsernameEncryption::setUsernameChar(short index, char nChar)
{
	_username[index] = nChar;
}

void UsernameEncryption::encryption01()
{
	int secret[5] = { 123, 33, 234, 143, 183};
	int c = 0;

	for (size_t i = 0; i < strlen(_username); i++)
	{
		_password[i] =  (secret[c] ^ (int)_username[i]) % 10;
		secret[c] = _username[i];
		c < 4 ? c++ : c = 0;
	}
}