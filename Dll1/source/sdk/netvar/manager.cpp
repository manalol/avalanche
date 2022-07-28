#include "manager.h"

#include <iostream>



void netvar::DumpRecvTable(const char* client_class, RecvTable* recv_table)
{
	for (int i = 0; i < recv_table->m_nProps; ++i)
	{
		auto prop = &recv_table->m_pProps[i];
		if (!prop || isdigit(prop->m_pVarName[0]))
			continue;

		if (fnv::hash(prop->m_pVarName) == fnv::cphash("baseclass"))
			continue;

		if (!prop->m_pDataTable) 
		{
			const auto formatted_string = std::format("{}->{}", client_class, prop->m_pVarName);
			netvars[fnv::hash(formatted_string.c_str())] = prop->m_Offset;
		}
		else
		{
			DumpRecvTable(client_class, prop->m_pDataTable);
		}
	}
}

void netvar::Dump()
{
	static auto class_head = reinterpret_cast<ClientClass*>(
		interfaces::client->GetAllClasses()
	); // Get the head of the linked list and start looping through every client class

	for (auto client_class = class_head; client_class != nullptr; client_class = client_class->m_pNext)
	{
		auto table = client_class->m_pRecvTable;
		DumpRecvTable(client_class->m_pNetworkName, table);
	}
}

uintptr_t netvar::GetNetvar(std::string netvar)
{
	return netvars[fnv::hash(netvar.c_str())];
}