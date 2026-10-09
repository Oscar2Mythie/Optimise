#include "QTree.h"
#include "iostream"
#include "raymath.h"
QTree::QTree() : Critters_DP(nullptr), QTree_childen(nullptr)
{

}

QTree::QTree(std::pair<Vector2, Vector2> Boundary, Vector2 ScreenBoundary, Critter* Destoryer) : Qtree_Boundary(Boundary), ScreenBoundary(ScreenBoundary), Destoryer(Destoryer), Tree_root(this), Critters_DP(nullptr), QTree_childen(nullptr)
{

}

QTree::QTree(std::pair<Vector2, Vector2> Boundary, Vector2 ScreenBoundary, QTree* Tree_root, QTree* paranet_Root, int childen_regin_number,Critter* Destoryer) : Qtree_Boundary(Boundary), ScreenBoundary(ScreenBoundary), Tree_root(Tree_root), paranet_Root(paranet_Root), childen_regin_number(childen_regin_number), Destoryer(Destoryer), Critters_DP(nullptr), QTree_childen(nullptr)
{
	//Qtree_Debug();
}

QTree::~QTree()
{
	if (QTree_childen != nullptr)  // If QTree_childen pointer is not null, Delete all childen then delete and set self to a null pointer.
	{
		for (int i = 0; i < 4; i++) // iterate though all info/data contained inside QTree_childen and delete it
		{
			if (QTree_childen[i] == nullptr) { continue; }
			
			delete QTree_childen[i];
		}

		// delete self and set pointer to nullpointer
	}
	delete[] QTree_childen;
	QTree_childen = nullptr;

	if (Critters_DP != nullptr)  // If QTree_Critter_DP_Array pointer is not null, Delete all childen then delete and set self to a null pointer.
	{
		for (int i = 0; i < QTree_Capacity; i++) // iterate though all info/data contained inside QTree_Critter_DP_Array and delete it
		{
			if (Critters_DP[i] == nullptr) { continue; }
			
			if (Critters_DP[i] != nullptr)
			{
				 Critters_DP[i] = nullptr;
			}



		}
		// delete self and set pointer to nullpointer
	}

	delete[] Critters_DP;
	Critters_DP = nullptr;

	//delete this;
}

bool QTree::insert(Critter* New_Critter) 
{
	if (this == NULL) { return false; }

	if (!contains(New_Critter,Qtree_Boundary)|| New_Critter->IsDead()) 
	{
		return false;
	}

	if (QTree_childen == nullptr)
	{
		if (Critters_DP == nullptr)
		{
			Critters_DP = new Critter*[QTree_Capacity];
			memset(Critters_DP, 0, sizeof(Critter*) * QTree_Capacity);
		}

		if (Critters_DP[QTree_Capacity - 1] == nullptr) 
		{
			for (int i = 0; i < QTree_Capacity; i++) 
			{
				if (Critters_DP[i] == nullptr) 
				{
					Critters_DP[i] = New_Critter;
					return true;
				}
			}
		}

		Subdivide();
	}

	if (QTree_childen != nullptr) 
	{
	
		std::pair<Vector2, Vector2> Test_region;

		for (int  i = 0; i < 4; i++)
		{	
			
			Test_region = Create_Boundary(Qtree_Boundary, i);
			
			if (QTree_childen[i] != nullptr) 
			{
				if (QTree_childen[i]->insert(New_Critter) == true)
				{
					return true;
				}
			}
			else if (QTree::contains(New_Critter,Test_region)) // Check where the critter has entered using the New make new bountry 
			{
				QTree* new_paranet_Root = this;
				QTree_childen[i] = new QTree(Test_region, ScreenBoundary, Tree_root, new_paranet_Root,i,Destoryer);

				if (QTree_childen[i]->insert(New_Critter) == true)
				{
					return true;
				}
			}
		}
	}

	for (int i = 0; i < 4; i++) 
	{
		if (QTree_childen[i]->insert(New_Critter) == true)
		{
			return true;
		}
	}

	return false;
}

bool QTree::Destoryer_insert(Critter* Destoryer)
{
	if (this == NULL) { return false; }

	if (!contains(Destoryer, Qtree_Boundary))
	{
		return false;
	}
}

