#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <tuple>
#include <map>
#include <vector>
#include <cstdlib>
#include <cstdint>
#include <curl/curl.h>

#include "solution.h"

#include <tinyxml.h>

using namespace std;

// ----------------------------------------------------------------------
// STDOUT dump and indenting utility functions
// ----------------------------------------------------------------------
const unsigned int NUM_INDENTS_PER_SPACE=2;

const char * getIndent( unsigned int numIndents )
{
	static const char * pINDENT="                                      + ";
	static const size_t LENGTH=strlen( pINDENT );
	size_t n=numIndents*NUM_INDENTS_PER_SPACE;
	if ( n > LENGTH ) n = LENGTH;

	return &pINDENT[ LENGTH-n ];
}

// same as getIndent but no "+" at the end
const char * getIndentAlt( unsigned int numIndents )
{
	static const char * pINDENT="                                        ";
	static const size_t LENGTH=strlen( pINDENT );
	size_t n=numIndents*NUM_INDENTS_PER_SPACE;
	if ( n > LENGTH ) n = LENGTH;

	return &pINDENT[ LENGTH-n ];
}

int dump_attribs_to_stdout(TiXmlElement* pElement, unsigned int indent)
{
	if ( !pElement ) return 0;

	TiXmlAttribute* pAttrib=pElement->FirstAttribute();
	int i=0;
	int ival;
	double dval;
	const char* pIndent=getIndent(indent);
	printf("\n");
	while (pAttrib)
	{
		printf( "%s%s: value=[%s]", pIndent, pAttrib->Name(), pAttrib->Value());

		if (pAttrib->QueryIntValue(&ival)==TIXML_SUCCESS)    printf( " int=%d", ival);
		if (pAttrib->QueryDoubleValue(&dval)==TIXML_SUCCESS) printf( " d=%1.1f", dval);
		printf( "\n" );
		i++;
		pAttrib=pAttrib->Next();
	}
	return i;	
}

void dump_to_stdout( TiXmlNode* pParent, unsigned int indent = 0 )
{
	if ( !pParent ) return;

	TiXmlNode* pChild;
	TiXmlText* pText;
	int t = pParent->Type();
	printf( "%s", getIndent(indent));
#if 1
	int num;
	switch ( t )
	{
    case TiXmlNode::TINYXML_DOCUMENT:
		printf( "Document" );
		break;

	case TiXmlNode::TINYXML_ELEMENT:
		printf( "Element [%s]", pParent->Value() );
		num=dump_attribs_to_stdout(pParent->ToElement(), indent+1);
		switch(num)
		{
			case 0:  printf( " (No attributes)"); break;
			case 1:  printf( "%s1 attribute", getIndentAlt(indent)); break;
			default: printf( "%s%d attributes", getIndentAlt(indent), num); break;
		}
		break;

	case TiXmlNode::TINYXML_COMMENT:
		printf( "Comment: [%s]", pParent->Value());
		break;

	case TiXmlNode::TINYXML_UNKNOWN:
		printf( "Unknown" );
		break;

	case TiXmlNode::TINYXML_TEXT:
		pText = pParent->ToText();
		printf( "Text: [%s]", pText->Value() );
		break;

	case TiXmlNode::TINYXML_DECLARATION:
		printf( "Declaration" );
		break;
	default:
		break;
	}
#endif
	printf( "\n" );
	for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
	{
		dump_to_stdout( pChild, indent+1 );
	}
}

bool StringToUInt32(const std::string & str, uint32_t & val)
{
    try
    {
        val = static_cast<uint32_t>(std::stoul(str, nullptr, 0));
        return true;
    }
    catch (std::invalid_argument)
    {
        return false;
    }
    catch (std::out_of_range)
    {
        return false;
    }
}

