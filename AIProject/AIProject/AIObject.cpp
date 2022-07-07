#include "AIObject.h"
#include "Condition.h"
#include "State.h"

using namespace Conditions;

AIObject::AIObject(NodeGraph* graph)
{
	tag = "AI";
    physics->SetCollider(cType::Circle);
    ((CircleCollider*)physics->collider)->center = physics->GetPosition();
    ((CircleCollider*)physics->collider)->radius = 25;



    CreateAIAgent();
    AIAgent->m_pathAgent->SetParentGraph(graph);
    // set up a FSM, we're going to have two states with their own conditions
    SqrDistanceCondition* closerThan5 = new SqrDistanceCondition(5.0f * AIAgent->m_pathAgent->parentGraph->m_cellSize, true);
    SqrDistanceCondition* furtherThan7 = new SqrDistanceCondition(7.0f * AIAgent->m_pathAgent->parentGraph->m_cellSize, false);

    // register these states with the FSM, so its responsible for deleting them now
    State* lingerState = new State(new WanderBehaviour());
    State* followState = new State(new FollowTargetBehaviour());
    lingerState->AddTransition(closerThan5, followState);
    followState->AddTransition(furtherThan7, lingerState);

    // make a finite state machine that starts off wandering
    FiniteStateMachine* fsm = new FiniteStateMachine(lingerState);

    fsm->AddState(lingerState);
    fsm->AddState(followState);
    AIAgent->SetBehaviour(fsm);


    AIAgent->m_pathAgent->SetSpeed(100);
	AddToGameWorld();
}

AIObject::~AIObject()
{
	delete AIAgent;
}

void AIObject::CreateAIAgent(FiniteStateMachine* fsm)
{
	AIAgent = new Agent(fsm);
	AIAgent->CreatePathAgent(physics);
}
void AIObject::CreateAIAgent()
{
	AIAgent = new Agent();
	AIAgent->CreatePathAgent(physics);
}

void AIObject::Update(float DeltaTime)
{
    Object::Update(DeltaTime);
	AIAgent->Update(DeltaTime);

}

void AIObject::Draw()
{
    Object::Draw();
	AIAgent->Draw();
}
