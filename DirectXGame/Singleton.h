#pragma once

// just use as a template since most singletons can't be combined into a base class

template <typename T>
class Singleton
{
public:
	static T* get()
	{
		if (!sharedInstance)
			sharedInstance = new T();

		return sharedInstance;
	}

	Singleton(Singleton const&) = delete;
	Singleton& operator=(Singleton const&) = delete;
	Singleton(Singleton&& other) noexcept = delete;
	Singleton& operator=(Singleton&& other) noexcept = delete;

protected:
	Singleton() = default;
	virtual ~Singleton() = default;
	static T* sharedInstance;

};