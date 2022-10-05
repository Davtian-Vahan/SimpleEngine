#include <Engine/Delegate/Delegate.h>

bool onHitDelegate::Bind(HitCallbackType Callback)
{
	if (callback_i + 1 == BIND_MAX) 
		return false;
	HitDelegates[++callback_i] = Callback;
	return true;
}

// Executes all the functions that are binded to this delegate
void onHitDelegate::Execute()
{
	// Iterate through all the binded functions and call them
	for (int iter = 0; iter <= callback_i; ++iter)
	{
		HitDelegates[iter](nullptr);
	}
}

bool onOverlapDelegate::Bind(HitCallbackType Callback)
{
	//
	return false;
}

void onOverlapDelegate::Execute()
{
	//
}
