#pragma once

/*
*	A not very well implemented function delegate system
*	TODO: Lambda, static and member function delegates
*/

// General interface for all delegate classes
template <class RetType, class... Params>
class IDelegate
{
public:
	virtual void exec(Params...args) = 0;

	IDelegate() = default;
	IDelegate(const IDelegate&) = delete;
	void operator=(const IDelegate&) = delete;
};

/*
	Class implements a minimal delegate that supports static functions

	Usage example: 
					void f(int x, double & y) {}

					StaticDelegate<void, int, double &> Delegate(&f);
					Delegate.exec(15, 10.3);
*/

template <class RetType, class... Params>
class StaticDelegate : IDelegate<RetType, Params...>
{
public:
	// Deduct function signature
	typedef RetType(*Signature)(Params...);

	// Construct this delegate
	StaticDelegate();
	explicit StaticDelegate(Signature&&);

	// Bind a new function
	void BindRaw(Signature&&);

	// Executes stored functionPtr with given args
	virtual void exec(Params... args) override;

private:
	// Function address that is to be executed
	Signature functionPtr;
};


/*
	Inline method definitions
*/

template<class RetType, class ...Params>
inline StaticDelegate<RetType, Params...>::StaticDelegate()
	: functionPtr(nullptr)
{}

template<class RetType, class ...Params>
inline StaticDelegate<RetType, Params...>::StaticDelegate(Signature&& funcRef)
	: functionPtr(funcRef)
{}

template<class RetType, class ...Params>
inline void StaticDelegate<RetType, Params...>::BindRaw(Signature&& funcRef)
{
	functionPtr = funcRef;
}

template<class RetType, class ...Params>
inline void StaticDelegate<RetType, Params...>::exec(Params ...args)
{
	(RetType)(functionPtr)(args...);
}