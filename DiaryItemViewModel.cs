using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel;

namespace MyDiary
{

    public class DiaryItemViewModel
    {
        public ObservableCollection<DiaryItem> AllItems = new ObservableCollection<DiaryItem>();
        public DiaryItemViewModel()
        {
            AllItems.Add(new DiaryItem());
            AllItems.Add(new DiaryItem());
        }
    }
}
