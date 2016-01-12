
#ifndef __SQL_BUILDER_H__
#define	__SQL_BUILDER_H__

#include <string.h>
#include <map>
#include <string>

class SQLBuilder
{
#if defined(_MSC_VER)
	typedef __int64				int64;
	typedef unsigned __int64	uint64;
#else
	typedef long long			int64;
	typedef unsigned long long	uint64;
#endif
	typedef int					int32;
	typedef unsigned int		uint32;
	typedef float				float32;
	typedef double				float64;

	enum E_TYPE
	{
		E_INT32,
		E_UINT32,
		E_INT64,
		E_UINT64,
		E_FLOAT32,
		E_FLOAT64,
		E_STRING
	};

	struct SValue
	{
		union
		{
			int32	iValue32;
			uint32	uValue32;
			int64	iValue64;
			uint64	uValue64;
			float64	fValue64;
			float32	fValue32;
		}value;
		E_TYPE		type;
		std::string	strValue;
	};

	struct less
	{
		bool operator()(const std::string& _Left,
						const std::string& _Right) const
		{
			if (_Left.size() == _Right.size() )
				return	( memcmp( _Left.c_str(), _Right.c_str(), _Left.size() ) < 0 );
			return	( _Left.size() > _Right.size() );
		}
	};

	typedef std::map< std::string, SValue, less >	Values;

private	:
	Values		_Values;

	SQLBuilder(const SQLBuilder& other)				{					}
	const SQLBuilder& operator=(const SQLBuilder&)	{	return	*this;	}

	std::string Parse(const std::string& value, const Values::const_iterator& it) const;
	void GetKeyTable(const char* keys, Values& table) const;
	std::string CreateWhere(const Values& table) const;

public	:
	SQLBuilder();

	inline void Reset()																{	_Values.clear();						}
	inline SQLBuilder& AddParam(const std::string& name, const int32& value)		{	return	AddParamInt32(name, value);		}
	inline SQLBuilder& AddParam(const std::string& name, const uint32& value)		{	return	AddParamUInt32(name, value);	}
	inline SQLBuilder& AddParam(const std::string& name, const int64& value)		{	return	AddParamInt64(name, value);		}
	inline SQLBuilder& AddParam(const std::string& name, const uint64& value)		{	return	AddParamUint64(name, value);	}
	inline SQLBuilder& AddParam(const std::string& name, const float64& value)		{	return	AddParamFloat64(name, value);	}
	inline SQLBuilder& AddParam(const std::string& name, const float32& value)		{	return	AddParamFloat32(name, value);	}
	inline SQLBuilder& AddParam(const std::string& name, const std::string& value)	{	return	AddParamString(name, value);	}
	inline SQLBuilder& AddParam(const char* name, const int32& value)				{	return	AddParamInt32(name, value);		}
	inline SQLBuilder& AddParam(const char* name, const uint32& value)				{	return	AddParamUInt32(name, value);	}
	inline SQLBuilder& AddParam(const char* name, const int64& value)				{	return	AddParamInt64(name, value);		}
	inline SQLBuilder& AddParam(const char* name, const uint64& value)				{	return	AddParamUint64(name, value);	}
	inline SQLBuilder& AddParam(const char* name, const float64& value)				{	return	AddParamFloat64(name, value);	}
	inline SQLBuilder& AddParam(const char* name, const float32& value)				{	return	AddParamFloat32(name, value);	}
	inline SQLBuilder& AddParam(const char* name, const std::string& value)			{	return	AddParamString(name, value);	}

	SQLBuilder& AddParamInt32(const std::string& name, const int32& value);
	SQLBuilder& AddParamUInt32(const std::string& name, const uint32& value);
	SQLBuilder& AddParamInt64(const std::string& name, const int64& value);
	SQLBuilder& AddParamUint64(const std::string& name, const uint64& value);
	SQLBuilder& AddParamFloat64(const std::string& name, const float64& value);
	SQLBuilder& AddParamFloat32(const std::string& name, const float32& value);
	SQLBuilder& AddParamString(const std::string& name, const std::string& value);
	SQLBuilder& AddParamString(const std::string& name, const char* value);

	SQLBuilder& AddParamInt32(const char* name, const int32& value);
	SQLBuilder& AddParamUInt32(const char* name, const uint32& value);
	SQLBuilder& AddParamInt64(const char* name, const int64& value);
	SQLBuilder& AddParamUint64(const char* name, const uint64& value);
	SQLBuilder& AddParamFloat64(const char* name, const float64& value);
	SQLBuilder& AddParamFloat32(const char* name, const float32& value);
	SQLBuilder& AddParamString(const char* name, const std::string& value);
	SQLBuilder& AddParamString(const char* name, const char* value);

	std::string Parse(const std::string& sql) const;
	std::string Parse(const char* sql) const;

	std::string InsertSql(const char* table, bool ignore = false) const;
	std::string InsertReplaceSql(const char* table, const char* keys) const;
	std::string UpdateSql(const char* table, const char* keys) const;
	std::string DeleteSql(const char* table, const char* keys) const;
};

#endif	//	__SQL_BUILDER_H__