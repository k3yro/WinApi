#ifndef USERNAMEENCRYPTION
#define USERNAMEENCRYPTION

class UsernameEncryption
{
private:
	char _username[23] = {};
	int _password[23] = {};

public:
	//UsernameEncryption();

	//set value with help of loop. 
	void setUsernameChar(short index, char nChar);

	//get value with help of loop.
	int getPassword(short n) { return _password[n]; }

	void encryption01();
};

#endif