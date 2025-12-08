/* C-callable header for C++ user code
 * Place calls to these from the generated main.c inside
 * USER CODE BEGIN / END blocks.
/*
 * user_cpp.h
 *
 *  Created on: [Date]
 *      Author: [Your Name]
 *
 *  C-compatible header for C++ functions.
 */
#ifndef USER_CPP_H
#define USER_CPP_H

#ifndef INC_USER_CPP_H_
#define INC_USER_CPP_H_

#ifdef __cplusplus
extern "C" {
#endif

// initialize user C++ subsystem
void UserCpp_Init(void);

// periodic tick or loop hook called from main
void UserCpp_Loop(void);

#ifdef __cplusplus
}
#endif

#endif // USER_CPP_H
#endif /* INC_USER_CPP_H_ */
