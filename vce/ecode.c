#include "vce.h"
#include "vcecommon.h"

char * vce_strerror( int ecode ) {
	switch ( ecode ){
    case VCE_NOERROR : return STRDEF_EMESG_NOERROR;
    case VCE_EGENERIC : return STRDEF_EMESG_EGENERIC;
    case VCE_EFULL  :  return  STRDEF_EMESG_EFULL;
    case VCE_EBUG   :  return  STRDEF_EMESG_EBUG;
    case VCE_ERANGE :  return  STRDEF_EMESG_ERANGE;
    case VCE_EINVAL :  return  STRDEF_EMESG_EINVAL;
    case VCE_EMEM   :  return  STRDEF_EMESG_EMEM;
    case VCE_ENOENT :  return  STRDEF_EMESG_ENOENT;
    case VCE_EIO    :  return  STRDEF_EMESG_EIO;
    case VCE_ESOCKET :  return  STRDEF_EMESG_ESOCKET;
    case VCE_EBIND :  return  STRDEF_EMESG_EBIND;
    case VCE_EIPADDR :  return  STRDEF_EMESG_EIPADDR;
    case VCE_ELISTEN :  return  STRDEF_EMESG_ELISTEN;
    case VCE_ECONFIG :  return  STRDEF_EMESG_ECONFIG;
    case VCE_EHOSTNAME :  return  STRDEF_EMESG_EHOSTNAME;
    case VCE_EFCNTL :  return  STRDEF_EMESG_EFCNTL;
    case VCE_ECONNECT :  return  STRDEF_EMESG_ECONNECT;
    case VCE_EBUFSMALL :  return  STRDEF_EMESG_EBUFSMALL;
    case VCE_EPROTO    :  return  STRDEF_EMESG_EPROTO;
    case VCE_ENOTREADY :  return  STRDEF_EMESG_ENOTREADY;
    case VCE_ENEGO    :  return  STRDEF_EMESG_ENEGO;
    case VCE_EPROTO_INVAL :  return  STRDEF_EMESG_EPROTO_INVAL;
    case VCE_EPROTO_ODD :  return  STRDEF_EMESG_EPROTO_ODD;
    case VCE_EPROTO_TOOLONG :  return  STRDEF_EMESG_EPROTO_TOOLONG;
    case VCE_ENOCALLBACK :  return  STRDEF_EMESG_ENOCALLBACK;
    case VCE_ESUPPORT  :  return  STRDEF_EMESG_ESUPPORT;
    case VCE_ECONNSERIAL :  return  STRDEF_EMESG_ECONNSERIAL;
    case VCE_EALIGNMENT :  return  STRDEF_EMESG_EALIGNMENT;
    case VCE_EFORMAT :  return  STRDEF_EMESG_EFORMAT;
    case VCE_ESEARCH :  return  STRDEF_EMESG_ESEARCH;
    case VCE_ECONTENTLEN :  return  STRDEF_EMESG_ECONTENTLEN;
    case VCE_ECONNINIT :  return  STRDEF_EMESG_ECONNINIT;
    case VCE_EBADKEYLEN :  return  STRDEF_EMESG_EBADKEYLEN;
    case VCE_EACCEPT :  return  STRDEF_EMESG_EACCEPT;
    case VCE_ESETSOCKOPT :  return  STRDEF_EMESG_ESETSOCKOPT;
    case VCE_EACCESSFILE :  return STRDEF_EMESG_EACCESSFILE;
    case VCE_EWINSOCKINIT : return STRDEF_EMESG_EWINSOCKINIT;
    case VCE_EWBFULL: return STRDEF_EMESG_EWBFULL;
    case VCE_ELONGINPUT: return STRDEF_EMESG_ELONGINPUT;
    case VCE_ETOOSHORT: return STRDEF_EMESG_ETOOSHORT;
    case VCE_EPROTO_BADLEN: return STRDEF_EMESG_EPROTO_BADLEN;
    case VCE_EPROTO_RESULT: return STRDEF_EMESG_EPROTO_RESULT;
    case VCE_EPROTO_SERVERINVAL: return STRDEF_EMESG_EPROTO_SERVERINVAL;
    case VCE_EPROTO_BADCOMMAND: return STRDEF_EMESG_EPROTO_BADCOMMAND;
    case VCE_EFOPEN_W: return STRDEF_EMESG_EFOPEN_W;
    case VCE_ERENAME: return STRDEF_EMESG_ERENAME;
    case VCE_ENOTFOUND: return STRDEF_EMESG_ENOTFOUND;
    case VCE_ELENTOOLONG: return STRDEF_EMESG_ELENTOOLONG;
    case VCE_EDATASHORT: return STRDEF_EMESG_EDATASHORT;
    case VCE_EOPENDIR: return STRDEF_EMESG_EOPENDIR;
    case VCE_EFSEEK: return STRDEF_EMESG_EFSEEK;
    case VCE_EFREAD: return STRDEF_EMESG_EFREAD;
    case VCE_EMKDIR: return STRDEF_EMESG_EMKDIR;
    case VCE_EALREADY: return STRDEF_EMESG_EALREADY;
    case VCE_EFINALIZE: return STRDEF_EMESG_EFINALIZE;
    case VCE_ECLOSED: return STRDEF_EMESG_ECLOSED;
    case VCE_EGENCOMMAND: return STRDEF_EMESG_EGENCOMMAND;
    case VCE_ENOCRYPTO: return STRDEF_EMESG_ENOCRYPTO;
    case VCE_ETOOLONGNAME: return STRDEF_EMESG_ETOOLONGNAME;
    case VCE_ESIZE: return STRDEF_EMESG_ESIZE;
    case VCE_ESWNOTREADY: return STRDEF_EMESG_ESWNOTREADY;
    case VCE_ESERVERDOWN: return STRDEF_EMESG_ESERVERDOWN;
    case VCE_EODDBUFSIZE: return STRDEF_EMESG_EODDBUFSIZE;
    case VCE_EODDKEYSIZE: return STRDEF_EMESG_EODDKEYSIZE;
    case VCE_EKEYEX: return STRDEF_EMESG_EKEYEX;
    case VCE_EMORESENDBUF: return STRDEF_EMESG_EMORESENDBUF;
    case VCE_EINIT: return STRDEF_EMESG_EINIT;
    case VCE_EARRAY: return STRDEF_EMESG_EARRAY;
    default: return STRDEF_UNKNOWNERROR;
    }
}

