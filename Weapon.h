#ifndef HW4_WEAPON_H
#define HW4_WEAPON_H

#include <iostream>


using std::endl;
using std::string;


enum Target {
    LEVEL,
    STRENGTH,
    LIFE
};

class Weapon {
    string name;
    Target target;
    int hit_strength;


public:
    /**
    * the functuin create a new struct weapon
    * @param name
    * @param target
    * @param hit_strength
    */
    Weapon(const string name, Target target, int hit_strength);

    /**
    * the function destroy struct weapon
    */

    Weapon(const Weapon &weapon)= default;

    /**
     * the destructor of the weapon
     */
    ~Weapon()= default;

/**
 * the function return the target of the weapon
 * @return target
 */
    Target getTarget() const;

    /**
     * the funtion return the hitStrength
     * @return int hitStrengh
     */
    int getHitStrength() const;

    /**
     * if target
     * @return int
     */
    int getValue() const;


    /**
     * operator hasama
     * @param weapon
     * @return weapon
     */
    Weapon &operator=(const Weapon &weapon)= default;

/**
 * the function print the weapon in the format that needed
 * @param fl
 * @param weapon
 * @return
 */
    friend std::ostream &operator<<(std::ostream &fl, const Weapon &weapon);
};

/**
 * the fuction get 2 weapon and check if there value eqal.
 * if yes return true else return false.
 * @param weapon1
 * @param weapon2
 * @return
 */
bool operator==(const Weapon &weapon1, const Weapon &weapon2);

/**
 *  the fuction get 2 weapon and check if their value different.
 * if yes return true else return false.
 * @param weapon1
 * @param weapon2
 * @return
 */
bool operator!=(const Weapon &weapon1, const Weapon &weapon2);

/**
 * the fuction get 2 weapon and check if weapon1 value smaller then weapon2.
 * if yes return true else return false.
 * @param weapon1
 * @param weapon2
 * @return
 */
bool operator<(const Weapon &weapon1, const Weapon &weapon2);

/**
 * the fuction get 2 weapon and check if weapon1 value bigger then weapon2.
 * if yes return true else return false.
 * @param weapon1
 * @param weapon2
 * @return
 */
bool operator>(const Weapon &weapon1, const Weapon &weapon2);


#endif //HW4_WEAPON_H