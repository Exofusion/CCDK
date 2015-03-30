#include "vce.h"
#include "sbuf.h"
#include "vcecommon.h"

int vce_sbuf_init( sbuf *s, int mi ) {
    s->start = s->end = 0;
	s->mem_i = mi;
	s->buf = vce_alloc_array_object( mi );
	s->len = vce_get_array_member_size( mi );
	
	if( !s->buf ) return vce_get_last_error();
	return SET_LAST_ERROR(0);
}

void vce_sbuf_cleanup( sbuf *s ) {
	if( !s || !s->buf ) return;

	s->start = s->end = 0;
	vce_free_array_object( s->mem_i, s->buf );
	s->buf = NULL;
	SET_LAST_ERROR(0);
}
int vce_sbuf_is_valid( sbuf *s ) {
	if( !s || !s->buf ) return 0; else return 1;
}

/*
  sbuf ��push����B
  append�ł���������Ԃ��B

  �o�O���Ă���ꍇ�͗����Ăق����̂ŁA�o�O�`�F�b�N�͂��Ȃ���

  VCE�ɓ����I�ȋ@�\�Ƃ��āA�w�肳�ꂽ�ʂ̃f�[�^�� append �ł��Ȃ������ꍇ�́A
  ���r���[�ȃf�[�^���������܂��G���[��Ԃ��B
  ����͊�{�I�ȃX�^���X�ł���B
  
 */
int vce_sbuf_push( sbuf *s, char *p , size_t pl ) {
    /* ����rest�́A�㔼�ɂ���c��ˁB�S�̂̎c��ł͂Ȃ��� */
    int rest =(int)s->len - s->end;
	if(pl==0)
		return 0;
    if( rest >= (int) pl ){
        memcpy( s->buf + s->end , p, pl );
        s->end += (int)pl;
		SET_LAST_ERROR(0);
        return (int)pl;
    }
    /* �c��̕����ɂ��̂܂ܑ����Ȃ��ꍇ�͂��炵�Ă��������ǂ���ׂ� */
    memmove( s->buf, s->buf + s->start , s->end - s->start );
    s->end -= s->start;
    s->start = 0;
    rest = (int)s->len - s->end;
    if( rest >= (int)pl ){
        memcpy( s->buf + s->end , p , pl );
        s->end += (int)pl;
		SET_LAST_ERROR(0);
        return (int)pl;
    } else {
		return SET_LAST_ERROR(VCE_EFULL);
    }
    return SET_LAST_ERROR(VCE_EBUG);
}

/*
  sbuf �̑O����肾��(shrink)

  char *out: �o�̓o�b�t�@
  size_t outl : ���̂�����

  �R�s�[�ł����������������B
  out ��NULL�������ƁA�R�s�[���Ȃ�
 */
int vce_sbuf_shrink( sbuf *s, char *out, size_t outl ) {
    int cplen;
    int datalen ;

    datalen = s->end - s->start;
    if( datalen == 0 ) return SET_LAST_ERROR(0);
    if( datalen < (int)outl ) cplen = datalen; else cplen = (int)outl;
	if(cplen<=0) return SET_LAST_ERROR(0);
    if(out) memcpy( out, s->buf + s->start , cplen );
    s->start += cplen;
    if( s->start == s->end ) s->start = s->end = 0;
	SET_LAST_ERROR(0);
    return cplen;
}
/* �c��o�b�t�@���������� */
int vce_sbuf_get_rest( sbuf *s ) {
	int r;
    /* �O�ƌ�ɋ󂫂����肤�邩��Bpush�̂Ƃ��ɋl�܂�� */
	SET_LAST_ERROR(0);
    r =  ( (int)s->len - s->end ) + ( s->start - 0 ) ;
	return r;
}
/* �g�p���̃f�[�^����Ԃ� */
int vce_sbuf_get_use( sbuf *s ) {
	SET_LAST_ERROR(0);
    return s->end - s->start;
}

void vce_sbuf_get_buffer( sbuf *s, char **b , int *l ) {
    if(b) *b = s->buf + s->start;
    if(l) *l = s->end - s->start;
	SET_LAST_ERROR(0);
}


