#include "manager.h"

void CNetvars::DumpRecvTable(RecvTable* recv_table)
{
	for (int i = 0; i < recv_table->m_nProps; ++i)
	{
		auto prop = recv_table->m_pProps[i];
		if (prop.m_pVarName == "baseclass")
			continue;

		if (!prop.m_pDataTable)
			this->netvars[prop.m_pVarName] = prop.m_Offset;
		else
		{
			DumpRecvTable(prop.m_pDataTable);
		}
	}
}

void CNetvars::Dump()
{
	static auto class_head = reinterpret_cast<ClientClass*>(
		interfaces::GetInterface<IBaseClientDLL>(L"client.dll", "VClient018")->GetAllClasses()
	);

	for (auto client_class = class_head; client_class != nullptr; client_class = client_class->m_pNext)
	{
		auto table = client_class->m_pRecvTable;
		DumpRecvTable(table);
	}
}

uintptr_t CNetvars::GetNetvar(std::string netvar_name)
{
	return netvars[netvar_name];
}