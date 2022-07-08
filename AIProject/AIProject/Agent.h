#pragma once
#include "Pathfinding.h"
#include "Behaviour.h"
using namespace Behaviours;
using namespace Pathfinding;

class Agent
{
public:
    Agent();
    Agent(Behaviour* _behaviour);
    ~Agent() { 
        delete currentBehaviour;
        delete pathAgent;
    }

    void Update(float deltaTime);
    void Draw();

    void CreatePathAgent(PhysicsComponent* ownerPhysicsComp) {
        pathAgent = new PathAgent(ownerPhysicsComp);
    };

    void SetBehaviour(Behaviour* behaviour);


    void SetColour(Color colour) {
        m_colour = colour;
    }

    void FaceTarget();


    PathAgent* pathAgent;
    Object* target;



private:
    Behaviour* currentBehaviour;
    Color m_colour = ORANGE;
};

