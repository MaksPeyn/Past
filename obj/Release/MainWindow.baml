   M S B A M L   `   `   `  ���� @  <Model, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null,"clr-namespace:Model;assembly=ModelModel  B >Ekzamen, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null!clr-namespace:EkzamenEkzamen 7 clr-namespace:Ekzamen.ConvertersEkzamen.Converters    Ekzamen.MainWindow   W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     @d2http://schemas.microsoft.com/expression/blend/2008     4model"clr-namespace:Model;assembly=Model     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     'localclr-namespace:Ekzamen     7
converters clr-namespace:Ekzamen.Converters       � Title$  Список задач��$	��442��$	��580�� � 
ResizeMode$ CanMinimize=� � 	Resources 2  ,Ekzamen.Converters.BoolToVisibilityConverter   	Converter��%   &	          .���  � ColumnDefinitions �� �� .+��� $6��0Панель для редактирования��$��1��.���� .+��� y��� *Ut+ �� 	Converter# [  .+��� $��13(�$
��Bold"�$��5 10 5 5q�$#��Название задачи���� $��5q����� *SelectedTask.Name+�� $��13(�$
��Bold"�$��5q�$#��Описание задачи���� $��5q����� *SelectedTask.Description+�� $��13(�$
��Bold"�$��5q�$#��Название группы���� $��5q����� *SelectedTask.Group+�� $��13(�$
��Bold"�$��5q�$��Статус���� $��5q� �� SelectedValuePath$ 	EnumValue�� �� DisplayMemberPath$ DisplayString����!  Ekzamen.EnumValuesExtension  *M� *model:TaskStatus++ �� SelectedValue �� *SelectedTask.Status+�� $��13(�$
��Bold"�$��5q�$:��4Планируемая дата завершения��(  "System.Windows.Controls.DatePicker  $��5q�   SelectedDate �� *SelectedTask.DueDate+�� $��13(�$
��Bold"�$��5 10 5 5q�$#��Название группы��y��� *Gr+# [  �� $��5q�y��� *Gr+# [  {��� *Auto+���� *SelectedGroup.Title+�� 	 �� Orientation$	 
Horizontal=�y��� *IsVisibility+# [  .+��� 
����� �$��8 5 5 5q�$	��110��
 �� 	IsDefault
 . $��Сохранить������ *SavedCommand+ �� Mode$ OneTime=��� 
�������
���Gc��$��5 5 5 5q� �� IsCancel . $	��110��$��Отмена������ *ClosCommand+$ OneTime=�� $��1��
�������y��� *Null+# [  .+��� $��Center=�$B��<Выберите элемент из дерева задач�� �� TextAlignment$ Center=�$
��Wrap=�
�������$��30(�
���  ���� $��0��$	 Vertical=�  	 Color �� Triggers �� Binding �� Value �� Property �� Value  ChildTemplate  NameTemplate �� ItemTemplate �� ItemsSource��%:  &	       &	 +    7  &	 �    7  ��  ��  �� *Status+ 0.a���  � ��
 ��  ���  �� *Status+ 1.a���  � ��
 �2�2���  �� *Status+ 2.a���  � ��
 �  ����  �� *Status+ 3.a���  � ��
 � �����  �� *Status+ 4.a���  � ��
 ������� .R��� $	 
Horizontal=�.+�A� $��0 0 3 0q�$��10��$��10��8��  �� $��Italic$����� *Name+�� 8    �� *Tasks+.R�� .+��� $��16��$��16��$��Images/folder.jpg���� $
��Bold"����� *Title+.+�  Ekzamen.ExtendedTreeView  $	��300��#��[ ���� *	MGroups+   SelectedItem_ �� *SelectedObject+$ TwoWay=��� $��Действия��.���� .+��� $��5q�$-��'Показать Завершённые������ *RedactComCommand+$ OneTime=��� $��5q�$+��%Показать Отменённые������ *RedactCanCommand+$ OneTime=��� $	 
Horizontal=�.+��� 
���`���$��5q�$	��113��$#��Добавить Группу������ *CreateGroupCommand+$ OneTime=��� 
���`���$��5q�$	��113��$#��Добавить Задачу������ *CreateTaskCommand+$ OneTime=