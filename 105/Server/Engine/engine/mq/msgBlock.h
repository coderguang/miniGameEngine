#ifndef _ENGINE_MQ_MSG_BLOCK_H_
#define _ENGINE_MQ_MSG_BLOCK_H_

#include "framework/SmartPoint/refObject.h"
#include "../serialize/serializestream.h"
#include "framework/SmartPoint/smartPoint.h"

namespace csg
{

	//�������ָ���ʵ��
	class SHandlerId
	{
	public:
		int id;
		int type;
		int typeEx;
		int typeEx2;

		//SHandlerId& operator=( const SHandlerId& other ); //Ϊ�˱���һЩ���ܴ��ڵ����⣬���ﲻ����=
	public:
		SHandlerId();
	public:
		bool operator==( const SHandlerId& other )const;
		bool operator!=( const SHandlerId& other )const;
		bool operator<( const SHandlerId& other )const;

		void _csg_init();
		void _csg_write(csg::CSerializeStream&)const;
		void _csg_read(csg::CSerializeStream&);
	};


	//��Ϣͷ����
	class SMsgHead
	{
	public:
		int command;
		SHandlerId fromId;
	public:
		SMsgHead();
	public:
		bool operator==( const SMsgHead& other )const;
		bool operator!=( const SMsgHead& other )const;
		bool operator<( const SMsgHead& other )const;

		void _csg_init();
		void _csg_write(csg::CSerializeStream& os)const;
		void _csg_read(csg::CSerializeStream& os);

	};

	// ������Ҫ���л�����̳д���
	class IMsgBase:public virtual CRefObject
	{
	public:
		virtual void _csg_write(csg::CSerializeStream&)const = 0;
		virtual void _csg_read(csg::CSerializeStream&) = 0;
		virtual void _csg_init()
		{
		};
		virtual IMsgBase* clone() = 0;
		IMsgBase& operator= ( const IMsgBase& msg )
		{
			return *this;
		};
		virtual int getType()const = 0;

		virtual void print()
		{
		};
	};

	typedef csg::CSmartPointShare<IMsgBase> IMsgBasePtr;

	//��Ϣ�壨ͷ+���ݣ�
	class CMsgBlock :public virtual CRefObject
	{
	public:
		SMsgHead _msgHead; //��Ϣͷ
		IMsgBasePtr _msgBase; //�ṹ��ָ��
	public:
		CMsgBlock();
		virtual ~CMsgBlock();

		virtual void _csg_write(csg::CSerializeStream& os)const;
		virtual void _csg_writeHead(csg::CSerializeStream& os)const;
		virtual void _csg_writeBody(csg::CSerializeStream& os)const;

		virtual void _csg_read(csg::CSerializeStream& is);
		virtual void _csg_readHead(csg::CSerializeStream& is);
		virtual void _csg_readBody(csg::CSerializeStream& is);
	private:
		CMsgBlock& operator=( const CMsgBlock& ) = delete; //Ϊ�˾��������ڴ�����
		CMsgBlock(const CMsgBlock&) = delete;
	};

	typedef csg::CSmartPointShare<CMsgBlock> CMsgBlockPtr;

}

#endif