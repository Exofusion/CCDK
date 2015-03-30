/*
  
  �s�ƃf���~�^�ɂ��e�L�X�g�����񏈗����[�`���B
  ����������ƁA�����ꏈ�����[�`���������ɓ���̂����B

  HTTP �������ӎ������w�b�_�\���𓾈ӂƂ���悤�Ƀf�U�C������B
  ��F

  Content-Length: 8937
  �̂悤�ȁB�܂��A�o�C�i���{�̂��e�L�X�g�̋�s(\n\n��������\r\n\r\n)
  �̒���ɑ������Ƃ��ӎ�����B

  ���ׂāA�I���������̃o�b�t�@�ɑ΂��鏈���Ƃ���B
  ���ł����t�@�C���𑗂�ꍇ�Ȃǂ͂����������Ȃ����A
  ���̂Ƃ��̓I���W�i���X���b�h���g���Ă��̂��B
  �܂��A
  divide_header_and_content �Ńw�b�_�Ɩ{�̂𕪗����邱�Ƃ��ł��A
  ��������ē���header �������
  get_header_info( nocase, "Content-Length" , ... )
  �Ƃ��Ď�肾�����Ƃ��ł���B
  "Content-Length: 8398" �ł� "Content-Length : 90823" �ł��A
  "content-length 29834" �ł�OK�ɂȂ�悤�ɂ���B
  ��̓I�ɂ́Acontent-length���s������͂��܂�A����
  ���̒����':' ' ' '\t' �������������Ă��������A�����ȊO�̕������o��
  �����ʒu������s�L���̑O�̕����܂ł���肾���B
  
 */

#include "vce.h"
#include "vcecommon.h"
#include "util.h"

int vce_httptext_divide_header_and_content( const char *in , int inlen, char **head, int *headlen, char **body, int *bodylen ) {
	int i;
    *head = (char*)in;
    *body = NULL;
    *headlen = *bodylen = 0;
    
	for(i=0;i<inlen; i++){
		int rest = ( inlen - i );
		if( rest >= 2 && in[i] == '\n' && in[i+1] == '\n' ){
			*headlen = i;
			*body = (char*)in + i + 2;
			*bodylen = inlen - ( i+2 );
			return SET_LAST_ERROR(0);
		}
		if(  rest >= 4 && in[i] == '\r' && in[i+1] == '\n' &&
			  in[i+2] == '\r' && in[i+3] == '\n' ){
			*headlen = i;
			*body = (char*)in + i + 4;
			*bodylen = inlen - (i+4);
			return SET_LAST_ERROR(0);
		}
	}
	return SET_LAST_ERROR( VCE_EFORMAT );
}

int vce_text_cmpnocase( const char *s1, const char *s2, int n ) {
    int i;
    for(i=0;i<n;i++){
        int c1, c2;
        if( s1[i] == '\0' || s1[i] == '\0' ) return 1;
        c1 = tolower_direct( s1[i] );
        c2 = tolower_direct( s2[i] );
        if( c1 != c2 ) return 1;
    }
    return 0;
}

/*
  ' ' , ':' , '\t' ���΂��Ă����ȊO�̕������������炻�̏ꏊ��Ԃ�
  �L���ȕ������Ȃ��ꍇ�� NULL ��Ԃ�
 */
static char *skip_header_item_spaces( char *b , int len, int *skipped ) {
    int i;
    for(i=0;i<len;i++){
        if( b[i] != ' ' && b[i] != ':' && b[i] != '\t' ){
            *skipped =i;
            return b + i;
        }
    }
    *skipped = -1;
    return NULL;
}

