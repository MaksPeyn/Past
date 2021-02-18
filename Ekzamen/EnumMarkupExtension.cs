using System;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Reflection;
using System.Windows.Markup;

namespace Ekzamen
{
    public class EnumValuesExtension : MarkupExtension
    {
        private readonly Type _type;

        public EnumValuesExtension(Type type)
        {
            _type = type;
        }

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return _type.GetFields(BindingFlags.Public | BindingFlags.Static)
                .Select(member => new EnumValueDescription(member.GetValue(null),
                    member.GetCustomAttributes(typeof(Attribute), true)
                    .Cast<DisplayAttribute>()
                    .Select(d => d.Name)
                    .FirstOrDefault()))
                .ToList();
        }
    }
}