/**
    \brief Converts a string to an unsigned 64-bit integer, with error checking.
    \param[in] str Input string
    \param[out] val On return (if function returns true), contains the converted unsigned 64-bit integer
    \return true indicates the string was converted properly; otherwise false
*/
bool StringToUInt64(const std::string & str, uint64_t & val)
{
    try
    {
        val = static_cast<uint64_t>(std::stoull(str, nullptr, 0));
        return true;
    }
    catch (std::invalid_argument)
    {
        return false;
    }
    catch (std::out_of_range)
    {
        return false;
    }
}

bool ElementValueStr(const TiXmlElement * xmlElement, std::string & val)
{
    if (nullptr == xmlElement)
    {
        return false;
    }

    const TiXmlNode * nodeElement = xmlElement->FirstChild();

    if (nullptr != nodeElement)
    {
        val = nodeElement->ValueStr();
        return true;
    }
    else
    {
        return false;
    }
}

/**
    \brief Parses an element with a node containing an unsigned 32-bit integer.
    \param[in] xmlElement XML element
    \param[out] val On return (if function returns true), contains the parsed unsigned 32-bit integer.
    \return true indicates the XML was parsed correctly; otherwise false
*/
bool ElementValueUInt32(const TiXmlElement * xmlElement, uint32_t & val)
{
    std::string str;
    if (ElementValueStr(xmlElement, str))
    {
        return StringToUInt32(str, val);
    }
    else
    {
        return false;
    }
}

/**
    \brief Parses an element with a node containing an unsigned 64-bit integer.
    \param[in] xmlElement XML element
    \param[out] val On return (if function returns true), contains the parsed unsigned 64-bit integer.
    \return true indicates the XML was parsed correctly; otherwise false
*/
bool ElementValueUInt64(const TiXmlElement * xmlElement, uint64_t & val)
{
    std::string str;
    if (ElementValueStr(xmlElement, str))
    {
        return StringToUInt64(str, val);
    }
    else
    {
        return false;
    }
}

// load the named file and dump its structure to STDOUT
void dump_to_stdout(const char* pFilename)
{
	TiXmlDocument doc(pFilename);
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
		printf("\n%s:\n", pFilename);
        TiXmlElement * root = doc.RootElement();
        TiXmlElement * segmentElement = root->FirstChildElement("segment");
        while (segmentElement != nullptr)
        {
            TiXmlNode * nodeElement = nullptr;
            // Get the elements that we are interested in. Ignore everything else.
            TiXmlElement * segmentNameElement    = segmentElement->FirstChildElement("name");
            TiXmlElement * segmentIDElement      = segmentElement->FirstChildElement("id");
            TiXmlElement * segmentAddressElement = segmentElement->FirstChildElement("address");

            std::string segmentName;
            if (!ElementValueStr(segmentNameElement, segmentName))
            {
                return;
            }
            cout << "name: " << segmentName << endl;

            // Parse the ID element.
            uint64_t segmentID = 0;
            if (!ElementValueUInt64(segmentIDElement, segmentID))
            {
                return;
            }
            cout << "id  : " << segmentID << endl;

            // Parse the address element.
            uint64_t segmentAddress = 0;
            if (!ElementValueUInt64(segmentAddressElement, segmentAddress))
            {
                return;
            }
            cout << "addr: " << segmentAddress << endl;
            // Go to the next segment.
            segmentElement = segmentElement->NextSiblingElement("segment");
            cout << endl;
        }
		//dump_to_stdout( &doc ); // defined later in the tutorial
	}
	else
	{
		printf("Failed to load file \"%s\"\n", pFilename);
	}
}

// ----------------------------------------------------------------------
// main() for printing files named on the command line
// ----------------------------------------------------------------------
void usage()
{
    cout << "usage: solution <xml file>" << endl;
}

int main(int argc, char* argv[])
{
    cout << "dude, you suck!" << endl;

    if (argc < 2) {
        usage();
        return -1;
    }

    cout << argv[0] << " Version " << solution_VERSION_MAJOR << "." << solution_VERSION_MINOR << endl;


    for (int i=1; i<argc; i++) {
        dump_to_stdout(argv[i]);
    }
	return 0;
}
