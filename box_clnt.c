/*
* Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h>
#include "box.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

box_results *
box_calc_1(dimensions *argp, CLIENT *clnt)
{
	static box_results clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));

	if (clnt_call(clnt, BOX_CALC, (xdrproc_t)xdr_dimensions, (char *)argp, (xdrproc_t)xdr_box_results, (char *)&clnt_res, TIMEOUT) != RPC_SUCCESS)
		return (NULL);
	return (&clnt_res);
}

