/******************************************************************************
 *  Copyright (C) 2017 Broadcom. The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 ******************************************************************************/

#include "packet.h"

#include <stdio.h>
#include <memory.h>


PacketItem::PacketItem(eDataType t, uint32_t data) :
   m_type(t), m_data(data), m_numBytes(4)
{
}

PacketItem::PacketItem(eDataType t, uint32_t data, uint32_t numBytes) :
   m_type(t), m_data(data), m_numBytes(numBytes)
{
}

PacketItem::PacketItem(GLbyte b) :
   m_type(eINT8), m_data((uint32_t)b), m_numBytes(4)
{
}

PacketItem::PacketItem(GLubyte b) :
   m_type(eUINT8), m_data((uint32_t)b), m_numBytes(4)
{
}

PacketItem::PacketItem(GLshort s) :
   m_type(eINT16), m_data((uint32_t)s), m_numBytes(4)
{
}

PacketItem::PacketItem(GLushort u) :
   m_type(eUINT16), m_data((uint32_t)u), m_numBytes(4)
{
}

PacketItem::PacketItem(GLint i) :
   m_type(eINT32), m_data((uint32_t)i), m_numBytes(4)
{
}

PacketItem::PacketItem(GLuint u) :
   m_type(eUINT32), m_data((uint32_t)u), m_numBytes(4)
{
}

PacketItem::PacketItem(GLfloat f) :
   m_type(eFLOAT), m_data(*(uint32_t*)&f), m_numBytes(4)
{
}

PacketItem::PacketItem(void *p) :
   m_type(eVOID_PTR), m_data((uint32_t)p), m_numBytes(4)
{
}

PacketItem::PacketItem(const void *p) :
   m_type(eVOID_PTR), m_data((uint32_t)p), m_numBytes(4)
{
}

PacketItem::PacketItem(const char *c) :
   m_type(eCHAR_PTR), m_data((uint32_t)c), m_numBytes(strlen(c) + 1)
{
}

PacketItem::PacketItem(void *a, uint32_t numBytes) :
   m_type(eBYTE_ARRAY), m_data((uint32_t)a), m_numBytes(a != 0 ? numBytes : 0)
{
}

PacketItem::PacketItem(long int s) :
   m_type(eINT32), m_data((uint32_t)s), m_numBytes(4)
{
}

template<typename T>
struct ArrayDeleter
{
   void operator ()(T const * p)
   {
      delete[] p;
   }
};

std::shared_ptr<uint8_t> Packet::AddBuffer(size_t size)
{
   std::shared_ptr<uint8_t> buffer(new uint8_t[size], ArrayDeleter<uint8_t>());
   m_buffers.push_back(buffer);
   return buffer;
}