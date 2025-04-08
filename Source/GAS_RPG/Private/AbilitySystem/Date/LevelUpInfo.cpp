// 关于GAS系统的学习


#include "AbilitySystem/Date/LevelUpInfo.h"

int32 ULevelUpInfo::FindLeveForXP(int32 XP) const
{
	int32 Level =1;
	bool bSearching = true;
	while (bSearching)
	{
		//数组索引【0】为空数据，索引下标表示对应等级的数据，如果遍历完成了整个数组，说明当前等级已经达到最大值，直接返回当前等级
		if(LevelUpInfomation.Num()-1 <= Level) return Level;
		//判断当前经验值是否已经达到对应的等级所需经验值
		if (XP >= LevelUpInfomation[Level].LevelUpRequirement)
		{
			//查询登记数据增加一级
			Level++;
		}
		else
		{
			//如果经验值没有达到，则结束循环
			bSearching = false;
		}
	}
	return Level;
}
