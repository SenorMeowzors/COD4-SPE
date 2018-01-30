
init()
{
	precacheShader( "damage_feedback" );


	level.player.hud_damagefeedback = newHudElem( level.player );
	level.player.hud_damagefeedback.alignX = "center";
	level.player.hud_damagefeedback.alignY = "middle";
	level.player.hud_damagefeedback.horzAlign = "center";
	level.player.hud_damagefeedback.vertAlign = "middle";
	level.player.hud_damagefeedback.alpha = 0;
	level.player.hud_damagefeedback.x = 0;
	level.player.hud_damagefeedback.y = 12;
	level.player.hud_damagefeedback.archived = true;
	level.player.hud_damagefeedback setShader( "damage_feedback", 24, 48 );
	thread monitorDamage();
	
}

monitorDamage()
{

	for ( ;; )
	{
		self waittill( "damage", damage, attacker, direction, point, method );


		if (attacker == level.player && isdefined(self))
			{
				
				if(self.health > 0)
				{						
					level.player updateDamageFeedback();
					self.hasBeenHitByPlayer = true;
				}
				else if(damage >= self.health * -1)
				{
					level.player updateDamageFeedback();
					self.hasBeenHitByPlayer = true;
				}

			}

	}
	
}

monitorFlashBang()
{

	for( ;; )
	{

		self waittill( "flashbang", amount_distance, amount_angle, attacker );
		if( isdefined(attacker) && attacker == level.player)
			level.player updateDamageFeedback();	
		
	}

}

updateDamageFeedback()
{
	if ( !isPlayer( self ) )
		return;
	
	self playlocalsound( "SP_hit_alert" );
	self.hud_damagefeedback.alpha = 1;
	self.hud_damagefeedback fadeOverTime( 1 );
	self.hud_damagefeedback.alpha = 0;



}