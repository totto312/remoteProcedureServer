/* box_client2.c
   Client for the RPC_BOX service using version 2 of the protocol
   Compile with: cc box_client2.c box_clnt.c box_xdr.c -o box_client
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "box2.h"

/* Print out the box details */
void print_box(float l, float w, float h, float sa, float v) {
    printf("A box of dimensions %f x %f x %f\n", l, w, h);
    printf("Has a surface area of %f\n", sa);
    printf("And a volume of %f\n", v);
}

/* Print out the postage rate */
void print_postage(float rate) {
    printf("The postage rate is %f\n", rate);
}

int main(int argc, char **argv) {
    CLIENT *clnt;
    dimensions dims;
    mail_dims m_dims;
    box_results *box_res;
    float *postage_res;

    if (argc != 6) {
        fprintf(stderr, "Usage: %s remote_host length width height mass\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Set up the dimensions for box calculation */
    dims.length = atof(argv[2]);
    dims.width = atof(argv[3]);
    dims.height = atof(argv[4]);

    /* Set up the mass for mail calculation */
    m_dims.mass = atof(argv[5]);

    /* Create a connection handle */
    clnt = clnt_create(argv[1], RPC_BOX, BOXVERSION2, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror(argv[1]);
        exit(EXIT_FAILURE);
    }

    /* Perform the box calculation */
    box_res = box_calc_2(&dims, clnt);
    if (box_res == NULL) {
        clnt_perror(clnt, "box_calc_2 failed");
        exit(EXIT_FAILURE);
    }

    /* Print out the box results */
    print_box(dims.length, dims.width, dims.height, box_res->surface, box_res->volume);

    /* Set up the mail dimensions for postage calculation */
    m_dims.volume = box_res->volume;
//    m_dims.mass = 100.0; /* Example mass value, adjust as needed */

    /* Perform the postage calculation */
    postage_res = mail_calc_2(&m_dims, clnt);
    if (postage_res == NULL) {
        clnt_perror(clnt, "mail_calc_2 failed");
        exit(EXIT_FAILURE);
    }

    /* Print out the postage result */
    print_postage(*postage_res);
    clnt_destroy(clnt);
    return 0;
}
