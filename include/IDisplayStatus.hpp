#pragma once



class IDisplayStatus {
public:
	virtual void display(const char *message) = 0;
};