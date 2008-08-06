#ifndef XMLPARSER_H
#define XMLPARSER_H

// Includes
#include "global.h"

#ifndef XML_STATIC
	#define XML_STATIC
#endif
#include <expat/expat.h>

#include <map>
using std::map;

// Forward declarations

// Typedefs
typedef map<string, string> AttributeMap;

/**
	This is the base class for easy event-based XML parsing.
	Derive from this class and implement the needed functions
	to parse an xml document.

	@todo
		- Provide some error checking functions
*/
class XMLPARSER_API XmlParser
{
private:
	// Member variables
	XML_Parser m_parser;
	string m_context, m_text;
	string m_lastError;

public:
	// Constructors and destructor
	XmlParser();
	virtual ~XmlParser();

	// Parse function
	bool parse(const string &filename, bool useDTD = true);
	bool parse(std::istream &stream, bool useDTD = true);
	const string &getLastError() { return m_lastError; }


	// To be overloaded

	/*!
		Implement this function if you want to do something when the parsing starts.

		@param filename The file that is going to be parsed
	*/
	virtual void startParsing(const string &filename) {}

	/*!
		Implement this function if you want to do something when the parsing has ended.

		@param filename The file that is parsed
	*/
	virtual void doneParsing(const string &filename) {}

	/*!
		Implement this function if you want information of the parsed XML header.
		It is also called with header information of any parsed DTD inside the XML document.

		@param version The version attribute of the parsed XML document (can be empty)
		@param encoding The encoding of the parsed XML document (can be empty)
		@param standalone -1 if no standalone parameter is set in the XML document. 0 if "no" is set, 1 if "yes" is set
	*/
	virtual void header(string version, string encoding, int standalone) {}

	/*!
		Implement this function if you want to be notified when a tag starts in the parsed XML document.

		@param name The name of the started tag
		@param attributes A map of the attributes of the started tag (name=>value)
	*/
	virtual void startTag(string name, AttributeMap attributes) {}

	/*!
		Implement this function if you want to be notified when a tag ends in the parsed XML document.
		This function is also called with an empty tag (<tag />).

		@param name The name of the ended tag
	*/
	virtual void endTag(string name) {}

	/*!
		Implement this function if you want to be notified when tag content is parsed in the XML document
		(text inside a tag).

		@param text The text inside a tag (<tag>text</tag>)
		@param context The name of the containing tag
	*/
	virtual void content(string text, const string &context) {}

protected:
	// Protected functions
	void stopParsing();

private:
	// Private functions
	void reset(bool useDTD);
	static bool parse(XML_Parser parser, const string &filename);
	static bool parse(XML_Parser parser, std::istream &stream);

	// The callback functions of expat. We use a pointer to a XmlParser class as user data
	static void XMLCALL declHandler(void *data, const XML_Char *version, const XML_Char *encoding, int standalone);
	static void XMLCALL startHandler(void *data, const char *el, const char **attr);
	static void XMLCALL endHandler(void *data, const char *el);
	static void XMLCALL textHandler(void *data, const XML_Char *s, int len);
	static int XMLCALL externalEntityHandler(XML_Parser p, const XML_Char *context, const XML_Char *base, const XML_Char *systemId, const XML_Char *publicId);

	// Utility functions (copied from StringUtil)
	static void trim(string &text);
	static void convertSlashes(string &filename);
	static string getFilePath(const string &filename);
	static string getFileName(const string &filename);
	static string toString(int value);
};

#endif // XMLPARSER_H
