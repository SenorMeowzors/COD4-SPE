main()
{
	maps\_load::main();

	init();
}

init()
{
	PreCacheItem( "mp5_silencer" );
    level.player giveWeapon( "mp5_silencer" );
}