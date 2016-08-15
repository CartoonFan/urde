#ifndef __URDE_CGUNWEAPON_HPP__
#define __URDE_CGUNWEAPON_HPP__

#include "RetroTypes.hpp"
#include "CWeaponMgr.hpp"
#include "Collision/CMaterialList.hpp"
#include "zeus/CVector3f.hpp"

namespace urde
{

class CGunWeapon
{
public:
    CGunWeapon(u32, EWeaponType type, TUniqueId, EMaterialTypes, const zeus::CVector3f& vec);
};

}

#endif // __URDE_CGUNWEAPON_HPP__