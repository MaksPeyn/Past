   M S B A M L   `   `   `  ����@  <Model, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null,"clr-namespace:Model;assembly=ModelModel  5   	   B >Ekzamen, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null!clr-namespace:EkzamenEkzamen 5   	   7 clr-namespace:Ekzamen.ConvertersEkzamen.Converters 5   	      Ekzamen.MainWindow   5   	   W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   4model"clr-namespace:Model;assembly=Model     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   'localclr-namespace:Ekzamen     5   	   7
converters clr-namespace:Ekzamen.Converters     5   	     � Title$  Список задач��5
   	   $	��442��6   $	��580��6+    � 
ResizeMode$ CanMinimize=�5   	    � 	Resources 5      2  ,Ekzamen.Converters.BoolToVisibilityConverter   	Converter��%   &	          5   
   6/   5      .��5      �  � ColumnDefinitions 5   
   �� 5      �� 5      .+�5   
   �� $6��0Панель для редактирования��6   $��1��66   .��5      �� .+�5      �� y�6   �� *Ut+ �� 	Converter# [  .+�5      �� $��13(�6    $
��Bold"�6.   $��5 10 5 5q�6@   $#��Название задачи��6R   �� 5      $��5q�6   ��6)   �� *SelectedTask.Name+�� 5      $��13(�6    $
��Bold"�6.   $��5q�6@   $#��Описание задачи��6K   �� 5      $��5q�6   ��6)   �� *SelectedTask.Description+�� 5      $��13(�6    $
��Bold"�6.   $��5q�6@   $#��Название группы��6K   �� 5      $��5q�6   ��6)   �� *SelectedTask.Group+�� 5      $��13(�6    $
��Bold"�6.   $��5q�6@   $��Статус��6K   �� 5       $��5q�6    �� SelectedValuePath$ 	EnumValue��5!       �� DisplayMemberPath$ DisplayString��6+   ��5    *   !  Ekzamen.EnumValuesExtension  *M� *model:TaskStatus++ �� SelectedValue 5"      �� *SelectedTask.Status+�� 5#      $��13(�6    $
��Bold"�6.   $��5q�6@   $:��4Планируемая дата завершения��6K   (  "System.Windows.Controls.DatePicker  5$      $��5q�6!      SelectedDate 6,   �� *SelectedTask.DueDate+5&      �� 5'      $��13(�6   $
��Bold"�6*   $��5 10 5 5q�6<   $#��Название группы��5)      y�5(      �� *Gr+# [  5)      �� 5*      $��5q�6   y�6%   �� *Gr+# [  {�5+      �� *Auto+��5,      �� *SelectedGroup.Title+�� 5-      	 �� Orientation$	 
Horizontal=�6   y�5.      �� *IsVisibility+# [  .+�50      �� 
����� �$��8 5 5 5q�6/   $	��110��6@   
 �� 	IsDefault
 . $��Сохранить��51      ��61   �� *SavedCommand+ �� Mode$ OneTime=��� 52      
�������
���Gc��$��5 5 5 5q�6H    �� IsCancel . $	��110��53      $��Отмена��6)   ��6:   �� *ClosCommand+$ OneTime=�54      55      56      � 57   
   $��1��6   
�������y�58      �� *Null+# [  .+�59      �� $��Center=�6   $B��<Выберите элемент из дерева задач��63    �� TextAlignment$ Center=�5:      $
��Wrap=�6/   
�������$��30(�5;   /   
���  ��6=   5<      �� 5=   
   $��0��6   $	 Vertical=�6%    5>       	 Color �� Triggers �� Binding �� Value �� Property �� Value  ChildTemplate  NameTemplate �� ItemTemplate �� ItemsSource��%�  &	       &	     7  &	 �    7  �� 5?       5@      �� 5A       6&   �� *Status+ 06A   .a�5B      ��  � ��
 ��  �6=   5C      �� 5D       6&   �� *Status+ 16A   .a�5E      ��  � ��
 �2�2�6=   5F      �� 5G       6&   �� *Status+ 26A   .a�5H      ��  � ��
 �  ��6=   5I      �� 5J       6&   �� *Status+ 36A   .a�5K      ��  � ��
 � ���6=   5L      �� 5M       6&   �� *Status+ 46A   .a�5N      ��  � ��
 �����6=   5O      5Q      �� 5R      .R�5S      �� $	 
Horizontal=�6!   .+�5T      A� $��0 0 3 0q�6"   $��10��63   $��10��6?   8��  6J   �� 5U      $��Italic$�6$   ��67   �� *Name+5V      5W      �� 5X      8    5Y      �� *Tasks+.R�5[      � .+�5\      �� $��16��6    $��16��6,   $��Images/folder.jpg��67   �� 5]      $
��Bold"�6;   ��6$   �� *Title+6;   5^      5_      5`      .+�5a        Ekzamen.ExtendedTreeView  $	��300��6%   #��[ 5c   %   ��5a   2   �� *	MGroups+   SelectedItem_ 5b   %   �� *SelectedObject+$ TwoWay=�5c   %   �� 5d      $��Действия��6   .��5e      �� .+�5f      �� $��5q�6   $-��'Показать Завершённые��6*   ��6I   �� *RedactComCommand+$ OneTime=��� 5g      $��5q�6   $+��%Показать Отменённые��6*   ��6H   �� *RedactCanCommand+$ OneTime=��� 5h      $	 
Horizontal=�6!   .+�5i      �� 
���`���$��5q�69   $	��113��6D   $#��Добавить Группу��6P   ��6j   �� *CreateGroupCommand+$ OneTime=��� 5j      
���`���$��5q�69   $	��113��6D   $#��Добавить Задачу��6P   ��6j   �� *CreateTaskCommand+$ OneTime=�5k      5l      5m      5n      5o      5p      