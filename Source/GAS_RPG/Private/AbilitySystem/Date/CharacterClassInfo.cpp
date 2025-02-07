// 关于GAS系统的学习


#include "AbilitySystem/Date/CharacterClassInfo.h"

FCharacterClassDefaultInfo UCharacterClassInfo::GetClassDefaultInfo(ECharacterClass Class) const
{
	return CharacterClassInformation.FindChecked(Class);
}
