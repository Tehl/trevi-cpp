/*
	Buffer Class (Template)
	Matt Howe	E5034116
	Mar 07
*/

#pragma once
#include "die.h"

template<typename T>
class Buffer
{
	public:
		Buffer(int, int);
		Buffer(const Buffer<T>&);
		Buffer();
		~Buffer();

		const Buffer<T>& operator = (const Buffer<T>&);
		Buffer<T> operator + (const Buffer<T>&) const;
		Buffer<T> operator - (const Buffer<T>&) const;
		Buffer<T> operator * (const Buffer<T>&) const;
		Buffer<T> operator / (const Buffer<T>&) const;
		Buffer<T> operator * (double) const;
		Buffer<T> operator / (double) const;
		const Buffer<T>& operator += (const Buffer<T>&);
		const Buffer<T>& operator -= (const Buffer<T>&);
		const Buffer<T>& operator *= (const Buffer<T>&);
		const Buffer<T>& operator /= (const Buffer<T>&);
		const Buffer<T>& operator *= (double);
		const Buffer<T>& operator /= (double);

		int height() const;
		int width() const;
		T& loc(int, int);
		T& loc(int, int) const;
		Buffer<T> sub(int, int, int, int) const;
		T average();
		void clear(T);

	private:
		T* m_tData;
		int m_iHeight, m_iWidth;
};

//========== Implimentation ==========//

// constructor
template<typename T>
Buffer<T>::Buffer(int iX, int iY)
{
	if (iX < 1 || iY < 1)
	{
		die("Buffer must be at least 1x1 in dimension");
	} else {
		m_tData = new T[iX * iY];
		for (int i = 0; i < iX * iY; i++)
		{
			m_tData[i] = 0.0;
		}
		m_iWidth = iX;
		m_iHeight = iY;
	}
}

// copy constructor
template<typename T>
Buffer<T>::Buffer(const Buffer<T>& chArg)
{
	m_iWidth = chArg.m_iWidth;
	m_iHeight = chArg.m_iHeight;
	m_tData = new T[m_iWidth * m_iHeight];
	for (int i = 0; i < m_iWidth * m_iHeight; i++)
	{
		m_tData[i] = chArg.m_tData[i];
	}
}

// default constructor
template<typename T>
Buffer<T>::Buffer()
{
	die("Buffer must have dimensions");
}

// destructor
template<typename T>
Buffer<T>::~Buffer()
{
	if (m_iWidth * m_iHeight > 1)
	{
		delete [] m_tData;
	} else {
		delete m_tData;
	}
}

// operators
template<typename T>
const Buffer<T>& Buffer<T>::operator = (const Buffer<T>& chArg)
{
	m_iWidth = chArg.m_iWidth;
	m_iHeight = chArg.m_iHeight;
	delete [] m_tData;
	m_tData = new T[m_iWidth * m_iHeight];
	for (int i = 0; i < m_iWidth * m_iHeight; i++)
	{
		m_tData[i] = chArg.m_tData[i];
	}
	return *this;
}

template<typename T>
Buffer<T> Buffer<T>::operator + (const Buffer<T>& chArg) const
{
	if (m_iWidth == chArg.m_iWidth && m_iHeight == chArg.m_iHeight)
	{
		Buffer<T>* result = new Buffer(m_iWidth, m_iHeight);
		for (int i = 0; i < m_iWidth * m_iHeight; i++)
		{
			result->m_tData[i] = m_tData[i] + chArg.m_tData[i];
		}
		return *result;
	} else {
		die("Buffers must be the same size");
	}
}

template<typename T>
Buffer<T> Buffer<T>::operator - (const Buffer<T>& chArg) const
{
	if (m_iWidth == chArg.m_iWidth && m_iHeight == chArg.m_iHeight)
	{
		Buffer<T>* result = new Buffer(m_iWidth, m_iHeight);
		for (int i = 0; i < m_iWidth * m_iHeight; i++)
		{
			result->m_tData[i] = m_tData[i] - chArg.m_tData[i];
		}
		return *result;
	} else {
		die("Buffers must be the same size");
	}
}

template<typename T>
Buffer<T> Buffer<T>::operator * (const Buffer<T>& chArg) const
{
	if (m_iWidth == chArg.m_iWidth && m_iHeight == chArg.m_iHeight)
	{
		Buffer<T>* result = new Buffer(m_iWidth, m_iHeight);
		for (int i = 0; i < m_iWidth * m_iHeight; i++)
		{
			result->m_tData[i] = m_tData[i] * chArg.m_tData[i];
		}
		return *result;
	} else {
		die("Buffers must be the same size");
	}
}

