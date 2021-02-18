namespace Ekzamen
{
    public class EnumValueDescription
    {
        public EnumValueDescription(object value, string display)
        {
            EnumValue = value;
            DisplayString = display;
        }
        public object EnumValue { get; }
        public string DisplayString { get; }
    }
}
