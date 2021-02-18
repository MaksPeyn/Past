using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using Model;
using Model.Annotations;

namespace ViewModel
{
    /*Программа для записи задач с различными состояниями.*/
    public class MainWindowViewModel: INotifyPropertyChanged
    {
        private const string Auto1 = "Просроченные";
        private const string Auto2 = "Истекают завтра";
        private const string Auto3 = "Без группы";

        public MainWindowViewModel()
        {
            Null = true;
            Create();
        }

        public RelayCommand SavedCommand => _savedCommand?? (_savedCommand = new RelayCommand(Saved));
        public RelayCommand CreateGroupCommand => _createGroupCommand?? (_createGroupCommand = new RelayCommand(CreateGroup));
        public RelayCommand CreateTaskCommand => _createTaskCommand?? (_createTaskCommand = new RelayCommand(CreateTask));
        public RelayCommand RedactComCommand => _redactComCommand?? (_redactComCommand = new RelayCommand(RedactCom));
        public RelayCommand RedactCanCommand => _redactCanCommand?? (_redactCanCommand = new RelayCommand(RedactCan));
        public RelayCommand ClosCommand => _closCommand?? (_closCommand = new RelayCommand(Clos));

        private List<UserTask> _groups = new List<UserTask>
        {
            new UserTask
            {
                Name = "Захватить мир",
                Description = "Чем мы сегодня займёмся, Брейн?",
                Group = "Глобальные",
                DueDate = new DateTime(2016, 3, 5)
            },
            new UserTask
            {
                Name = "Сдать экзамен",
                Description = "Надежда есть",
                Group = "Дополнительный курс",
                DueDate = new DateTime(2016, 3, 5),
                Status = TaskStatus.InProgress
            },
            new UserTask
            {
                Name = "Уехать домой",
                Description = "Успеть бы на 15:30",
                Group = "Очень важно!",
                DueDate = new DateTime(2016, 3, 5),
                Status = TaskStatus.InProgress
            },
            new UserTask
            {
                Name = "Сделать иконки для дерева",
                Description = "Интересно, они заметят?",
                Group = "Дополнительный курс",
                DueDate = new DateTime(2016, 2, 29),
                Status = TaskStatus.Postponded
            },
            new UserTask
            {
                Name = "Прочитать учебник по философии",
                Description = "Что - то меня в этом беспокоит",
                Group = "Студентские",
                DueDate = new DateTime(2016, 3, 7)
            },
            new UserTask
            {
                Name = "Сделать все свои грязные дела",
                Description = "Лучше чтоб без свидетелей",
                DueDate = new DateTime(2016, 1, 1),
                Status = TaskStatus.Completed
            }
        };

        public List<Grup> MGroups { get; set; } = new List<Grup>
        {
            new Grup { Title = Auto1 },
            new Grup { Title = Auto2 },
            new Grup { Title = Auto3 }
        };

        private RelayCommand _savedCommand;
        private RelayCommand _createTaskCommand;
        private RelayCommand _createGroupCommand;
        private RelayCommand _redactComCommand;
        private RelayCommand _redactCanCommand;
        private RelayCommand _closCommand;
        private UserTask _selectedTask;
        private Grup _selectedGroup;
        private bool _isVisibility;
        private bool _gr;
        private bool _chCom;
        private bool _chCan;
        private bool _null;
        private bool _auto;

        public bool Null
        {
            get { return _null; }
            set
            {
                _null = value;
                OnPropertyChanged();
            }
        }

        public bool Auto
        {
            get { return _auto; }
            set
            {
                _auto = value;
                OnPropertyChanged();
            }
        }

        public UserTask SelectedTask
        {
            get { return _selectedTask; }
            set
            {
                Gr = false;
                if (_selectedTask != null) _selectedTask.PropertyChanged -= Modify;
                _selectedTask = value;
                _selectedTask.PropertyChanged += Modify;
                OnPropertyChanged();
            }
        }

        public Grup SelectedGroup
        {
            get { return _selectedGroup; }
            set
            {
                Gr = true;
                if (_selectedGroup != null) _selectedGroup.PropertyChanged -= Modify;
                _selectedGroup = value;
                _selectedGroup.PropertyChanged += Modify;
                Auto = IsVisibility || _selectedGroup.Title != Auto1 && _selectedGroup.Title != Auto2 && _selectedGroup.Title != Auto3;
                OnPropertyChanged();
            }
        }

        public object SelectedObject
        {
            get { return Gr ? (object) SelectedGroup : SelectedTask; }
            set
            {
                var task = value as UserTask;
                if (task == null)
                    SelectedGroup = IsVisibility ? new Grup { Title = ((Grup)value).Title } : (Grup)value;
                else
                {
                    SelectedTask = IsVisibility? new UserTask
                    {
                        Name = task.Name,
                        Description = task.Description,
                        Group = task.Group,
                        Status = task.Status,
                        DueDate = task.DueDate
                    }
                    : (UserTask)value;
                }
                Null = false;
            }
        }

