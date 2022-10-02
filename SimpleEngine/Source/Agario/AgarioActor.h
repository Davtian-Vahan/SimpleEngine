#pragma once

#include <Engine/ActorBase/ActorBase.h>

class AgarioActor : public ActorBase
{
public:
	explicit AgarioActor() 
	{
		bool Ok = SetTexture("C:\\Users\\jedav\\Desktop\\SimpleEngine\\SimpleEngine\\Source\\Agario\\sample_texture.png");
		if (!Ok)
		{
			printf("Failed to open asset.");
		}

		sprite.setScale(TVector(0.5, 0.5));
	}
};