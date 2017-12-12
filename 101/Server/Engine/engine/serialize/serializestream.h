#ifndef _ENGINE_SERIALIZE_SERIALIZE_STREAM_H_
#define _ENGINE_SERIALIZE_SERIALIZE_STREAM_H_

#include "engine/serialize//bytesbuffer.h"
#include <vector>
#include "engine/def/csg_def.h"
#include <string>

#define SERIALIZE_MAX_RESIZE (1024*100)

namespace csg
{
	class CSerializeStream :public virtual CBytesBuffer
	{
	public:
		CSerializeStream();
		~CSerializeStream();

		void append(const void* buf ,int length);

		void resize(int size);

		void clear();

		void reset();

	public:

		void setUseBitMark(bool useBitMark);

		bool getUseBitMark();
		//������ flagByte д�뵽 _flagBytes,���л�ǰ׼��
		void prepareToAppend();
		//�� ���е� _flagBytes д�뵽 _flagBytes,�����л�ǰ׼��
		void prepareToRead();

		//��ȡ _flagBytes �ĳ���
		int getFlagDataSize();

		const char* getFlagData()const;

		/*
		*data operation
		*only int,string,byte,bool,long
		*/
		void writeSize(int);
		void readSize(int&);
		
		void writeSize(uint_t);
		void readSize(uint_t&);


		/*
		* byte data
		*/
		void write(byte_t v);
		void read(byte_t &v);
		void write(const std::vector<byte_t>&);
		void read(std::vector<byte_t>&);

		/**
		* bool data operation
		*/
		void write(bool v);
		void write(const std::vector<bool>&);
		void read(bool& v);
		void read(std::vector<bool>&);

		/**
		* short data operation
		*/
		void write(short);
		void write(const std::vector<short>&);
		void read(short&);
		void read(std::vector<short>&);

		/**
		* int data operation
		*/
		void write(int);
		void write(const std::vector<int>&);
		void read(int&);
		void read(std::vector<int>&);

		/**
		* long64_t data operation
		*/
		void write(long64_t);
		void write(const std::vector<long64_t>&);
		void read(long64_t&);
		void read(std::vector<long64_t>&);

		/**
		* string data operation
		*/
		void write(const std::string&);
		void write(const std::vector<std::string>&);
		void read(std::string&);
		void read(std::vector<std::string>&);

	protected:
		void checkReadLength(int readLength ,const char* name);

		int getBytesLeft()const;

		void addReadIndex(int len);

		char* getReadPoint()const;

	private:
		//bitMark opeation
		void markBitFlag(bool isDefault = false);

		bool readBitFlag();

	private:
		bool _useBitMark;//�Ƿ�ʹ��bigMark
		bool _isUseFlagBitMark; //flagByte �Ƿ�洢��bitMark��Ϣ
		CBytesBuffer _flagBytes; //_flagBytes��Ϣ Ĭ��ֵ��־λbuffer
		byte_t _flagedBit;//bitMark�������� 
		byte_t _flagByte;//bitMark��������
		size_t _flagByteReadPos;//_flagBytes λ��
		int _readIndex;//�̳��� bytesbuffer �ڵ� buffer��λ��

	private:
		CSerializeStream(const CSerializeStream&);
		CSerializeStream& operator=( const CSerializeStream& );
	};
}

#endif