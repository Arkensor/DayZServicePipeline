@echo off

taskkill /F /IM DayZ_x64.exe /T > nul 2>&1

cd ../../

start DayZ_x64.exe -mission=.\Missions\DayZServicePipeline.ChernarusPlus -nosplash -noPause -noBenchmark