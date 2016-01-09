
#include <stdio.h>
#include <assert.h>
#include "SQLBuilder.h"

SQLBuilder::SQLBuilder()
{
}

SQLBuilder& SQLBuilder::AddParamInt32(const std::string& name, const int32& value)
{
	SValue	value_;
	value_.value.iValue32	=	value;
	value_.type				=	E_INT32;
	_Values[":" + name]		=	value_;
	return	*this;
}

SQLBuilder& SQLBuilder::AddParamUInt32(const std::string& name, const uint32& value)
{
	SValue	value_;
	value_.value.uValue32	=	value;
	value_.type				=	E_UINT32;
	_Values[":" + name]		=	value_;
	return	*this;
}

SQLBuilder& SQLBuilder::AddParamInt64(const std::string& name, const int64& value)
{
	SValue	value_;
	value_.value.iValue64	=	value;
	value_.type				=	E_INT64;
	_Values[":" + name]		=	value_;
	return	*this;
}

SQLBuilder& SQLBuilder::AddParamUint64(const std::string& name, const uint64& value)
{
	SValue	value_;
	value_.value.uValue64	=	value;
	value_.type				=	E_UINT64;
	_Values[":" + name]		=	value_;
	return	*this;
}

SQLBuilder& SQLBuilder::AddParamFloat64(const std::string& name, const float64& value)
{
	SValue	value_;
	value_.value.fValue64	=	value;
	value_.type				=	E_FLOAT64;
	_Values[":" + name]		=	value_;
	return	*this;
}

SQLBuilder& SQLBuilder::AddParamFloat32(const std::string& name, const float32& value)
{
	SValue	value_;
	value_.value.fValue32	=	value;
	value_.type				=	E_FLOAT32;
	_Values[":" + name]		=	value_;
	return	*this;
}

SQLBuilder& SQLBuilder::AddParamString(const std::string& name, const char* value)
{
	SValue	value_;
	value_.strValue			=	value;
	value_.type				=	E_STRING;
	_Values[":" + name]		=	value_;
	return	*this;
}

SQLBuilder& SQLBuilder::AddParamString(const std::string& name, const std::string& value)
{
	SValue	value_;
	value_.strValue			=	value;
	value_.type				=	E_STRING;
	_Values[":" + name]		=	value_;
	return	*this;
}

SQLBuilder& SQLBuilder::AddParamInt32(const char* name, const int32& value)
{
	SValue	value_;
	value_.value.iValue32	=	value;
	value_.type				=	E_INT32;
	_Values[std::string(":") + name]	=	value_;
	return	*this;
}

SQLBuilder& SQLBuilder::AddParamUInt32(const char* name, const uint32& value)
{
	SValue	value_;
	value_.value.uValue32	=	value;
	value_.type				=	E_UINT32;
	_Values[std::string(":") + name]	=	value_;
	return	*this;
}

SQLBuilder& SQLBuilder::AddParamInt64(const char* name, const int64& value)
{
	SValue	value_;
	value_.value.iValue64	=	value;
	value_.type				=	E_INT64;
	_Values[std::string(":") + name]	=	value_;
	return	*this;
}

SQLBuilder& SQLBuilder::AddParamUint64(const char* name, const uint64& value)
{
	SValue	value_;
	value_.value.uValue64	=	value;
	value_.type				=	E_UINT64;
	_Values[std::string(":") + name]	=	value_;
	return	*this;
}

SQLBuilder& SQLBuilder::AddParamFloat64(const char* name, const float64& value)
{
	SValue	value_;
	value_.value.fValue64	=	value;
	value_.type				=	E_FLOAT64;
	_Values[std::string(":") + name]	=	value_;
	return	*this;
}

SQLBuilder& SQLBuilder::AddParamFloat32(const char* name, const float32& value)
{
	SValue	value_;
	value_.value.fValue32	=	value;
	value_.type				=	E_FLOAT32;
	_Values[std::string(":") + name]	=	value_;
	return	*this;
}

