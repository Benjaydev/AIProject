#include "AICivilian.h"
#include "Condition.h"
#include "State.h"
#include "UtilityAI.h"
#include "FiniteStateMachine.h"
using namespace Conditions;

AICivilian::AICivilian(NodeGraph* graph) : AIObject(graph) {
    spriteObject->LoadSprite((char*)"Images/CharacterM2.png");
    spriteObject->sprite->SetScale(0.5f);

    UtilityAI* utilityAI = new UtilityAI();
    utilityAI->AddBehaviour(new WanderBehaviour(20));
    utilityAI->AddBehaviour(new FollowTargetBehaviour(10));
    AIAgent->SetBehaviour(utilityAI);

    // set up a FSM, we're going to have two states with their own conditions
    SqrDistanceCondition* furtherThan15 = new SqrDistanceCondition(15.0f * AIAgent->pathAgent->parentGraph->m_cellSize, false);
    SeeCondition* seesTarget = new SeeCondition(400, 45, 1);

    UtilityAI* utilityUnAlert = new UtilityAI();
    utilityUnAlert->AddBehaviour(new GoToImportantBehaviour());
    utilityUnAlert->AddBehaviour(new LingerBehaviour(50));

    // register these states with the FSM, so its responsible for deleting them now
    State* UnAlertState = new State(utilityUnAlert);
    State* utilityState = new State(utilityUnAlert);
    
    //utilityUnAlert->AddTransition(seesTarget, utilityState);
    //utilityState->AddTransition(furtherThan15, lingerState);

    // make a finite state machine that starts off lingering
    FiniteStateMachine* fsm = new FiniteStateMachine(UnAlertState);

    fsm->AddState(UnAlertState);



    AIAgent->SetBehaviour(fsm);



    AddChild(spriteObject);
    spriteObject->physics->SetRotation(-90 * DEG2RAD);
    spriteObject->physics->SetPosition(-spriteObject->sprite->GetCentreOffset().x, spriteObject->sprite->GetCentreOffset().y);


    AddToGameWorld();
}