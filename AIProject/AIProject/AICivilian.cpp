#include "AICivilian.h"
#include "Condition.h"
#include "State.h"
#include "UtilityAI.h"
#include "FiniteStateMachine.h"
using namespace Conditions;

AICivilian::AICivilian(NodeGraph* graph) : AIObject(graph) {

    InitSprites();

    // Set up conditions
    SqrDistanceCondition* furtherThan15 = new SqrDistanceCondition(15.0f * AIAgent->pathAgent->parentGraph->m_cellSize, false);
    SeeSuspiciousCondition* seesSuspiciousTarget = new SeeSuspiciousCondition(400, 45, 1);

    // Create utility behaviours
    UtilityAI* utilityUnAlert = new UtilityAI();
    utilityUnAlert->AddBehaviour(new LingerBehaviour(50)); 
    utilityUnAlert->AddBehaviour(new GoToImportantBehaviour(0.05)); 
    
    UtilityAI* utilityAlert = new UtilityAI();
    utilityAlert->AddBehaviour(new FleeTargetBehaviour(20));

    // Add behaviour to fsm
    State* UnAlertState = new State(utilityUnAlert);
    State* AlertState = new State(utilityAlert);
    
    UnAlertState->AddTransition(seesSuspiciousTarget, AlertState);
    //AlertState->AddTransition(furtherThan15, UnAlertState);

    FiniteStateMachine* fsm = new FiniteStateMachine(UnAlertState);

    fsm->AddState(UnAlertState);

    AIAgent->SetBehaviour(fsm);



    AddToGameWorld();
}