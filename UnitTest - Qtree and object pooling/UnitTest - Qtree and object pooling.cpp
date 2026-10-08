//#include "raymath.h"
//#include "raylib.h"
#include "CppUnitTest.h"
#include "../CDDS_Optimise/Critter.h"
#include "../CDDS_Optimise/QTree.h"
#include <stack>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace QTree_ObjectPolling
{
	
	TEST_CLASS(Test_QTree)
	{
	public:
		
		TEST_METHOD(Collapsed)
		{
			int Test_screenWidth = 800;
			int Test_screenHeight = 450;
			Vector2 Test_ScreenSize = { Test_screenWidth , Test_screenHeight };
			int Test_Critter_Amount = 5;
			const int Test_MAX_VELOCITY = 0;

			Critter* Test_critters = new Critter[Test_Critter_Amount];



			Critter* destroyer = new Critter;
			Vector2 velocity =
			{
				-100 + (rand() % 200),
				-100 + (rand() % 200)
			};
			destroyer->Init(Vector2{ (float)(Test_screenWidth >> 1), (float)(Test_screenHeight >> 1) }, velocity, 20, "res/9.png");

			std::pair<Vector2, Vector2> Test_QTree_Starting_boundry = { Test_ScreenSize,{0,0} };

			QTree Test_RootTree(Test_QTree_Starting_boundry, Test_ScreenSize, destroyer);


			for (int i = 0; i < Test_Critter_Amount; i++)
			{

				Vector2 velocity = // create a random direction vector for the velocity
				{
					-100 + (rand() % 200),
					-100 + (rand() % 200)
				};

				Test_critters[i].Init( // create a critter in a random location
					{
						(float)(5 + rand() % (Test_screenWidth/2 - 10)),
						(float)(5 + (rand() % (Test_screenHeight/2 - 10)))
					},
					velocity,
					12,
					"res/10.png"
				);
				Test_RootTree.insert(&Test_critters[i]);
			}

			Test_RootTree.Update_QTree(Test_MAX_VELOCITY,0);
			QTree** Test_child = Test_RootTree.Get_QTree_childen();

			Assert::IsTrue(Test_RootTree.Get_QTree_childen() != nullptr);
			Assert::IsTrue(Test_child[0] != nullptr && Test_child[1] == nullptr && Test_child[2] == nullptr && Test_child[3] == nullptr);
		}
		TEST_METHOD(Respawn) 
		{
			int Test_screenWidth = 800;
			int Test_screenHeight = 450;
			Vector2 Test_ScreenSize = { Test_screenWidth , Test_screenHeight };
			int Test_Critter_Amount = 1;
			const int Test_MAX_VELOCITY = 0;

			Critter* Test_critters = new Critter[Test_Critter_Amount];

			Critter* destroyer = new Critter;
			Vector2 velocity =
			{
				-100 + (rand() % 200),
				-100 + (rand() % 200)
			};
			destroyer->Init(Vector2{ (float)(Test_screenWidth >> 1), (float)(Test_screenHeight >> 1) }, velocity, 20, "res/9.png");

			for (int i = 0; i < Test_Critter_Amount; i++)
			{

				Vector2 velocity = // create a random direction vector for the velocity
				{
					-100 + (rand() % 200),
					-100 + (rand() % 200)
				};

				Test_critters[i].Init( // create a critter in a random location
					{
						(float)(5 + rand() % (Test_screenWidth - 10)),
						(float)(5 + (rand() % (Test_screenHeight - 10)))
					},
					velocity,
					12,
					"res/10.png"
				);
			}

			std::stack<Critter*> DeadStack;

			std::pair<Vector2, Vector2> Test_QTree_Starting_boundry = { Test_ScreenSize,{0,0} };

			QTree Test_RootTree(Test_QTree_Starting_boundry, Test_ScreenSize, destroyer);

			Test_critters->Destroy();
			DeadStack.push(Test_critters);

			if (!DeadStack.empty())
			{
				DeadStack.top()->respawn({ 0,0 }, {0,0}, Test_ScreenSize);
				Test_RootTree.insert(DeadStack.top());
				DeadStack.pop();
			}

			Assert::IsTrue(Test_RootTree.Get_QTree_Critters_DP() != nullptr);
			Assert::IsTrue(DeadStack.empty());
		}
		TEST_METHOD(Subdivide)
		{
	
			int Test_screenWidth = 800;
			int Test_screenHeight = 450;
			Vector2 Test_ScreenSize = { Test_screenWidth , Test_screenHeight };
			int Test_Critter_Amount = 5;
			const int Test_MAX_VELOCITY = 0;

			Critter* Test_critters = new Critter[Test_Critter_Amount];

			Critter* destroyer = new Critter;
			Vector2 velocity =
			{
				-100 + (rand() % 200),
				-100 + (rand() % 200)
			};
			destroyer->Init(Vector2{ (float)(Test_screenWidth >> 1), (float)(Test_screenHeight >> 1) }, velocity, 20, "res/9.png");

			std::pair<Vector2, Vector2> Test_QTree_Starting_boundry = { Test_ScreenSize,{0,0} };

			QTree Test_RootTree(Test_QTree_Starting_boundry, Test_ScreenSize , destroyer);

			for (int i = 0; i < Test_Critter_Amount; i++)
			{

				Vector2 velocity = // create a random direction vector for the velocity
				{
					-100 + (rand() % 200),
					-100 + (rand() % 200)
				};

				Test_critters[i].Init( // create a critter in a random location
					{
						(float)(5 + rand() % (Test_screenWidth - 10)),
						(float)(5 + (rand() % (Test_screenHeight - 10)))
					},
					velocity,
					12,
					"res/10.png"
				);
				Test_RootTree.insert(&Test_critters[i]);
			}


			Assert::IsTrue(Test_RootTree.Get_QTree_childen() != nullptr);
		}
	};

	
}
