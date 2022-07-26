#include "AITarget.h"
#include "Condition.h"
#include "State.h"
#include "UtilityAI.h"
#include "FiniteStateMachine.h"

AITarget::AITarget(NodeGraph* graph) : AIObject(graph)
{
    SetCostume("Target");


    InitSprites();


    // set up a FSM, we're going to have two states with their own conditions
    SqrDistanceCondition* furtherThan15 = new SqrDistanceCondition(15.0f * AIAgent->pathAgent->parentGraph->m_cellSize, false);
    SeeSuspiciousCondition* seesSuspiciousTarget = new SeeSuspiciousCondition(400, 50, .25);

    UtilityAI* utilityUnAlert = new UtilityAI();
    utilityUnAlert->AddBehaviour(new GoToImportantBehaviour(0.2f));
    utilityUnAlert->AddBehaviour(new LingerBehaviour(200));
    utilityUnAlert->AddBehaviour(new GoToToiletBehaviour(1));

    UtilityAI* utilityAlert = new UtilityAI();
    utilityAlert->AddBehaviour(new FleeTargetBehaviour(20));

    // register these states with the FSM, so its responsible for deleting them now
    State* UnAlertState = new State(utilityUnAlert);
    State* AlertState = new State(utilityAlert);

    UnAlertState->AddTransition(seesSuspiciousTarget, AlertState);
    //AlertState->AddTransition(furtherThan15, UnAlertState);

    // make a finite state machine that starts off lingering
    FiniteStateMachine* fsm = new FiniteStateMachine(UnAlertState);

    fsm->AddState(UnAlertState);

    AIAgent->SetBehaviour(fsm);



    AddToGameWorld();
}
