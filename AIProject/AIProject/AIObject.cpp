#include "AIObject.h"
#include "Condition.h"
#include "State.h"
#include "UtilityAI.h"

using namespace Conditions;

AIObject::AIObject(NodeGraph* graph)
{
	tag = "AI";
    spriteObject->LoadSprite((char*)"Images/CharacterM2.png");
    spriteObject->sprite->SetScale(0.5f);

    physics->SetCollider(cType::Circle);
    ((CircleCollider*)physics->collider)->center = physics->GetPosition();
    ((CircleCollider*)physics->collider)->radius = 25;

    CreateAIAgent();
    AIAgent->pathAgent->SetParentGraph(graph);

    UtilityAI* utilityAI = new UtilityAI();
    utilityAI->AddBehaviour(new WanderBehaviour(20));
    utilityAI->AddBehaviour(new FollowTargetBehaviour(10));
    AIAgent->SetBehaviour(utilityAI);


    //// set up a FSM, we're going to have two states with their own conditions
    //SqrDistanceCondition* closerThan10 = new SqrDistanceCondition(10.0f * AIAgent->pathAgent->parentGraph->m_cellSize, true);
    //SqrDistanceCondition* furtherThan15 = new SqrDistanceCondition(15.0f * AIAgent->pathAgent->parentGraph->m_cellSize, false);

    //// register these states with the FSM, so its responsible for deleting them now
    //State* lingerState = new State(new LingerBehaviour(200));
    //State* followState = new State(new FollowTargetBehaviour());
    //lingerState->AddTransition(closerThan10, followState);
    //followState->AddTransition(furtherThan15, lingerState);

    //// make a finite state machine that starts off wandering
    //FiniteStateMachine* fsm = new FiniteStateMachine(lingerState);

    //fsm->AddState(lingerState);
    //fsm->AddState(followState);
    //AIAgent->SetBehaviour(fsm);


    AIAgent->pathAgent->SetSpeed(100);


    AddChild(spriteObject);
    spriteObject->physics->SetRotation(-90 * DEG2RAD);
    spriteObject->physics->SetPosition(-spriteObject->sprite->GetCentreOffset().x, spriteObject->sprite->GetCentreOffset().y);

	AddToGameWorld();

    physics->deceleration = 10;
    physics->moveSpeed = 100;


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
