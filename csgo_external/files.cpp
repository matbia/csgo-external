#include "files.hpp"
#include <windows.h>
#include <stdio.h>
#include <string>

Files* files = new Files();

void Files::OnSetup()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);

	memset(m_fileName, 0x00, 255);
	strcpy_s(m_fileName, std::string(buffer).substr(0, std::string(buffer).find_last_of("\\/") + 1).c_str());
	strcat_s(m_fileName, "settings.cfg");
}

int Files::ReadInt(char* element, char* item)
{
	return GetPrivateProfileIntA(element, item, NULL, m_fileName);
}

float Files::ReadFloat(char* element, char* item)
{
	char result[255];
	GetPrivateProfileStringA(element, item, NULL, result, 255, m_fileName);
	return atof(result);
}

bool Files::ReadBool(char* element, char* item)
{
	char result[255];
	GetPrivateProfileStringA(element, item, NULL, result, 255, m_fileName);
	return (strcmp(result, "True") == 0 || strcmp(result, "true") == 0) ? true : false;
}

void Files::WriteInt(char* element, char* item, int value)
{
	char temp[255];
	sprintf_s(temp, "%d", value);
	WritePrivateProfileStringA(element, item, temp, m_fileName);
}

void Files::WriteFloat(char* element, char* item, float value)
{
	char temp[255];
	sprintf_s(temp, "%f", value);
	WritePrivateProfileStringA(element, item, temp, m_fileName);
}

void Files::WriteBool(char* element, char* item, bool value)
{
	char temp[255];
	sprintf_s(temp, "%s", value ? "true" : "false");
	WritePrivateProfileStringA(element, item, temp, m_fileName);
}
