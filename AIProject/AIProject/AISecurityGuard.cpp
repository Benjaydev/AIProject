#include "AISecurityGuard.h"
#include "Condition.h"
#include "State.h"
#include "UtilityAI.h"
#include "FiniteStateMachine.h"
#include "Game.h"

AISecurityGuard::AISecurityGuard(NodeGraph* graph) : AIObject(graph)
{
    SetCostume("Security");
    SetWeapon("Pistol");
    InitSprites();


    // set up a FSM, we're going to have two states with their own conditions
    SqrDistanceCondition* furtherThan15 = new SqrDistanceCondition(15.0f * AIAgent->pathAgent->parentGraph->m_cellSize, false);
    SeeSuspiciousCondition* seesSuspiciousTarget = new SeeSuspiciousCondition(400, 90, 1);
    SeeCondition* seesTarget = new SeeCondition(400, 95, 3);
    NearUrgantSituationCondition* nearUrgentSituation = new NearUrgantSituationCondition(400);

    UtilityAI* utilityUnAlert = new UtilityAI();
    utilityUnAlert->AddBehaviour(new GoToImportantBehaviour());
    utilityUnAlert->AddBehaviour(new LingerBehaviour(50));
    utilityUnAlert->AddBehaviour(new DefendBehaviour(Game::eliminationTarget));

    UtilityAI* utilityAlert = new UtilityAI();
    utilityAlert->AddBehaviour(new SearchAreaBehaviour(200));

    // register these states with the FSM, so its responsible for deleting them now
    State* UnAlertState = new State(utilityUnAlert);
    State* AlertState = new State(utilityAlert);
    State* GetPlayerState = new State(new FollowTargetBehaviour());

    // Sees player, follow player
    UnAlertState->AddTransition(seesSuspiciousTarget, GetPlayerState);
    // Sees urgant situation go to alert
    UnAlertState->AddTransition(nearUrgentSituation, AlertState);
    // Sees player when alert, follow player
    AlertState->AddTransition(seesSuspiciousTarget, GetPlayerState);
    GetPlayerState->AddTransition(seesTarget, AlertState, false);
    // make a finite state machine that starts off lingering
    FiniteStateMachine* fsm = new FiniteStateMachine(UnAlertState);

    fsm->AddState(UnAlertState);

    AIAgent->SetBehaviour(fsm);



    AddToGameWorld();
}

void AISecurityGuard::Update(float DeltaTime)
{
    AIObject::Update(DeltaTime);

    if (AIAgent->currentBehaviour->name == "Follow") {
        shootCooldownCount += DeltaTime;
        if (shootCooldownCount >= shootCooldown) {
            shootCooldownCount = 0;
            UseWeapon();
        }
    }
    
}
