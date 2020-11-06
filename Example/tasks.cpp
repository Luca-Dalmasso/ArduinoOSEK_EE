/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2017 - 2019 Evidence s.r.l.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License, version 2, for more details.
 * 
 * You should have received a copy of the GNU General Public License,
 * version 2, along with this program; if not, see
 * <www.gnu.org/licenses/old-licenses/gpl-2.0.html >.
 * 
 * This program is distributed to you subject to the following
 * clarifications and special exceptions to the GNU General Public
 * License, version 2.
 * 
 * THIRD PARTIES' MATERIALS
 * 
 * Certain materials included in this library are provided by third
 * parties under licenses other than the GNU General Public License. You
 * may only use, copy, link to, modify and redistribute this library
 * following the terms of license indicated below for third parties'
 * materials.
 * 
 * In case you make modified versions of this library which still include
 * said third parties' materials, you are obligated to grant this special
 * exception.
 * 
 * The complete list of Third party materials allowed with ERIKA
 * Enterprise version 3, together with the terms and conditions of each
 * license, is present in the file THIRDPARTY.TXT in the root of the
 * project.
 * ###*E*### */

/** \file	tasks.cpp
 *  \brief	Tasks.
 *
 *  This file contains the code of application tasks for Erika Enterprise.
 *
 *  \author	Giuseppe Serano
 *  \date	2017
 */

/* ERIKA Enterprise. */
#include "ee.h"

/* Arduino SDK. */
#include "Arduino.h"

extern "C" {

DeclareTask(TaskL1);
DeclareTask(TaskL2);

#if (defined(OSEE_API_DYNAMIC))
extern TaskType TaskL1;
extern TaskType TaskL2;
#endif /* OSEE_API_DYNAMIC */

extern int led;

unsigned int volatile TaskL1_count;
unsigned int volatile TaskL2_count;

extern boolean stk_wrong;

unsigned int volatile isr_cnt;

#define	TIMER1_ISR_DIVISOR	1000

TASK(TaskL1)
{
  isr_cnt++;
  if (isr_cnt >= TIMER1_ISR_DIVISOR)
  {
    isr_cnt = 0;
    Serial.write("TASK-L1\r\n", strlen("TASK-L1\r\n"));
    ActivateTask(TaskL2);
  }

  ++TaskL1_count;
  TerminateTask();
};

TASK(TaskL2)
{
  Serial.write("TASK-L2\r\n", strlen("TASK-L2\r\n"));

  /* turn the LED on (HIGH is the voltage level) */
  digitalWrite(led, HIGH);

  delay(1000);	/* wait for a second */

  /* turn the LED off by making the voltage LOW */
  digitalWrite(led, LOW);

  delay(1000);	/* wait for a second */

  ++TaskL2_count;
  TerminateTask();
};

}	/* extern "C" */
