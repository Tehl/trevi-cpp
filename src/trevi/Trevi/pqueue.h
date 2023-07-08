/*
	Priority Queue (Template)
	Matt Howe	E5034116
	Mar 07
*/

#pragma once
#include <string>
#include <vector>

using namespace std;

template<typename T>
class PriorityQueue
{
	public:
		PriorityQueue();
		~PriorityQueue();

		void insert(T, double);
		T top();
		T pop();
		bool empty();

	private:
		void heapify();
		vector<T> m_vtObject;
		vector<double> m_vfPriority;
		int m_iNumNodes;
};

//========== IMPLIMENTATION ==========//

// constructor
template<typename T>
PriorityQueue<T>::PriorityQueue()
{
	m_iNumNodes = 0;
}

// destructor
template<typename T>
PriorityQueue<T>::~PriorityQueue()
{
	// nothing to do here
}

template<typename T>
void PriorityQueue<T>::insert(T tObject, double fPriority)
{
	m_iNumNodes++;
	m_vtObject.push_back(tObject);
	m_vfPriority.push_back(fPriority);

	heapify();
}

template<typename T>
T PriorityQueue<T>::top()
{
	return m_vtObject[0];
}

template<typename T>
T PriorityQueue<T>::pop()
{
	m_iNumNodes--;

	T result = m_vtObject[0];

	m_vtObject[0] = m_vtObject[m_iNumNodes];
	m_vfPriority[0] = m_vfPriority[m_iNumNodes];

	m_vtObject.pop_back();
	m_vfPriority.pop_back();

	heapify();

	return result;
}

template<typename T>
bool PriorityQueue<T>::empty()
{
	if (m_iNumNodes == 0)
	{
		return true;
	} else {
		return false;
	}
}

template<typename T>
void PriorityQueue<T>::heapify()
{
	for (int i = 0; i < m_iNumNodes; i++)
	{
		int iLeftNode = 2 * i + 1;
		int iRightNode = 2 * i + 2;
		if (iLeftNode < m_iNumNodes && iLeftNode >= 0)
		{
			if (m_vfPriority[iLeftNode] > m_vfPriority[i])
			{
				double fTemp = m_vfPriority[iLeftNode];
				m_vfPriority[iLeftNode] = m_vfPriority[i];
				m_vfPriority[i] = fTemp;

				T tTemp = m_vtObject[iLeftNode];
				m_vtObject[iLeftNode] = m_vtObject[i];
				m_vtObject[i] = tTemp;
	
				heapify();
			}
		}
		if (iRightNode < m_iNumNodes && iRightNode >= 0)
		{
			if (m_vfPriority[iRightNode] > m_vfPriority[i])
			{
				double fTemp = m_vfPriority[iRightNode];
				m_vfPriority[iRightNode] = m_vfPriority[i];
				m_vfPriority[i] = fTemp;

				T tTemp = m_vtObject[iRightNode];
				m_vtObject[iRightNode] = m_vtObject[i];
				m_vtObject[i] = tTemp;

				heapify();
			}
		}
	}
}