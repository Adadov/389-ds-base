/** BEGIN COPYRIGHT BLOCK
 * Copyright (C) 2001 Sun Microsystems, Inc. Used by permission.
 * Copyright (C) 2005 Red Hat, Inc.
 * All rights reserved.
 * END COPYRIGHT BLOCK **/

#include "repl5_prot_private.h"
 
#ifndef _WINDOWS_PROT_PRIVATE_H_
#define _WINDOWS_PROT_PRIVATE_H_

#define ACQUIRE_SUCCESS 101
#define ACQUIRE_REPLICA_BUSY 102
#define ACQUIRE_FATAL_ERROR 103
#define ACQUIRE_CONSUMER_WAS_UPTODATE 104
#define ACQUIRE_TRANSIENT_ERROR 105

typedef struct windows_private_repl_protocol
{
	void (*delete)(struct windows_private_repl_protocol **);
	void (*run)(struct windows_private_repl_protocol *);
	int (*stop)(struct windows_private_repl_protocol *);
	int (*status)(struct windows_private_repl_protocol *);
	void (*notify_update)(struct windows_private_repl_protocol *);
	void (*notify_agmt_changed)(struct windows_private_repl_protocol *);
        void (*notify_window_opened)(struct windows_private_repl_protocol *);
        void (*notify_window_closed)(struct windows_private_repl_protocol *);
	void (*update_now)(struct windows_private_repl_protocol *);
	PRLock *lock;
	PRCondVar *cvar;
	int stopped;
	int terminate;
	PRUint32 eventbits;
	Repl_Connection *conn;
	int last_acquire_response_code;
	Repl_Agmt *agmt;
	Object *replica_object;
	void *private;
    PRBool replica_acquired;
} Windows_Private_Repl_Protocol;

/*
extern Windows_Private_Repl_Protocol *Windows_Inc_Protocol_new();
extern Windows_Private_Repl_Protocol *Windows_Tot_Protocol_new();
*/

#define PROTOCOL_TERMINATION_NORMAL 301
#define PROTOCOL_TERMINATION_ABNORMAL 302
#define PROTOCOL_TERMINATION_NEEDS_TOTAL_UPDATE 303

#define RESUME_DO_TOTAL_UPDATE 401
#define RESUME_DO_INCREMENTAL_UPDATE 402
#define RESUME_TERMINATE 403
#define RESUME_SUSPEND 404

/* Backoff timer settings for reconnect */
#define PROTOCOL_BACKOFF_MINIMUM 3 /* 3 seconds */
#define PROTOCOL_BACKOFF_MAXIMUM (60 * 5) /* 5 minutes */
/* Backoff timer settings for replica busy reconnect */
#define PROTOCOL_BUSY_BACKOFF_MINIMUM PROTOCOL_BACKOFF_MINIMUM
#define PROTOCOL_BUSY_BACKOFF_MAXIMUM PROTOCOL_BUSY_BACKOFF_MINIMUM

/* protocol related functions */

CSN *get_current_csn(Slapi_DN *replarea_sdn);
char* protocol_response2string (int response);

void windows_dirsync_inc_run(Private_Repl_Protocol *prp);
ConnResult windows_replay_update(Private_Repl_Protocol *prp, slapi_operation_parameters *op);
int windows_process_total_entry(Private_Repl_Protocol *prp,Slapi_Entry *e);

#endif /* _REPL5_PROT_PRIVATE_H_ */