        private void Create()
        {
            foreach (var ut in _groups)
            {
                var b1 = ut.Group != "" && ut.Group != Auto1 && ut.Group != Auto2 && ut.Group != Auto3;
                var b2 = (ut.Status != TaskStatus.Completed || _chCom) && (ut.Status != TaskStatus.Canceled || _chCan);
                if (b1 && b2)
                {
                    var grup = MGroups.FirstOrDefault(gr => gr.Title == ut.Group);
                    if (grup == null)
                    {
                        grup = new Grup { Title = ut.Group };
                        MGroups.Add(grup);
                    }
                    grup.Tasks.Add(ut);
                    Date(ut);
                }
                else if (b2)
                {
                    Date(ut);
                    ut.Group = "";
                    MGroups.First(gr => gr.Title == Auto3).Tasks.Add(ut);
                }
                else if (b1)
                {
                    if (MGroups.All(g => g.Title != ut.Group))
                        MGroups.Add(new Grup { Title = ut.Group });
                }
                else ut.Group = "";
            }
        }

        private void Modify(object sender, PropertyChangedEventArgs e)
        {
            if (IsVisibility) return;
            switch (e.PropertyName)
            {
                case nameof(Grup.Title):
                    if(SelectedTask != null) SelectedTask.PropertyChanged -= Modify;
                    var grup = (Grup) sender;
                    if (grup.Title == Auto1 || grup.Title == Auto2)
                    {
                        SelectedGroup.PropertyChanged -= Modify;
                        grup.Title = $"Безымянная № {MGroups.Count(gr => gr.Title.Contains("Безымянная")) + 1}";
                        SelectedGroup.PropertyChanged += Modify;
                        foreach (var t in grup.Tasks)
                        {
                            t.Group = grup.Title;
                        }
                    }
                    else if (grup.Title == "" || grup.Title == Auto3)
                    {
                        var auto = MGroups.First(g => g.Title == Auto3);
                        foreach (var ut in grup.Tasks)
                        {
                            ut.Group = "";
                            auto.Tasks.Add(ut);
                        }
                        SelectedGroup = auto;
                        MGroups.Remove(grup);
                    }
                    else
                    {
                        foreach (var t in grup.Tasks)
                        {
                            t.Group = grup.Title;
                        }
                        var grp = MGroups.FirstOrDefault(g => g.Title == grup.Title && !grup.Equals(g));
                        if (grp != null)
                        {
                            foreach (var ut in grp.Tasks)
                            {
                                grup.Tasks.Add(ut);
                            }
                            MGroups.Remove(grp);
                        }
                    }
                    if (SelectedTask != null) SelectedTask.PropertyChanged += Modify;
                    break;
                case nameof(UserTask.DueDate):
                    var task = (UserTask) sender;
                    MGroups.FirstOrDefault(
                        g => (g.Title == Auto1 || g.Title == Auto2) && g.Tasks.Contains(task))
                        ?.Tasks.Remove(task);
                    Date(task);
                    break;
                case nameof(UserTask.Status):
                    var tsk = (UserTask) sender;
                    if (tsk.Status == TaskStatus.Completed &&
                        !_chCom || tsk.Status == TaskStatus.Canceled && !_chCan)
                    {
                        if (tsk.Group == "") MGroups.First(gr => gr.Title == Auto3).Tasks.Remove(tsk);
                        else MGroups.First(gr => gr.Title == tsk.Group).Tasks.Remove(tsk);
                        var year = tsk.DueDate.Year - DateTime.Today.Year;
                        if (year == 0)
                        {
                            var days = tsk.DueDate.DayOfYear - DateTime.Today.DayOfYear;
                            if (days < 0) MGroups.First(gr => gr.Title == Auto1).Tasks.Remove(tsk);
                            else if (days < 2) MGroups.First(gr => gr.Title == Auto2).Tasks.Remove(tsk);
                        }
                        else if (year < 0) MGroups.First(gr => gr.Title == Auto1).Tasks.Remove(tsk);
                    }
                    else if (MGroups.All(g => !g.Tasks.Contains(tsk)))
                    {
                        if (tsk.Group == "") MGroups.First(gr => gr.Title == Auto3).Tasks.Add(tsk);
                        else MGroups.First(gr => gr.Title == tsk.Group).Tasks.Add(tsk); 
                        Date(tsk);
                    }
                    break;
                case nameof(UserTask.Group):
                    var ts = (UserTask) sender;
                    MGroups.FirstOrDefault(
                        g => g.Tasks.Contains(ts) && g.Title != Auto1 && g.Title != Auto2)
                        ?.Tasks.Remove(ts);
                    if (ts.Group != "" && ts.Group != Auto1
                        && ts.Group != Auto2 && ts.Group != Auto3)
                    {
                        var grp = MGroups.FirstOrDefault(gr => gr.Title == ts.Group);
                        if (grp == null)
                        {
                            grp = new Grup { Title = ts.Group };
                            MGroups.Add(grp);
                        }
                        grp.Tasks.Add(ts);
                    }
                    else
                    {
                        SelectedTask.PropertyChanged -= Modify;
                        ts.Group = "";
                        SelectedTask.PropertyChanged += Modify;
                        MGroups.First(gr => gr.Title == Auto3).Tasks.Add((UserTask)sender);
                    }
                    break;
            }
        }

