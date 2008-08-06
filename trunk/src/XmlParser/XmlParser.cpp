// Includes
#include "XmlParser.h"
#include <fstream>


/******************************
* Constructors and destructor *
******************************/

XmlParser::XmlParser()
{
	// Create the parser
	m_parser = XML_ParserCreate(NULL);
}

XmlParser::~XmlParser()
{
	// Clean up the parser
	XML_ParserFree(m_parser);
}


/******************
* Other functions *
******************/

/*!
	Parse an XML document from file. A DTD declared in the document can optionally
	be parsed to provide default values for parameters.
	This function can be used multiple times, to parse different documents.

	@param filename The filename of the XML document you want to parse (including path)
	@param useDTD Enable or disable DTD parsing
*/
bool XmlParser::parse(const string &filename, bool useDTD)
{
	// Reset the parser
	reset(useDTD);

	// Set the base path (used when processing DTDs)
	XML_SetBase(m_parser, getFilePath(filename).c_str());

	// Exexute the virtual function
	startParsing(filename);

	bool succes = parse(m_parser, filename);

	// Exexute the virtual function
	doneParsing(filename);

	return succes;
}

/** Parses an XML document from an input stream. */
bool XmlParser::parse(std::istream &stream, bool useDTD)
{
	static const string emptyString;

	// Reset the parser
	reset(useDTD);

	// Exexute the virtual function
	startParsing(emptyString);

	bool succes = parse(m_parser, stream);

	// Exexute the virtual function
	doneParsing(emptyString);

	return succes;
}


/**********************
* Protected functions *
**********************/

/*!
	Stops parsing (can be called in the implemented callback functions
	of derived parser classes).
*/
void XmlParser::stopParsing()
{
	XML_StopParser(m_parser, XML_FALSE);
}

/*!
	Resets the parser to be able to parse the next document.
	@param useDTD Enable DTD parsing or not
*/
void XmlParser::reset(bool useDTD)
{
	// No errors
	m_lastError = "";

	// No context
	m_context = "";

	// Reset the parser
	XML_ParserReset(m_parser, NULL);

	// Use a pointer to this class instance as user data
	XML_SetUserData(m_parser, this);

	// DTD parsing setting
	XML_SetParamEntityParsing(m_parser, XML_PARAM_ENTITY_PARSING_UNLESS_STANDALONE);

	// Set the parser handlers
	XML_SetXmlDeclHandler(m_parser, declHandler);
	XML_SetElementHandler(m_parser, startHandler, endHandler);
	XML_SetCharacterDataHandler(m_parser, textHandler);

	if(useDTD)
		XML_SetExternalEntityRefHandler(m_parser, externalEntityHandler);
	else
		XML_SetExternalEntityRefHandler(m_parser, NULL);
}

/*!
	@param filename The filename, including file path
*/
bool XmlParser::parse(XML_Parser parser, const string &filename)
{
	// Open the file
	std::ifstream stream(filename.c_str());
	if(!stream) return false;

	bool result = parse(parser, stream);

	// Close the file
	stream.close();
	return result;
}

/*! @param stream The opened stream to parse XML from */
bool XmlParser::parse(XML_Parser parser, std::istream &stream)
{
	// Read the stream in chunks of 1024 characters
	static const int chunkSize = 1024;

	while(!stream.eof())
	{
		// Read directly into the expat buffer
		void *pBuffer = XML_GetBuffer(parser, chunkSize);
		if(!pBuffer)
			return false;

		stream.read((char *) pBuffer, sizeof(XML_Char) * chunkSize);
		int bytesRead = stream.gcount();

		int result = XML_ParseBuffer(parser, bytesRead, stream.eof());
		if(result == XML_STATUS_ERROR)
		{
			// Get the error into a human-readable string
			XML_Error err = XML_GetErrorCode(parser);
			string errstr = XML_ErrorString(err);
			XmlParser *pParser = (XmlParser *) XML_GetUserData(parser);
			int column = XML_GetCurrentColumnNumber(parser);
			int line = XML_GetCurrentLineNumber(parser);
			pParser->m_lastError = "Error parsing XML stream ";
			pParser->m_lastError += " at line "  + toString(line) + ", column " + toString(column);
			pParser->m_lastError += ": " + errstr;
			return false;
		}
	}

	return true;
}


/**************************
* Expat handler functions *
**************************/

/*
	Expat XML declaration handler
	@param standalone -1 if none given, 0 for no and 1 for yes

	@todo
		- version can be NULL, if this is a text declaration discovered in an external entity
		- encoding can be NULL too
*/
void XMLCALL XmlParser::declHandler(void *data, const XML_Char *version, const XML_Char *encoding, int standalone)
{
	// Get the xml parser instance
	XmlParser *pParser = (XmlParser *) data;

	// The xml version
	string strVersion;
	if(version)
		strVersion = string(version);

	// The xml encoding
	string strEncoding;
	if(encoding)
		strEncoding = string(encoding);

	// Exexute the virtual function
	pParser->header(strVersion, strEncoding, standalone);
}

void XMLCALL XmlParser::startHandler(void *data, const char *el, const char **attr)
{
	// Get the xml parser instance
	XmlParser *pParser = (XmlParser *) data;

	// Set the current context
	pParser->m_context = string(el);

	// The attributes
	AttributeMap attributes;
	for(unsigned int i = 0; attr[i]; i += 2)
		attributes[attr[i]] = attr[i + 1];

	// Execute the virtual function
	pParser->startTag(el, attributes);
}

void XMLCALL XmlParser::endHandler(void *data, const char *el)
{
	// Get the xml parser instance
	XmlParser *pParser = (XmlParser *) data;

	// Handle text data
	trim(pParser->m_text);
	if(!pParser->m_text.empty())
	{
		pParser->content(pParser->m_text, pParser->m_context);
		pParser->m_text.clear();
	}

	// Execute the virtual function
	pParser->endTag(el);
}

void XMLCALL XmlParser::textHandler(void *data, const XML_Char *s, int len)
{
	// Get the xml parser instance
	XmlParser *pParser = (XmlParser *) data;

	// Append the text (this is called multiple times for one tag if newlines exist)
	pParser->m_text.append(s, len);
}

int XMLCALL XmlParser::externalEntityHandler(XML_Parser p, const XML_Char *context, const XML_Char *base, const XML_Char *systemId, const XML_Char *publicId)
{
	// Create the parser for the DTD (it inherits the settings of the given parser)
	XML_Parser dtdParser = XML_ExternalEntityParserCreate(p, context, NULL);

	string filename = string(base) + string(systemId);
	bool result = parse(dtdParser, filename);
	if(!result)
		return XML_STATUS_ERROR;

	// Clean up the DTD parser
	XML_ParserFree(dtdParser);

	return XML_STATUS_OK;
}


/********************
* Utility functions *
********************/

/*!
	Trims (leading and trailing) white spaces from the given text.
*/
void XmlParser::trim(string &text)
{
	static const string delims = " \t\r\n";
	text.erase(text.find_last_not_of(delims) + 1); // trim right
	text.erase(0, text.find_first_not_of(delims)); // trim left
}

/*!
	Convert all backslashes ('\') in a filename to normal slashes ('/').
*/
void XmlParser::convertSlashes(string &filename)
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
string XmlParser::getFilePath(const string &filename)
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
string XmlParser::getFileName(const string &filename)
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


string XmlParser::toString(int value)
{
	char buffer[256];
	sprintf(buffer, "%d", value);
	return string(buffer);
}
