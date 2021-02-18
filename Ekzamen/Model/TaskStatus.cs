using System.ComponentModel.DataAnnotations;

namespace Model
{
    public enum TaskStatus
    {
        [Display(Name = "Новая")]
        New,
        [Display(Name = "Выполняется")]
        InProgress,
        [Display(Name = "Отложена")]
        Postponded,
        [Display(Name = "Завершена")]
        Completed,
        [Display(Name = "Отменена")]
        Canceled
    }
}
