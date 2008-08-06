// Includes
#include "StringUtil.h"
using namespace NVE;

// Static member variables
const string StringUtil::emptyString("");
//char StringUtil::m_buffer[];


/******************
* Other functions *
******************/

void StringUtil::toLowerCase(string &text)
{
	for(string::iterator it = text.begin(); it != text.end(); ++it)
		*it = tolower(*it);
}

string StringUtil::getLowerCase(const string &text)
{
	string result = text;
	toLowerCase(result);
	return result;
}

void StringUtil::toUpperCase(string &text)
{
	for(string::iterator it = text.begin(); it != text.end(); ++it)
		*it = toupper(*it);
}

string StringUtil::getUpperCase(const string &text)
{
	string result = text;
	toUpperCase(result);
	return result;
}

bool StringUtil::startsWith(const string &text, const string &start)
{
	// A string always starts with an empty string
	if(start.empty()) return true;

	unsigned int textLength = text.length();
	unsigned int startLength = start.length();

	// Can't compare if text is shorter than start
	if(startLength == 0 || textLength < startLength) return false;

	return (text.compare(0, startLength, start) == 0);
}

bool StringUtil::endsWith(const string &text, const string &end)
{
	unsigned int textLength = text.length();
	unsigned int endLength = end.length();

	// Can't compare if text is shorter than end
	if(endLength == 0 || textLength < endLength) return false;

	return (text.compare(textLength - endLength, endLength, end) == 0);
}

bool StringUtil::contains(const string &text, const string &part, bool caseSensitive)
{
	size_t pos;
	if(caseSensitive)
		pos = text.find(part);
	else
		pos = getLowerCase(text).find(getLowerCase(part));

	return (pos != string::npos);
}

/*!
	Trims (leading and trailing) white spaces from the given text.
*/
void StringUtil::trim(string &text)
{
	static const string delims = " \t\r";
	text.erase(text.find_last_not_of(delims) + 1); // trim right
	text.erase(0, text.find_first_not_of(delims)); // trim left
}

/*!
	Returns the trimmed version of the given text.
	\so trim
*/
string StringUtil::trimmed(const string &text)
{
	string result = text;
	trim(result);
	return result;
}

/*!
	cut the text into different parts, delimited by delims.
*/
void StringUtil::tokenize(const string &text, StringVector &tokens, const string &delims)
{
	tokens.clear();

	// Find the starting position (cut all starting delimiters)
	size_t startPos = text.find_first_not_of(delims);

	// Find the ending position
	size_t endPos = text.find_first_of(delims, startPos);

	// Find the tokens
	while(startPos != string::npos || endPos != string::npos)
	{
		tokens.push_back(text.substr(startPos, endPos - startPos));
		startPos = text.find_first_not_of(delims, endPos);
		endPos = text.find_first_of(delims, startPos);
	}
}

/*! Get the first word of a string (the part until the first space) */
string StringUtil::getFirstWord(const string &text, const string &delims)
{
	size_t pos = text.find_first_of(delims);
	return pos == string::npos ? text : text.substr(0, pos);
}

/*!
	Returns the extension of a file name (the part after the last dot),
	in lower case.
*/
string StringUtil::getFileExtension(const string &filename)
{
	// Find the last dot
	size_t dotpos = filename.rfind(".");

	// Get the part of the filename after the dot
	string ext = filename.substr(dotpos + 1);

	// Convert to lowercase
	toLowerCase(ext);

	return ext;
}

/*!
	Cuts the file extension off a file name.
*/
void StringUtil::cutFileExtension(string &filename)
{
	// Find the last dot
	size_t dotpos = filename.rfind(".");

	// Cut the file extension (the part of the filename after the dot)
	if(dotpos != string::npos)
		filename.erase(dotpos);
}

/*!
	Convert all backslashes ('\') in a filename to normal slashes ('/').
*/
void StringUtil::convertSlashes(string &filename)
{
	for(string::iterator it = filename.begin(); it != filename.end(); ++it)
		if(*it == '\\') *it = '/';
}

