#pragma once
#include "raylib.h"
#include "Critter.h" 
#include <vector>

class Critter;

class QTree
{
public :

	static const int QTree_Capacity = 4; // How many Critters can one Quad tree can have before branching off

	enum SubTree
	{
		nwTL_Side = 0,
		neTR_Side,
		swBL_Side,
		seBR_Side,
	};

	QTree();

	QTree(std::pair<Vector2, Vector2>, Vector2,Critter*);
	QTree(std::pair<Vector2, Vector2>, Vector2, QTree*,QTree*, int,Critter*);

	~QTree();

	bool insert(Critter*);
	bool Destoryer_insert(Critter*);

	std::pair<Vector2, Vector2> Create_Boundary(std::pair<Vector2, Vector2> Current_Boundary, int target_region);

	void Subdivide();
	//void Create_QTree_branch();
	//void remove(QTree* Tree_remove);

	void Update(float deltatime);
	void Draw();
	void Qtree_Debug();

	bool contains(Critter* Critter_contains , std::pair<Vector2, Vector2> Boundary);

	void Update_QTree(const int MAX_VELOCITY, float Delta_FramTime);
	void Critter_Update(const int MAX_VELOCITY, float delta_frameTime);
	void Critter_Collision_Critter(const int MAX_VELOCITY, float delta_frameTime);
	void Destoryer_Update(const int MAX_VELOCITY, float delta_frameTime);

	QTree** Get_QTree_childen() { return QTree_childen; }
	Critter** Get_QTree_Critters_DP() { return Critters_DP; }

	QTree* Tree_root;
	QTree* paranet_Root;
	int childen_regin_number;

	Vector2 ScreenBoundary;

	int No_critter_count = 0;
	int No_Active_child = 0;
	int Qtree_childen_No_critter = 0;

private:
			/*  Size - Postion	*/
	std::pair<Vector2, Vector2> Qtree_Boundary = { {-1,-1} , {-1,-1} }; 
	QTree** QTree_childen; // place holder for pointers that will point to childen
	Critter** Critters_DP; // dyymatic double pointer Array of Critters in it's regenion 
	Critter* Destoryer;

};

