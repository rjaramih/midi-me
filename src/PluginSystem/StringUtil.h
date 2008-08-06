#ifndef NVE_STRINGUTIL_H
#define NVE_STRINGUTIL_H

// Includes
#include "global.h"
#include <vector>

// Defines
#define BUFFLENGTH 256

namespace NVE
{
	// Typedefs
	typedef std::vector<std::string> StringVector;

	/**
		This class contains useful static functions
		to work with strings.

		@todo Make all functions work with both normal and Unicode strings
	 */
	class StringUtil
	{
	protected:
		// Member variables
		//static char m_buffer[BUFFLENGTH];

	public:
		// Public static members
		static const string emptyString;

	public:
		// Static functions
		static void toLowerCase(string &text);
		static string getLowerCase(const string &text);
		static void toUpperCase(string &text);
		static string getUpperCase(const string &text);

		static bool startsWith(const string &text, const string &start);
		static bool endsWith(const string &text, const string &end);
		static bool contains(const string &text, const string &part, bool caseSensitive = true);

		static void trim(string &text);
		static string trimmed(const string &text);

		static void tokenize(const string &text, StringVector &tokens, const string &delims = " \t\r");

		static string getFirstWord(const string &text, const string &delims = " \t\r");

		static string getFileExtension(const string &filename);
		static void cutFileExtension(string &filename);
		static void convertSlashes(string &filename);
		static string getFilePath(const string &filename);
		static string getFileName(const string &filename);
		static void cleanPath(string &path);

		// Conversion function
		static float toFloat(const string &value);
		static bool toBool(const string &value);
		static int toInt(const string &value);
		static unsigned int toUInt(const string &value);

		static string toString(bool value);
		static string toString(float value);
		static string toString(unsigned int value);
		static string toString(int value);

		// Unicode functions
		static wstring toUnicode(const string &text);
		static string fromUnicode(const wstring &text);
		static void convertSlashes(wstring &filename);
		static wstring getFilePath(const wstring &filename);
	};
}

#endif // NVE_STRINGUTIL_H
