#ifndef _CONN_H_
#define _CONN_H_

#include "vce.h"
#include "sbuf.h"
#include "osdep.h"


//  TCP�R�l�N�V����1�{��\������ 
typedef struct _conn {
    int fd;

	/* closed flag�B close ���Ăт������炱�̃t���O��1�ɂȂ�A
	   �`�F�b�N�̂Ƃ��ɂ��̃t���O��1����������ۂ� close �����B
       �A�v���P�[�V�������\���I�� close ���Ăт������Ƃ������A
       ���̃t���O���g���A�󓮓I�ɕ�����ꍇ�͒��� conn_free ���g����B
    */
	int closed_flag;

	/* �m���u���b�L���O connect �� connect ���I�����Ă��邩�ǂ����̃t���O�B
	   tcpcontext �� nonblock_connect �� 1 �łȂ��Ƃ��͂��̕ϐ��͎g���Ȃ� */
	int nonblock_connect_ok;

    // accept/connect �����Ƃ��ɂ킩��A�h���X 
	char remote_addr[16]; // ipv4 �̏ꍇ�͐擪��4�o�C�g�� NBOrder �ŁB ipv6 �̏ꍇ�͑S�̂� NBOrder 
	int remote_addr_len; // ipv4 �Ȃ�4�A ipv6 �Ȃ� 16 
	unsigned short remote_port; // network byte order
	char local_addr[16];
	int local_addr_len;
	unsigned short local_port;
    
    time_t last_access; // �Ō�ɃA�N�Z�X������������
    int timeout_sec;  // �^�C���A�E�g�̐ݒ�

	sbuf rb,wb;

    void *tcpc; // tcpcontext�ւ�ptr

    int is_server;
    
    int index; // conn�z��̒��� index 
	void *userdata; // additional userdata pointer 
	char *statebuf; // ��ԊǗ��o�b�t�@(tcpcontext��mi����Ƃ�|�C���^
	size_t statebuf_size; // tcpcontext�̃R�s�[ 
	int statebuf_mi; // tcpcontext�̃R�s�[ 

    int ( *protocol_parser ) ( conn_t );

	int ( *protocol_acceptwatcher ) ( conn_t ) ;
    int ( *protocol_hiwater_acceptwatcher ) (conn_t, int);
	int ( *protocol_closewatcher ) ( conn_t, CLOSE_REASON r );

	int ( *pcallback)(conn_t,char*,int);	// �v���g�R���R�[���o�b�N�֐� 
	
	unsigned int serial;  // �������g�̃V���A���ԍ� 


    /* exploit�΍�Abin16�p�[�T�ł̍ő�l�ݒ� */
	/* tcpcontext����󂯎�� */
	int (*maxlen_warning)(conn_t ct);
	int maxlen_record;


	/* ���v��� */
    VCEI64 recv_byte, send_byte, conn_write;
    VCEI64 recv_syscall, send_syscall;


    int call_parser_per_loop;

    void (*readwrite_callback)( conn_t, int rwflg, char *buf, size_t len );
} conn;


int vce_conn_init_world( void );
int vce_conn_alloc_num( int num );
void vce_conn_free_num( int num );
void vce_conn_free( conn *c, int closewatcher, CLOSE_REASON reason );
void vce_conn_free2( conn *c);
void vce_conn_free3( conn *c);

conn * vce_conn_alloc( void );
int vce_conn_get_index_from_pointer( conn *c );
void vce_conn_io( conn *c , int rf , int wf, int call_protoparser );

int vce_conn_init_world(void);
int vce_conn_fin_world(void);

void vce_conn_set_enable_protocol_callback( conn_t ct, int val ) ;


extern int vce_conn_mi;

#endif
