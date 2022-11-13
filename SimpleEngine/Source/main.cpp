#include "Agario/Agario.h"
#include <Engine/GameManager/GameManager.h>

int main()
{
	GameManager Manager(new AgarioGame());
	return Manager.StartGame();
}


//// Test delegate
//#include <iostream>
//#include <Engine/Delegate/Delegate.h>
//void f1(ActorBase* actor)
//{
//	std::cout << "Succesfuly binded f1()\n";
//}
//
//void f2(ActorBase* actor)
//{
//	std::cout << "Succesfuly binded f2()\n";
//}
//
//void f3(ActorBase* actor, int x)
//{
//	std::cout << "Should not bind f3()\n";
//}
//
//
//int main()
//{
//	onHitDelegate del;
//	del.Bind(&f1);
//	del.Bind(&f2);
//	//del.Bind(f3);
//	del.Execute();
//	return 0;
//}