std::pair<Vector2, Vector2> QTree::Create_Boundary(std::pair<Vector2, Vector2> Current_Boundary, int target_region)
{
														// Size on the x axis			// size on the y axis		// X and Y postion
	std::pair<Vector2, Vector2> New_Qtree_Boundary = { {(Current_Boundary.first.x / 2),(Current_Boundary.first.y / 2)}, Current_Boundary.second};

	switch (target_region) 
	{
	case 0 :
		return New_Qtree_Boundary;

	case 1 :
		New_Qtree_Boundary.second.x = (New_Qtree_Boundary.second.x + New_Qtree_Boundary.first.x);
		return New_Qtree_Boundary;

	case 2 :
		New_Qtree_Boundary.second.y = (New_Qtree_Boundary.second.y + New_Qtree_Boundary.first.y);
		return New_Qtree_Boundary;

	case 3 :
		New_Qtree_Boundary.second = { (New_Qtree_Boundary.second.x + New_Qtree_Boundary.first.x),(New_Qtree_Boundary.second.y + New_Qtree_Boundary.first.y) };
		return New_Qtree_Boundary;
	};
}

void QTree::Subdivide()
{
	QTree_childen = new QTree* [4];
	QTree* new_paranet_Root = this;

	QTree_childen[nwTL_Side] = new QTree(Create_Boundary(Qtree_Boundary, nwTL_Side), ScreenBoundary, Tree_root, new_paranet_Root, nwTL_Side,Destoryer); // make an new Qtree with the New Boundary size and starting postion [Top Left]

	QTree_childen[neTR_Side] = new QTree(Create_Boundary(Qtree_Boundary, neTR_Side), ScreenBoundary, Tree_root, new_paranet_Root, neTR_Side,Destoryer); // make an new Qtree with the New Boundary size and new x postion [Top Right]

	QTree_childen[swBL_Side] = new QTree(Create_Boundary(Qtree_Boundary, swBL_Side), ScreenBoundary,Tree_root, new_paranet_Root, swBL_Side, Destoryer); // make an new Qtree with the New Boundary size and new y postion [bottom left]

	QTree_childen[seBR_Side] = new QTree(Create_Boundary(Qtree_Boundary, seBR_Side), ScreenBoundary, Tree_root, new_paranet_Root, seBR_Side,Destoryer); // make an new Qtree with the New Boundary size and the new x plus y postions. [bottom right]

	if (Critters_DP != nullptr) 
	{
		for (int i = 0; i < QTree_Capacity; i++) 
		{
			if (Critters_DP[i] == nullptr)
			{
				continue;
			}

			for (int j = 0; j < 4; j++)
			{
				if (QTree_childen[j]->insert(Critters_DP[i]) == true)
				{
					break;
				}
			}

			Critters_DP[i] = nullptr;
		}
		delete Critters_DP;
		Critters_DP = nullptr;

	}
}

void QTree::Update_QTree(const int MAX_VELOCITY, float delta_frameTime)
{
	No_critter_count = 0;
	if (QTree_childen == nullptr) 
	{
		Critter_Update(MAX_VELOCITY,delta_frameTime);
		//Destoryer_Update(MAX_VELOCITY, delta_frameTime);
	}
	else if (QTree_childen != nullptr)
	{
		No_Active_child = 0;
		for (int i = 0; i < 4; i++)
		{
			if (QTree_childen[i] == nullptr) 
			{
				No_Active_child++;
				
				if (No_Active_child > 3) 
				{
					if (paranet_Root != nullptr) 
					{
						if (paranet_Root->QTree_childen != nullptr)
						{
							if (paranet_Root->QTree_childen[childen_regin_number] != nullptr)
							{
								paranet_Root->QTree_childen[childen_regin_number] = nullptr;

									delete this; 
							}
						}
					}
				}
				continue; 
			}
			
			if (QTree_childen[i] != nullptr)
			{
				QTree_childen[i]->Update_QTree(MAX_VELOCITY, delta_frameTime);

				if (QTree_childen[i] == nullptr) { continue; }

				if (QTree_childen[i]->No_critter_count < QTree_Capacity) 
				{
					QTree_childen[i]->No_critter_count = 0;
				}
				else
				{
					delete QTree_childen[i];
					QTree_childen[i] = nullptr;
					No_critter_count++;
				}

			}

		}
	}

}

