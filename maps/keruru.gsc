#include maps\_hud_util;


//Health Bar Mod
initHealthbar()
{
	precacheShader ( "white" ); 
    precacheShader ( "black" ); 
    level.secondaryProgressBarX = 500;
    level.secondaryProgressBarY = 215;
    level.secondaryProgressBarHeight = 14;
    level.secondaryProgressBarWidth = 152;
    level.secondaryProgressBarTextY = 45;
    level.secondaryProgressBarFontSize = 2;
    level.player thread initHP();
    level.player thread updateHealth(); 


}

initHP()
{
    self.progressbar = createSecondaryProgressBar();

    level.player setProgressBarProgress(1);
}

updateHealth()
{

    for(;;)
    {
        wait .1;
        level.player setProgressBarProgress(level.player.health/level.player.maxhealth);
    }
}


startProgressBar(planttime)
{
    // show hud elements
    self.progressbar = createSecondaryProgressBar(); }

setProgressBarProgress(amount)
{
    if (amount > 1)
        amount = 1;
    
    self.progressbar updateBar(amount);
}

endProgressBar()
{
    self notify("progress_bar_ended");
    self.progresstext destroyElem();
    self.progressbar destroyElem();
}

// should be moved to _hud.gsc
createSecondaryProgressBar()
{
    bar = createBar( "white", "black", level.secondaryProgressBarWidth, level.secondaryProgressBarHeight );
    bar setPoint("LEFT", undefined, level.secondaryProgressBarX, level.secondaryProgressBarY);
    return bar;
}