int vce_httptext_get_header_info( const char *h, int hlen , char *item , char *out, int outlen_real ) {
    int outlen = outlen_real - 1; /* NULL�I�[���Areturn���钼�O�ɂ�� */
    int i,lineno = 1,cplen , itemlen = (int)strlen( item);
    char *top = (char*)h;
    for(i=0; i<hlen;i++){
        int rest = ( hlen - i );
        int skip_byte;
        char *value;
        if( rest > 2 && h[i] == '\r' && h[i+1] == '\n' ){
            if( vce_text_cmpnocase( top, item, itemlen )==0){
                top = top + itemlen;
                value = skip_header_item_spaces( top, (int)(i-(top-h)) , &skip_byte );
                if( value ){
                    memcpy( out, value,
                            cplen = MIN( i-(int)(top-h)-skip_byte, outlen));
					out[cplen]=0;
                    return cplen;
                }                
            }
            
            top = (char*)h + i + 2;
            i += 1;
            lineno ++;
        } else if( rest > 1 && h[i] == '\n' ){
            if( vce_text_cmpnocase( top , item, itemlen )==0){
                top = top + itemlen;

                value = skip_header_item_spaces( top, i-(int)(top-h), &skip_byte );
                if( value ){
                    memcpy( out, value,
                            cplen = MIN(i-(int)(top-h)-skip_byte, outlen));
					out[cplen]=0;					
                    return cplen;
                }
            }
            top = (char*)h + i + 1;
            lineno ++;
        } else if( rest == 1 ){
            if( vce_text_cmpnocase( top , item, itemlen )==0){
                top = top + itemlen;
                value = skip_header_item_spaces( top, i-(int)(top-h)+1,&skip_byte );
                if( value ){
                    memcpy( out, value,
                            cplen = MIN(i-(int)(top-h)+1-skip_byte,outlen));
					out[cplen]=0;					
                    return cplen;
                }
            }
        }
    }
    memcpy( out, "" , cplen = MIN( 1, outlen ));
    return cplen;
}

char *vce_text_split_index( const char *src, char c, int index ) {
	int i,count;
	SET_LAST_ERROR(0);
	if( index == 0 ) return (char*)src;

	count = 0;
	for(i=0;;i++){
		if( src[i] == 0 ){
			
			if( count == 0 ){
				return (char*)src;
			} else {
				SET_LAST_ERROR(VCE_ENOTFOUND);
				return NULL;
			}
		}
		if( src[i] == c ){
			count++;
			if( count == index ) return (char*)src + i + 1;
		}
	}
	/* not reached */
}

int vce_text_split_index_get_string( const char *src, char c, int index, char *out, int outlen ) {
	int ret;
	char *token_top ;

	if( src[0] == '\0' ) return SET_LAST_ERROR(VCE_ENOTFOUND);
	
	token_top = vce_text_split_index( src,c,index);
	if( !token_top ) return SET_LAST_ERROR(VCE_ENOTFOUND);

	if( ( token_top == src )
		&& (index > 0) ) return SET_LAST_ERROR(VCE_ENOTFOUND);

	ret = vce_copy_cstring_upto( out, token_top, c, outlen );
	if( ret < 0 ) return SET_LAST_ERROR(ret); else SET_LAST_ERROR(0);
	return ret;
}

int vce_text_split_index_get_int( const char *src, char c, int index, int *v ) {
	char *token_top ;
	char output[20];

	if( src[0] == '\0' ) return SET_LAST_ERROR(VCE_ENOTFOUND);
	
	token_top = vce_text_split_index( src,c,index);
	if( !token_top ) return SET_LAST_ERROR(VCE_ENOTFOUND );

	if( ( token_top == src )
		&& (index > 0) ) return SET_LAST_ERROR(VCE_ENOTFOUND);
	
	vce_copy_cstring_upto( output, token_top, c, sizeof( output ));
	*v = atoi( output );
	return SET_LAST_ERROR(0);
}

int vce_copy_cstring( char *dest , int destlen , const char *src ) {
    int i;
    for( i = 0 ; i < (destlen-1) ; i++ ) {
        dest[i] = src[i];
        if( !src[i] ){
            return 0;
        }
    }
    dest[i] = '\0';
    if(src[i]){
        return 1;
    } else {
        return 0;
    }
}

int vce_copy_cstring_upto( char *dest, const char *src, char c, int destlen  ) {
	int i;
	for(i=0;i<destlen-1;i++){
		if( src[i] == '\0' ){
			dest[i] = '\0';
			return i+1;
		}
		if( src[i] == c ){
			dest[i] = '\0';
			return i+1;
		}
		dest[i] = src[i];
	}
	dest[i]=0;
	return i+1;
}

int vce_strcmptail( const char *s1, const char *s2 ) {
	int l1 = (int)strlen(s1);
	int l2 = (int)strlen(s2);
	if( l1 > l2 ){
		return strcmp( s1+(l1-l2), s2 );
	} else if( l2 > l1 ){
		return strcmp( s2+(l2-l1), s1 );
	} else {
		return strcmp( s1,s2);
	}
}

