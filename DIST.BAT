@echo off

which cl.exe > nul 2>&1
if errorlevel 1 goto error

	mkdir dist
	mkdir dist\lib
	cl -c include\glad.c rey\grey\grey.c rey\grey\grey++.cpp -I include
	lib /out:dist\lib\grey.lib *.obj lib\glfw3.lib opengl32.lib msvcrt.lib vcruntime.lib shell32.lib gdi32.lib user32.lib
	del grey.obj
	del grey++.obj
	del glad.obj	
	copy main.cpp dist\
	xcopy include\** dist\include\ /E /H /C /I
	copy rey\grey\grey dist\include\
	copy "rey\grey\grey++" dist\include\

	goto end

:error
echo Run this batch file with Developer Command Prompt for VS2019 (search for it in the start menu)

:end