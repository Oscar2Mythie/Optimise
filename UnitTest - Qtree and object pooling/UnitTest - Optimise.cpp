//#include "raymath.h"
//#include "raylib.h"
#include "CppUnitTest.h"
#include "../CDDS_Optimise/Critter.h"
#include "../CDDS_Optimise/QTree.h"
#include <stack>
#include "raylib.h"
#include "raymath.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//namespace Control
//{
//	
//	TEST_CLASS(Test_QTree)
//	{
//	public:
//		
//		TEST_METHOD(Collapsed)
//		{
//			int Test_screenWidth = 800;
//			int Test_screenHeight = 450;
//			Vector2 Test_ScreenSize = { Test_screenWidth , Test_screenHeight };
//			int Test_Critter_Amount = 5;
//			const int Test_MAX_VELOCITY = 0;
//
//			Critter* Test_critters = new Critter[Test_Critter_Amount];
//
//
//
//			Critter* destroyer = new Critter;
//			Vector2 velocity =
//			{
//				-100 + (rand() % 200),
//				-100 + (rand() % 200)
//			};
//			destroyer->Init(Vector2{ (float)(Test_screenWidth >> 1), (float)(Test_screenHeight >> 1) }, velocity, 20, "res/9.png");
//
//			std::pair<Vector2, Vector2> Test_QTree_Starting_boundry = { Test_ScreenSize,{0,0} };
//
//			QTree Test_RootTree(Test_QTree_Starting_boundry, Test_ScreenSize, destroyer);
//
//
//			for (int i = 0; i < Test_Critter_Amount; i++)
//			{
//
//				Vector2 velocity = // create a random direction vector for the velocity
//				{
//					-100 + (rand() % 200),
//					-100 + (rand() % 200)
//				};
//
//				Test_critters[i].Init( // create a critter in a random location
//					{
//						(float)(5 + rand() % (Test_screenWidth/2 - 10)),
//						(float)(5 + (rand() % (Test_screenHeight/2 - 10)))
//					},
//					velocity,
//					12,
//					"res/10.png"
//				);
//				Test_RootTree.insert(&Test_critters[i]);
//			}
//
//			Test_RootTree.Update_QTree(Test_MAX_VELOCITY,0);
//			QTree** Test_child = Test_RootTree.Get_QTree_childen();
//
//			Assert::IsTrue(Test_RootTree.Get_QTree_childen() != nullptr);
//			Assert::IsTrue(Test_child[0] != nullptr && Test_child[1] == nullptr && Test_child[2] == nullptr && Test_child[3] == nullptr);
//		}
//		TEST_METHOD(Respawn) 
//		{
//			int Test_screenWidth = 800;
//			int Test_screenHeight = 450;
//			Vector2 Test_ScreenSize = { Test_screenWidth , Test_screenHeight };
//			int Test_Critter_Amount = 1;
//			const int Test_MAX_VELOCITY = 0;
//
//			Critter* Test_critters = new Critter[Test_Critter_Amount];
//
//			Critter* destroyer = new Critter;
//			Vector2 velocity =
//			{
//				-100 + (rand() % 200),
//				-100 + (rand() % 200)
//			};
//			destroyer->Init(Vector2{ (float)(Test_screenWidth >> 1), (float)(Test_screenHeight >> 1) }, velocity, 20, "res/9.png");
//
//			for (int i = 0; i < Test_Critter_Amount; i++)
//			{
//
//				Vector2 velocity = // create a random direction vector for the velocity
//				{
//					-100 + (rand() % 200),
//					-100 + (rand() % 200)
//				};
//
//				Test_critters[i].Init( // create a critter in a random location
//					{
//						(float)(5 + rand() % (Test_screenWidth - 10)),
//						(float)(5 + (rand() % (Test_screenHeight - 10)))
//					},
//					velocity,
//					12,
//					"res/10.png"
//				);
//			}
//
//			std::stack<Critter*> DeadStack;
//
//			std::pair<Vector2, Vector2> Test_QTree_Starting_boundry = { Test_ScreenSize,{0,0} };
//
//			QTree Test_RootTree(Test_QTree_Starting_boundry, Test_ScreenSize, destroyer);
//
//			Test_critters->Destroy();
//			DeadStack.push(Test_critters);
//
//			if (!DeadStack.empty())
//			{
//				DeadStack.top()->respawn({ 0,0 }, {0,0}, Test_ScreenSize);
//				Test_RootTree.insert(DeadStack.top());
//				DeadStack.pop();
//			}
//
//			Assert::IsTrue(Test_RootTree.Get_QTree_Critters_DP() != nullptr);
//			Assert::IsTrue(DeadStack.empty());
//		}
//		TEST_METHOD(Subdivide)
//		{
//	
//			int Test_screenWidth = 800;
//			int Test_screenHeight = 450;
//			Vector2 Test_ScreenSize = { Test_screenWidth , Test_screenHeight };
//			int Test_Critter_Amount = 5;
//			const int Test_MAX_VELOCITY = 0;
//
//			Critter* Test_critters = new Critter[Test_Critter_Amount];
//
//			Critter* destroyer = new Critter;
//			Vector2 velocity =
//			{
//				-100 + (rand() % 200),
//				-100 + (rand() % 200)
//			};
//			destroyer->Init(Vector2{ (float)(Test_screenWidth >> 1), (float)(Test_screenHeight >> 1) }, velocity, 20, "res/9.png");
//
//			std::pair<Vector2, Vector2> Test_QTree_Starting_boundry = { Test_ScreenSize,{0,0} };
//
//			QTree Test_RootTree(Test_QTree_Starting_boundry, Test_ScreenSize , destroyer);
//
//			for (int i = 0; i < Test_Critter_Amount; i++)
//			{
//
//				Vector2 velocity = // create a random direction vector for the velocity
//				{
//					-100 + (rand() % 200),
//					-100 + (rand() % 200)
//				};
//
//				Test_critters[i].Init( // create a critter in a random location
//					{
//						(float)(5 + rand() % (Test_screenWidth - 10)),
//						(float)(5 + (rand() % (Test_screenHeight - 10)))
//					},
//					velocity,
//					12,
//					"res/10.png"
//				);
//				Test_RootTree.insert(&Test_critters[i]);
//			}
//
//
//			Assert::IsTrue(Test_RootTree.Get_QTree_childen() != nullptr);
//		}
//	};
//
//	
////}