/*!
	Returns the path of a file name (the part before the last slash, <b>including</b> the slash).

	@note
		The input string can contain normal and back slashes,
		but the output will only contain normal slashes.
*/
string StringUtil::getFilePath(const string &filename)
{
	// Convert backslashes to normal slashes
	string newname = filename;
	convertSlashes(newname);

	// Find the last slash
	size_t slashpos = newname.rfind("/");

	// Check if a path is present
	if(slashpos == string::npos)
		return "./";

	// Get the part of the filename before the slash, including the slash
	return newname.substr(0, slashpos + 1);
}

/*!
	Returns the name of a file (without the proceeding file path).
*/
string StringUtil::getFileName(const string &filename)
{
	// Convert backslashes to normal slashes
	string newname = filename;
	convertSlashes(newname);

	// Find the last slash
	size_t slashpos = newname.rfind("/");

	// Check if a path is present
	if(slashpos == string::npos)
		return newname;

	// Cut the file path (leave everything after the last slash)
	return newname.substr(slashpos + 1, newname.length() - slashpos);
}

/*! Cleans a file path (converts all slashes to normal slashes, removes unneeded parts) */
void StringUtil::cleanPath(string &path)
{
	// Convert all slashes to normal ones
	convertSlashes(path);

	// Check if the path ends with a slash
	if(!endsWith(path, "/"))
		path += "/";

	// Remove all occurencies of "./"
	size_t pos = 0;
	do
	{
		pos = path.find("./", pos);
		
		unsigned char testing = 0;
		if(pos != string::npos && pos != 0)
			testing = path.at(pos - 1);

		if(pos != string::npos && (pos == 0 || path.at(pos - 1) != '.'))
			path.erase(pos, 2);
		else if(pos != string::npos)
			++pos;
	} while(pos != string::npos);

	//! @todo Clean ../ parts (if ../ is found, remove the dir in front of it. Special cases? ...)
	//! @todo On pocket pc, if the path starts with ./, insert the current path
}

float StringUtil::toFloat(const string &value)
{
	return (float) atof(value.c_str());
}

bool StringUtil::toBool(const string &value)
{
	string newValue = getLowerCase(value);

	if(newValue == "true" || newValue == "yes" || newValue == "enabled" || newValue == "1")
		return true;
	else if(newValue == "false" || newValue == "no" || newValue == "disabled" || newValue == "0")
		return false;
	else
	{
		cerr << "[StringUtil] Warning: Unknown boolean value '" << newValue;
		cerr << "'. Returning false." << endl;
		return false;
	}
}

int StringUtil::toInt(const string &value)
{
	return atoi(value.c_str());
}

unsigned int StringUtil::toUInt(const string &value)
{
	return (unsigned int) atoi(value.c_str());
}

string StringUtil::toString(bool value)
{
	return value ? "true" : "false";
}

string StringUtil::toString(float value)
{
	char buffer[256];
	sprintf(buffer, "%f", value);
	return string(buffer);
}

string StringUtil::toString(unsigned int value)
{
	char buffer[256];
	sprintf(buffer, "%d", value);
	return string(buffer);
}

string StringUtil::toString(int value)
{
	char buffer[256];
	sprintf(buffer, "%d", value);
	return string(buffer);
}

/*!
	Convert a normal string to a unicode string
*/
wstring StringUtil::toUnicode(const string &text)
{
	wchar_t wstr[BUFFLENGTH];

	for(unsigned i = 0; i < text.length(); ++i)
		wstr[i] = (wchar_t) text[i];
	wstr[text.length()] = 0;

	return wstring(wstr);
}

/*!
	Convert a unicode string to a normal string
*/
string StringUtil::fromUnicode(const wstring &text)
{
	char str[BUFFLENGTH];

	for(unsigned i = 0; i < text.length(); ++i)
		str[i] = (char) text[i];
	str[text.length()] = 0;

	return string(str);
}

void StringUtil::convertSlashes(wstring &filename)
{
	for(wstring::iterator it = filename.begin(); it != filename.end(); ++it)
		if(*it == '\\') *it = '/';
}

wstring StringUtil::getFilePath(const wstring &filename)
{
	// Convert backslashes to normal slashes
	wstring newname = filename;
	convertSlashes(newname);

	// Find the last slash
	size_t slashpos = newname.rfind(L"/");

	// Check if a path is present
	if(slashpos == wstring::npos)
		return L"./";

	// Get the part of the filename before the slash, including the slash
	return newname.substr(0, slashpos + 1);
}
