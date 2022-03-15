#include "ObjectPool.h"
#include "SharedObject.h"
#include <algorithm>

auto GetFirstNonUsed = [] (const SharedObjectPtr & sharedObjectPtr) {
	return !sharedObjectPtr->IsUsed();
};

//----------------------------------------------------------------------------
SharedObjectPtr ObjectPool::AcquireInstance(const std::string& key)
{
	auto keyToSharedObjectInfoItr = s_sharedObjectPool.find(key);
	if (keyToSharedObjectInfoItr == s_sharedObjectPool.end())
	{
		std::cout << "[POOL] Creator function not registered for " << key << std::endl;
		return nullptr;
	}

	if (keyToSharedObjectInfoItr->second.m_creator == nullptr)
	{
		std::cout << "[POOL] Creator function not registered for " << key << std::endl;
		return nullptr;
	}

	auto pooledObjects = keyToSharedObjectInfoItr->second.m_objects;

	auto it = std::find_if(pooledObjects.begin(), pooledObjects.end(), GetFirstNonUsed);

	if (it != pooledObjects.end())
	{
		std::cout << "[POOL] Returning an existing " << key << std::endl;
		(*it)->SetIsUsed();
		(*it)->Reset();
		return *it;
	}

	std::cout << "[POOL] Creating a new " << key << std::endl;
	auto sharedObj = keyToSharedObjectInfoItr->second.m_creator();
	keyToSharedObjectInfoItr->second.m_objects.push_back(sharedObj);
	sharedObj->SetIsUsed();
	return sharedObj;
}

//----------------------------------------------------------------------------
void ObjectPool::ReleaseInstance(const std::string& key, SharedObjectPtr& instance)
{
	auto keyToSharedObjectInfoItr = s_sharedObjectPool.find(key);
	if (keyToSharedObjectInfoItr == s_sharedObjectPool.end())
	{
		std::cout << "[POOL] " << key << " not registered" << std::endl;
		return;
	}

	auto objectPool = keyToSharedObjectInfoItr->second.m_objects;

	auto it = std::find(objectPool.begin(), objectPool.end(), instance);
	if (it != objectPool.end())
		instance->ClearIsUsed();
}

//----------------------------------------------------------------------------
void ObjectPool::RegisterCreator(const std::string& key, const Creator& creator)
{
	s_sharedObjectPool[key].m_creator = creator;
}
