echo �� ���������� ���������� ����������
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

FC /b incorrectAmountArgument4.txt CheckData/invalidArguments.txt



echo ����� ���������� ������ ,�� ���� ����� �� �����
Triangle.exe . 2 1  > notNumeric1.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b notNumeric1.txt CheckData/invalidArguments.txt

Triangle.exe 2 . 1  > notNumeric2.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b notNumeric2.txt CheckData/invalidArguments.txt

Triangle.exe 3 2 .  > notNumeric3.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b notNumeric3.txt CheckData/invalidArguments.txt


echo � ����� �� ����� ���� ��������� �����
Triangle.exe 0..2 2 1  > notNumeric4.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b notNumeric4.txt CheckData/invalidArguments.txt

Triangle.exe 2 9.4.2 1  > notNumeric5.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b notNumeric5.txt CheckData/invalidArguments.txt

Triangle.exe 3 2 1.2..2  > notNumeric6.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b notNumeric6.txt CheckData/invalidArguments.txt



echo ���������� ����� ���� ������ �����
Triangle.exe a 2 1  > notNumeric7.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b notNumeric7.txt CheckData/invalidArguments.txt

Triangle.exe 2 + 1  > notNumeric8.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b notNumeric8.txt CheckData/invalidArguments.txt

Triangle.exe 3 2 _  > notNumeric9.txt

IF NOT ERRORLEVEL 1 GOTO err

FC /b notNumeric9.txt CheckData/invalidArguments.txt





echo ���������� �� ����� ���� ������������� �����
Triangle.exe -1 2 3 >> Degenerate1.txt
IF NOT ERRORLEVEL 1 GOTO err
FC /b Degenerate1.txt CheckData/invalidArguments.txt

echo ����������� �����������(�� �����������)
Triangle.exe 1 2 3 >> Degenerate2.txt
IF ERRORLEVEL 1 GOTO err
FC /b Degenerate2.txt CheckData/NotTrianlge.txt

echo �������������� �����������
Triangle.exe 2 2 3 >> Isosceles.txt 
IF ERRORLEVEL 1 GOTO err
FC /b Isosceles.txt CheckData/Isosceles.txt

echo �������������� �����������
Triangle.exe 2 2 2 >> Equilateral.txt 
IF ERRORLEVEL 1 GOTO err
FC /b Equilateral.txt CheckData/Equilateral.txt

echo ������� �����������
Triangle.exe 2 4 3 >> Simple.txt 
IF ERRORLEVEL 1 GOTO err
FC /b Simple.txt CheckData/Simple.txt

ECHO Program testing succeeded :-) 
PAUSE
EXIT
  
:err
ECHO Program testing failed :-( 
PAUSE
EXIT