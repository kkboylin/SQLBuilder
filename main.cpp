
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "SQLBuilder.h"

int main(int argc, const char** argv)
{
	SQLBuilder	builder;
	builder . AddParam("idGuild", (unsigned __int64)200)
			. AddParam("idCity", (unsigned int)101)
			. AddParam("oil", (unsigned int)102)
			. AddParam("metal", (unsigned int)103)
			. AddParam("gas", (unsigned int)104)
			. AddParam("food", (unsigned int)104)
			. AddParam("crystal", (unsigned int)105)
			. AddParam("reset_time", (unsigned __int64)time(NULL))
			. AddParam("refresh_time", (unsigned __int64)time(NULL))
			. AddParam("occupied_time", (unsigned __int64)time(NULL))
			. AddParam("soldiers", (unsigned int)10000)
			. AddParam("occupied", (unsigned int)1)
			. AddParam("totalSoldiers", (unsigned __int64)0)
			. AddParam("idServer", (unsigned int)1)
			. AddParam("state", (unsigned int)0);
	
	std::string	result	=	builder.InsertSql("guild_dungoen");
	result = builder.InsertReplaceSql("guild_dungoen", "idGuild,idCity");
	result = builder.UpdateSql("guild_dungoen", "idGuild,idCity");
	result = builder.DeleteSql("guild_dungoen", "idGuild,idCity");
	result =
	builder.Parse(	"insert into guild_dungoen(idGuild, idCity, oil, metal, gas, food, crystal, reset_time, refresh_time, occupied_time, soldiers, occupied, totalSoldiers, idServer, state)"
					"values(:idGuild,:idCity,:oil,:metal,:gas,:food,:crystal,:reset_time,:refresh_time,:occupied_time,:soldiers,:occupied,:totalSoldiers,:idServer,0)"
					"on duplicate key update oil=:oil,metal=:metal,gas=:food,food=:food,crystal=:crystal,refresh_time=:reset_time,occupied_time=:occupied_time,state=0,"
					"soldiers=:soldiers,occupied=:occupied,totalSoldiers=:totalSoldiers");
	return	0;
}
