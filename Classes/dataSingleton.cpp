#include <stddef.h>
#include "dataSingleton.h"

dataSingleton* dataSingleton::m_plnstance = NULL;

dataSingleton* dataSingleton::getInstance()
{
	if (!m_plnstance)
	{
		m_plnstance = new dataSingleton;
	}
	return m_plnstance;
}