#include "AIJanitor.h"
#include "Condition.h"
#include "State.h"
#include "UtilityAI.h"
#include "FiniteStateMachine.h"

AIJanitor::AIJanitor(NodeGraph* graph) : AIObject(graph)
{
    SetCostume("Janitor");

    InitSprites();

    // set up a FSM, we're going to have two states with their own conditions
    SeeSuspiciousCondition* seesSuspiciousTarget = new SeeSuspiciousCondition(400, 90, 1);
    NearUrgantSituationCondition* nearUrgentSituation = new NearUrgantSituationCondition(400);

    UtilityAI* utilityUnAlert = new UtilityAI();
    utilityUnAlert->AddBehaviour(new GoToImportantBehaviour(0.1f));
    utilityUnAlert->AddBehaviour(new LingerBehaviour(200));
    utilityUnAlert->AddBehaviour(new GoToToiletBehaviour(0.5));

    UtilityAI* utilityAlert = new UtilityAI();
    utilityAlert->AddBehaviour(new GoToImportantBehaviour(0.2f));

    FleeTargetBehaviour* fleeTarget = new FleeTargetBehaviour();

    // register these states with the FSM, so its responsible for deleting them now
    State* UnAlertState = new State(utilityUnAlert);
    State* AlertState = new State(utilityAlert);
    State* FleeTargetState = new State(fleeTarget);

    UnAlertState->AddTransition(seesSuspiciousTarget, FleeTargetState);
    UnAlertState->AddTransition(nearUrgentSituation, AlertState);
    // Alerted
    AlertState->AddTransition(seesSuspiciousTarget, FleeTargetState);
    FleeTargetState->AddTransition(seesSuspiciousTarget, AlertState, false);

    FiniteStateMachine* fsm = new FiniteStateMachine(UnAlertState);

    fsm->AddState(UnAlertState);

    AIAgent->SetBehaviour(fsm);



    AddToGameWorld();
}
