#ifndef _TCP_H_
#define _TCP_H_

#include "vce.h"
#include "conn.h"

#ifdef WIN32
#include <windows.h>
#endif


/*************************************************************************

  tcpcontext�\���́B �N���C�A���g�ƃT�[�o�̗����ɋ��ʂ̍ŏ����{���ݒ�B

 *************************************************************************/

typedef struct _tcpcontext
{
    int is_server;
    int timeout_sec; // �f�t�H���g�^�C���A�E�g 
    int max_conn;  // ���̃T�[�o�[�̍ő�ڑ��� 
	int conn_in_use;

    /* r/w buffer �̒���(per conn)�B�����/�Í����ς݂̃f�[�^�p���܂����������T�C�Y��p�ӂ���B */
    size_t rblen,erblen;
    size_t wblen,ewblen;

	/* ��ԊǗ��p�o�b�t�@�BVEC��linkage ���ꂽ��A�����ω�����̂ŁA
	   ��U������āA�܂����肠�ĂȂ����B(�g���b�L�[������) */
	size_t statebuf_size;
	int statebuf_mi;     /* �z�� */
	int statebuf_num;    /* �� */


	int rbmaster_mi, wbmaster_mi, erbmaster_mi, ewbmaster_mi;


	/* �g�[�^���̓ǂ�/����/accept �Ȃǂ̉� */
	VCEI64 recv_byte,send_byte,keyex_count;
	/* �V�X�e���R�[���̉� */
	VCEI64 recv_syscall, recv_syscall_e;
	VCEI64 send_syscall, send_syscall_e;
	VCEI64 accept_syscall, accept_syscall_e;
	VCEI64 connect_syscall, connect_syscall_e;

    /* VCE�̃C�x���g�� */
	VCEI64 conn_write,conn_timeout,tcpcontext_connect;

    /* bind ����A�h���X�A�T�[�o�̏ꍇ�̂� */
    struct sockaddr_in sa;

	/* �ꕪ�������accept���e�� */
	int accept_count,accept_max;
	VCEI64 accept_lasttime;
	int (*accept_warning)(tcpcontext_t t);

	
	void *userdata; // userdata pointer 

	char ps_host[256];
	unsigned short ps_mainport;
	unsigned short ps_subport;
    
    int accept_more; // ����accept���邩�ǂ����B�T�[�o�̏ꍇ�̂�
    int mainsock; // bind�psocket(�T�[�o�̏ꍇ) 
    int index;    // tcpcontext �̒���index
    int nonblock_connect;    // client connect���u���b�N���邩
	int nodelay; // �\�P�b�g��NODELAY�ɂ���

    int ( *protocol_parser ) ( conn_t );

	int ( *protocol_acceptwatcher ) ( conn_t ); /* accept �����Ƃ��̔��� */
    int ( *protocol_hiwater_acceptwatcher ) (conn_t,int);
	int ( *protocol_closewatcher ) ( conn_t,CLOSE_REASON r );/*close�����Ƃ� */
    
	int ( *pcallback)(conn_t,char*, int);  // �p�[�T���Ăт������[��΂����֐� 

	void (*conn_finalizer)(conn_t);


    /* �ڑ����� hiwater ��f�f���邽�߂̂������l */
    int conn_hiwater_thres;

    /* exploit�΍�Abin16�p�[�T�ł̍ő�l�ݒ�*/
	/* tcpcontext����󂯎�� */
	int (*maxlen_warning)(conn_t ct);
	int maxlen_record;

	/* conn �̃V���A���ԍ��̍ő�B�[����������A
       serial �̍ő�l�̃R���g���[���͂��Ȃ�(Default) */
    unsigned int conn_serial_max;

    /* 1 heartbeat �ɉ��� parser ���ĂԂ��B�f�t�H���g�� 1 */
    int call_parser_per_loop;

	/* �������ݐ����ł��^�C���A�E�g�J�E���^������������Ȃ�A
       ���̃t���O��1�ɂ���B�ʏ��0�ł��� */
    int recv_reset_timeout, send_reset_timeout;

} tcpcontext;



void vce_tcp_poll( int isolate_conn_serial );
int vce_tcpcontext_init_world( void );
int vce_tcpcontext_fin_world(void);
int vce_tcpcontext_get_next_conn_serial();

extern int vce_select_timeout_us;

#endif
