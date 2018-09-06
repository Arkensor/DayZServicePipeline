
RD /s /q "C:\Program Files (x86)\Steam\steamapps\common\DayZ\Missions\DayZServicePipeline.ChernarusPlus" > NUL
xcopy /s/e /y /i "D:\Projekte\C++\DayZServicePipeline\Enscript\Missions\DayZServicePipeline.ChernarusPlus" "C:\Program Files (x86)\Steam\steamapps\common\DayZ\Missions\DayZServicePipeline.ChernarusPlus" > NUL

chdir /d "C:\Program Files (x86)\Steam\steamapps\common\DayZ\Missions\DayZServicePipeline.ChernarusPlus"

CALL "Run Tests.bat"