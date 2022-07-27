#pragma once
#include "Pathfinding.h"
#include "Behaviour.h"
using namespace Behaviours;
using namespace Pathfinding;

class Agent
{
public:
    Agent();
    Agent(Object* owningGameObject);
    Agent(Behaviour* _behaviour, Object* owningGameObject);
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
    Object* owner;
    bool active = true;

    Behaviour* currentBehaviour;
    Color m_colour = ORANGE;


};

