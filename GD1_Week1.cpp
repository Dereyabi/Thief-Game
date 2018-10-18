// GD1_Week1.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
using namespace tle;


void facingVector(IModel *guard, float &x, float &y, float &z);
bool sphere2sphere(float guardXPos, float guardZPos, float checkpointXPos, float checkpointZPos, float checkpointRad);
bool box2point(float tileXPos, float tileZPos, float thiefXPos, float thiefZPos, float tileWidth, float tileLength);
int arrayCycle(int& currentCheckpoint);

//constants
const int kNumDummies = 5;
const int kNumSquares = 6;

//KeyCodes
EKeyCode kForwardKey = Key_W;
EKeyCode kBackKey = Key_S;
EKeyCode kLeftTurnKey = Key_A;
EKeyCode kRightTurnKey = Key_D;
EKeyCode kQuitKey = Key_Escape;
EKeyCode kKillKey = Key_E;


//enum
enum guardState {Idle, Alert, gDead};
enum thiefState {Crouching, Walking, Running};
enum gameState {Alive, Dead};


//structs
//dont need to do IModel here 
struct Dummy
{
	float dummyX;
	float dummyY;
	float dummyZ;
};

struct Square
{
	float squareX;
	float squareY;
	float squareZ;
};



//starting states
guardState currentGuardState = Idle;
thiefState currentThiefState = Walking;
gameState currentGameState = Alive;


//array initialisation
Dummy dummies[kNumDummies];
Square squares[kNumSquares];


