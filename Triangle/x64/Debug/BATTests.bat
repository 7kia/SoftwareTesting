Triangle.exe
IF NOT ERRORLEVEL 1 GOTO err

Triangle.exe 1
IF NOT ERRORLEVEL 1 GOTO err

Triangle.exe 1 2
IF NOT ERRORLEVEL 1 GOTO err

# >> Degenerate1.txt
Triangle.exe -1 2 3 >> Degenerate1.txt
IF ERRORLEVEL 1 GOTO err
FC /b Degenerate1.txt CheckData/degenerate1.txt

# >> Degenerate2.txt
Triangle.exe 1 2 3 >> Degenerate2.txt
IF ERRORLEVEL 1 GOTO err
FC /b Degenerate2.txt CheckData/degenerate2.txt

# >> Isosceles1.txt
Triangle.exe 2 2 3 >> Isosceles1.txt 
IF ERRORLEVEL 1 GOTO err
FC /b Isosceles1.txt CheckData/Isosceles1.txt

# >> Equilateral1.txt
Triangle.exe 2 2 2 >> Equilateral1.txt 
IF ERRORLEVEL 1 GOTO err
FC /b Equilateral1.txt CheckData/Equilateral1.txt

# >> Versatile1.txt
Triangle.exe 2 4 3 >> Versatile1.txt 
IF ERRORLEVEL 1 GOTO err
FC /b Versatile1.txt CheckData/Versatile1.txt

# >> Rectangular1.txt
Triangle.exe 3 4 5 >> Rectangular1.txt 
IF ERRORLEVEL 1 GOTO err
FC /b Rectangular1.txt CheckData/Rectangular1.txt

# >> Rectangular2.txt
Triangle.exe 3 4.24 3 >> Rectangular2.txt 
IF ERRORLEVEL 1 GOTO err
FC /b Rectangular2.txt CheckData/Rectangular2.txt

# >> Obtuse2.txt
Triangle.exe 3 5.19615 3 >> Obtuse2.txt 
IF ERRORLEVEL 1 GOTO err
FC /b Obtuse2.txt CheckData/Obtuse2.txt

ECHO Program testing succeeded :-) 
PAUSE
EXIT
  
:err
ECHO Program testing failed :-( 
PAUSE
EXIT