char *vce_strerror_close_reason(CLOSE_REASON reason)
{
//  static char tmp[256];
	switch(reason) {
	case CLOSE_REASON_NONE:             //  VCE�������I�Ɏg�p����D���ꂪ�Ԃ����̂́C VCE �̃o�O���l������D
		return "CLOSE_REASON_NONE";
	case CLOSE_REASON_UNKNOWN:          //  �����s���D��{�I�ɕԂ���邱�Ƃ͂Ȃ��D �Ԃ��ꂽ�ꍇ�́CVCE�̃o�O���l������D
		return "CLOSE_REASON_UNKNOWN";
	case CLOSE_REASON_REMOTE:           //  �����[�g�s�A�ɂ���ăR�l�N�V�������ؒf���ꂽ���߁C �������݂��ǂ݂��݂��ł��Ȃ��Ȃ����D CLOSE_REASON_REMOTE �́C�����[�g�^�̒��ŁC���ɕ��ނł��Ȃ������ꍇ�� generic �ȗ��R�̂Ƃ��ɕԂ����D
		return "CLOSE_REASON_REMOTE";
	case CLOSE_REASON_APPLICATION:      //  �A�v���P�[�V�����ɂ���āC vce_conn_close �Ȃǂ��Ăт����ꂽ�D �u���[�J���^�v�̓T�^�I�ȃN���[�Y���R�ł���D
		return "CLOSE_REASON_APPLICATION";
	case CLOSE_REASON_TIMEOUT:          //  �^�C���A�E�g���ԂɂȂ�܂ŁC����M���s���Ȃ��������߁C �ؒf���ꂽ�D�^�C���A�E�g�̏ꍇ�́C�����[�g�������Ȃ̂��C ���[�J���������Ȃ̂��C���ʂ͂��Ȃ��D
		return "CLOSE_REASON_TIMEOUT";
	case CLOSE_REASON_DECODER:          //  �Í��f�R�[�f�B���O�֐��̓����ŃG���[���N�����D ���肩�瑗���Ă����f�[�^�̃t�H�[�}�b�g���ُ�ł��邩�C �f�[�^���R�[�h���K�v�Ƃ��Ă��镪�̃f�[�^���͂��Ȃ��ԂɃR�l�N�V������ ���p�s�\�ɂȂ��Ă��܂����ꍇ�ɋN����D �܂�C���̃G���[�́C�u�����[�g�^�v�ł���D ���̃G���[�́C�R�l�N�V�������������̈Í��l�S�V�G�[�V�������I���C �f�[�^�̌������n�܂��Ă���N����D
		return "CLOSE_REASON_DECODER";
	case CLOSE_REASON_ENCODER:          //  �Í��G���R�[�f�B���O�֐��̓����ŃG���[���N�����D ���̃G���[�́C�R�l�N�V�������������̈Í��l�S�V�G�[�V�������I���C �f�[�^�̌������n�܂��Ă���N����D VCE �͈Í����p�ɓ��ʂȃ��������g��Ȃ����Ƃ�����C���̗��R�� �u�����[�g�^�v�ł���D
		return "CLOSE_REASON_ENCODER";
	case CLOSE_REASON_PARSER:           //  �v���g�R���p�[�T�[�֐������̒l��Ԃ����̂ŁC �R�l�N�V������ؒf�����D ����́C���[�J���^�ł���D���[�J���̃p�[�T�[�֐��̕Ԃ�l�����ł������D
		return "CLOSE_REASON_PARSER";
	case CLOSE_REASON_INTERNAL:         //  VCE �̓����I�Ȗ��ɂ��C�R�l�N�V����������D VCE�̓���������������Ȃ��ꍇ��C�G���[�`�F�b�N�� ���s�����ꍇ��CVCE�̃o�O���l������D ���[�J���^�ł���D
		return "CLOSE_REASON_INTERNAL";
	case CLOSE_REASON_FULL:             //  SWP���g���Ă���ꍇ�ɁCSWP�֑��鑗�M�o�b�t�@����t�ɂȂ��Ă���ꍇ�� ���̒l�ɂȂ�DSWP�֑��鑗�M�o�b�t�@����t�Ƃ������Ƃ́C SWP�̃T�[�o�[����̎�M�o�b�t�@����t�ɂȂ��Ă���\���������D SWP�̃o�b�t�@�[�e�ʂ�傫�����邩�C ����ނ�����̗e�ʂ���t�ɂȂ��Ă��邱�Ƃ��^���ׂ��ł���D �����[�g�z�X�g�̃o�b�t�@����t�ɂȂ��Ă��邱�Ƃ���C �u�����[�g�^�v�ƌ�����D
		return "CLOSE_REASON_FULL";
	default:
		//sprintf(tmp,"CLOSE_REASON_?",reason);
		return "CLOSE_REASON_?????";
	}
}


int vce_get_last_error( void ) {
    return vce_last_error;
}