int screenWidth = 800;
int screenHeight = 450;
const int CRITTER_COUNT = 30000;
const int MAX_VELOCITY = 80;
float delta = 1 ;
int Frame_Test_Count = 600;
Critter* Create_Array_Critters()
{
	//----------------------------------create some critters----------------------------------------------------
	Critter critters[CRITTER_COUNT];
	int Pick_Random_Dead = (rand() % CRITTER_COUNT);
	for (int i = 0; i < CRITTER_COUNT; i++) {
		Vector2 velocity = // create a random direction vector for the velocity
		{
			-100 + (rand() % 200),
			-100 + (rand() % 200)
		};
		velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY); // normalize and scale by a random speed
		critters[i].Init( // create a critter in a random location
			{
				(float)(5 + rand() % (screenWidth - 10)),
				(float)(5 + (rand() % (screenHeight - 10)))
			},
			velocity,
			12,
			"res/10.png"
		);

		if (i == Pick_Random_Dead)
		{
			critters[i].Destroy();
		}
	}
	return critters;
}

std::stack<Critter> Create_Stack_Critters()
{
	//----------------------------------create some critters----------------------------------------------------
	Critter critters[CRITTER_COUNT];
	std::stack<Critter> Deadstack;
	int Pick_Random_Dead = rand() % (CRITTER_COUNT);
	for (int i = 0; i < CRITTER_COUNT; i++) {
		Vector2 velocity = // create a random direction vector for the velocity
		{
			-100 + (rand() % 200),
			-100 + (rand() % 200)
		};
		velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY); // normalize and scale by a random speed
		critters[i].Init( // create a critter in a random location
			{
				(float)(5 + rand() % (screenWidth - 10)),
				(float)(5 + (rand() % (screenHeight - 10)))
			},
			velocity,
			12,
			"res/10.png"
		);

		if (i == Pick_Random_Dead)
		{
			critters[i].Destroy();
			Deadstack.push(critters[i]);
		}
	}
	return Deadstack;
}

