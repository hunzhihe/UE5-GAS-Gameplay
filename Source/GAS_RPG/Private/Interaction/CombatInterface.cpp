// 关于GAS系统的学习


#include "Interaction/CombatInterface.h"

// Add default functionality here for any ICombatInterface functions that are not pure virtual.
int32 ICombatInterface::GetLevel()
{
	return  0 ;
}

FVector ICombatInterface::GetCombatSocketLocation()
{
	return  FVector();
}
