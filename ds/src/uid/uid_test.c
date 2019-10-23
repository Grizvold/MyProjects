#include <stdio.h>  /* printf 							*/
#include <stdlib.h> /* system 							*/
#include <unistd.h> /*  							*/

#include "uid.h"   /* declarations of the uid functions */

/* edit test */

int main()
{
	ilrd_uid_t uid_test1 = {0};
	ilrd_uid_t uid_test2 = {0};
	ilrd_uid_t uid_test3 = {0};

	uid_test1 = UIDCreate();
	uid_test2 = UIDCreate();

	system("sleep 1");
	uid_test3 = UIDCreate();

/* ################################## Create #################################*/
	printf("uid_tes1:\n");
	printf("\tcurr_time = %lu\n\tcounter = %lu\n\tpid = %d\n\tis_error = %d\n",
			uid_test1.curr_time, uid_test1.counter, uid_test1.pid,
			uid_test1.is_error);

	printf("uid_tes2:\n");
	printf("\tcurr_time = %lu\n\tcounter = %lu\n\tpid = %d\n\tis_error = %d\n",
			uid_test2.curr_time, uid_test2.counter, uid_test2.pid,
			uid_test2.is_error);

	printf("uid_tes3:\n");
	printf("\tcurr_time = %lu\n\tcounter = %lu\n\tpid = %d\n\tis_error = %d\n",
			uid_test3.curr_time, uid_test3.counter, uid_test3.pid,
			uid_test3.is_error);

/* #################################  IsEqual ################################*/
	printf("\n*** IsEqual ***\n");
	printf("uid_test1 & uid_test1 = %d\n", UIDIsEqual(uid_test1, uid_test1));
	printf("uid_test1 & uid_test2 = %d\n", UIDIsEqual(uid_test1, uid_test2));
	printf("uid_test1 & uid_test3 = %d\n", UIDIsEqual(uid_test1, uid_test3));
	printf("uid_test2 & uid_test3 = %d\n", UIDIsEqual(uid_test2, uid_test3));

/* ##################################  IsError ###############################*/
	printf("\n*** IsError ***\n");
	printf("uid_test1 is_error = %d\n", UIDIsError(uid_test1));

	return 0;
}

