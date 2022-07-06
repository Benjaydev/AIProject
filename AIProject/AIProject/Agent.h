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
        delete m_current;
        delete m_pathAgent;
    }

    void Update(float deltaTime);
    void Draw();

    void CreatePathAgent(PhysicsComponent* ownerPhysicsComp) {
        m_pathAgent = new PathAgent(ownerPhysicsComp);
    };

    void SetBehaviour(Behaviour* behaviour);


    void SetColour(Color colour) {
        m_colour = colour;
    }

    PathAgent* m_pathAgent;
    Object* target;



private:
    Behaviour* m_current;
    Color m_colour = ORANGE;
};

