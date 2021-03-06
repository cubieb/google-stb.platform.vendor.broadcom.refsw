/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _DSGCCCLIENTCALLBACK_RPC_H_RPCGEN
#define _DSGCCCLIENTCALLBACK_RPC_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct dsgccClientNotification {
	int eventType;
	int eventValue;
	int clientPort;
};
typedef struct dsgccClientNotification dsgccClientNotification;

#define DSGCCSTATUSCALLBACK 0x05082002
#define DSGCCSTATUSCALLBACKVERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define DSGCCCLIENTNOTIFICATION 1
extern  int * dsgccclientnotification_1(struct dsgccClientNotification *, CLIENT *);
extern  int * dsgccclientnotification_1_svc(struct dsgccClientNotification *, struct svc_req *);
extern int dsgccstatuscallback_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define DSGCCCLIENTNOTIFICATION 1
extern  int * dsgccclientnotification_1();
extern  int * dsgccclientnotification_1_svc();
extern int dsgccstatuscallback_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_dsgccClientNotification (XDR *, dsgccClientNotification*);

#else /* K&R C */
extern bool_t xdr_dsgccClientNotification ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_DSGCCCLIENTCALLBACK_RPC_H_RPCGEN */