        public bool IsVisibility
        {
            get { return _isVisibility; }
            set
            {
                _isVisibility = value;
                OnPropertyChanged();
            }
        }

        public bool Gr
        {
            get { return _gr; }
            set
            {
                _gr = value;
                OnPropertyChanged();
                OnPropertyChanged(nameof(Ut));
            }
        }

        public bool Ut => !_gr;

        private void Saved(object o)
        {
            IsVisibility = false;
            if (Gr)
            {
                if (SelectedGroup.Title != "" && SelectedGroup.Title != Auto1 && SelectedGroup.Title != Auto2
                    && SelectedGroup.Title != Auto3 && MGroups.All(gr => gr.Title != SelectedGroup.Title))
                {
                    MGroups.Add(SelectedGroup);
                }
                else Null = true;
            }
            else
            {
                var b1 = SelectedTask.Group != "" && SelectedTask.Group != Auto1 
                    && SelectedTask.Group != Auto2 && SelectedTask.Group != Auto3;
                var b2 = (SelectedTask.Status != TaskStatus.Completed || _chCom)
                    && (SelectedTask.Status != TaskStatus.Canceled || _chCan);
                if (b1 && b2)
                {
                    var grup = MGroups.FirstOrDefault(gr => gr.Title == SelectedTask.Group);
                    if (grup == null)
                    {
                        grup = new Grup {Title = SelectedTask.Group};
                        MGroups.Add(grup);
                    }
                    grup.Tasks.Add(SelectedTask);
                    Date(SelectedTask);
                }
                else if (b2)
                {
                    Date(SelectedTask);
                    SelectedTask.PropertyChanged -= Modify;
                    SelectedTask.Group = "";
                    SelectedTask.PropertyChanged += Modify;
                    MGroups.First(gr => gr.Title == Auto3).Tasks.Add(SelectedTask);
                }
                else if (b1)
                {
                    if (MGroups.All(g => g.Title != SelectedTask.Group))
                        MGroups.Add(new Grup {Title = SelectedTask.Group});
                }
                else
                {
                    SelectedTask.PropertyChanged -= Modify;
                    SelectedTask.Group = "";
                    SelectedTask.PropertyChanged += Modify;
                }
                _groups.Add(SelectedTask);
            }
        }

        private void CreateGroup(object o)
        {
            SelectedGroup = new Grup();
            IsVisibility = true;
            Null = false;
        }

        private void CreateTask(object o)
        {
            SelectedTask = new UserTask();
            IsVisibility = true;
            Null = false;
        }

        private void Clos(object o)
        {
            Null = true;
            IsVisibility = false;
        }

        private void Redact (TaskStatus s)
        {
            if (s == TaskStatus.Completed ? _chCom : _chCan)
            {
                foreach (var t in _groups.Where(t => t.Status == s))
                {
                    if (t.Group == "") MGroups.First(gr => gr.Title == Auto3).Tasks.Add(t);
                    else MGroups.First(g => g.Title == t.Group).Tasks.Add(t);
                    Date(t);
                }
            }
            else foreach (var gr in MGroups)
            {
                foreach (var t in gr.Tasks.Where(t => t.Status == s).ToArray())
                {
                    gr.Tasks.Remove(t);
                }
            }
        }

        private void Date(UserTask ut)
        {
            var year = ut.DueDate.Year - DateTime.Today.Year;
            if (year == 0)
            {
                var days = ut.DueDate.DayOfYear - DateTime.Today.DayOfYear;
                if (days < 0) MGroups.First(gr => gr.Title == Auto1).Tasks.Add(ut);
                else if (days < 2) MGroups.First(gr => gr.Title == Auto2).Tasks.Add(ut);
            }
            else if (year < 0) MGroups.First(gr => gr.Title == Auto1).Tasks.Add(ut);
        }

        private void RedactCom(object o)
        {
            _chCom = !_chCom;
            Redact(TaskStatus.Completed);
        }

        private void RedactCan(object o)
        {
            _chCan = !_chCan;
            Redact(TaskStatus.Canceled);
        }

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
