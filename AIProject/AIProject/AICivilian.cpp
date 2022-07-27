#include "AICivilian.h"
#include "Condition.h"
#include "State.h"
#include "UtilityAI.h"
#include "FiniteStateMachine.h"
using namespace Conditions;

AICivilian::AICivilian(NodeGraph* graph) : AIObject(graph) {

    InitSprites();

    // set up a FSM, we're going to have two states with their own conditions
    SqrDistanceCondition* furtherThan15 = new SqrDistanceCondition(15.0f * AIAgent->pathAgent->parentGraph->m_cellSize, false);
    SeeSuspiciousCondition* seesSuspiciousTarget = new SeeSuspiciousCondition(400, 90, 1);
    NearUrgantSituationCondition* nearUrgentSituation = new NearUrgantSituationCondition(400);

    UtilityAI* utilityUnAlert = new UtilityAI();
    utilityUnAlert->AddBehaviour(new GoToImportantBehaviour(0.2f));
    utilityUnAlert->AddBehaviour(new LingerBehaviour(200));
    utilityUnAlert->AddBehaviour(new GoToToiletBehaviour(0.1));

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