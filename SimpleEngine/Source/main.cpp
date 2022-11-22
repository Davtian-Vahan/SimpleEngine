//#include "Agario/Agario.h"
//#include <Engine/GameManager/GameManager.h>
//
//int main()
//{
//	GameManager Manager(new AgarioGame());
//	return Manager.StartGame();
//}


/*
	Unit tests for Simple delegate classes
*/


#include <cstdio>
#include <Engine/Delegate/Delegate.h>


/*
	Test reference params
*/
void TestStaticFunction0(const int &x, const int &y)
{
	printf("TestStaticFunction0::Params:  x = %d,		      y = %d\n", x, y);
	printf("TestStaticFunction0::Params: &x = %p,  &y = %p\n\n", &x, &y);
}

/*
	Test const params
*/
void TestStaticFunction1(const int x, const int y)
{
	printf("TestStaticFunction1::Params:  x = %d,		      y = %d\n", x, y);
	printf("TestStaticFunction1::Params: &x = %p,  &y = %p\n\n", &x, &y);
}

/*
	Test value params
*/
float TestStaticFunction2(int x, int y)
{
	printf("TestStaticFunction2::Params:  x = %d,		      y = %d\n", x, y);
	printf("TestStaticFunction2::Params: &x = %p,  &y = %p\n\n", &x, &y);

	return x / y * 1.15f;
}

/*
	Test other types and param counts
*/
void TestStaticFunction3(double x, char y, int z)
{
	printf("TestStaticFunction3::Params:  x = %f,	      y = %c,	             z = %d\n", x, y, z);
	printf("TestStaticFunction3::Params: &x = %p,  &y = %p  &z = %p\n\n", &x, &y, &z);
}

/*
	Test pointer param
*/
void TestStaticFunction4(double * dPtr)
{
	printf("TestStaticFunction4::Params: *dPtr = %f\n", *dPtr);
	printf("TestStaticFunction4::Params:  dPtr = %p\n\n", dPtr);
}


int main()
{
	// Make sample delegate with sample functor
	StaticDelegate<void,  const int&, const int&> DelegTest0(&TestStaticFunction0);
	StaticDelegate<void,  const int,  const int>  DelegTest1(&TestStaticFunction1);
	StaticDelegate<float, int,        int>		  DelegTest2(&TestStaticFunction2);
	StaticDelegate<void,  double,     char, int>  DelegTest3(&TestStaticFunction3);
	StaticDelegate<void,  double *>				  DelegTest4(&TestStaticFunction4);

	// Sample values
	int SampleInt1 = 10, SampleInt2 = 5;
	double SampleDbl = 105.1;
	float  SampleFlt = 0.15f;
	double* SamplePtr = &SampleDbl;

	// Execute delegate with test variables
	DelegTest0.exec(SampleInt1, 123);
	DelegTest1.exec(14, SampleInt2);
	DelegTest2.exec(SampleInt1, SampleInt2);
	DelegTest3.exec(125.3f, SampleInt2, 12);
	DelegTest4.exec(SamplePtr);

	return 0;
}