SQLBuilder& SQLBuilder::AddParamString(const char* name, const char* value)
{
	SValue	value_;
	value_.strValue	=	value;
	value_.type		=	E_STRING;
	_Values[std::string(":") + name]	=	value_;
	return	*this;
}

SQLBuilder& SQLBuilder::AddParamString(const char* name, const std::string& value)
{
	SValue	value_;
	value_.strValue	=	value;
	value_.type		=	E_STRING;
	_Values[std::string(":") + name]	=	value_;
	return	*this;
}

std::string SQLBuilder::Parse(const std::string& sql) const
{
	return	Parse( sql.c_str() );
}

std::string SQLBuilder::Parse(const std::string& value, const Values::const_iterator& it) const
{
	std::string	result;
	char		buffer[64];
	buffer[0]	=	0;
	switch( (*it).second.type )
	{
		case	E_INT32		:	sprintf_s(buffer, sizeof(buffer), "%d", (*it).second.value.iValue32);		break;
		case	E_UINT32	:	sprintf_s(buffer, sizeof(buffer), "%u", (*it).second.value.uValue32);		break;
		case	E_INT64		:	sprintf_s(buffer, sizeof(buffer), "%I64d", (*it).second.value.iValue64);	break;
		case	E_UINT64	:	sprintf_s(buffer, sizeof(buffer), "%I64u", (*it).second.value.uValue64);	break;
		case	E_FLOAT32	:	sprintf_s(buffer, sizeof(buffer), "%f", (*it).second.value.fValue32);		break;
		case	E_FLOAT64	:	sprintf_s(buffer, sizeof(buffer), "%f", (*it).second.value.fValue64);		break;
	}

	const char*	cur	=	value.c_str();
	const char*	end	=	&cur[value.size()];
	while (cur < end)
	{
		const char*	now = strstr(cur, (*it).first.c_str());
		if (now == NULL)
		{
			result	+=	cur;
			break;
		}
		result	+=	std::string(cur, now - cur);
		if( (*it).second.type == E_STRING )
		{
			result	+=	"'";
			result	+=	(*it).second.strValue;
			result	+=	"'";
		}
		else
			result	+=	buffer;
		cur	=	now;
		cur	+=	(*it).first.size();
	}
	return	result;
}

std::string SQLBuilder::Parse(const char* sql) const
{
	if( (sql != NULL) &&
		(*sql != 0) )
	{
		if (_Values.size() > 0)
		{
			std::string	result(sql);
			Values::const_iterator	it	=	_Values.begin();
			for( ; it != _Values.end(); ++it )
				result	=	Parse(result, it);
			return	result;
		}
		return	sql;
	}
	return	std::string("");
}

static const char* StringChar(const char* value, const char* chars)
{
	while (*value != 0)
	{
		if (strchr(chars, *value) != NULL)
			return	value;
		++value;
	}
	return	NULL;
}

void SQLBuilder::GetKeyTable(const char* keys, Values& table) const
{
	if( (keys != NULL) ||
		(*keys != 0) )
	{
		for( ; ; )
		{
			const char*	ptr	=	StringChar(keys, ", \t");
			if (ptr == NULL)
			{
				std::string				key(std::string(":") + keys);
				Values::const_iterator	it	=	_Values.find(key);
				if( it != _Values.end() )
					table[key]	=	(*it).second;
				break;
			}
			std::string				key(std::string(":") + std::string(keys, ptr - keys));
			Values::const_iterator	it	=	_Values.find(key);
			if (it != _Values.end())
				table[key]	=	(*it).second;
			keys	=	&ptr[1];
		}
	}
}

