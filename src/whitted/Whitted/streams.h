/*
	String Stream Operators
	Taken from TXFLIB
*/

#pragma once;
#include <string>
#include <list>
#include <sstream>
using namespace std;

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