int vce_text_hashpjw( const char *s ) {
    char *p;
    unsigned int h = 0 , g;
    for( p = (char*)s ; *p ; p ++ ){
        h = ( h << 4 ) + (*p);
        if( ( g = h & 0xf0000000 ) != 0 ){
            h = h ^ ( g >> 24 );
            h = h ^ g;
        }
    }
    return h / 16; /* �L���Ȓl�ɂȂ�悤�� 16�Ŋ����Ă��� */
}

char *vce_makecstr( char *out, int outlen, const char *in, int inlen ) {
    memcpy( out, in, MIN(outlen,inlen));
    if(inlen>=outlen){
        out[outlen-1]='\0';
    } else {
        out[inlen]='\0';
    }
    return out;
}


char *vce_chop_string_destroy( char *s ) {
	int l;
	l = (int)strlen(s);
	if( l >=  1){
		if( l >= 2 ){
			if( s[l-2] == '\r' && s[l-1] == '\n' ){
				s[l-2] = s[l-1] = '\0';
			} else if( s[l-1] == '\n' ) s[l-1] = '\0';
		} else {
			if( s[l-1] == '\n' ) s[l-1] = '\0';
		}
	}
	return s;
}

int vce_strlenmax( const char *s, int max ) {
	int i;
	for(i=0;i<max;i++){
		if( s[i] == 0 ) return i;
	}
	return -1;
}

int vce_strncat( char *out, int outlen, const char *append ) {
	int al = (int)strlen(append);
	int l = (int)strlen(out);
	int after_append = l + al + 1;

	if( after_append > outlen ) return VCE_EFULL;

	strcat( out, append );
	return after_append;
}

void vce_strncpy( char *to, int to_len, const char *from, int from_len ) {
    int i, len;

    len = from_len;
    for(i=0;i<len;i++){
        if( from[i] == '\0' ) {
            len = i;
            break;
        }
    }

    if( to_len-1 < len ) len = to_len -1;
    memcpy( to, from, len );
    to[len] = '\0';
    
}

int vce_escape_string( char *to, int tolen, const char *from, int fromlen ) {
  char *to_start=to;
  char *end;

  if( tolen < (fromlen*2+1)) return SET_LAST_ERROR(VCE_ETOOSHORT);
  
  for (end=(char*)from+fromlen; from != end ; from++)
  {
    switch (*from) {
    case 0:				/* Must be escaped for 'mysql' */
      *to++= '\\';
      *to++= '0';
      break;
    case '\n':				/* Must be escaped for logs */
      *to++= '\\';
      *to++= 'n';
      break;
    case '\r':
      *to++= '\\';
      *to++= 'r';
      break;
    case '\\':
      *to++= '\\';
      *to++= '\\';
      break;
    case '\'':
      *to++= '\\';
      *to++= '\'';
      break;
    case '"':				/* Better safe than sorry */
      *to++= '\\';
      *to++= '"';
      break;
    case '\032':			/* This gives problems on Win32 */
      *to++= '\\';
      *to++= 'Z';
      break;
    default:
      *to++= *from;
    }
  }
  *to=0;
  SET_LAST_ERROR(VCE_NOERROR);
  return (int)(to-to_start);
}

int vce_descape_string( char *to, int tolen, const char *from ) {
    int i,so_far;
    int l = (int)strlen(from);

    so_far = 0;
    for(i=0;i<l;i++){
        if( from[i] == '\\' ){
            switch( from[i+1] ){
            case '0':
                to[so_far] = '\0';
                break;
            case 'n':
                to[so_far] = '\n';
                break;
            case 'r':
                to[so_far] = '\r';
                break;
            case '\\':
                to[so_far] = '\\';
                break;
            case '\'':
                to[so_far] = '\'';
                break;
            case '\"':
                to[so_far] = '\"';
                break;
            case 'Z':
                to[so_far] = '\032';
                break;
            }
            i++;
            so_far++;
        } else {
            to[so_far] = from[i];
            so_far++;
        }
        if( so_far ==(tolen-1)){
            break;
        }
    }
    to[so_far]='\0';
    if(i<l){
        return SET_LAST_ERROR(VCE_EFULL);
    } else {
        SET_LAST_ERROR(VCE_NOERROR);
        return so_far;
    }
}
