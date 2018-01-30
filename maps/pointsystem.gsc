

init()
{
	level.player thread xp_init();
	spawners = getspawnerarray();
	for ( i = 0;i < spawners.size;i++ )
	{
		spawners[ i ] thread attachToSpawners();
	}
}

attachToSpawners()
{
	for(;;)
	{
		self waittill( "spawned", spawn );

			if(isDefined(spawn))
			{
				spawn thread player_score_think();
			}
	}
}


xp_init()
{
	self.rankUpdateTotal = 0;
	self.hud_rankscroreupdate = newHudElem( self );
	self.hud_rankscroreupdate.horzAlign = "center";
	self.hud_rankscroreupdate.vertAlign = "middle";
	self.hud_rankscroreupdate.alignX = "center";
	self.hud_rankscroreupdate.alignY = "middle";
	self.hud_rankscroreupdate.x = 0;
	self.hud_rankscroreupdate.y = -60;
	self.hud_rankscroreupdate.font = "default";
	self.hud_rankscroreupdate.fontscale = 2;
	self.hud_rankscroreupdate.archived = false;
	self.hud_rankscroreupdate.color = ( 1, 1, 0.5 );
	self.hud_rankscroreupdate fontPulseInit();
}

fontPulseInit()
{
	self.baseFontScale = self.fontScale;
	self.maxFontScale = self.fontScale * 2;
	self.inFrames = 3;
	self.outFrames = 5;
}


trackDamage()
{
    for ( ;; )
	{
		self waittill( "damage", damage, attacker, direction, point, method );
		if (attacker == level.player && isdefined(self))
			{
				
				//What the fuck shawn clean this up
				if(self.health > 0)
				{						
					//level.player addPoints();
					self.hasBeenHitByPlayer = true;
				}
				else if(damage >= self.health * -1)
				{
					//level.player addPoints();
					self.hasBeenHitByPlayer = true;
				}

			}

	}
}




player_score_think()
{
	if ( self.team == "allies" )
		return;
	self waittill( "death", attacker );
	if ( isdefined( attacker )  ){
		if( attacker == level.player )
		{
			level.player thread updatePlayerScore( 10 );
		}
		else
		{
			if(isdefined(self.hasBeenHitByPlayer))
			level.player thread updatePlayerScore( 1 + randomint( 3 ) );
		}
	}
}



updatePlayerScore( amount )
{
	if ( amount == 0 )
		return;

	self notify( "update_xp" );
	self endon( "update_xp" );

	self.rankUpdateTotal += amount;

	self.hud_rankscroreupdate.label = &"SCRIPT_PLUS";
		
	self.hud_rankscroreupdate setValue( self.rankUpdateTotal );
	self.hud_rankscroreupdate.alpha = 1;
	self.hud_rankscroreupdate thread fontPulse( level.player );

	wait 1;
	self.hud_rankscroreupdate fadeOverTime( 0.75 );
	self.hud_rankscroreupdate.alpha = 0;
	
	self.rankUpdateTotal = 0;
}

 


fontPulse( player )
{
	self notify( "fontPulse" );
	self endon( "fontPulse" );
	
	scaleRange = self.maxFontScale - self.baseFontScale;
	
	while ( self.fontScale < self.maxFontScale )
	{
		self.fontScale = min( self.maxFontScale, self.fontScale + ( scaleRange / self.inFrames ) );
		wait 0.05;
	}
		
	while ( self.fontScale > self.baseFontScale )
	{
		self.fontScale = max( self.baseFontScale, self.fontScale - ( scaleRange / self.outFrames ) );
		wait 0.05;
	}
}
