*************************************
���������� ���� ������ ���� / �������.
*************************************

Add date event � �������� � ���� ������ ���� (date, event);
Print � ������� �� ���������� ���� ������;
Find condition � ������� ��� ������, ������������ � ���� ������, ������� ������������� ������� condition;
Del condition � ������� �� ���� ��� ������, ������� ������������� ������� condition;
Last date � ������� ������ � ��������� ��������, ����������� �� ����� ������ ����.

������� � �������� Find � Del ����������� ����������� ����������� �� ���� � �������, ��������:
Find date < 2017-11-06 � ����� ��� �������, ������� ��������� ������ 6 ������ 2017 ����;
Del event != "holiday" � ������� �� ���� ��� �������, ����� �holiday�;
Find date >= 2017-01-01 AND date < 2017-07-01 AND event == "sport event" � ����� �� ������� �sport event�, ����������� � ������ �������� 2017 ����;
Del date < 2017-01-01 AND (event == "holiday" OR event == "sport event") � ������� �� ���� ��� ������� �holiday� � �sport event�, ����������� �� 2017 ����.
� �������� ����� ����� ������� ����� ���� �������: ��� ����� ������� �������� ��� �������.

**********************
������ ����� � ������.
**********************

� ����������� ����� ���������� ������� ��� ������ � ����� ������, �� ����� ������� � ������. ��������� ��������� �� � ������� ���������� ��������� � ����������� �����.
������� ��������� ������ ��������� ����.
1) ������� Add
�������� ������� Add date event, ���� ��������� ������ �������� ���� (date, event) � ���� ������ � ����� ���������� � ��� ������ (������� Find) ��� ������ (������� Print).
���������� �������, ������������ � ���� � ��� �� ����, ��������� �� �����: ���������� � ���� ��� ������������ ���� (date, event) ������ ��������������. � ���� � �� �� ���� ����� ��������� ����� ������ �������, �� ������ ������ �� ��� ���������.
�������������, ��� ���� date � ������� Add ����� ������ ����-�����-�����, ��� ��� � ��� ����� ����� �� 0 �� 9999, ����� � ��� ����� ������ �� 1 �� 12 ������������, ���� � ��� ����� ��� �� 1 �� 31 ������������.
����� ���� ����������� ������� ������, ���������� � �� �������. ������� ���������� ���: 2017-11-07, 0-2-31.
��� ��������� ����� ������ � ������� Add ����� �������. ��� ����� ��������� �������, ������� ��� ��� ���������� ������ ��������������� �������� getline. ��� ���� �������������, ��� �������� ������� �� ����� ��������� ������ ������� (").
����� �������, ���� ������ ����� ����������� ���� � ������� � �������� Find � Del, ������� ������������� �������� �������.
��� ������� Add 2017-11-07 big sport event ��������� ������ �������� � ���� ������ ���� (2017-11-07, big sport event).

2) ������� Del
�������� ������� Del condition, ���� ��������� ������ ������� �� ���� ������ ��� �������, ��������������� ������� condition, � ������� � ����������� ����� ���������� �������� ������� N � ������� �Removed N entries�.
���� ������� �����, ����������� ���������� ������� ������ ����� ������� ���� ���� ������.

3) ������� Print
�������� ������� Print, ���� ��������� ������ ������� ��� ���� (����, �������), ������� � ������ ������ ���������� � ���� ������. ���� ���� �������� �� ����� � ������.
��� ������ ���� ������������� �� ���� �� �����������.
������� � ������ ����� ���� ���������� �������� � ������� ���������� (�� ����������� ��� �������� � ������� ���������� ��������).
���� ���� �������� � ������� ����-��-��, ��� �, �, � � ��� ����� ����� ����, ������ � ��� ��������������.
���� �����-�� ����� ����� ������ ��������, ��� �����, ��� ���� ��������� ������, ��������: 0001-01-01 � ������ ������ ������� ����.

4) ������� Find
�������� ������� Find condition, ���� ��������� ������ ������� ��� ���� (����, �������), ������� � ������ ������ ���������� � ���� ������ � ������������� ������� condition. 
������ ������ ���������� ������� Print. ����� � ������ �������� ������������ ������� Print.
� ����� ������� ������ ������� ������ Found N entries, ��� N � ���������� ��������� ���.

5) ������� Last
�� ������� Last date ����� ������� ��������� �� �������, ����������� � ���� date. ����� ���������:
	- ����� ���� ��������� ��� ������� ����� ����� ����������, �� ������������� date;
	- �� ���� ������� � ����� ����� ����� ������� ��������� ����������� � ������� � �������, ����������� ������� ������� Print;
	- ���� date ������ ���� ��������� ���, ���������� ������� �No entries�.
