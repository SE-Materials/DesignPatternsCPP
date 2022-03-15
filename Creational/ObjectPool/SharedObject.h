#pragma once
#include <iostream>


class SharedObject
{
	bool m_isused;
public:
	void SetIsUsed() {
		m_isused = true;
	}

	void ClearIsUsed() {
		m_isused = false;
	}

	bool IsUsed() {
		return m_isused;
	}

	void Reset() {

	}

	virtual void Update() = 0;
};

