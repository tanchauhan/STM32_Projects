/* C-callable header for C++ user code
 * Place calls to these from the generated main.c inside
 * USER CODE BEGIN / END blocks.
 */
#ifndef USER_CPP_H
#define USER_CPP_H

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