void QTree::Critter_Update(const int MAX_VELOCITY, float delta_frameTime)
{
	Critter_Collision_Critter(MAX_VELOCITY, delta_frameTime);

	for (int i = 0; i < QTree_Capacity; i++) {

		if (Critters_DP == nullptr) { No_critter_count = 4; break; }

		if (Critters_DP[i] == nullptr) { No_critter_count++; continue; }

		Critters_DP[i]->Update(delta_frameTime);

		//update the Critters_DP  by check against screen bounds
		Critters_DP[i]->Update(delta_frameTime);
		if (Critters_DP[i]->GetX() < 0) {
			Critters_DP[i]->SetX(0);
			Critters_DP[i]->SetVelocity(Vector2{ -Critters_DP[i]->GetVelocity().x, Critters_DP[i]->GetVelocity().y });
		}
		if (Critters_DP[i]->GetX() > ScreenBoundary.x) {
			Critters_DP[i]->SetX(ScreenBoundary.x);
			Critters_DP[i]->SetVelocity(Vector2{ -Critters_DP[i]->GetVelocity().x, Critters_DP[i]->GetVelocity().y });
		}
		if (Critters_DP[i]->GetY() < 0) {
			Critters_DP[i]->SetY(0);
			Critters_DP[i]->SetVelocity(Vector2{ Critters_DP[i]->GetVelocity().x, -Critters_DP[i]->GetVelocity().y });
		}
		if (Critters_DP[i]->GetY() > ScreenBoundary.y) {
			Critters_DP[i]->SetY(ScreenBoundary.y);
			Critters_DP[i]->SetVelocity(Vector2{ Critters_DP[i]->GetVelocity().x, -Critters_DP[i]->GetVelocity().y });
		}


		//check each critter against Qtree bounds
		if (Critters_DP[i]->GetX() < Qtree_Boundary.second.x)
		{
			Tree_root->insert(Critters_DP[i]);
			Critters_DP[i] = nullptr;
		}
		else if (Critters_DP[i]->GetX() > Qtree_Boundary.second.x + Qtree_Boundary.first.x)
		{
			Tree_root->insert(Critters_DP[i]);
			Critters_DP[i] = nullptr;
		}
		else if (Critters_DP[i]->GetY() < Qtree_Boundary.second.y)
		{
			Tree_root->insert(Critters_DP[i]);
			Critters_DP[i] = nullptr;
		}
		else if (Critters_DP[i]->GetY() > Qtree_Boundary.second.y + Qtree_Boundary.first.y)
		{
			Tree_root->insert(Critters_DP[i]);
			Critters_DP[i] = nullptr;
		}
	}

	if (Critters_DP == nullptr) 
	{ 
		if (paranet_Root != nullptr) 
		{
			paranet_Root->QTree_childen[childen_regin_number] = nullptr;
			delete this;
		}
	}

	//for (int i = 0; i < QTree_Capacity; i++) {

	//	if (Critters_DP == nullptr) { break; }

	//	if (Critters_DP[i] == nullptr) { continue; }
	//	 kill any critter touching the destroyer
	//	 simple circle-to-circle collision check
	//	float dist = Vector2Distance(Critters_DP[i]->GetPosition(), Critters_DP[i]->GetPosition());
	//	if (dist < Critters_DP[i]->GetRadius() + Destoryer->GetRadius()) {
	//		Critters_DP[i]->Destroy();// <-- this would be the perfect time to put the critter into an object pool
	//		Critters_DP[i] = nullptr;
	//	}
	//}

}

void QTree::Critter_Collision_Critter(const int MAX_VELOCITY, float delta_frameTime)
{
	// check for critter-on-critter collisions
for (int i = 0; i < QTree_Capacity; i++) {

	if (Critters_DP == nullptr) { break; }

	if (Critters_DP[i] == nullptr) { continue; }

	for (int j = 0; j < QTree_Capacity; j++) {

		if (Critters_DP[j] == nullptr) { continue; }

		if (i == j || Critters_DP[i]->IsDirty()) continue; // note: the other critter (j) could be dirty - that's OK    
		// check every critter against every other critter
		float dist = Vector2Distance(Critters_DP[i]->GetPosition(), Critters_DP[j]->GetPosition());
		if (dist < Critters_DP[i]->GetRadius() + Critters_DP[j]->GetRadius()) {// <-- collision!.. do math to get critters bouncing
			Vector2 normal = Vector2Normalize(Vector2Subtract(Critters_DP[j]->GetPosition(), Critters_DP[i]->GetPosition()));

			if (isnan(normal.x) || isnan(normal.y))
			{
				normal = { (float)(rand() % 100 / 100),(float)(rand() % 100 / 100) };
			}

			Critters_DP[i]->SetVelocity(Vector2Scale(normal, -MAX_VELOCITY)); // not even close to real physics, but fine for our needs
			Critters_DP[i]->SetDirty(); // set the critter to *dirty* so we know not to process any more collisions on it
			// we still want to check for collisions in the case where 1 critter is dirty - so we need a check 
			// to make sure the other critter is clean before we do the collision response
			if (!Critters_DP[j]->IsDirty()) {
				Critters_DP[j]->SetVelocity(Vector2Scale(normal, MAX_VELOCITY));
				Critters_DP[j]->SetDirty();
			}
			break;
		}
	}
}
}

