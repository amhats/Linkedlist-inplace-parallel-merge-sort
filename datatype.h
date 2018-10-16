#ifndef DATATYPE_H
#define DATATYPE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef long long unsigned int degrees;

typedef struct term_q_{
    mpq_t coef;
    degrees *deg;
    struct term_q_* next;
}term_q;

typedef struct linked_list_q_{
    int size;
    term_q *head;
    term_q *tail;
}linked_list_q;

typedef struct term_z_{
    mpz_t coef;
    degrees *deg;
    struct term_z_* next;
}term_z;

typedef struct linked_list_z_{
    int size;
    term_z *head;
    term_z *tail;
}linked_list_z;

#ifdef __cplusplus
}
#endif

#endif /* DATATYPE_H */

