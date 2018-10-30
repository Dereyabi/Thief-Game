// GD1_Week1.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
using namespace tle;


void facingVector(IModel *guard, float &x, float &y, float &z);
bool sphere2sphere(float guardXPos, float guardZPos, float checkpointXPos, float checkpointZPos, float checkpointRad);
bool box2point(float tileXPos, float tileZPos, float thiefXPos, float thiefZPos, float tileWidth, float tileLength);
int arrayCycle(int& currentCheckpoint);

//constants
const int kNumDummies = 5;
const int kNumTiles = 6;

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

struct Tile
{
	float tileX;
	float tileY;
	float tileZ;
};



//starting states
guardState currentGuardState = Idle;
thiefState currentThiefState = Walking;
gameState currentGameState = Alive;


//array initialisation
Dummy dummies[kNumDummies];
Tile objTile[kNumTiles];


void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( "./Media" );

	/**** Set up your scene here ****/

	//variables
	int currentCheckpoint = 0;					//checkpoint cycles through dummies, guard goes to current checkpoint when patrolling 
	float forwardSpeed = 0.005f;				//speed forwards the thief is moving at 
	float backSpeed = 0.0025f;					//speed backwards the thief is moving at 
	float crouchingSpeed = 0.002f;				//speed forwards when in crouched, walking or running state
	float walkingSpeed = 0.005f;				
	float runningSpeed = 0.008f;				
	float backMovementMultiplier = 2.0f;		//forward speed divided by this to get back speed 
	float turnSpeed = 0.05f;					//speed of thief turning
	float guardSpeed = 0.002;					//forward speed of guard 
	float guardX;								//guard X,Y and Z location
	float guardY;
	float guardZ;
	float guardDetectionRange = 8.0f;			//units between guard and thief that will trigger the alert state
	float thiefEscapeRange = 12.0f;				//units between guard and thief to trigger the idle state
	float guardKillRange = 3.0f;				//range between the thief and guard to be able to kill the guard
	float thiefKillRange = 1.0f;				//range between the guard and thief to be able to kill the thief 

	//object position variables
	float cameraStartingX = 0.0f;				//starting positions of camera
	float cameraStartingY = 3.0f;
	float cameraStartingZ = -10.0f;
	float guardStartingX = 0.0f;				//starting positions of guard
	float guardStartingY = 0.0f;
	float guardStartingZ = 0.0f;
	float thiefStartingX = 0.0f;				//starting positions of thief
	float thiefStartingY = 0.0f;
	float thiefStartingZ = -50.0f;
	float guardStateStartingX = 0.0f;			//starting positions of guard state
	float guardStateStartingY = 5.0f;
	float guardStateStartingZ = 0.0f;

	//guard state skin variables
	string idleSkin = "blue.png";
	string alertSkin = "red.png";
	string deadSkin = "purple.png";


	//Camera
	ICamera* myCamera;
	myCamera = myEngine->CreateCamera(kManual, cameraStartingX, cameraStartingY, cameraStartingZ);

	//Objects
	//Meshes
	IMesh* guardMesh = myEngine->LoadMesh("casual_A.x");
	IMesh* thiefMesh = myEngine->LoadMesh("sierra.x");
	IMesh* guardStateMesh = myEngine->LoadMesh("state.x");
	IMesh* dummyMesh = myEngine->LoadMesh("Dummy.x");
	IMesh* tileMesh = myEngine->LoadMesh("Square.x");

	//Models
	IModel* guard;
	IModel* thief;
	IModel* guardStateModel;
	IModel* dummy[kNumDummies];
	IModel* tile[kNumTiles];

	//Model Locations
	guard = guardMesh->CreateModel(guardStartingX, guardStartingY, guardStartingZ);
	thief = thiefMesh->CreateModel(thiefStartingX, thiefStartingY, thiefStartingZ);
	guardStateModel = guardStateMesh->CreateModel(guardStateStartingX, guardStateStartingY, guardStateStartingZ);

	//Skins
	guardStateModel->SetSkin(idleSkin);

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

	//Tiles
	//positions of tiles
	objTile[0] = { 10.0f, 0.0f, 30.0f };
	objTile[1] = { -30.0f, 0.0f, 0.0f };
	objTile[2] = { -15.0f, 0.0f, -50.0f };
	objTile[3] = { 35.0f, 0.0f, -50.0f };
	objTile[4] = { 50.0f, 0.0f, -50.0f };
	objTile[5] = { 0.0f, 0.0f, 0.0f };

	//creation of all tiles
	for (int i = 0; i < kNumTiles; i++)
	{
		tile[i] = tileMesh->CreateModel(objTile[i].tileX, objTile[i].tileY, objTile[i].tileZ);
	}


	//Chase Cam
	myCamera->AttachToParent(thief);
	//myCamera->AttachToParent(guard);
	guardStateModel->AttachToParent(guard);





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
				forwardSpeed = crouchingSpeed;
				backSpeed = crouchingSpeed/backMovementMultiplier;
				break;
			}
			case Walking:
			{
				forwardSpeed = walkingSpeed;
				backSpeed = walkingSpeed/backMovementMultiplier;
				break;
			}
			case Running:
			{
				forwardSpeed = runningSpeed;
				backSpeed = runningSpeed/backMovementMultiplier;
				break;
			}
			}
			//end of thief state


			//start of switch
			switch (currentGuardState)
			{
			case Idle:
			{

				guardStateModel->SetSkin(idleSkin);

				if (dotProduct > 0 && distanceCheck < guardDetectionRange)
				{
					currentGuardState = Alert;
				}
				else
				{
					currentGuardState = Idle;
				}

				if (distanceCheck < guardKillRange && myEngine->KeyHit(kKillKey))
				{
					currentGuardState = gDead;
				}

				if (sphere2sphere(guard->GetX(), guard->GetZ(), dummy[currentCheckpoint]->GetX(), dummy[currentCheckpoint]->GetZ(), 1))
				{
					arrayCycle(currentCheckpoint);
				}

				for (int i = 0; i < kNumTiles; i++)
				{
					if (currentThiefState == Walking && distanceCheck < guardDetectionRange && box2point(tile[i]->GetX(), tile[i]->GetZ(), thief->GetX(), thief->GetZ(), 1.0f , 1.0f ))
					{
						currentGuardState = Alert;
					}
					else if (currentThiefState == Running && distanceCheck < thiefEscapeRange && box2point(tile[i]->GetX(), tile[i]->GetZ(), thief->GetX(), thief->GetZ(), 1.0f, 1.0f))
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

				/*if (distanceCheck > thiefEscapeRange)
				{
					currentGuardState = Idle;
				}*/
				if (distanceCheck < thiefKillRange)
				{
					currentGuardState = gDead;
					currentGameState = Dead;
				}

				break;
			}
			case gDead:
			{
				guardStateModel->SetSkin(deadSkin);


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
			guardStateModel->SetSkin(deadSkin);

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