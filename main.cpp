
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "SQLBuilder.h"

int main(int argc, const char** argv)
{
	clock_t	start	=	clock();
	static const int	players	=	3000;	/* online player count */
	static const int	requests=	20;		/* request per second */
	for (int i = 0; i < (players * requests); ++i)
	{
		SQLBuilder	builder;
		builder . AddParam("guild", (unsigned __int64)200)
				. AddParam("city", (unsigned int)101)
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
	
		std::string	result;
		/* Simple way. */
		result	=	builder.InsertReplaceSql("table", "guild,city");

		/* Complex ways. */
		result	=
		builder.Parse(	"insert into table(guild, city, oil, metal, gas, food, crystal, reset_time, refresh_time, occupied_time, soldiers, occupied, totalSoldiers, idServer, state)"
						"values(:guild,:city,:oil,:metal,:gas,:food,:crystal,:reset_time,:refresh_time,:occupied_time,:soldiers,:occupied,:totalSoldiers,:idServer,0)"
						"on duplicate key update oil=:oil,metal=:metal,gas=:food,food=:food,crystal=:crystal,refresh_time=:reset_time,occupied_time=:occupied_time,state=0,"
						"soldiers=:soldiers,occupied=:occupied,totalSoldiers=:totalSoldiers");

		/* Select Statement. */
		result =
		builder.Parse("select * from table where guild = :guild and city = :city");
	}
	clock_t	end	=	clock();
	printf("%u\n", static_cast<unsigned int>(end - start) );
	return	0;
}
