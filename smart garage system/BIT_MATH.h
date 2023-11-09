/*
 * BIT_MATH.h
 *
 *  Created on: Aug 10, 2023
 *      Author: Mariam
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG,BIT_NUM)      (REG=REG|(1<<BIT_NUM))
#define CLR_BIT(REG,BIT_NUM)      (REG=REG&(~(1<<BIT_NUM)))
#define TOG_BIT(REG,BIT_NUM)      (REG=REG^(1<<BIT_NUM))
#define GET_BIT(REG,BIT_NUM)      (((REG)>>(BIT_NUM)) &1)

//3 operations functions like macro


#define SET_PORT(REG)             (REG) |= 0xFF
#define CLR_PORT(REG)             (REG) &= 0x00
#define TOG_PORT(REG)             (REG) ^= 0xFF


#endif /* BIT_MATH_H_ */