std::string SQLBuilder::CreateWhere(const Values& table) const
{
	std::string	result;
	if (table.size() > 0)
	{
		result	+=	" where ";
		char		buffer[64];
		std::string	where;
		Values::const_iterator	it = table.begin();
		for (; it != table.end(); ++it)
		{
			switch ((*it).second.type)
			{
				case	E_INT32		:	sprintf_s(buffer, sizeof(buffer), "%d", (*it).second.value.iValue32);		break;
				case	E_UINT32	:	sprintf_s(buffer, sizeof(buffer), "%u", (*it).second.value.uValue32);		break;
				case	E_INT64		:	sprintf_s(buffer, sizeof(buffer), "%I64d", (*it).second.value.iValue64);	break;
				case	E_UINT64	:	sprintf_s(buffer, sizeof(buffer), "%I64u", (*it).second.value.uValue64);	break;
				case	E_FLOAT32	:	sprintf_s(buffer, sizeof(buffer), "%f", (*it).second.value.fValue32);		break;
				case	E_FLOAT64	:	sprintf_s(buffer, sizeof(buffer), "%f", (*it).second.value.fValue64);		break;
			}
			if (where.empty() == false)
				where	+=	" and ";

			where	+=	&(*it).first.c_str()[1];
			if ((*it).second.type == E_STRING)
			{
				where	+=	"='";
				where	+=	(*it).second.strValue;
				where	+=	"'";
			}
			else
			{
				where	+=	"=";
				where	+=	buffer;
			}
		}
		result	+=	where;
	}
	return	result;
}

std::string SQLBuilder::DeleteSql(const char* table, const char* keys) const
{
	assert(table != NULL);
	assert(*table != 0);
	assert(_Values.empty() == false);

	Values	keyTable;
	GetKeyTable( keys, keyTable );
	if (keyTable.empty() == true)
		return	"";

	std::string	result("delete from ");
	result	+=	table;
	result	+=	CreateWhere(keyTable);
	return	result;
}

std::string SQLBuilder::UpdateSql(const char* table, const char* keys) const
{
	assert(table != NULL);
	assert(*table != 0);
	assert(_Values.empty() == false);

	Values	keyTable;
	GetKeyTable(keys, keyTable);

	std::string	updates;
	char		buffer[64];
	Values::const_iterator	it = _Values.begin();
	for (; it != _Values.end(); ++it)
	{
		if (keyTable.count( (*it).first ) != 0)
			continue;

		switch( (*it).second.type )
		{
			case	E_INT32		:	sprintf_s(buffer, sizeof(buffer), "%d", (*it).second.value.iValue32);		break;
			case	E_UINT32	:	sprintf_s(buffer, sizeof(buffer), "%u", (*it).second.value.uValue32);		break;
			case	E_INT64		:	sprintf_s(buffer, sizeof(buffer), "%I64d", (*it).second.value.iValue64);	break;
			case	E_UINT64	:	sprintf_s(buffer, sizeof(buffer), "%I64u", (*it).second.value.uValue64);	break;
			case	E_FLOAT32	:	sprintf_s(buffer, sizeof(buffer), "%f", (*it).second.value.fValue32);		break;
			case	E_FLOAT64	:	sprintf_s(buffer, sizeof(buffer), "%f", (*it).second.value.fValue64);		break;
		}
		if ((*it).second.type == E_STRING)
		{
			if(updates.empty() == false)
				updates	+=	",";
			updates +=	&(*it).first.c_str()[1];
			updates	+=	"='";
			updates	+=	(*it).second.strValue;
			updates	+=	"'";
		}
		else
		{
			if (updates.empty() == false)
				updates	+=	",";
			updates	+=	&(*it).first.c_str()[1];
			updates	+=	"=";
			updates	+=	buffer;
		}
	}

	std::string	result("update ");
	result	+=	table;
	result	+=	" set ";
	result	+=	updates;
	result	+=	CreateWhere(keyTable);
	return	result;
}

