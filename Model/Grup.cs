using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using Model.Annotations;

namespace Model
{
    public class Grup: INotifyPropertyChanged
    {
        private string _title;
        public string Title
        {
            get { return _title?? (_title = ""); }
            set
            {
                 _title = value;
                 OnPropertyChanged();
            }
        }

        public ObservableCollection<UserTask> Tasks { get; set; } = new ObservableCollection<UserTask>();

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
