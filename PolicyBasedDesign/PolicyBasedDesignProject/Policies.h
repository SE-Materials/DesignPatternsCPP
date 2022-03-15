#pragma once

#include <iostream>


template<typename T>
struct OpNewCreator
{
	static T* Create()
	{
		return new T();
	}
};

template <typename T>
struct MallocCreator
{
	static T* Create()
	{
		void* buf = std::malloc(sizeof(T));
		if (!buf) return 0;
		return new(buf)T;
	}
};

template <typename T>
struct PrototypeCreator
{
	PrototypeCreator(T* obj = 0) : m_prototype(obj) {}

	T* Create()
	{
		return m_prototype ? m_prototype->Clone() : 0;
	}

	T* GetPrototype() 
	{
		return m_prototype;
	}

	void SetPrototype(T* pObj)
	{
		m_prototype = pObj;
	}

private:
	T* m_prototype;
};