void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( "./Media" );

	/**** Set up your scene here ****/
	//Camera
	ICamera* myCamera;
	myCamera = myEngine->CreateCamera(kManual, 0.0f, 3.0f, -10.0f);

	//Objects
	//Meshes
	IMesh* guardMesh = myEngine->LoadMesh("casual_A.x");
	IMesh* thiefMesh = myEngine->LoadMesh("sierra.x");
	IMesh* guardStateMesh = myEngine->LoadMesh("state.x");
	IMesh* dummyMesh = myEngine->LoadMesh("Dummy.x");
	IMesh* squareMesh = myEngine->LoadMesh("Square.x");

	//Models
	IModel* guard;
	IModel* thief;
	IModel* guardStateModel;
	IModel* dummy[kNumDummies];
	IModel* square[kNumSquares];

	//Model Locations
	guard = guardMesh->CreateModel(0, 0, 0);
	thief = thiefMesh->CreateModel(0, 0, -50);
	guardStateModel = guardStateMesh->CreateModel(0, 5, 0);

	//Skins
	guardStateModel->SetSkin("blue.png");

	//Dummies
	//positions of all dummies
	dummies[0] = { 0.0f, 0.0f, 40.0f };
	dummies[1] = { -40.0f, 0.0f, 10.0f };
	dummies[2] = { -25.0f, 0.0f, -40.0f };
	dummies[3] = { 25.0f, 0.0f, -40.0f };
	dummies[4] = { 40.0f, 0.0f, 10.0f };
	
	//creation of all dummies
	for (int i = 0; i < kNumDummies; i++)																				
	{
		dummy[i] = dummyMesh->CreateModel(dummies[i].dummyX, dummies[i].dummyY, dummies[i].dummyZ);
	}

	//Squares
	//positions of squares
	squares[0] = { 10.0f, 0.0f, 30.0f };
	squares[1] = { -30.0f, 0.0f, 0.0f };
	squares[2] = { -15.0f, 0.0f, -50.0f };
	squares[3] = { 35.0f, 0.0f, -50.0f };
	squares[4] = { 50.0f, 0.0f, -50.0f };
	squares[5] = { 0.0f, 0.0f, 0.0f };

	//creation of all squares
	for (int i = 0; i < kNumSquares; i++)
	{
		square[i] = squareMesh->CreateModel(squares[i].squareX, squares[i].squareY, squares[i].squareZ);
	}


	//Chase Cam
	myCamera->AttachToParent(thief);
	//myCamera->AttachToParent(guard);
	guardStateModel->AttachToParent(guard);

	//variables
	int currentCheckpoint = 0;
	float forwardSpeed = 0.005f;
	float backSpeed = 0.0025f;
	float turnSpeed = 0.05f;
	float guardSpeed = 0.002;
	float guardX;
	float guardY;
	float guardZ;



	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/
		//start of game state switch
		switch (currentGameState)
		{
		case Alive:
		{
			//Thief Movement
			if (myEngine->KeyHeld(kForwardKey))
			{
				thief->MoveLocalZ(forwardSpeed);
			}

			if (myEngine->KeyHeld(kBackKey))
			{
				thief->MoveLocalZ(-backSpeed);
			}

			if (myEngine->KeyHeld(kLeftTurnKey))
			{
				thief->RotateLocalY(-turnSpeed);
			}

			if (myEngine->KeyHeld(kRightTurnKey))
			{
				thief->RotateLocalY(turnSpeed);
			}
			if (myEngine->KeyHit(Key_1))
			{
				currentThiefState = Crouching;
			}
			if (myEngine->KeyHit(Key_2))
			{
				currentThiefState = Walking;
			}
			if (myEngine->KeyHit(Key_3))
			{
				currentThiefState = Running;
			}

			//Distance from guard to thief, can he see the thief? length of vector
			float xDistCheck = thief->GetX() - guard->GetX();
			float zDistCheck = thief->GetZ() - guard->GetZ();
			float distanceCheck = sqrt((xDistCheck*xDistCheck) + (zDistCheck*zDistCheck));



			//facing vector of guard
			guardX = guard->GetX();
			guardY = guard->GetY();
			guardZ = guard->GetZ();
			facingVector(guard, guardX, guardY, guardZ);

			float dotProduct = ((xDistCheck*guardX) + (zDistCheck*guardZ));


			//start of switch
			switch (currentThiefState)
			{
			case Crouching:
			{
				forwardSpeed = 0.002;
				backSpeed = 0.001;
				break;
			}
			case Walking:
			{
				forwardSpeed = 0.005;
				backSpeed = 0.0025;
				break;
			}
			case Running:
			{
				forwardSpeed = 0.008;
				backSpeed = 0.004;
				break;
			}
			}
			//end of thief state


			//start of switch
			switch (currentGuardState)
			{
			case Idle:
			{

				guardStateModel->SetSkin("blue.png");

				if (dotProduct > 0 && distanceCheck < 8.0f)
				{
					currentGuardState = Alert;
				}
				else
				{
					currentGuardState = Idle;
				}

				if (distanceCheck < 3.0f && myEngine->KeyHit(kKillKey))
				{
					currentGuardState = gDead;
				}

				if (sphere2sphere(guard->GetX(), guard->GetZ(), dummy[currentCheckpoint]->GetX(), dummy[currentCheckpoint]->GetZ(), 1))
				{
					arrayCycle(currentCheckpoint);
				}

				for (int i = 0; i < kNumSquares; i++)
				{
					if (box2point(currentThiefState == Walking && distanceCheck < 8.0f && square[i]->GetX(), square[i]->GetZ(), thief->GetX(), thief->GetZ(), 1.0f , 1.0f ))
					{
						currentGuardState = Alert;
					}
					else if (currentThiefState == Running && distanceCheck < 12.0f && box2point(square[i]->GetX(), square[i]->GetZ(), thief->GetX(), thief->GetZ(), 1.0f, 1.0f))
					{
						currentGuardState = Alert;
					}
				}

				guard->LookAt(dummy[currentCheckpoint]);
				guard->MoveLocalZ(guardSpeed);

				break;
			}
			case Alert:
			{

				guardStateModel->SetSkin("red.png");
				guard->LookAt(thief);
				guard->MoveLocalZ(guardSpeed);

				/*if (distanceCheck > 12.0f)
				{
					currentGuardState = Idle;
				}*/
				if (distanceCheck < 1.0f)
				{
					currentGuardState = gDead;
					currentGameState = Dead;
				}

				break;
			}
			case gDead:
			{
				guardStateModel->SetSkin("purple.png");


				break;
			}
			}
			//end of guard state	
			break;
		}
		//end of alive state
		case Dead:
		{
			thief->RotateLocalY(0.5);
			guardStateModel->SetSkin("purple.png");

			break;
		}
		}
		//end of game state switch

		if (myEngine->KeyHit(kQuitKey))
		{
			myEngine->Stop();
		}
	}
	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}

void facingVector(IModel *guard, float &x, float &y, float &z)
{
	float guardMatrix[16];

	guard->GetMatrix(guardMatrix);

	x = guardMatrix[8];
	y = guardMatrix[9];
	z = guardMatrix[10];
}

int arrayCycle(int& currentCheckpoint)
{
	currentCheckpoint = (currentCheckpoint + 1) % kNumDummies;

	return currentCheckpoint;
}

bool sphere2sphere(float guardXPos, float guardZPos, float checkpointXPos, float checkpointZPos, float checkpointRad)
{
	float distX = checkpointXPos - guardXPos;
	float distZ = checkpointZPos - guardZPos;
	float distance = sqrt(distX*distX + distZ * distZ);

	return(distance < (checkpointRad));
}

bool box2point(float tileXPos, float tileZPos, float thiefXPos, float thiefZPos, float tileWidth, float tileLength)
{
	float distX = tileXPos - thiefXPos;
	float distZ = tileZPos - thiefZPos;
	float distance = sqrt(distX*distX + distZ * distZ);

	if (distance < (tileWidth) || distance < (tileLength))
	{
		return (true);
	}
	return (false);
}