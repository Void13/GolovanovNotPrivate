#ifndef _H__BAKERYFACTORY
#define _H__BAKERYFACTORY

#include <string>
#include <unordered_map>

template<class TBase>
class CFactory
{
public:
	~CFactory()
	{
		for (auto &pClass : Factories)
		{
			delete pClass.second;
			pClass.second = nullptr;
		}
	};

	template<class TDerived>
	void RegisterClass(std::string const &_sName)
	{
		Factories[_sName] = new IDerivedType<TDerived>;
	};

	TBase *CreateInstance(std::string const &_sName)
	{
		return Factories[_sName]->CreateInstance();
	};

private:
	class IBaseType
	{
	public:
		virtual ~IBaseType() {};

		virtual TBase *CreateInstance() const = 0;
	};

	template<class T>
	class IDerivedType : public IBaseType
	{
	public:
		TBase *CreateInstance() const
		{
			return new T();
		};
	};

	std::unordered_map<std::string, IBaseType *> Factories;
};

#endif