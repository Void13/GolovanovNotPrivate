#include <stdio.h>
#include <conio.h>
#include <memory.h>

#include <algorithm>

#define DYNAMIC_STR_START_MEMORY_SIZE 4

class CDynamicString
{
public:
	CDynamicString()
	{
		m_uStrLength = 0;
		m_uMemLength = DYNAMIC_STR_START_MEMORY_SIZE;
		m_pString = new char[m_uMemLength];
	};

	CDynamicString(CDynamicString const &_SrcDynStr)
	{
		m_uStrLength = _SrcDynStr.m_uStrLength;
		m_uMemLength = _SrcDynStr.m_uMemLength;
		m_pString = new char[m_uMemLength];

		memcpy(m_pString, _SrcDynStr.m_pString, m_uStrLength);
	};

	CDynamicString(CDynamicString &&_SrcDynStr)
	{
		if (this != &_SrcDynStr)
		{
			m_pString = _SrcDynStr.m_pString;
			m_uStrLength = _SrcDynStr.m_uStrLength;
			m_uMemLength = _SrcDynStr.m_uMemLength;

			memset(&_SrcDynStr, 0, sizeof(CDynamicString));
		}
	};

	CDynamicString(char const *const _pSrcStr)
	{
		m_uMemLength = DYNAMIC_STR_START_MEMORY_SIZE;

		unsigned int nSrcStrLength = 0;
		char const *pSrcStr = _pSrcStr;
		while (*pSrcStr)
		{
			nSrcStrLength++;
			pSrcStr++;
		}

		nSrcStrLength++;

		if (nSrcStrLength > m_uMemLength)
		{
			while (nSrcStrLength > m_uMemLength)
				m_uMemLength <<= 1;
		}

		m_uStrLength = nSrcStrLength;

		m_pString = new char[m_uMemLength];

		memcpy(m_pString, _pSrcStr, m_uStrLength);
	};

	~CDynamicString()
	{
		if (m_pString)
			delete[] m_pString;
	};

	const CDynamicString &operator=(const CDynamicString &_SrcDynStr)
	{
		if (this != &_SrcDynStr)
		{
			if (_SrcDynStr.m_uStrLength > m_uMemLength)
			{
				while (_SrcDynStr.m_uStrLength > m_uMemLength)
					m_uMemLength <<= 1;

				delete[] m_pString;

				m_pString = new char[m_uMemLength];
			}

			m_uStrLength = _SrcDynStr.m_uStrLength;

			memcpy(m_pString, _SrcDynStr.m_pString, m_uStrLength);
		}

		return *this;
	};

	const CDynamicString &operator=(CDynamicString &&_SrcDynStr)
	{
		if (this != &_SrcDynStr)
		{
			m_pString = _SrcDynStr.m_pString;
			m_uStrLength = _SrcDynStr.m_uStrLength;
			m_uMemLength = _SrcDynStr.m_uMemLength;

			memset(&_SrcDynStr, 0, sizeof(CDynamicString));
		}

		return *this;
	};

	friend const CDynamicString operator+(const CDynamicString &_SrcDynStr1, const CDynamicString &_SrcDynStr2)
	{
		CDynamicString tmp;
		tmp.m_uStrLength = _SrcDynStr1.m_uStrLength + _SrcDynStr2.m_uStrLength - 1;

		if (tmp.m_uStrLength > tmp.m_uMemLength)
		{
			while (tmp.m_uStrLength > tmp.m_uMemLength)
				tmp.m_uMemLength <<= 1;

			delete[] tmp.m_pString;

			tmp.m_pString = new char[tmp.m_uMemLength];
		}

		memcpy(tmp.m_pString, _SrcDynStr1.m_pString, _SrcDynStr1.m_uStrLength - 1);
		memcpy(tmp.m_pString + _SrcDynStr1.m_uStrLength - 1, _SrcDynStr2.m_pString, _SrcDynStr2.m_uStrLength);

		return tmp;
	}

	char const *const GetString() const 
	{
		return m_pString;
	};

	unsigned int const GetLength() const 
	{
		return m_uStrLength;
	};
private:
	char *m_pString;
	unsigned int m_uStrLength;
	unsigned int m_uMemLength;
};

int main()
{
	CDynamicString strings[5] = 
	{
		"firststr",
		"secondstr",
		"myhanded",
		"flasth",
		"nebebe"
	};

	strings[0] = strings[0] + strings[3];

	struct {
		bool operator()(CDynamicString const &first, CDynamicString const &second)
		{
			return strcmp(first.GetString(), second.GetString()) < 0;
		};
	} customPred;

	std::sort(strings, strings + 5, customPred);
	
	for (int i = 0; i < 5; i++)
		printf("%s\n", strings[i].GetString());

	//_getch();
	return 0;
}