#pragma once
class MenuHandler
{
public:
	virtual void handleMenu() = 0;
	virtual int displayMenu() const = 0;
};