#pragma once
#include <iostream>
#include <vector>
#include <functional>

//----------------------------------------------------------
class SharedObject;
using SharedObjectPtr = std::shared_ptr<SharedObject>;


//----------------------------------------------------------
using Creator = std::function<SharedObjectPtr()>;

struct SharedObjectInfo {
	std::vector<SharedObjectPtr> m_objects{};
	Creator                      m_creator{ nullptr };
};

//----------------------------------------------------------
class ObjectPool
{
	ObjectPool() = default;
	inline static std::unordered_map<std::string, SharedObjectInfo> s_sharedObjectPool{};

public:
	static SharedObjectPtr AcquireInstance(const std::string &key);
	static void ReleaseInstance(const std::string& key, SharedObjectPtr& instance);
	static void RegisterCreator(const std::string& key, const Creator& creator);
};
