#pragma once
#include <Engine/GameBase/GameBase.h>
#include <Engine/ActorBase/ActorBase.h>

/*
	TODO: Add bind removal functionality
		  Add overlap delegate logic
*/

#define BIND_MAX 256 // arbitrary bind limit
struct onHitDelegate
{
private:
	int callback_i = -1;

	// Hit Delegate signature and bind array
	typedef void (*HitCallbackType)(class ActorBase*);
	HitCallbackType HitDelegates[BIND_MAX];

public:
	bool Bind(HitCallbackType Callback);
	void Execute();
};

struct onOverlapDelegate
{
private:
	int callback_i = -1;

	// Hit Delegate signature and bind array
	typedef void (*HitCallbackType)(class ActorBase*);
	HitCallbackType HitDelegates[BIND_MAX];

public:
	bool Bind(HitCallbackType Callback);
	void Execute();
};