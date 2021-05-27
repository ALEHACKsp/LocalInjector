#pragma once

#ifndef Singleton_hh
#define Singleton_hh

template <typename Inst>
class CSingleton {
protected:
	CSingleton() = default;
	~CSingleton() = default;

	CSingleton(const CSingleton&) = delete;
	CSingleton& operator=(const CSingleton&) = delete;

	CSingleton(CSingleton&&) = delete;
	CSingleton& operator=(CSingleton&&) = delete;

public:
	static Inst& Get() {

		static Inst Instance{};
		return Instance;
	}
};

#endif // !Singleton_hh