QTree Create_Test_QuadTree()
{
	Vector2 ScreenSize = { screenWidth , screenHeight };
	std::pair<Vector2, Vector2> QTree_Starting_boundry = { ScreenSize,{0,0} };
	QTree Test_RootTree(QTree_Starting_boundry, ScreenSize, nullptr); // The Null pointer is there to igoure the need of  a destoyer
	Critter* Test_Critter_Array_Insert = Create_Array_Critters();
	for (int i = 0; i < CRITTER_COUNT; i++)
	{
		Test_RootTree.insert(&Test_Critter_Array_Insert[i]);
	}

	return Test_RootTree;
}

namespace Object_Pooling 
{

	TEST_CLASS(Array_VS_Stack)
	{
	public:

		Critter* Test_Critter_Arrays = Create_Array_Critters();
		Critter Test_Critter_Stack = Create_Stack_Critters().top();
		TEST_METHOD(Array_Search)
		{
			for (int Loop_Frames = 0; Loop_Frames < Frame_Test_Count; Loop_Frames++)
			{
				for (int i = 0; i < CRITTER_COUNT; i++)
				{
					if (Test_Critter_Arrays[i].IsLoaded() == false)
					{
						Assert::IsTrue(Test_Critter_Arrays[i].IsLoaded() == false);
					}
				}
			}

		};
		TEST_METHOD(Stack_Search)
		{
			for (int Loop_Frames = 0; Loop_Frames < Frame_Test_Count; Loop_Frames++)
			{
				Assert::IsTrue(Test_Critter_Stack.IsLoaded() == false);
			}
		}
	};
}

namespace QuadTree 
{
	QTree Test_RootQuadTree = Create_Test_QuadTree();

	Critter* critters = Create_Array_Critters();
	
	TEST_CLASS(QuadTree_VS_Double_Loop)
	{
		TEST_METHOD(Double_Loop_collision)
		{
			for (int Loop_Frames = 0; Loop_Frames < Frame_Test_Count; Loop_Frames++) 
			{
				for (int i = 0; i < CRITTER_COUNT; i++) {
					for (int j = 0; j < CRITTER_COUNT; j++) {
						if (i == j || critters[i].IsDirty()) continue; // note: the other critter (j) could be dirty - that's OK    
						// check every critter against every other critter
						float dist = Vector2Distance(critters[i].GetPosition(), critters[j].GetPosition());
						if (dist < critters[i].GetRadius() + critters[j].GetRadius()) {// <-- collision!.. do math to get critters bouncing
							Vector2 normal = Vector2Normalize(Vector2Subtract(critters[j].GetPosition(), critters[i].GetPosition()));
							critters[i].SetVelocity(Vector2Scale(normal, -MAX_VELOCITY)); // not even close to real physics, but fine for our needs
							critters[i].SetDirty(); // set the critter to *dirty* so we know not to process any more collisions on it
							// we still want to check for collisions in the case where 1 critter is dirty - so we need a check 
							// to make sure the other critter is clean before we do the collision response
							if (!critters[j].IsDirty()) {
								critters[j].SetVelocity(Vector2Scale(normal, MAX_VELOCITY));
								critters[j].SetDirty();
							}
							break;
						}
					}
				}
			}
		};

		TEST_METHOD(QuadTree_collision) 
		{
			for (int Loop_Frames = 0; Loop_Frames < Frame_Test_Count; Loop_Frames++)
			{
				Test_RootQuadTree.Update_QTree(MAX_VELOCITY, delta);
			}
		}
	};
}