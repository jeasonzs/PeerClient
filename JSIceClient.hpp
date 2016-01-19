#ifndef _JS_ICE_CLIENT_H
#define _JS_ICE_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <pjlib.h>
#include <pjlib-util.h>
#include <pjnath.h>







class JSIceClient
{
public:
    JSIceClient();
    ~JSIceClient();

    
public:
    void setIceCb(pj_ice_strans_cb *iceCb);
    void setLogFile(char* logFile);
    void setDNS(char* dns);
    void setMaxhost(int value);
    void setRegular(int value);
    void setStun(char* value);
    void setTurn(char* turn,int turn_tcp,char* userName,char* passwd);

public:
    void icedemo_create_instance(void);
    void icedemo_destroy_instance(void);
    void icedemo_init_session(unsigned rolechar);
    void icedemo_stop_session(void);
    void icedemo_input_remote(void);
    void icedemo_start_nego(void);
    void icedemo_send_data(unsigned comp_id, const char *data);
    void icedemo_console(void);
    
private:
    void threadWork();
    static int icedemo_worker_thread(void *context);
    void icedemo_perror(const char *title, pj_status_t status);
    void err_exit(const char *title, pj_status_t status);
    pj_status_t handle_events(unsigned max_msec, unsigned *p_count);
    pj_status_t icedemo_init(void);
    void reset_rem_info(void);
    int encode_session(char buffer[], unsigned maxlen);

private:
    void icedemo_show_ice(void);
    void icedemo_help_menu(void);
    void icedemo_print_menu(void);
    //void icedemo_console(void);
    void icedemo_usage();
    int print_cand(char buffer[], unsigned maxlen, const pj_ice_sess_cand *cand);
private:
    /* Our global variables */
    pj_caching_pool	 cp;
    pj_pool_t		*pool;
    pj_thread_t		*thread;
    pj_bool_t		 thread_quit_flag;
    pj_ice_strans_cfg	 ice_cfg;
    pj_ice_strans	*icest;
    pj_ice_strans_cb iceCb;
    /* Variables to store parsed remote ICE info */
    struct rem_info
    {
        char		 ufrag[80];
        char		 pwd[80];
        unsigned	 comp_cnt;
        pj_sockaddr	 def_addr[PJ_ICE_MAX_COMP];
        unsigned	 cand_cnt;
        pj_ice_sess_cand cand[PJ_ICE_ST_MAX_CAND];
    } rem;
};
#endif