std::string SQLBuilder::InsertReplaceSql(const char* table, const char* keys) const
{
	assert(table != NULL);
	assert(*table != 0);
	assert(_Values.empty() == false);
	if( (keys == NULL) ||
		(*keys == 0) )
		return	InsertSql(table);

	Values	keyTable;
	GetKeyTable(keys, keyTable);
	if(keyTable.size() == 0)
		return	InsertSql(table);

	std::string	result("insert into ");
	std::string	values;
	std::string	names;
	std::string	updates;
	char		buffer[64];
	Values::const_iterator	it = _Values.begin();
	for (; it != _Values.end(); ++it)
	{
		if(names.empty() == false)
			names	+=	",";
		if (values.empty() == false)
			values	+=	",";
		names	+=	&(*it).first.c_str()[1];
		switch( (*it).second.type )
		{
			case	E_INT32		:	sprintf_s(buffer, sizeof(buffer), "%d", (*it).second.value.iValue32);		break;
			case	E_UINT32	:	sprintf_s(buffer, sizeof(buffer), "%u", (*it).second.value.uValue32);		break;
			case	E_INT64		:	sprintf_s(buffer, sizeof(buffer), "%I64d", (*it).second.value.iValue64);	break;
			case	E_UINT64	:	sprintf_s(buffer, sizeof(buffer), "%I64u", (*it).second.value.uValue64);	break;
			case	E_FLOAT32	:	sprintf_s(buffer, sizeof(buffer), "%f", (*it).second.value.fValue32);		break;
			case	E_FLOAT64	:	sprintf_s(buffer, sizeof(buffer), "%f", (*it).second.value.fValue64);		break;
		}
		if ((*it).second.type == E_STRING)
		{
			values	+=	"'";
			values	+=	(*it).second.strValue;
			values	+=	"'";
			if (keyTable.count((*it).first) == 0)
			{
				if(updates.empty() == false)
					updates	+=	",";
				updates +=	&(*it).first.c_str()[1];
				updates	+=	"='";
				updates	+=	(*it).second.strValue;
				updates	+=	"'";
			}
		}
		else
		{
			values	+=	buffer;
			if (keyTable.count((*it).first) == 0)
			{
				if (updates.empty() == false)
					updates	+=	",";
				updates	+=	&(*it).first.c_str()[1];
				updates	+=	"=";
				updates	+=	buffer;
			}
		}
	}

	result	+=	table;
	result	+=	"(";
	result	+=	names;
	result	+=	")";
	result	+=	"values(";
	result	+=	values;
	result	+=	")";
	result	+=	"on duplicate key update ";
	result	+=	updates;
	return	result;
}

std::string SQLBuilder::InsertSql(const char* table, bool ignore) const
{
	assert(table != NULL);
	assert(*table != 0);
	assert(_Values.empty() == false);

	std::string	result("insert");
	if(ignore == true)
		result += " ignore ";
	result	+=	" into ";
	std::string	values;
	std::string	names;
	char		buffer[64];
	Values::const_iterator	it = _Values.begin();
	for (; it != _Values.end(); ++it)
	{
		if(names.empty() == false)
			names	+=	",";
		if (values.empty() == false)
			values	+=	",";
		names	+=	&(*it).first.c_str()[1];
		switch( (*it).second.type )
		{
			case	E_INT32		:	sprintf_s(buffer, sizeof(buffer), "%d", (*it).second.value.iValue32);		break;
			case	E_UINT32	:	sprintf_s(buffer, sizeof(buffer), "%u", (*it).second.value.uValue32);		break;
			case	E_INT64		:	sprintf_s(buffer, sizeof(buffer), "%I64d", (*it).second.value.iValue64);	break;
			case	E_UINT64	:	sprintf_s(buffer, sizeof(buffer), "%I64u", (*it).second.value.uValue64);	break;
			case	E_FLOAT32	:	sprintf_s(buffer, sizeof(buffer), "%f", (*it).second.value.fValue32);		break;
			case	E_FLOAT64	:	sprintf_s(buffer, sizeof(buffer), "%f", (*it).second.value.fValue64);		break;
		}
		if ((*it).second.type == E_STRING)
		{
			values	+=	"'";
			values	+=	(*it).second.strValue;
			values	+=	"'";
		}
		else
		{
			values	+=	buffer;
		}
	}

	result	+=	table;
	result	+=	"(";
	result	+=	names;
	result	+=	")";
	result	+=	"values(";
	result	+=	values;
	result	+=	")";

	return	result;
}
