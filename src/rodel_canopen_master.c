#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <fcntl.h>

#include <net/if.h>

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "CANOpen/CANOpen.h"
#include "CANOpen/CANOpen_batch.h"

#include "rodel_controller.h"

static int interrupted;
static int stop_thread;

int s_can;

void sigint_handler(int sig){
	interrupted = 1;
}

void* canopen_checkloop(void* d){

	while(!stop_thread){
		CANOpen_timerLoop();
		usleep(100);
	}

	pthread_exit(NULL);

}

void* canopen_rxloop(void* d){

    struct can_frame frame;

    struct timeval timeout;
    fd_set set;
    int rv;
    int nbytes;

	while(!stop_thread){
	    FD_ZERO(&set);
	    FD_SET(s_can, &set);

	    timeout.tv_sec = 0;
	    timeout.tv_usec = 100000;

	    rv = select(s_can + 1, &set, NULL, NULL, &timeout);
	    if(rv > 0){
	        nbytes = read(s_can, &frame, sizeof(frame));
	        /*
	        if(nbytes > 0) {
	        	printf("0x%X [%d] ", frame.can_id, frame.can_dlc);
	        	int i;
	            for(i = 0; i < 8; i++)
	            	printf("0x%02X ",frame.data[i]);
	         }
	        printf("\n");*/
	        CANOpen_addRxBuffer(frame.can_id, frame.data);
	    }
	}

	pthread_exit(NULL);

}

int main()
{
    int ret;
    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_filter rfilter[1];


    //system("sudo ip link set can0 type can bitrate 1000000");
    //system("sudo ifconfig can0 up");

    //1.Create socket
    s_can = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (s_can < 0) {
        perror("socket PF_CAN failed");
        return 1;
    }

    //2.Specify can0 device
    strcpy(ifr.ifr_name, "can0");
    ret = ioctl(s_can, SIOCGIFINDEX, &ifr);
    if (ret < 0) {
        perror("ioctl failed");
        return 1;
    }

    //3.Bind the socket to can0
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    ret = bind(s_can, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) {
        perror("bind failed");
        return 1;
    }

    //4.Receive all frame
    rfilter[0].can_id = 0x000;
    rfilter[0].can_mask = 0x000;
    setsockopt(s_can, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));


    // 5.Create CANOpen loop thread
    signal(SIGINT, sigint_handler);

    pthread_t p_thread[2];
    int thr_id;

    thr_id = pthread_create(&p_thread[0], NULL, canopen_checkloop, NULL);
    if(thr_id < 0){
    	perror("thread create error : ");
    	exit(0);
    }

    thr_id = pthread_create(&p_thread[1], NULL, canopen_rxloop, NULL);
    if(thr_id < 0){
    	perror("thread create error : ");
    	exit(0);
    }

    stop_thread = 0;

    sleep(1);

    // 6. Batch Start
    CANOpen_batch_M1_start();
    CANOpen_batch_M2_start();

    // 7. To do something
    while(!interrupted){
    	control_loop();
    	usleep(10000); // 10ms
    }

    // 8. Batch end
    CANOpen_batch_M1_end();
    CANOpen_batch_M2_end();

    stop_thread = 1;

    int status;
    pthread_join(p_thread[0], (void **)&status);
    pthread_join(p_thread[1], (void **)&status);

    //7.Close the socket and can0
    close(s_can);
    //system("sudo ifconfig can0 down");
    return 0;
}
