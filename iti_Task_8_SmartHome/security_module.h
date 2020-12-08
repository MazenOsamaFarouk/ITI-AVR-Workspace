/*
 * security_module.h
 *
 *  Created on: Jul 2, 2020
 *      Author: mazen
 */

#ifndef SECURITY_MODULE_H_
#define SECURITY_MODULE_H_

#define NO_TRIALS     3
#define ADMIN           "admin"
#define ADMIN_PASS      "admin"
#define USR_MAZEN       "mazen"
#define USR_MAZEN_PASS  "1234"


u8 get_char_to_display(u8 key_press ,const char *key_map[]);
void get_user_id(void);
void get_pass(void);
u8 verify_user(void);
u8 verify_Pass(void);


#endif /* SECURITY_MODULE_H_ */
