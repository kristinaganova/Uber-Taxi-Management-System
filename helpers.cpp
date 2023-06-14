#include "helpers.h"

bool isUpper(char c)
{
	return (c >= 'A' && c <= 'Z');
}

bool isLower(char c)
{
	return (c >= 'a' && c <= 'z');
}

bool isDigit(char c)
{
	return (c >= '0' && c <= '9');
}

bool isAlphanumeric(char c)
{
	return isLower(c) || isUpper(c) || isDigit(c);
}

bool isValidUsername(const MyString& username)
{
	if (username.length() < 6 && username.length() > 30)
	{
		return false;
	}

	for (int i = 0; i < username.length(); i++)
	{
		char c = username[i];
		if (!isAlphanumeric(c))
		{
			return false;
		}
	}

	return true;
}

bool isValidPassword(const MyString& password)
{
	if (password.length() < 8 && password.length() > 30)
	{
		return false;
	}
	bool hasUppercase = false;
	for (int i = 0; i < password.length(); i++)
	{
		char c = password[i];
		if (isUpper(c))
		{
			hasUppercase = true;
			break;
		}
	}
	if (!hasUppercase)
	{
		std::cout << "The password must have at least one upper case letter!" << std::endl;
		return false;
	}
	bool hasDigit = false;
	for (int i = 0; i < password.length(); i++)
	{
		char c = password[i];
		if (isDigit(c))
		{
			hasDigit = true;
			break;
		}
	}
	if (!hasDigit)
	{
		std::cout << "The password must have at least one digit!" << std::endl;
		return false;
	}
	return true;
}

bool isValidName(const MyString& name)
{
	if (name.length() == 0)
	{
		return false;
	}

	if (!isUpper(name[0]))
	{
		return false;
	}

	for (size_t i = 1; i < name.length(); i++)
	{
		if (!isLower(name[i]))
		{
			return false;
		}
	}

	return true;
}