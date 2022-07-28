#pragma once
#include <string>
#include <utility>
#include <unordered_map>

#include "../interfaces/interface.h"
#include "../../utils/fnv.h"
#include "../../utils/globals.h"



class RecvTable;
namespace netvar
{
    inline std::unordered_map<std::uint32_t, uintptr_t> netvars;

    void Dump();
    void DumpRecvTable(const char* client_class, RecvTable* recv_table);
    uintptr_t GetNetvar(std::string netvar);
}
 
class RecvProp
{
public:
    char* m_pVarName;
    void* m_RecvType;
    int                     m_Flags;
    int                     m_StringBufferSize;
    int                     m_bInsideArray;
    const void* m_pExtraData;
    RecvProp* m_pArrayProp;
    void* m_ArrayLengthProxy;
    void* m_ProxyFn;
    void* m_DataTableProxyFn;
    RecvTable* m_pDataTable;
    int                     m_Offset;
    int                     m_ElementStride;
    int                     m_nElements;
    const char* m_pParentArrayPropName;
};

class RecvTable
{
public:

    RecvProp* m_pProps;
    int            m_nProps;
    void* m_pDecoder;
    char* m_pNetTableName;
    bool        m_bInitialized;
    bool        m_bInMainList;
};

class ClientClass
{
public:
    void* m_pCreateFn;
    void* m_pCreateEventFn;
    char* m_pNetworkName;
    RecvTable* m_pRecvTable;
    ClientClass* m_pNext;
    int                m_ClassID;
};


