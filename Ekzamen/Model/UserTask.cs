using System;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using Model.Annotations;

namespace Model
{
    public class UserTask:INotifyPropertyChanged
    {
        public UserTask()
        {
            Status = TaskStatus.New;
            DueDate = DateTime.Now;
        }
        private string _group;
        private DateTime _dueDate;
        private TaskStatus _status;
        public string Description { get; set; }
        private string _name;

        public string Name
        {
            get { return _name ?? (_name = "Безымянная"); }
            set
            {
                if (value != "") _name = value;
                OnPropertyChanged();
            }
        }

        public string Group
        {
            get { return _group?? (_group = ""); }
            set
            {
                _group = value;
                OnPropertyChanged();
            }
        }

        public DateTime DueDate
        {
            get { return _dueDate; }
            set
            {
                _dueDate = value;
                OnPropertyChanged();
            }
        }

        public TaskStatus Status
        {
            get { return _status; }
            set
            {
                _status = value;
                OnPropertyChanged();
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}