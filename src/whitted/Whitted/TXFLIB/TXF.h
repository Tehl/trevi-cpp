/*
	FILE:    TXF.h
	AUTHOR:  Tyrone Davison
	VERSION: 1.2.7114
	DATE:    14 November 2006
	PURPOSE: LIB to assist data file loading
*/


#ifndef __TXF__
#define __TXF__


#define TXF_MAJOR_VERSION  1
#define TXF_MINOR_VERSION  1
#define TXF_BUILD_YEAR     6
#define TXF_BUILD_MONTH    11
#define TXF_BUILD_DAY      14

#define TXF_SDK_VERSION (TXF_MAJOR_VERSION << 24 | TXF_MINOR_VERSION << 16 | (12 * TXF_BUILD_YEAR + TXF_BUILD_MONTH) << 8 | TXF_BUILD_DAY)


#include <string>
#include <list>
#include <sstream>
#include <vector>
#include <utility>


namespace TXF
{

	// import from std
	using std::string;
	using std::list;
	using std::pair;


	// TXF exceptions
	class Exception {};
	class DataNotFoundException      : public Exception {};
	class FileNotFoundException      : public Exception {};
	class InternalErrorException     : public Exception {};
	class InvalidCallException       : public Exception {};
	class InvalidFileFormatException : public Exception {};
	class InvalidParameterException  : public Exception {};
	class NotImplementedException    : public Exception {};


	// TXF internal classes
	class CDocument;
	class CElement;
	class CImageFile;


	class Element
	{
	public:
		Element  ( CElement* );
		Element  ( const Element& );
		~Element ( );
	public:
		const Element&  operator =( const Element& );
	public:
		string                       Attribute       ( const char* name );
		int                          AttributeCount  ( );
		list< pair<string,string> >  Attributes      ( );
		int                          ChildCount      ( );
		list<Element>                Children        ( const char* name );
		list<Element>                Children        ( );
		string&                      Content         ( );
		void                         CreateAttribute ( const char* name, const char* content );
		Element                      CreateChild     ( const char* name );
		Element                      FirstChild      ( const char* name );
		bool                         HasAttribute    ( const char* name );
		bool                         HasChild        ( const char* name );
		bool                         HasContent      ( );
		CElement*                    Interface       ( );
		string                       Name            ( );
		list<Element>                Query           ( const char* path );
	private:
		Element ( );
	private:
		CElement*  _interface;
	};


	class Document
	{
	public:
		Document  ( const char* name=0 );
		Document  ( const Document& );
		~Document ( );
	public:
		const Document&  operator =( const Document& );
	public:
		bool     Read        ( const char* filename );
		Element  RootElement ( );
		bool     Write       ( const char* filename );
	private:
		CDocument*  _interface;
	};


	// Currently only supports TGA
	class ImageFile
	{
	public:
		ImageFile  ( );
		ImageFile  ( const ImageFile& );
		~ImageFile ( );
	public:
		const ImageFile&  operator= ( const ImageFile& );
	public:
		int   BytesPerPixel  ( ) const;
		bool  Close          ( );
		int   GetPixels      ( unsigned char* buffer, int bufferCapacity );
		int   Height         ( ) const;
		void  New            ( const char* filename );
		bool  Open           ( const char* filename );
		void  SetFilename    ( const char* filename );
		int   SetPixels      ( int width, int height, int bytesPerPixel, const unsigned char* buffer, int bufferCapacity );
		void  UseCompression ( bool );
		int   Width          ( ) const;
	private:
		CImageFile*  _interface;
	};

};


namespace TXFSTL
{

	template< class T >
	std::istream&  operator >> ( const std::string& str, T& f )
	{
		static std::stringstream stream;
		stream.clear();
		stream.str( str );
		stream >> f;
		return stream;
	}

	template< class T >
	std::istream&  operator >> ( std::istream& stream, std::vector<T>& v )
	{
		T tmp;
		stream >> tmp;
		while ( stream.fail() == false )
		{
			v.push_back(tmp);
			stream >> tmp;
		}
		return stream;
	}

	template< class T >
	std::istream&  operator >> ( std::istream& stream, std::list<T>& l )
	{
		T tmp;
		stream >> tmp;
		while ( stream.fail() == false )
		{
			l.push_back(tmp);
			stream >> tmp;
		}
		return stream;
	}

};


#endif // end #ifdef __TXF__
