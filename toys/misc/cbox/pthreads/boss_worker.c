#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

#define COMM_BUF_SIZE       256

#define CREATE_ACCT_TRANS   42
#define DEPOST_TRANS        43
#define WITHDRAW_TRANS      44
#define BALANCE_TRANS       45
#define QUIT                46

typedef struct workorder {
    int conn;
    char req_buf[COMM_BUF_SIZE];
} workorder_t;

void server_comm_send_response(int conn, char *buf)
{
}

void server_shutdown()
{
}

void create_account(char *req)
{
}

void deposit(char *req, char *resp)
{
}

void withdraw(char *req, char *resp)
{
}

void balance(char *req, char *resp)
{
}

void process_request(void *order)
{
    workorder_t *workorderp = (workorder_t *) order;
    char resp_buf[COMM_BUF_SIZE];
    int trans_id;
    sscanf(workorderp->req_buf, "%d", &trans_id);

    switch (trans_id) {
        case CREATE_ACCT_TRANS:
            printf("proc: create\n");
            break;
        case DEPOST_TRANS:
            printf("proc: deposit\n");
            break;
        case WITHDRAW_TRANS:
            printf("proc: withdraw\n");
            break;
        case BALANCE_TRANS:
            printf("proc: balance\n");
            break;
        default:
            break;
    }
    server_comm_send_response(workorderp->conn, resp_buf);
    free(workorderp);
}

void server_comm_get_request(int *conn, char *buf)
{
    int id;
    printf("input trans id: ");
    scanf("%d", &id);
    sprintf(buf, "%d", id);
    *conn = 33;
}

int main()
{
    workorder_t *workorderp;
    pthread_t *worker_threadp;
    int conn;
    int trans_id;

    for (;;) {
        workorderp = (workorder_t *) malloc(sizeof(workorder_t));
        server_comm_get_request(&workorderp->conn, workorderp->req_buf);
        sscanf(workorderp->req_buf, "%d", &trans_id);

        switch (trans_id) {
            case CREATE_ACCT_TRANS:
                printf("recv: create\n");
                break;
            case DEPOST_TRANS:
                printf("recv: deposit\n");
                break;
            case WITHDRAW_TRANS:
                printf("recv: withdraw\n");
                break;
            case BALANCE_TRANS:
                printf("recv: balance\n");
                break;
            case QUIT:
                printf("recv: quit\n");
                goto exit_program;
                break;
            default:
                break;
        }

        worker_threadp = (pthread_t *) malloc(sizeof(pthread_t));
        pthread_create(worker_threadp, NULL, (void *) process_request, (void *) workorderp);
        pthread_detach(*worker_threadp);
        free(worker_threadp);
    }

exit_program:
    server_shutdown();

    return 0;
}

