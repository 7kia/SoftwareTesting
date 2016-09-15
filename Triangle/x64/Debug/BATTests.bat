echo Не правильное количество аргументов
Triangle.exe > incorrectAmountArgument1.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b incorrectAmountArgument1.txt CheckData/invalidArguments.txt



Triangle.exe 1 > incorrectAmountArgument2.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b incorrectAmountArgument2.txt CheckData/invalidArguments.txt



Triangle.exe 1 2 > incorrectAmountArgument3.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b incorrectAmountArgument3.txt CheckData/invalidArguments.txt



Triangle.exe 1 2 3 4 > incorrectAmountArgument4.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b incorrectAmountArgument4s.txt CheckData/invalidArguments.txt



echo Точка допустимый , символ но одна точка не число
Triangle.exe . 2 1  > notNumeric1.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b notNumeric1.txt CheckData/invalidArguments.txt

Triangle.exe 2 . 1  > notNumeric2.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b notNumeric2.txt CheckData/invalidArguments.txt

Triangle.exe 3 2 .  > notNumeric3.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b notNumeric3.txt CheckData/invalidArguments.txt


echo В числе не может быть несколько точек
Triangle.exe 0..2 2 1  > notNumeric4.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b notNumeric4.txt CheckData/invalidArguments.txt

Triangle.exe 2 9.4.2 1  > notNumeric5.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b notNumeric5.txt CheckData/invalidArguments.txt

Triangle.exe 3 2 1.2..2  > notNumeric6.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b notNumeric6.txt CheckData/invalidArguments.txt



echo Аргументом могут быть только числа
Triangle.exe a 2 1  > notNumeric7.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b notNumeric7.txt CheckData/invalidArguments.txt

Triangle.exe 2 + 1  > notNumeric8.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b notNumeric8.txt CheckData/invalidArguments.txt

Triangle.exe 3 2 _  > notNumeric9.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b notNumeric9.txt CheckData/invalidArguments.txt





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