template<typename T>
Buffer<T> Buffer<T>::operator / (const Buffer<T>& chArg) const
{
	if (m_iWidth == chArg.m_iWidth && m_iHeight == chArg.m_iHeight)
	{
		Buffer<T>* result = new Buffer(m_iWidth, m_iHeight);
		for (int i = 0; i < m_iWidth * m_iHeight; i++)
		{
			result->m_tData[i] = m_tData[i] / chArg.m_tData[i];
		}
		return *result;
	} else {
		die("Buffers must be the same size");
	}
}

template<typename T>
Buffer<T> Buffer<T>::operator * (double fArg) const
{
	Buffer<T> result;
	for (int i = 0; i < chArg.m_iWidth * chArg.m_iHeight; i++)
	{
		result[i] = m_tData[i] * fArg;
	}
	return result;
}

template<typename T>
Buffer<T> Buffer<T>::operator / (double fArg) const
{
	Buffer<T> result;
	for (int i = 0; i < chArg.m_iWidth * chArg.m_iHeight; i++)
	{
		result[i] = m_tData[i] / fArg;
	}
	return result;
}

template<typename T>
const Buffer<T>& Buffer<T>::operator += (const Buffer<T>& chArg)
{
	if (m_iWidth == chArg.m_iWidth && m_iHeight == chArg.m_iHeight)
	{
		for (int i = 0; i < m_iWidth * m_iHeight; i++)
		{
			m_tData[i] = m_tData[i] + chArg.m_tData[i];
		}
	} else {
		die("Buffers must be the same size");
	}
	return *this;
}

template<typename T>
const Buffer<T>& Buffer<T>::operator -= (const Buffer<T>& chArg)
{
	if (m_iWidth == chArg.m_iWidth && m_iHeight == chArg.m_iHeight)
	{
		for (int i = 0; i < m_iWidth * m_iHeight; i++)
		{
			m_tData[i] = m_tData[i] - chArg.m_tData[i];
		}
	} else {
		die("Buffers must be the same size");
	}
	return *this;
}

template<typename T>
const Buffer<T>& Buffer<T>::operator *= (const Buffer<T>& chArg)
{
	if (m_iWidth == chArg.m_iWidth && m_iHeight == chArg.m_iHeight)
	{
		for (int i = 0; i < m_iWidth * m_iHeight; i++)
		{
			m_tData[i] = m_tData[i] * chArg.m_tData[i];
		}
	} else {
		die("Buffers must be the same size");
	}
	return *this;
}

template<typename T>
const Buffer<T>& Buffer<T>::operator /= (const Buffer<T>& chArg)
{
	if (m_iWidth == chArg.m_iWidth && m_iHeight == chArg.m_iHeight)
	{
		for (int i = 0; i < m_iWidth * m_iHeight; i++)
		{
			m_tData[i] = m_tData[i] / chArg.m_tData[i];
		}
	} else {
		die("Buffers must be the same size");
	}
	return *this;
}

template<typename T>
const Buffer<T>& Buffer<T>::operator *= (double fArg)
{
	for (int i = 0; i < m_iWidth * m_iHeight; i++)
	{
		m_tData[i] = m_tData[i] * fArg;
	}
	return *this;
}

template<typename T>
const Buffer<T>& Buffer<T>::operator /= (double fArg)
{
	for (int i = 0; i < m_iWidth * m_iHeight; i++)
	{
		m_tData[i] = m_tData[i] / fArg;
	}
	return *this;
}

// data access
template<typename T>
int Buffer<T>::width() const
{
	return m_iWidth;
}

template<typename T>
int Buffer<T>::height() const
{
	return m_iHeight;
}

template<typename T>
T& Buffer<T>::loc(int iX, int iY)
{
	return m_tData[iY * m_iWidth + iX];
}

template<typename T>
T& Buffer<T>::loc(int iX, int iY) const
{
	return m_tData[iY * m_iWidth + iX];
}

template<typename T>
Buffer<T> Buffer<T>::sub(int iSX, int iSY, int iEX, int iEY) const
{
	int width = iEX - iSX + 1;
	int height = iEY - iSY + 1;

	Buffer<T> result(width, height);

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			result.m_tData[j * width + i] = m_tData[(j + iSY) * m_iWidth + iSX + i];
		}
	}

	return result;
}

template<typename T>
T Buffer<T>::average()
{
	T tTotal = 0;
	for (int i = 0; i < m_iWidth * m_iHeight; i++)
	{
		tTotal += m_tData[i];
	}
	return tTotal / (m_iWidth * m_iHeight);
}

template<typename T>
void Buffer<T>::clear(T tValue)
{
	for (int i = 0; i < m_iWidth * m_iHeight; i++)
	{
		m_tData[i] = tValue;
	}
}