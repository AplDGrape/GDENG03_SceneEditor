#pragma once
#include <iostream>
#include <string>

class Resource
{
public:
	Resource(const wchar_t* full_path);
	virtual ~Resource();
protected:
	std::wstring fullPath;
};