void QTree::Destoryer_Update(const int MAX_VELOCITY, float delta_frameTime) 
{
	Destoryer->Update(delta_frameTime);
	if (Destoryer->GetX() < 0) {
		Destoryer->SetX(0);
		Destoryer->SetVelocity(Vector2{ -Destoryer->GetVelocity().x, Destoryer->GetVelocity().y });
	}
	if (Destoryer->GetX() > ScreenBoundary.x) {
		Destoryer->SetX(ScreenBoundary.x);
		Destoryer->SetVelocity(Vector2{ -Destoryer->GetVelocity().x, Destoryer->GetVelocity().y });
	}
	if (Destoryer->GetY() < 0) {
		Destoryer->SetY(0);
		Destoryer->SetVelocity(Vector2{ Destoryer->GetVelocity().x, -Destoryer->GetVelocity().y });
	}
	if (Destoryer->GetY() > ScreenBoundary.y) {
		Destoryer->SetY(ScreenBoundary.y);
		Destoryer->SetVelocity(Vector2{ Destoryer->GetVelocity().x, -Destoryer->GetVelocity().y });
	}
}

void QTree::Draw() 
{
	Color child_Boundary;

	if (QTree_childen == nullptr) 
	{
		child_Boundary = WHITE;

		DrawLine(Qtree_Boundary.second.x, Qtree_Boundary.second.y, Qtree_Boundary.second.x + Qtree_Boundary.first.x, Qtree_Boundary.second.y, child_Boundary); // Top left to Top right

		DrawLine(Qtree_Boundary.second.x, Qtree_Boundary.second.y, Qtree_Boundary.second.x, Qtree_Boundary.second.y + Qtree_Boundary.first.y, child_Boundary); // Top Left to Bottom left

		DrawLine(Qtree_Boundary.second.x + Qtree_Boundary.first.x, Qtree_Boundary.second.y, Qtree_Boundary.second.x + Qtree_Boundary.first.x, Qtree_Boundary.second.y + Qtree_Boundary.first.y, child_Boundary); // Top right to bottm right

		DrawLine(Qtree_Boundary.second.x, Qtree_Boundary.second.y + Qtree_Boundary.first.y, Qtree_Boundary.second.x + Qtree_Boundary.first.x, Qtree_Boundary.second.y + Qtree_Boundary.first.y, child_Boundary); // bottom left to bottm right
	}
	else
	{
			child_Boundary = BLACK;	
	}
	
	DrawLine(Qtree_Boundary.second.x, Qtree_Boundary.second.y,Qtree_Boundary.second.x + Qtree_Boundary.first.x, Qtree_Boundary.second.y, child_Boundary); // Top left to Top right

	DrawLine(Qtree_Boundary.second.x, Qtree_Boundary.second.y,Qtree_Boundary.second.x,Qtree_Boundary.second.y + Qtree_Boundary.first.y, child_Boundary); // Top Left to Bottom left

	DrawLine(Qtree_Boundary.second.x + Qtree_Boundary.first.x, Qtree_Boundary.second.y, Qtree_Boundary.second.x + Qtree_Boundary.first.x,Qtree_Boundary.second.y + Qtree_Boundary.first.y, child_Boundary); // Top right to bottm right

	DrawLine(Qtree_Boundary.second.x, Qtree_Boundary.second.y + Qtree_Boundary.first.y, Qtree_Boundary.second.x + Qtree_Boundary.first.x,Qtree_Boundary.second.y + Qtree_Boundary.first.y, child_Boundary); // bottom left to bottm right

	if (QTree_childen != nullptr)  // if QTree_childen is not a nullpointer, draw  childen 
	{
		for (int i = 0; i < 4; i++) 
		{	
			if (QTree_childen[i] != nullptr && QTree_childen[i] != 0)
			{
				QTree_childen[i]->Draw();
			}
		}
	}

	if (Critters_DP != nullptr) // if Critters_DP is not a null pointer, draw Criiters.
	{
		for (int i = 0; i < 4; i++) 
		{
			if (Critters_DP[i] != nullptr) 
			{
				Critters_DP[i]->Draw();
			}
		}
	}


}

void QTree::Qtree_Debug()
{
	std::cout << "Logic reached here" << std::endl;
	std::cout << sizeof(Critter) << std::endl;
}

bool QTree::contains(Critter* critter, std::pair<Vector2, Vector2> Boundary)
{
	Vector2 pos = critter->GetPosition();

	return

		pos.x >= Boundary.second.x &&

		pos.x < Boundary.second.x + Boundary.first.x &&

		pos.y >= Boundary.second.y &&

		pos.y < Boundary.second.y + Boundary.first.y;

}