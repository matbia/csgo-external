#pragma once

class Files
{
public:
	/*[junk_enable 2 5 /]
	[junk_enable_declares /]
	[swap_lines]*/
	void OnSetup();
	int	ReadInt(char* element, char* item);
	float ReadFloat(char* element, char* item);
	bool ReadBool(char* element, char* item);
	void WriteInt(char* element, char* item, int value);
	void WriteFloat(char* element, char* item, float value);
	void WriteBool(char* element, char* item, bool value);
	/*[/ swap_lines]
	[junk_disable /]*/
private:
	char m_fileName[255];
};

extern Files* files;